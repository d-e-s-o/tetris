// TestMoveIterator.cpp

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

#include "Moveable.hpp"


namespace test
{
  /**
   * @param value some value this object will have
   */
  Moveable::Moveable(int value)
    : value_(value)
  {
  }

  /**
   * @param other other object to move from
   */
  Moveable::Moveable(Moveable&& other)
    : value_(other.value_)
  {
    other.value_ = 0;
  }

  /**
   * @param other other object to move from
   * @return this moveable object
   */
  Moveable& Moveable::operator =(Moveable&& other)
  {
    if (this != &other)
    {
      value_ = other.value_;
      other.value_ = 0;
    }
    return *this;
  }
}
