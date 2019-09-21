// Scanner.cpp

/***************************************************************************
 *   Copyright (C) 2012,2019 Daniel Mueller (deso@posteo.net)              *
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

#include <tokenize/Token.hpp>
#include <tokenize/Terminal.hpp>
#include <tokenize/TerminalRange.hpp>
#include <tokenize/TerminalCustom.hpp>
#include <tokenize/Sequence.hpp>
#include <tokenize/Repetition.hpp>
#include <tokenize/Alternative.hpp>

#include "options/Scanner.hpp"


namespace opt
{
  namespace scanner
  {
    /**
     * @param type
     * @param begin
     * @param end
     */
    Token::Token(TokenType type, char_t const* begin, char_t const* end)
      : type(type),
        begin(begin),
        end(end)
    {
    }

    /**
     * @return result describing the success of the scan
     * @see tok::Result
     */
    tok::Result scan(char_t const* begin, char_t const* end, Tokens& tokens)
    {
      typedef tok::BoolTerminalCreator<char_t>            BTC;
      typedef tok::BoolTerminalTrue<char_t>               True;
      typedef tok::TerminalCreator<Symbols, Tokens>       T;
      typedef tok::TerminalRangeCreator<Symbols, Tokens>  TR;
      typedef tok::TerminalCustomCreator<Symbols, Tokens> TC;

      auto inf0 = tok::RepeatCount<0, static_cast<unsigned int>(-1)>();
      auto inf1 = tok::RepeatCount<1, static_cast<unsigned int>(-1)>();

      auto bool_space = BTC::T<TEXT(' ')>();
      auto bool_quote = BTC::T<TEXT('"')>();
      auto bool_dash  = BTC::T<TEXT('-')>();

      // terminal symbols
      auto term_letter    = TR::T<TEXT('a'), TEXT('z')>() | TR::T<TEXT('A'), TEXT('Z')>();
      auto term_digit     = TR::T<TEXT('0'), TEXT('9')>();
      auto term_no_dsq    = TC::T(!bool_dash && !bool_space && !bool_quote);
      auto term_noquote   = TC::T(!bool_quote);
      auto term_quote     = T::T<TEXT('"')>();
      auto term_space     = T::T<TEXT(' ')>();
      auto term_equal     = T::T<TEXT('=')>();
      auto term_dash      = T::T<TEXT('-')>();
      auto term_ddash     = term_dash + term_dash;
      auto term_opt_chr   = term_letter | term_digit;
      auto term_opt_str   = term_opt_chr + (term_opt_chr | term_dash + term_opt_chr) * inf1;
      auto term_arg_str   = term_no_dsq * inf1;
      auto term_arg_str_q = term_noquote * inf0;
      auto term_separator = term_space + term_ddash + term_space;
      auto term_any       = TC::T(True());

      // tokens
      auto dash      = tok::makeToken<SymbolToken<TOKEN_TYPE_DASH> >(term_dash);
      auto ddash     = tok::makeToken<SymbolToken<TOKEN_TYPE_DOUBLE_DASH> >(term_ddash);
      auto equal     = tok::makeToken<SymbolToken<TOKEN_TYPE_EQUAL> >(term_equal);
      auto opt_str   = tok::makeToken<SymbolToken<TOKEN_TYPE_OPTION_STRING> >(term_opt_str);
      auto opt_chr   = tok::makeToken<SymbolToken<TOKEN_TYPE_OPTION_CHARACTER> >(term_opt_chr);
      auto arg_str   = tok::makeToken<SymbolToken<TOKEN_TYPE_ARGUMENT_STRING> >(term_arg_str);
      auto arg_str_q = tok::makeToken<SymbolToken<TOKEN_TYPE_ARGUMENT_STRING> >(term_arg_str_q);
      auto separator = tok::makeToken<SymbolToken<TOKEN_TYPE_SEPARATOR> >(term_separator);
      auto anything  = tok::makeToken<SymbolToken<TOKEN_TYPE_ANYTHING> >(term_any);

      // note that an option string always is an argument string as well, however the opposite is
      // not necessarily true; we take care of this fact by trying to scan option strings first;
      // however, the parser for the scanned tokens needs to consider this as well, i.e., if it
      // wants an argument string it might also "just" get an option string
      auto scanner = (ddash | dash | equal | separator | term_space | opt_str | opt_chr |
                      term_quote + arg_str_q + term_quote | arg_str | anything) * inf0;

      return scanner.scan(Symbols(begin, end), tokens);
    }
  }
}
