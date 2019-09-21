// Parser.cpp

/***************************************************************************
 *   Copyright (C) 2012,2014,2019 Daniel Mueller (deso@posteo.net)         *
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

#include <util/Assert.hpp>
#include <tokenize/Token.hpp>
#include <tokenize/Terminal.hpp>
#include <tokenize/TerminalCustom.hpp>
#include <tokenize/Sequence.hpp>
#include <tokenize/Repetition.hpp>
#include <tokenize/Alternative.hpp>

#include "options/Parser.hpp"


namespace opt
{
  namespace parser
  {
    namespace
    {
      struct LongOpt: Option
      {
        LongOpt(scanner::Token const* begin, scanner::Token const* end)
          : Option(parse(begin, end))
        {
        }

        Option parse(scanner::Token const* begin, scanner::Token const* end)
        {
          ASSERTOP(begin + 2, eq, end);

          scanner::Token const* opt = begin + 1;
          return Option(true, opt->begin, opt->end, 0, 0);
        }
      };

      struct LongOptA: Option
      {
        LongOptA(scanner::Token const* begin, scanner::Token const* end)
          : Option(parse(begin, end))
        {
        }

        Option parse(scanner::Token const* begin, scanner::Token const* end)
        {
          ASSERTOP(begin + 4, eq, end);

          scanner::Token const* opt = begin + 1;
          scanner::Token const* arg = begin + 3;

          return Option(true, opt->begin, opt->end, arg->begin, arg->end);
        }
      };

      struct ShortOpt: Option
      {
        ShortOpt(scanner::Token const* begin, scanner::Token const* end)
          : Option(parse(begin, end))
        {
        }

        Option parse(scanner::Token const* begin, scanner::Token const* end)
        {
          ASSERTOP(begin + 2, eq, end);

          scanner::Token const* opt = begin + 1;
          return Option(false, opt->begin, opt->end, 0, 0);
        }
      };

      struct ShortOptA: Option
      {
        ShortOptA(scanner::Token const* begin, scanner::Token const* end)
          : Option(parse(begin, end))
        {
        }

        Option parse(scanner::Token const* begin, scanner::Token const* end)
        {
          ASSERTOP(begin + 3, eq, end);

          scanner::Token const* opt = begin + 1;
          scanner::Token const* arg = begin + 2;

          return Option(false, opt->begin, opt->end, arg->begin, arg->end);
        }
      };
    }


    /**
     * @param is_long
     * @param name_begin
     * @param name_end
     * @param arg_begin
     * @param arg_end
     */
    Option::Option(bool is_long, char_t const* name_begin, char_t const* name_end,
                                 char_t const* arg_begin,  char_t const* arg_end)
      : is_long(is_long),
        name_begin(name_begin),
        name_end(name_end),
        arg_begin(arg_begin),
        arg_end(arg_end)
    {
    }

    /**
     * @param begin
     * @param end
     */
    SymbolStream::SymbolStream(scanner::Token const* begin, scanner::Token const* end)
      : tok::SymbolStream<TokenType, scanner::Token const*>(begin, end)
    {
    }

    /**
     * @copydoc tok::SymbolStream::dereference
     */
    TokenType const& SymbolStream::dereference() const
    {
      return current()->type;
    }

    tok::Result parse(scanner::Token const* begin, scanner::Token const* end, Tokens& tokens)
    {
      typedef tok::BoolTerminalTrue<TokenType>            True;
      typedef tok::TerminalCreator<Symbols, Tokens>       T;
      typedef tok::TerminalCustomCreator<Symbols, Tokens> TC;

      auto inf0 = tok::RepeatCount<0, static_cast<unsigned int>(-1)>();
      auto once = tok::RepeatCount<0, 1>();

      // terminal symbols
      auto dash      = T::T<TOKEN_TYPE_DASH>();
      auto ddash     = T::T<TOKEN_TYPE_DOUBLE_DASH>();
      auto equal     = T::T<TOKEN_TYPE_EQUAL>();
      auto opt_chr   = T::T<TOKEN_TYPE_OPTION_CHARACTER>();
      auto opt_str   = T::T<TOKEN_TYPE_OPTION_STRING>();
      auto arg_str   = T::T<TOKEN_TYPE_ARGUMENT_STRING>() | T::T<TOKEN_TYPE_OPTION_STRING>();
      auto separator = T::T<TOKEN_TYPE_SEPARATOR>();
      auto anything  = TC::T(True());

      // tokens
      auto lopta = tok::makeToken<LongOptA>(ddash + opt_str + equal + arg_str);
      auto lopt  = tok::makeToken<LongOpt>(ddash + opt_str);
      auto sopta = tok::makeToken<ShortOptA>(dash + opt_chr + arg_str);
      auto sopt  = tok::makeToken<ShortOpt>(dash + opt_chr);

      auto parser = ((lopta | lopt | sopta | sopt) * inf0) + ((separator + (anything * inf0)) * once);

      return parser.scan(Symbols(begin, end), tokens);
    }
  }
}
