// StoneDropper.hpp

/***************************************************************************
 *   Copyright (C) 2013 Daniel Mueller (deso@posteo.net)                   *
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

#ifndef TTRSAISTONEDROPPER_HPP
#define TTRSAISTONEDROPPER_HPP

#include <container/Array.hpp>

#include "tetris/game/ai/State.hpp"
#include "tetris/game/ai/Action.hpp"


namespace ttrs
{
  namespace ai
  {
    class Field;
    class Stone;


    /**
     *
     */
    typedef ctr::Array<Stone> StoneList;


    /**
     *
     */
    class StoneDropper
    {
    public:
      StoneDropper() = default;

      // use default copy and move constructor and copy and move assignment operator

      ActionList search(Field const& field, StoneList const& stones);

    private:
      /**
       * A number of states, for instance, created by expanding a parent state.
       */
      typedef ctr::Array<StatePointer> States;

      States expand(StatePointer const& state) const;
      ActionList constructActionList(StatePointer const& state) const;

      bool isValidState(StatePointer const& state) const;
      bool isStoneDropped(StatePointer const& state) const;
      bool isStoneDone(StatePointer const& state) const;
      bool areStonesLeft(StatePointer const& state, StoneList const& stones) const;
    };
  }
}


#endif
