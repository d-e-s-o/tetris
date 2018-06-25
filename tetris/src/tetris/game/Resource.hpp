// Resource.hpp

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

#ifndef TTRSRESOURCE_HPP
#define TTRSRESOURCE_HPP

#include "tetris/String.hpp"


namespace ttrs
{
  /**
   * @todo all these things should be taken out of the settings object
   */

  namespace
  {
    String TETRIS_PIECE_TEXTURE      = String(TEXT("mem://tetris_piece_32x32.png"));
    String TETRIS_FIELD_WALL_TEXTURE = String(TEXT("mem://tetris_wall_32x32.png"));
    String TETRIS_FIELD_BACK_TEXTURE = String(TEXT("mem://tetris_field_256x512.png"));
  }
}


#endif
