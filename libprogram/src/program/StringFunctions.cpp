// StringFunctions.cpp

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


#include <util/Algorithm.hpp>
#include <container/String.hpp>
#include <container/StringFunctions.hpp>

#include "StringFunctions.hpp"


namespace pgm
{
  namespace
  {
    ctr::String const LOWER_LETTERS = ctr::String("abcdefghijklmnopqrstuvwxyz");
    ctr::String const UPPER_LETTERS = ctr::String("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    ctr::String const LETTERS       = LOWER_LETTERS + UPPER_LETTERS;
    ctr::String const WHITESPACES   = ctr::String(" \t");
  }


  /**
   *
   */
  bool IsLetter(char c)
  {
    // as far as I know the c++ standard does NOT define the numeric values of
    // chars like 'A' == 65 or their order ('a' does not have to be < 'b')
    // return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
    return utl::find(LETTERS.begin(), LETTERS.end(), c) != LETTERS.end();
  }

  /**
   *
   */
  bool IsWhitespace(char c)
  {
    return utl::find(WHITESPACES.begin(), WHITESPACES.end(), c) != WHITESPACES.end();
  }

  /**
   *
   */
  bool IsUppercase(char c)
  {
    return utl::find(UPPER_LETTERS.begin(), UPPER_LETTERS.end(), c) != UPPER_LETTERS.end();
  }

  /**
   *
   */
  ctr::String TrimLeft(ctr::String str)
  {
    while (str.size() > 0 && IsWhitespace(str[0]))
      ctr::remove(str, 0, 1);

    return str;
  }

  /**
   *
   */
  ctr::String TrimRight(ctr::String str)
  {
    size_t len = 0;

    while ((len = str.size()) > 0 && IsWhitespace(str[len - 1]))
      ctr::remove(str, str.size() - 1, 1);

    return str;
  }

  /**
   *
   */
  Strings Text2Strings(ctr::String const& text, char_t separator)
  {
    Strings list;
    ctr::String::ConstIterator begin = text.begin();
    ctr::String::ConstIterator it    = text.begin();
    ctr::String::ConstIterator end   = text.end();

    while (it != end)
    {
      ctr::String::ConstIterator found = utl::find(it, end, separator);

      if (found != end)
        ctr::append(list, ctr::subString(text, it - begin, found - it));
      else
      {
        ctr::append(list, ctr::subString(text, it - begin));
        return list;
      }

      it = found + 1;
    }
    return list;
  }
}
