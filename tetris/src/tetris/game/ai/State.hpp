// State.hpp

/***************************************************************************
 *   Copyright (C) 2013-2014,2019 Daniel Mueller (deso@posteo.net)         *
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

#ifndef TTRSAISTATE_HPP
#define TTRSAISTATE_HPP

#include <pointer/SharedPointer.hpp>

#include "tetris/game/ai/Stone.hpp"
#include "tetris/game/ai/Field.hpp"
#include "tetris/game/ai/ClosedStones.hpp"
#include "tetris/game/ai/Action.hpp"


namespace ttrs
{
  namespace ai
  {
    struct State;


    /**
     * Our states are all dynamically allocated. Each contains a pointer to the previous state
     * (and only to that one, so there can be no cycles) and a reference counted pointer suites this
     * usecase perfectly.
     */
    typedef ptr::SharedPointer<State> StatePointer;


    /**
     * This class keeps track of various stone and field related variables that need to be
     * remembered when performing a search for the best possible outcome.
     * @note to better understand the purpose of the various associated variables a distinction
     *       between a "stone" and a "stone instance" is made; a "stone" refers to a set of pieces,
     *       grouped moved, and rotated in uniformly; when a "stone" in that sense is moved or
     *       rotated it still stays the same "stone"; a "stone instance" on the other hand is a
     *       stone in a rotational state and at a certain position, if it is rotated or moved a new
     *       "stone instance" is born
     */
    class State
    {
    public:
      static bool compare(State const& lhs, State const& rhs);

      static StatePointer initial(Field const& field, Stone const& stone);
      static StatePointer derive(StatePointer const& state, Action const& action);
      static StatePointer merge(StatePointer const& state, Stone const& next);

      static void mergeAndUpdateBest(StatePointer const& state);

      void markClosed();
      void markDropped();

      StatePointer const& parent() const;
      StatePointer const& best() const;

      Action const& action() const;
      Action const& lastMove() const;
      Stone  const& stone() const;

      size_t index() const;

      bool isClosed() const;
      bool isValid() const;
      bool isDone() const;

    private:
      /**
       * The field is shared between stone instances, so we need a pointer to the field that can get
       * passed around.
       */
      typedef ptr::SharedPointer<Field> FieldPointer;

      /**
       * The state of which state is closed, i.e., was already expanded and investigated, is shared
       * accross stone instances. So we need a pointer here as well.
       */
      typedef ptr::SharedPointer<ClosedStones> ClosedStonesPointer;

      /**
       * The best state is a pointer to a state (shared across all States for the same stone) along
       * with its utility.
       */
      typedef ctr::Pair<StatePointer, uint_t> BestState;
      typedef ptr::SharedPointer<BestState>   BestStatePointer;

      /**
       * The parent state, i.e., the one this state was created from by applying the given action.
       * @note the parent state is a per stone instance attribute
       */
      StatePointer parent_;

      /**
       * The best state encountered for the associated stone along with its utility.
       * @note the best state is a per stone attribute
       */
      BestStatePointer best_;

      /**
       * The stone we are talking about.
       * @note the stone is a per stone instance attribute
       */
      Stone stone_;

      /**
       * @note the field is a per stone attribute
       */
      FieldPointer field_;

      /**
       * @note the set of closed stones is a per stone attribute
       */
      ClosedStonesPointer closed_;

      /**
       * The action that led to this stone, i.e., the last action performed.
       * @note the action is a per stone instance attribute
       */
      Action action_;

      /**
       * This variable stores the last move action performed, i.e., whenever we perform one of
       * {MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT} this variable gets updated. This is solely used for
       * keeping the number of expanded states low by not expanding duplicated states at all.
       * @note the last move action is a per stone instance attribute
       */
      Action last_move_;

      /**
       * The index of the stone in the StoneList we are working on, i.e., derived the current stone
       * from.
       * @note the index is a per stone attribute
       */
      size_t index_;

      /**
       * The cost to get to this state, i.e., the costs of the actions performed so far. The lower
       * this value the better.
       * @note the cost is a per stone instance attribute
       */
      uint_t cost_;

      /**
       * The utility of this state or more precisely the utility of all previous but this state (but
       * this kind of depends on how one defines this term). It is basically the sum of all previous
       * utilities and it will only get updated when we create a new state via merge.
       * @note the utility is a per stone instance attribute
       * @see State::merge
       */
      uint_t utility_;


      static Field mergeAndUpdate(StatePointer& state, uint_t& utility);

      State(FieldPointer const& field, Stone const& stone);
      State(StatePointer const& parent, Stone const& stone, Action action);
      State(StatePointer const& parent, FieldPointer const& field, Stone const& stone, uint_t utility);

      State(State const&) = default;
      State(State&&) = delete;

      State& operator =(State const&) = default;
      State& operator =(State&&) = delete;

      void updateBest(StatePointer const& best, uint_t utility);
      uint_t estimateUtility(size_t lines_cleared) const;
    };
  }
}


namespace ttrs
{
  namespace ai
  {
    /**
     * @return pointer to parent state
     */
    inline StatePointer const& State::parent() const
    {
      return parent_;
    }

    /**
     * @return pointer to best state encountered so far
     */
    inline StatePointer const& State::best() const
    {
      return best_->first;
    }

    /**
     * @return action that was performed on the parent state that yielded this state
     */
    inline Action const& State::action() const
    {
      return action_;
    }

    /**
     * @return last move action performed
     * @see StoneDropper::expand
     */
    inline Action const& State::lastMove() const
    {
      return last_move_;
    }

    /**
     * @return stone associated with this state
     */
    inline Stone const& State::stone() const
    {
      return stone_;
    }

    /**
     * @return index used for keeping track which stone to evaluate next
     * @todo this somehow does not fit in here -- find a better/more generic way to preserve this
     *       information
     */
    inline size_t State::index() const
    {
      return index_;
    }

    /**
     * @return true if this state is closed, i.e., the corresponding stone was expanded previously
     */
    inline bool State::isClosed() const
    {
      return closed_->contains(stone_);
    }

    /**
     * @return true if this state is valid, i.e., the corresponding stone does not collide with the
     *         field
     */
    inline bool State::isValid() const
    {
      return !stone_.collidesWith(*field_);
    }

    /**
     * @return true if each x position has been visited in all rotation states, false otherwise
     * @see State::markDropped
     */
    inline bool State::isDone() const
    {
      return closed_->done();
    }

    /**
     * This function can be used to compare State objects with regard to their cost and utility.
     * This is useful for the A* algorithm we employ where we always want to work with the lowest
     * rated state next.
     * @param lhs first state to compare to second
     * @param rhs second state to compare to first
     * @return true if the first state is less (i.e., better) than the second, false otherwise
     */
    inline bool State::compare(State const& lhs, State const& rhs)
    {
      // version 1:
      // makes testDropMultiple2 fail
      //uint_t cost1 = lhs.cost_ + lhs.utility_;
      //uint_t cost2 = rhs.cost_ + rhs.utility_;

      //return cost1 <  cost2 ||
      //       cost1 == cost2 && lhs.utility_ > rhs.utility_;

      // version 2:
      //return lhs.cost_ <  rhs.cost_ ||
      //       lhs.cost_ == rhs.cost_ && lhs.utility_ > rhs.utility_;

      // version 3:
      return (lhs.index_ <  rhs.index_) ||
             (lhs.index_ == rhs.index_ && lhs.cost_ <  rhs.cost_) ||
             (lhs.index_ == rhs.index_ && lhs.cost_ == rhs.cost_ && lhs.utility_ > rhs.utility_);
    }
  }
}


#endif
