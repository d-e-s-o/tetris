// Moveable.hpp

/***************************************************************************
 *   Copyright (C) 2014 Daniel Mueller (deso@posteo.net)                   *
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

#ifndef CTRTESTMOVEABLE_HPP
#define CTRTESTMOVEABLE_HPP


namespace test
{
  /**
   * A class representing moveable but not copyable objects. When moved, the source object (from
   * which the move is performed) will reset its value to zero.
   */
  struct Moveable
  {
    Moveable(int value);
    Moveable(Moveable&& other);
    Moveable(Moveable const& other) = delete;

    Moveable& operator =(Moveable&& other);
    Moveable& operator =(Moveable const& other) = delete;

    int value_;
  };
}


#endif
