// TokenType.hpp

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

#ifndef OPTTOKENTYPE_HPP
#define OPTTOKENTYPE_HPP


namespace opt
{
  enum TokenType
  {
    TOKEN_TYPE_MIN,
    TOKEN_TYPE_DASH,
    TOKEN_TYPE_DOUBLE_DASH,
    TOKEN_TYPE_SEPARATOR,
    TOKEN_TYPE_EQUAL,
    TOKEN_TYPE_OPTION_CHARACTER,
    TOKEN_TYPE_OPTION_STRING,
    TOKEN_TYPE_ARGUMENT_STRING,
    TOKEN_TYPE_ANYTHING,
    TOKEN_TYPE_MAX
  };


  template<typename SymbolT>
  struct TokenCreator
  {
    template<typename TokenT>
    static TokenT create(SymbolT const* begin, SymbolT const* end)
    {
      return TokenT(begin, end);
    }
  };
}


#endif
