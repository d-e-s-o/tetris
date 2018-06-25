// Action.hpp

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

#ifndef TTRSAIACTION_HPP
#define TTRSAIACTION_HPP

#include <util/Assert.hpp>
#include <container/Array.hpp>


namespace ttrs
{
  namespace ai
  {
    /**
     *
     */
    enum class Action
    {
      MIN,
      NONE,
      MERGE,
      MOVE_DOWN,
      MOVE_LEFT,
      MOVE_RIGHT,
      ROTATE_LEFT,
      ROTATE_RIGHT,
      MAX
    };


    /**
     * A sequence of actions that yield a desired outcome. In our case a list of actions that lead
     * to a stone in an end position.
     */
    typedef ctr::Array<Action> ActionList;


    template<typename StoneT>
    StoneT perform(Action action, StoneT const& stone);

    template<typename StoneT>
    StoneT performOnCopy(Action action, StoneT const& stone);

    bool isMove(Action action);
  }
}


namespace ttrs
{
  namespace ai
  {
    /**
     * @param action
     * @param stone
     */
    template<typename StoneT>
    void perform(Action action, StoneT& stone)
    {
      ASSERT(Action::MIN < action && action < Action::MAX);

      switch (action)
      {
      case Action::MOVE_DOWN:    stone.moveDown();    break;
      case Action::MOVE_LEFT:    stone.moveLeft();    break;
      case Action::MOVE_RIGHT:   stone.moveRight();   break;
      case Action::ROTATE_LEFT:  stone.rotateLeft();  break;
      case Action::ROTATE_RIGHT: stone.rotateRight(); break;
      default:                   ASSERT(false);       break;
      }
    }

    /**
     * @param action
     * @param stone
     * @return
     */
    template<typename StoneT>
    StoneT performOnCopy(Action action, StoneT const& stone)
    {
      ASSERT(Action::MIN < action && action < Action::MAX);

      StoneT copy = stone;
      perform(action, copy);
      return copy;
    }

    /**
     * @param action some action
     * @return true if the given action represents a move, false otherwise
     */
    inline bool isMove(Action action)
    {
      return action == Action::MOVE_DOWN ||
             action == Action::MOVE_LEFT ||
             action == Action::MOVE_RIGHT;
    }
  }
}


#endif
