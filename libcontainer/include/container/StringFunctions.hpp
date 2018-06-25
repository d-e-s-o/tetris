// StringFunctions.hpp

/***************************************************************************
 *   Copyright (C) 2012 Daniel Mueller (deso@posteo.net)                   *
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

#ifndef CTRSTRINGFUNCTIONS_HPP
#define CTRSTRINGFUNCTIONS_HPP

/**
 * @note all functions declared in ArrayFunctions can equally well be used for all types of Strings
 *       and in fact we would like to provide them here as well -- so include the header
 */
#include "container/ArrayFunctions.hpp"
#include "container/String.hpp"


namespace ctr
{
  template<typename StringT>
  StringT subString(StringT const& string, size_t index, size_t count);

  template<typename StringT>
  StringT subString(StringT const& string, size_t index);

  template<typename StringT>
  size_t findSubString(StringT const& string, StringT const& substring, size_t index = 0);
}


namespace ctr
{
  /**
   * @param string
   * @param index
   * @param count
   * @return
   */
  template<typename StringT>
  StringT subString(StringT const& string, size_t index, size_t count)
  {
    return StringT(string.begin() + index, string.begin() + index + count);
  }

  /**
   * @param string
   * @param index
   * @return
   */
  template<typename StringT>
  StringT subString(StringT const& string, size_t index)
  {
    return subString(string, index, string.size() - index);
  }

  /**
   * @param string string to search in
   * @param substring substring to find
   * @param index index where to start the search
   * @return
   */
  template<typename StringT>
  size_t findSubString(StringT const& string, StringT const& substring, size_t index)
  {
    if (string.size() >= substring.size())
    {
      size_t size     = string.size() - (substring.size() > 0 ? substring.size() - 1 : 0);
      size_t sub_size = substring.size();

      for ( ; index < size; ++index)
      {
        size_t new_index = index;
        size_t sub_index = 0;

        for ( ; sub_index < sub_size; ++sub_index, ++new_index)
        {
          if (string[new_index] != substring[sub_index])
            break;
        }

        // if we got through the whole substring successfully, we found a match and are done
        if (sub_index == sub_size)
          return index;
      }
    }
    return string.size();
  }
}


#endif
