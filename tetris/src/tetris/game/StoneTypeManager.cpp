// StoneTypeManager.cpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#include "tetris/game/StoneTypeManager.hpp"


namespace ttrs
{
  namespace
  {
    /**
     * Pre-defined array with coordinates of Piece objects
     */
    coordinate_t const StonesWith4Pieces[][4][2] =
    {
      { {0, 0}, {1, 0}, {1, 1}, {0, 1} }, // O
      { {0, 0}, {1, 0}, {1, 1}, {2, 1} }, // S
      { {0, 1}, {1, 1}, {1, 0}, {2, 0} }, // Z
      { {0, 0}, {0, 1}, {0, 2}, {0, 3} }, // I
      { {0, 0}, {1, 0}, {1, 1}, {2, 0} }, // T
      { {0, 0}, {1, 0}, {0, 1}, {0, 2} }, // J
      { {0, 0}, {1, 0}, {1, 1}, {1, 2} }  // L
    };
  }


  /**
   * The constructor creates a new StoneTypeManager with it all available StoneType objects.
   */
  StoneTypeManager::StoneTypeManager(bool register_default_stones)
    : stone_types_()
  {
    if (register_default_stones)
      registerTemplates(StonesWith4Pieces);
  }

  /**
   * @param index index specifing the stone type to retrieve [0, count())
   * @return stone type at the given position
   */
  StoneTypeManager::StoneType const& StoneTypeManager::type(size_t index) const
  {
    ASSERTOP(index, ge, 0);
    ASSERTOP(index, lt, stone_types_.size());
    return stone_types_[index];
  }

  /**
   * @return number of StoneType objects available
   */
  size_t StoneTypeManager::count() const
  {
    return stone_types_.size();
  }
}
