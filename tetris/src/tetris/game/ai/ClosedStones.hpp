// ClosedStones.hpp

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

#ifndef TTRSAICLOSEDSTONES_HPP
#define TTRSAICLOSEDSTONES_HPP

#include <container/Pair.hpp>

#include "tetris/game/AbstractField.hpp"
#include "tetris/game/ai/Orientation.hpp"


namespace ttrs
{
  namespace ai
  {
    class Stone;


    typedef ctr::Pair<bool, Orientation> ClosedStone;


    /**
     * This class represents the set of closed (i.e., already examined) states. For the
     * implementation we rely on the functionality of AbstractField, but do not expose the
     * interface. The basic principle is that when considering one and the same stone it can only
     * be on one position at a time but in four different rotated states (not rotated and rotated
     * one, two, or three times to the left). We incorporate that knowledge by using the
     * Orientation enum which is basically a bitfield with one bit set for each rotated state.
     * That is also what we store here. This way we can check if a state was already present in
     * constant time by looking up if its current Orientation value does already exist in the
     * field.
     * One important fact is that a state might be represented by a stone that is actually not
     * inside the corresponding field (see below for an explanation). We cope with that case by
     * creating a slack space of half the actual field width/height around the field. That means
     * that in effect this field will be larger than it would have to be without this requirement.
     */
    class ClosedStones: private AbstractField<ClosedStone>
    {
    public:
      ClosedStones(dimension_t width, dimension_t height);

      void addClosed(Stone const& stone);
      void addDropped(Stone const& stone);

      bool contains(Stone const& stone) const;
      bool done() const;

    private:
      typedef ctr::Array<ClosedStone> DroppedStones;

      coordinate_t offset_x_;
      coordinate_t offset_y_;

      DroppedStones dropped_;

      ClosedStone&       entry(Stone const& stone);
      ClosedStone const& entry(Stone const& stone) const;

      void update(ClosedStone& entry, Stone const& stone) const;
    };
  }
}


#endif
