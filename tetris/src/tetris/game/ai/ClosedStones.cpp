// ClosedStones.cpp

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

#include "tetris/game/ai/Stone.hpp"
#include "tetris/game/ai/ClosedStones.hpp"


namespace ttrs
{
  namespace ai
  {
    /**
     * @param width
     * @param height
     */
    ClosedStones::ClosedStones(dimension_t width, dimension_t height)
      : AbstractField<ClosedStone>(2 * width, 2 * height),
        offset_x_(width / 2),
        offset_y_(height / 2),
        dropped_(width)
    {
      dropped_.grow(width, ctr::makePair(false, Orientation::MIN));
    }

    /**
     * @param stone stone to add to the set of closed stones
     */
    void ClosedStones::addClosed(Stone const& stone)
    {
      ASSERT(!contains(stone));

      update(entry(stone), stone);
    }

    /**
     * @param stone
     */
    void ClosedStones::addDropped(Stone const& stone)
    {
      ASSERTOP(stone.x(), ge, 0);
      ASSERTOP(stone.x(), lt, dropped_.size());
      ASSERT(contains(stone));

      update(dropped_[stone.x()], stone);
    }

    /**
     * @param stone
     * @return true if the given stone does already exist in the set of closed stones, false if
     *         it does not
     */
    bool ClosedStones::contains(Stone const& stone) const
    {
      ClosedStone const& entry = this->entry(stone);

      if (!entry.first)
        return false;

      return ai::contains(entry.second, stone.orientation());
    }

    /**
     * @return
     */
    bool ClosedStones::done() const
    {
      for (auto it = dropped_.begin(), end = dropped_.end(); it != end; it++)
      {
        if (!it->first || !full(it->second))
          return false;
      }
      return true;
    }

    /**
     * @param stone
     * @return
     */
    inline ClosedStone& ClosedStones::entry(Stone const& stone)
    {
      coordinate_t x = stone.x() + offset_x_;
      coordinate_t y = stone.y() + offset_y_;

      ASSERTOP(x, ge, 0);
      ASSERTOP(x, lt, width());
      ASSERTOP(y, ge, 0);
      ASSERTOP(y, lt, height());

      return (*this)[x][y];
    }

    /**
     * @param stone
     * @return
     */
    inline ClosedStone const& ClosedStones::entry(Stone const& stone) const
    {
      return const_cast<ClosedStones*>(this)->entry(stone);
    }

    /**
     * @param entry
     * @param stone
     */
    inline void ClosedStones::update(ClosedStone& entry, Stone const& stone) const
    {
      // @todo reenable me!
      //ASSERT(!entry.first || combine(entry.second, stone.orientation()), ne, entry.second);

      if (!entry.first)
      {
        entry.first  = true;
        entry.second = stone.orientation();
      }
      else
        entry.second = combine(entry.second, stone.orientation());
    }
  }
}
