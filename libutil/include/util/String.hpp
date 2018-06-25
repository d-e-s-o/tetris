// String.hpp

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

#ifndef UTLSTRING_HPP
#define UTLSTRING_HPP

#include "util/Config.hpp"
#include "util/Util.hpp"
#include "util/Assert.hpp"
#include "util/Algorithm.hpp"


namespace utl
{
  template<typename CharT>
  size_t length(CharT const* string);

  template<typename CharT>
  int compare(CharT const* string1, CharT const* string2);

  template<typename CharT>
  CharT* copy(CharT const* src, CharT* dst, size_t count);
}


namespace utl
{
  /**
   * @param string zero terminated C-style character array
   * @return length of the given string (excluding zero termination byte)
   */
  template<typename CharT>
  size_t length(CharT const* string)
  {
    ASSERTOP(string, ne, nullptr);

    size_t length = 0;

    while (*string != '\0')
    {
      ++string;
      ++length;
    }
    return length;
  }

  /**
   * @param string1 first string
   * @param string2 second string
   * @return a value less than 0 if 'string1' is less than 'string2', a value greater than 0 if
   *         'string1' is greater than 'string2', or 0 if they are equal
   */
  template<typename CharT>
  int compare(CharT const* string1, CharT const* string2)
  {
    ASSERTOP(string1, ne, nullptr);
    ASSERTOP(string2, ne, nullptr);

    auto lhs_it = string1;
    auto rhs_it = string2;

    for ( ; *lhs_it != '\0' && *rhs_it != '\0'; ++lhs_it, ++rhs_it)
    {
      if (*lhs_it < *rhs_it)
        return -1;

      if (*lhs_it > *rhs_it)
        return 1;
    }

    // if we did not bail out until here we know one or both strings reached their termination
    // character, so only check which one did not
    if (*lhs_it != '\0')
      return 1;

    // the second string is longer so the first one is "less" than the second
    if (*rhs_it != '\0')
      return -1;

    // both are equal
    return 0;
  }

  /**
   * @param src source string
   * @param dst destination buffer
   * @param count number of elements in destination buffer
   * @return pointer right after the last element copied to the destination buffer
   * @note this function behaves differently than strncpy in two ways:
   *       - it always creates a zero terminated string
   *       - it does not fill remaining (untouched) elements (up to 'count') with zero
   * @todo if required, add a faster function that only requires one pass over the source string
   *       (and not two as with our separate length() invocation)
   */
  template<typename CharT>
  CharT* copy(CharT const* src, CharT* dst, size_t count)
  {
    // add one element to account for zero terminating byte
    auto len = length(src) + 1;
    // we must not copy more than the destination buffer can hold
    auto max = min(count, len);
    auto end = copy(src, src + max, dst);

    // ensure zero termination in any case: in the normal case we did copy the zero terminating byte
    // from the source buffer; however, if the source buffer exceeds the destination buffer's
    // capacity, we have to make sure to zero out the last valid byte of the destination buffer
    if (len > count)
    {
      // size_t is unsigned -- take care not to cause an overflow
      if (count > 0)
        dst[count - 1] = '\0';
      else
        dst[0] = '\0';
    }
    return end;
  }
}


#endif
