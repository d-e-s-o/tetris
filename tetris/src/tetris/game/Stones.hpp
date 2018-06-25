// Stones.hpp

/***************************************************************************
 *   Copyright (C) 2006-2012 Daniel Mueller (deso@posteo.net)              *
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

#ifndef TTRSSTONES_HPP
#define TTRSSTONES_HPP

#include "tetris/game/Coordinate.hpp"
#include "tetris/game/Dimension.hpp"
#include "tetris/game/Stone.hpp"
#include "tetris/game/StoneFactory.hpp"


namespace ttrs
{
  /**
   * This class holds a variable number of preview stones.
   * @todo change the way positions are handled: origin is lower left corner not upper left
   */
  class Stones
  {
  public:
    typedef typename StoneFactory::StoneList StoneList;

    Stones(StoneFactory const& factory, coordinate_t x, coordinate_t y, int stones);

    void render() const;

    Stone pop();

    StoneList const& list() const;

    dimension_t width() const;
    dimension_t height() const;

  private:
    static coordinate_t const SPACE;

    coordinate_t x_;
    coordinate_t y_;

    StoneList stones_;

    StoneFactory const* factory_;

    Stones(Stones const&) = delete;
    Stones& operator =(Stones const&) = delete;

    void addNewStones(int count);
    void addNewStone(int top);
  };
}


#endif
