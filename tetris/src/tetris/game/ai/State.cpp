// State.cpp

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

#include <util/Util.hpp>
#include <util/Assert.hpp>

#include "tetris/game/FieldFunctions.hpp"
#include "tetris/game/ai/State.hpp"


namespace ttrs
{
  namespace ai
  {
    namespace
    {
      static uint_t INITIAL_COST    = 0;
      static uint_t INITIAL_UTILITY = 0;


      /**
       * @param stone
       * @return
       */
      uint_t actionCost(Action action)
      {
        ASSERT(Action::MIN < action && action < Action::MAX);

        switch (action)
        {
        case Action::MOVE_DOWN:    return 1;
        case Action::MOVE_LEFT:    return 2;
        case Action::MOVE_RIGHT:   return 2;
        case Action::ROTATE_LEFT:  return 1;
        case Action::ROTATE_RIGHT: return 1;
        default: break;
        }
        ASSERT(false);
        return -1;
      }
    }


    /**
     * @param field
     * @param stone
     * @return
     */
    StatePointer State::initial(Field const& field, Stone const& stone)
    {
      return StatePointer(new State(FieldPointer(new Field(field)), stone));
    }

    /**
     * @param state
     * @param action
     * @return
     */
    StatePointer State::derive(StatePointer const& state, Action const& action)
    {
      Stone copy = performOnCopy(action, state->stone_);
      return StatePointer(new State(state, copy, action));
    }

    /**
     * @param state
     * @return
     * @todo I hate this pass-out-parameter-via-reference style -- fix this!
     */
    Field State::mergeAndUpdate(StatePointer& state, uint_t& utility)
    {
      ASSERT(state->isValid());

      Field field = *state->field_;
      Stone stone =  state->stone_;
      stone.mergeWith(field);

      utility = state->estimateUtility(clearLines(field, stone));

      if (state->utility_ + utility > state->best_->second)
        state->updateBest(state, state->utility_ + utility);

      return field;
    }

    /**
     * @param state
     */
    void State::mergeAndUpdateBest(StatePointer const& state)
    {
      // create a copy of the given pointer and work in it; we are only interested in updating the
      // the "best" state attribute but mergeAndUpdate() will also touch the utility
      StatePointer copy = state;
      uint_t utility;
      mergeAndUpdate(copy, utility);
    }

    /**
     * @param state
     * @param next
     * @return
     */
    StatePointer State::merge(StatePointer const& state, Stone const& next)
    {
      uint_t utility;
      StatePointer copy  = state;
      FieldPointer field = FieldPointer(new Field(mergeAndUpdate(copy, utility)));
      return StatePointer(new State(copy, field, next, utility));
    }

    /**
     * Constructor for creating an initial state.
     * @param field
     * @param stone
     * @see State::initial
     */
    State::State(FieldPointer const& field, Stone const& stone)
      : parent_(nullptr),
        best_(nullptr),
        field_(field),
        closed_(new ClosedStones(field->width(), field->height())),
        stone_(stone),
        action_(Action::NONE),
        last_move_(Action::NONE),
        index_(0),
        cost_(INITIAL_COST),
        utility_(INITIAL_UTILITY)
    {
      // now that our state is fully constructed lets make it the best
      // note that we create a copy of the current state -- see State::updateBest for an explanation
      best_ = BestStatePointer(new BestState(StatePointer(new State(*this)), INITIAL_UTILITY));
    }

    /**
     * Constructor for deriving a new state from an existing one.
     * @param parent
     * @param stone
     * @param action
     * @see State::derive
     */
    State::State(StatePointer const& parent, Stone const& stone, Action action)
      : parent_(parent),
        best_(parent->best_),
        field_(parent->field_),
        closed_(parent->closed_),
        stone_(stone),
        action_(action),
        last_move_(isMove(action) ? action : parent->action_),
        index_(parent->index_),
        cost_(parent->cost_ + actionCost(action)),
        utility_(parent->utility_)
    {
    }

    /**
     * Constructor for merging a state, i.e., merging its associated stone into the associated field
     * and creating a new state using this very field and a newly supplied stone.
     * @param parent
     * @param field
     * @param stone
     * @see State::merge
     */
    State::State(StatePointer const& parent, FieldPointer const& field, Stone const& stone, uint_t utility)
      : parent_(parent),
        best_(parent->best_),
        field_(field),
        closed_(new ClosedStones(field->width(), field->height())),
        stone_(stone),
        action_(Action::MERGE),
        last_move_(Action::NONE),
        index_(parent->index_ + 1),
        cost_(parent->cost_),
        utility_(parent->utility_ + utility)
    {
      ASSERTOP(utility_, ge, parent->utility_);
      ASSERTOP(utility_, le, parent->best_->second);
      // we are starting over with a new stone; that means that we are not interested in any previous
      // best state but start all over
      //best_ = BestStatePointer(new BestState(StatePointer(new State(*this)), INITIAL_UTILITY));
    }

    /**
     * @param best
     * @param utility
     */
    void State::updateBest(StatePointer const& best, uint_t utility)
    {
      ASSERTOP(best, ne, nullptr);
      ASSERT(best->isValid());

      // note that it is important that we create a copy of the state and not simply store the
      // pointer for two reasons:
      // - storing the pointer would not work when we just store a StatePointer object directly (see
      //   declaration of best_), we would need another level of indirection to make the pointer
      //   shared across states
      // - when using a reference counted pointer we do not want to create loops but this can
      //   actually happen if we would only copy the StatePointer
      *best_->first  = *best;
       best_->second = utility;
    }

    /**
     * Mark the given state as closed, i.e., remember that we have expanded the corresponding stone.
     */
    void State::markClosed()
    {
      ASSERT(!isClosed());
      closed_->addClosed(stone_);
    }

    /**
     * Mark the given state as dropped, i.e., remember the orientation for this stone at this x
     * position.
     */
    void State::markDropped()
    {
      closed_->addDropped(stone_);
    }

    /**
     * @param state
     * @param lines_cleared
     * @return some utility value calculated for the given state, the higher the better
     * @todo try out if it makes sense to further value the stone's position within the field,
     *       e.g., give higher utility to stones on one of the sides, less to ones in the middle
     * @todo we need to avoid strange placement of L stones: at the moment they are often placed in
     *       a way such that there is a whole below it, but this whole is not acknowledged as such
     *       (I believe) because it is not surrounded by pieces but open on one side
     */
    uint_t State::estimateUtility(size_t lines_cleared) const
    {
      Field const& field = *field_;

      // there are two things that make up a states's utility:
      // - the y position of the corresponding stone (the further down the better)
      // - the number of lines cleared when merging the stone with the field
      // note that the cost does not play any role at all; it influences the search and decides
      // over whether a state is visited in the first place but it does not play into the utility
      uint_t utility = 0;
      utility += field.height() - stone_.y();
      utility += 2 * lines_cleared * lines_cleared;

      // ===========================================================================================
      //coordinate_t x_min = stone_.x();
      //coordinate_t x_max = min(stone_.x() + stone_.width(), field.width());
      //coordinate_t y_min = 0;
      //coordinate_t y_max = stone_.y();

      //uint_t holes = 0;

      //for (coordinate_t x = x_min + 1; x < x_max; x++)
      //{
      //  for (coordinate_t y = y_max - 1; y > y_min; y--)
      //  {
      //    if (!field[x][y])
      //      holes++;
      //  }
      //}

      //utility -= holes;

      // ===========================================================================================
      //utility += field.width() + utl::abs(field.width() / 2 - stone_.x());

      // ===========================================================================================
      //uint_t holes = 0;

      //for (coordinate_t x = 1; x < field.width() - 1; x++)
      //{
      //  for (coordinate_t y = 1; y < field.height(); y++)
      //  {
      //    if (!field[x][y-1] && field[x-1][y] && field[x+1][y] && field[x][y])
      //      holes += 1;
      //  }
      //}

      //utility -= holes;

      // ===========================================================================================
      uint_t holes = 0;
      uint_t pieces = 0;

      for (coordinate_t x = 0; x < field.width(); x++)
      {
        bool found = false;

        for (coordinate_t y = field.height() - 1; y >= 0; y--)
        {
          if (field[x][y])
            pieces++;

          if (!found)
          {
            if (field[x][y])
              found = true;
          }
          else
          {
            if (!field[x][y])
              holes++;
            //else
            //  break;
          }
        }
      }

      //holes = pieces / (holes > 0 ? holes : 1);
      //holes /= (pieces >= 32) ? pieces / 32 : 1;
      utility += field.width() * field.height() - holes;

      // ===========================================================================================
      //coordinate_t min_y = field.height();
      //coordinate_t max_y = 0;

      //for (coordinate_t x = 0; x < field.width() - 1; x++)
      //{
      //  for (coordinate_t y = field.height() - 1; y >= 0; y--)
      //  {
      //    if (field[x][y])
      //    {
      //      if (y < min_y)
      //        min_y = y;

      //      if (y > max_y)
      //        max_y = y;

      //      break;
      //    }
      //  }
      //}

      //utility -= max_y - min_y;

      // ===========================================================================================
      uint_t roughness = 0;
      coordinate_t y_top = 0;

      for (coordinate_t x = 0; x < field.width() - 1; x++)
      {
        for (coordinate_t y = field.height() - 1; y >= 0; y--)
        {
          if (field[x][y])
          {
            if (x > 0)
              roughness += utl::abs(y_top - y);

            y_top = y;
            break;
          }
        }
      }

      roughness /= field.height() > 8 ? field.height() / 8 : 1;
      utility += field.width() * field.height() - roughness;

      return utility;
    }
  }
}
