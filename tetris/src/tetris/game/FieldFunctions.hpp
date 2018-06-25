// FieldFunctions.hpp

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

#ifndef TTRSFIELDFUNCTIONS_HPP
#define TTRSFIELDFUNCTIONS_HPP

#include <util/Assert.hpp>

#include "tetris/game/Coordinate.hpp"
#include "tetris/game/Dimension.hpp"


namespace ttrs
{
  template<typename FieldT, typename StoneT>
  bool linesComplete(FieldT const& field, StoneT const& stone);

  template<typename FieldT, typename StoneT>
  size_t clearLines(FieldT& field, StoneT const& stone);
}


namespace ttrs
{
  /**
   * @param field
   * @param stone
   * @return
   */
  template<typename FieldT, typename StoneT>
  bool linesComplete(FieldT const& field, StoneT const& stone)
  {
    coordinate_t min = stone.y();
    coordinate_t max = stone.y() + stone.height() - 1;

    ASSERTOP(min, ge, 0);
    ASSERTOP(min, le, max);
    ASSERTOP(max, ge, 0);
    ASSERTOP(max, le, field.height());

    for (coordinate_t line = min; line <= max; line++)
    {
      if (field.lineComplete(line))
        return true;
    }
    return false;
  }

  /**
   * @param field
   * @param stone the stone that was dropped and which may have lead to "full" lines
   * @return number of removed lines
   */
  template<typename FieldT, typename StoneT>
  size_t clearLines(FieldT& field, StoneT const& stone)
  {
    coordinate_t min = stone.y();
    coordinate_t max = stone.y() + stone.height() - 1;

    ASSERTOP(min, ge, 0);
    ASSERTOP(min, le, max);
    ASSERTOP(max, ge, 0);
    ASSERTOP(max, le, field.height());

    size_t cleared = 0;

    // go from highest line to lowest
    for (coordinate_t line = max; line >= min; line--)
    {
      if (field.lineComplete(line))
      {
        field.clearLine(line);
        ++cleared;
      }
    }
    return cleared;
  }
}


#endif
