// Types.hpp

/***************************************************************************
 *   Copyright (C) 2012 Daniel Mueller                                     *
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

#ifndef TESTTYPES_HPP
#define TESTTYPES_HPP

#include <tokenize/Terminal.hpp>
#include <tokenize/TerminalRange.hpp>
#include <tokenize/TerminalCustom.hpp>
#include <tokenize/SymbolStream.hpp>
#include <tokenize/TokenStream.hpp>


namespace test
{
  enum TokenType
  {
    TOKEN_TYPE_MIN,
    TOKEN_TYPE_A,
    TOKEN_TYPE_B,
    TOKEN_TYPE_PLUS,
    TOKEN_TYPE_STAR,
    TOKEN_TYPE_MAX
  };

  struct Token
  {
    Token(TokenType type);

    TokenType type;
  };

  bool operator == (Token const& lhs, Token const& rhs);
  bool operator != (Token const& lhs, Token const& rhs);

  Token const TOKEN_A    = Token(TOKEN_TYPE_A);
  Token const TOKEN_B    = Token(TOKEN_TYPE_B);
  Token const TOKEN_PLUS = Token(TOKEN_TYPE_PLUS);
  Token const TOKEN_STAR = Token(TOKEN_TYPE_STAR);


  template<TokenType Type>
  struct SymbolToken: Token
  {
    SymbolToken();
  };

  struct TokenCreator
  {
    template<typename TokenT>
    static TokenT create(char const* begin, char const* end);
  };


  typedef tok::Result                                 Result;
  typedef tok::SymbolStream<char, char const*>        Symbols;
  typedef tok::TokenStream<Token, TokenCreator>       Tokens;
  typedef tok::BoolTerminalCreator<char>              BTC;
  typedef tok::TerminalCreator<Symbols, Tokens>       T;
  typedef tok::TerminalRangeCreator<Symbols, Tokens>  TR;
  typedef tok::TerminalCustomCreator<Symbols, Tokens> TC;
  typedef tok::TerminalStreamBegin<Symbols, Tokens>   TB;
  typedef tok::TerminalStreamEnd<Symbols, Tokens>     TE;


  template<typename CharT, size_t N>
  tok::SymbolStream<CharT, CharT const*> makeSymbolStream(CharT const (& string)[N]);

  template<typename TokenT, size_t N>
  tok::TokenStream<TokenT, TokenCreator> makeTokenStream(TokenT const (& tokens)[N]);
}


namespace test
{
  inline Token::Token(TokenType type)
    : type(type)
  {
  }

  inline bool operator == (Token const& lhs, Token const& rhs)
  {
    return lhs.type == rhs.type;
  }

  inline bool operator != (Token const& lhs, Token const& rhs)
  {
    return !(lhs == rhs);
  }

  template<TokenType Type>
  inline SymbolToken<Type>::SymbolToken()
    : Token(Type)
  {
  }

  template<typename TokenT>
  inline TokenT TokenCreator::create(char const* begin, char const* end)
  {
    return TokenT();
  }

  /**
   * @param string string from which to create bew SymbolStream
   * @return newly created SymbolStream
   */
  template<typename CharT, size_t N>
  inline tok::SymbolStream<CharT, CharT const*> makeSymbolStream(CharT const (& string)[N])
  {
    return Symbols(string, string + N - 1);
  }

  /**
   * @param tokens array of tokens from which to create a new TokenStream
   * @return newly created TokenStream
   */
  template<typename TokenT, size_t N>
  inline tok::TokenStream<TokenT, TokenCreator> makeTokenStream(TokenT const (& tokens)[N])
  {
    tok::TokenStream<TokenT, TokenCreator> stream;

    for (size_t i = 0; i < N; i++)
      stream.push(tokens[i]);

    return stream;
  }
}


#endif
