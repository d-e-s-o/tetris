// Parser.hpp

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

#ifndef OPTPARSERPARSER_HPP
#define OPTPARSERPARSER_HPP

#include <tokenize/TokenStream.hpp>

#include "options/TokenType.hpp"
#include "options/Scanner.hpp"


namespace tok
{
  struct Result;
}

namespace opt
{
  namespace scanner
  {
    struct Token;
  }


  namespace parser
  {
    struct Option
    {
      Option(bool is_long, char_t const* name_begin, char_t const* name_end,
                           char_t const* arg_begin,  char_t const* arg_end);

      bool is_long;

      char_t const* name_begin;
      char_t const* name_end;

      char_t const* arg_begin;
      char_t const* arg_end;
    };


    /**
     *
     */
    struct SymbolStream: tok::SymbolStream<TokenType, scanner::Token const*>
    {
      SymbolStream(scanner::Token const* begin, scanner::Token const* end);

      // use compiler generated copy constructor and assignment operator

      TokenType const& dereference() const;
    };


    typedef SymbolStream                                            Symbols;
    typedef tok::TokenStream<Option, TokenCreator<scanner::Token> > Tokens;


    tok::Result parse(scanner::Token const* begin, scanner::Token const* end, Tokens& tokens);
  }
}


#endif
