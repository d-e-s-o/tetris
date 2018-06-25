// Move.hpp

/***************************************************************************
 *   Copyright (C) 2013-2014 Daniel Mueller                                *
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

#ifndef TYPTMOVE_HPP
#define TYPTMOVE_HPP


namespace typ
{
  template<typename T>
  constexpr T&& move(T& value);

  template<typename T>
  constexpr T&& forward(T& value);

  template<typename T>
  constexpr T&& forward(T&& value);
}


namespace typ
{
  /**
   * @param value reference to some value
   * @return value converted to rvalue
   */
  template<typename T>
  constexpr T&& move(T& value)
  {
    return static_cast<T&&>(value);
  }

  template<typename T>
  constexpr T&& forward(T& value)
  {
    return static_cast<T&&>(value);
  }

  /**
   * @param value const reference to some value
   * @return rvalue reference to given value
   */
  template<typename T>
  constexpr T&& forward(T&& value)
  {
    return static_cast<T&&>(value);
  }
}


#endif
