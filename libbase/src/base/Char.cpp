// Char.cpp

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

#include <iostream>

#include "base/Error.hpp"
#include "base/Char.hpp"


namespace base
{
  /**
   * @copydoc ConvertChar
   */
  template<>
  CharA convertChar(CharU c)
  {
    std::locale const& locale = std::cout.getloc();

    CharA ch = std::use_facet< std::ctype<CharU> >(locale).narrow(c, '\0');

    if (ch == '\0')
      throw error(TXT("Error converting CharU to CharA"), TXT("std::ctype::narrow failed"));

    return ch;
  }

  /**
   * @copydoc ConvertChar
   */
  template<>
  CharU convertChar(CharA c)
  {
    std::locale const& locale = std::cout.getloc();

    return std::use_facet< std::ctype<CharA> >(locale).widen(c);
  }
}
