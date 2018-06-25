// Scanner.hpp

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

#ifndef OPTSCANNERSCANNER_HPP
#define OPTSCANNERSCANNER_HPP

#include <tokenize/SymbolStream.hpp>
#include <tokenize/TokenStream.hpp>

#include "options/TokenType.hpp"


namespace tok
{
  struct Result;
}

namespace opt
{
  namespace scanner
  {
    /**
     * This class acts as the non template base class for SymbolToken. Objects of this type are not
     * meant to be created directly.
     * @see SymbolToken
     */
    struct Token
    {
      Token(TokenType type, char_t const* begin, char_t const* end);

      TokenType     type;
      char_t const* begin;
      char_t const* end;
    };


    /**
     * This class is used for tokens. It inherits from Token but does not add any additional members
     * to it. This is useful here because the actual token access always happens through Token
     * instances, because all objects are copied directly and not pointer/references to them and so
     * slicing would be an issue.
     * The constructor implements the interface as required for any token scannable by libtokenize.
     */
    template<TokenType Symbol>
    struct SymbolToken: Token
    {
      SymbolToken(char_t const* begin, char_t const* end);
    };


    typedef tok::SymbolStream<char_t, char_t const*>       Symbols;
    typedef tok::TokenStream<Token, TokenCreator<char_t> > Tokens;


    tok::Result scan(char_t const* begin, char_t const* end, Tokens& tokens);
  }
}


namespace opt
{
  namespace scanner
  {
    /**
     * @param begin
     * @param end
     */
    template<TokenType Symbol>
    SymbolToken<Symbol>::SymbolToken(char_t const* begin, char_t const* end)
      : Token(Symbol, begin, end)
    {
    }
  }
}


#endif
