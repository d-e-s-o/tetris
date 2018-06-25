// StoneDropper.cpp

/***************************************************************************
 *   Copyright (C) 2013-2014 Daniel Mueller (deso@posteo.net)              *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

#include <util/Assert.hpp>
#include <container/BinaryHeap.hpp>
#include <container/ArrayFunctions.hpp>

#include "tetris/game/ai/Stone.hpp"
#include "tetris/game/ai/Field.hpp"
#include "tetris/game/ai/ClosedStones.hpp"
#include "tetris/game/ai/StoneDropper.hpp"


namespace ttrs
{
  namespace ai
  {
    namespace
    {
      /**
       *
       */
      struct StateLess
      {
        bool operator()(StatePointer const& lhs, StatePointer const& rhs) const
        {
          ASSERTOP(lhs.pointer(), ne, nullptr);
          ASSERTOP(rhs.pointer(), ne, nullptr);

          return State::compare(*lhs, *rhs);
        }
      };


      typedef ctr::BinaryHeap<StatePointer, StateLess> OpenStates;
    }


    /**
     * @param field
     * @param stone
     * @return list of actions to be performed to achieve the best outcome
     */
    ActionList StoneDropper::search(Field const& field, StoneList const& stones)
    {
      ASSERTOP(stones.size(), gt, 0);

      auto state = State::initial(field, stones[0]);

      OpenStates open;
      open.insert(state);

      do
      {
        state = open.remove();

        // note that although we do not insert closed states into the list of open states directly,
        // ones in there might become closed between insertion and removal if expansion of another
        // state yielded the same stone -- skip those ones here
        if (state->isClosed())
          continue;

        state->markClosed();

        // if a state is invalid the corresponding stone somehow collides with the field or a stone
        // on it or lies outside the field; this can happen when performing an action on the stone
        // (rotating or moving it); we use this knowledge for detecting dropped stones: if a state
        // is invalid we check whether the last action performed on the corresponding stone was a
        // move down action, if this is the case we know that the parent state is the last valid
        // state, i.e., the parent state's stone is a dropped stone in our sense
        if (!state->isValid())
        {
          if (isStoneDropped(state))
          {
            StatePointer parent = state->parent();
            // @todo at the moment this functionality is not used at all -- incorporate it somehow!
            //parent->markDropped();

            if (areStonesLeft(state, stones))
              open.insert(State::merge(parent, stones[state->index() + 1]));
            else
              State::mergeAndUpdateBest(parent);
          }
          continue;
        }

        for (auto expanded : expand(state))
        {
          if (expanded->isClosed())
            continue;

          // note that one important fact here is that the expand() function itself does not check
          // whether an expanded state is valid, i.e., whether the corresponding stone is actually
          // within the bounds of the field; this means we might insert an "invalid" stone here, but
          // this is by design because this is essentially how we check for a reached goal
          open.insert(expanded);
        }
      } while (open.size() > 0);

      /**
       * @todo check if this is safe -- I bet there are lots of corner cases where this bites us in
       *       the ass
       */
      return constructActionList(state->best());
    }

    /**
     * @param state
     * @return list of new states
     */
    StoneDropper::States StoneDropper::expand(StatePointer const& state) const
    {
      ASSERT(state->isValid());

      States stones;
      ctr::append(stones, State::derive(state, Action::MOVE_DOWN));

      // the basic principle here is as follows: based on the last move action performed we decide
      // what further move actions are valid; if our last move action was a move down all bets are
      // off; if the last move was move to the right there is no use in moving left at all;
      // similarly for a left move
      if (state->lastMove() != Action::MOVE_RIGHT)
        ctr::append(stones, State::derive(state, Action::MOVE_LEFT));

      if (state->lastMove() != Action::MOVE_LEFT)
        ctr::append(stones, State::derive(state, Action::MOVE_RIGHT));

      Orientation orientation = state->stone().orientation();

      // if we are rotated to 180° there is no need to rotate in any direction at all
      if (orientation != Orientation::ROTATED_180)
      {
        // if we are rotated by 90° we got rotated to the right once in which case we do not want to
        // rotate left -- in the remaining cases (0° and 270°) we do
        if (orientation != Orientation::ROTATED_90)
          ctr::append(stones, State::derive(state, Action::ROTATE_LEFT));

        // if we are rotated by 270° we got rotated to the left once in which case we do not want to
        // rotate right -- in the remaining cases (0° and 90°) we do
        if (orientation != Orientation::ROTATED_270)
          ctr::append(stones, State::derive(state, Action::ROTATE_RIGHT));
      }
      return stones;
    }

    /**
     * @param state some state
     * @return list of actions performed to reach that state
     */
    ActionList StoneDropper::constructActionList(StatePointer const& state) const
    {
      ASSERTOP(state, ne, nullptr);

      ActionList actions;
      StatePointer next = state;

      if (next->parent() != nullptr)
        ctr::append(actions, Action::MERGE);

      do
      {
        if (next->action() != Action::NONE)
          ctr::insert(actions, 0, next->action());

        next = next->parent();
      }
      while (next != nullptr);

      ASSERT(next == nullptr || next->action() == Action::NONE && next->parent() == nullptr);
      return actions;
    }

    /**
     * @param state
     * @return
     */
    bool StoneDropper::isStoneDropped(StatePointer const& state) const
    {
      ASSERTOP(state, ne, nullptr);
      return state->action() == Action::MOVE_DOWN;
    }

    /**
     * @param state
     * @return
     */
    bool StoneDropper::isStoneDone(StatePointer const& state) const
    {
      ASSERTOP(state, ne, nullptr);
      ASSERT(state->action() == Action::MOVE_DOWN);

      // we _only_ have to consider stones that were moved down in their last step because we want
      // to make sure that this particular move down action yielded a stone that collides with the
      // field and as such the parent stone cannot be moved down any further
      return state->isDone();
    }

    /**
     * @param state
     * @param stones
     * @return
     */
    bool StoneDropper::areStonesLeft(StatePointer const& state, StoneList const& stones) const
    {
      ASSERTOP(state, ne, nullptr);
      ASSERT(state->action() == Action::MOVE_DOWN);

      return state->index() + 1 < stones.size();
    }
  }
}
