// Util.hpp

/***************************************************************************
 *   Copyright (C) 2013,2014 Daniel Mueller                                *
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

#ifndef TYPTUTIL_HPP
#define TYPTUTIL_HPP

#include "type/Types.hpp"
#include "type/Limits.hpp"


namespace typ
{
  template<typename T>
  constexpr size_t typeBits();

  template<typename T>
  constexpr size_t typeBits(T);

  template<typename T, size_t N>
  constexpr size_t arraySize(T (&)[N]);
}


namespace typ
{
  /**
   * @return number of bits required by objects of type T
   */
  template<typename T>
  constexpr size_t typeBits()
  {
    return BITS_PER_BYTE * sizeof(T);
  }

  /**
   * @param dummy some value of type T
   * @return number of bits required by objects of type T
   */
  template<typename T>
  constexpr size_t typeBits(T dummy)
  {
    return typeBits<T>();
  }

  /**
   * @param dummy some array of type T
   * @return number of elements in the given array
   */
  template<typename T, size_t N>
  constexpr size_t arraySize(T (&dummy)[N])
  {
    return N;
  }
}


#endif
