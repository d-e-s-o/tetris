// Util.hpp

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

#ifndef UTLUTIL_HPP
#define UTLUTIL_HPP

#include "util/Config.hpp"


namespace utl
{
  template<typename T>
  constexpr T min(T first, T second);

  template<typename T>
  constexpr T max(T first, T second);

  template<typename T>
  constexpr T abs(T first, T second);

  template<typename T>
  constexpr T align2(T value, size_t alignment);

  template<typename T>
  constexpr T* align2(T* value, size_t alignment);

  template<typename T>
  constexpr T roundUp(T value, size_t multiple_of);

  template<typename T>
  constexpr T* roundUp(T* value, size_t multiple_of);

  template<typename T>
  constexpr T roundDown(T value, size_t multiple_of);

  template<typename T>
  constexpr T* roundDown(T* value, size_t multiple_of);

  template<typename T>
  void swap(T& first, T& second);
}


namespace utl
{
  /**
   * @param value1 first value
   * @param value2 second value
   * @return minimum of the two given values
   */
  template<typename T>
  constexpr T min(T first, T second)
  {
    return first <= second ? first : second;
  }

  /**
   * @param value1 first value
   * @param value2 second value
   * @return maximum of the two given values
   */
  template<typename T>
  constexpr T max(T first, T second)
  {
    return first >= second ? first : second;
  }

  /**
   * @param value some value
   * @return absolute value of given value
   */
  template<typename T>
  constexpr T abs(T value)
  {
    return value >= 0 ? value : -value;
  }

  /**
   * @param value value to round up
   * @param multiple_of round up to the next multiple of this value
   * @return 'value' rounded up to the next multiple of 'multiple_of'
   * @todo needs unit test!
   */
  template<typename T>
  constexpr T roundUp(T value, size_t multiple_of)
  {
    return value + ((multiple_of - (value % multiple_of)) % multiple_of);
  }

  /**
   * @param value value to round up
   * @param multiple_of round up to the next multiple of this value
   * @return 'value' rounded up to the next multiple of 'multiple_of'
   */
  template<typename T>
  constexpr T* roundUp(T* value, size_t multiple_of)
  {
    return reinterpret_cast<T*>(roundUp(reinterpret_cast<byte_t const*>(value) -
                                        reinterpret_cast<byte_t const*>(0), multiple_of));
  }

  /**
   * @param value value to round down
   * @param multiple_of round down to the next multiple of this value
   * @return 'value' rounded down to the next multiple of 'multiple_of'
   * @todo needs unit test!
   */
  template<typename T>
  constexpr T roundDown(T value, size_t multiple_of)
  {
    return value - (value % multiple_of);
  }

  /**
   * @param value value to round down
   * @param multiple_of round down to the next multiple of this value
   * @return 'value' rounded down to the next multiple of 'multiple_of'
   */
  template<typename T>
  constexpr T* roundDown(T* value, size_t multiple_of)
  {
    return reinterpret_cast<T*>(roundDown(reinterpret_cast<byte_t const*>(value) -
                                          reinterpret_cast<byte_t const*>(0), multiple_of));
  }

  /**
   * This function swaps the contents of 'first' with that of 'second'.
   * @param first first variable to swap with second
   * @param second second variable to swap with first
   */
  template<typename T>
  void swap(T& first, T& second)
  {
    T temp = first;
    first  = second;
    second = temp;
  }
}


#endif
