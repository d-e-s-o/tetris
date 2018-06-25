// StoneFactory1.cpp

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

#include "test/StoneFactory1.hpp"


namespace test
{
  namespace
  {
    ttrs::coordinate_t const stone_with_1_piece[][1][2] =
    {
      { {0, 0} }
    };

    ttrs::coordinate_t const stones_with_2_pieces[][2][2] =
    {
      { {0, 0}, {1, 0} },
      { {0, 0}, {1, 1} }
    };

    ttrs::coordinate_t const stones_with_4_pieces[][4][2] =
    {
      { {0, 0}, {1, 0}, {1, 1}, {0, 1} },
      { {0, 0}, {0, 1}, {0, 2}, {0, 3} },
      { {0, 0}, {1, 0}, {1, 1}, {2, 0} }
    };
  }


  /**
   * @param type_manager
   */
  StoneTypeManager::StoneTypeManager()
    : ttrs::StoneTypeManager()
  {
    registerTemplates(stone_with_1_piece);
    registerTemplates(stones_with_2_pieces);
    registerTemplates(stones_with_4_pieces);
  }
}
