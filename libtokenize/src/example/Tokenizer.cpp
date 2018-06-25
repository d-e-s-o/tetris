// Tokenizer.cpp

/***************************************************************************
 *   Copyright (C) 2012,2014 Daniel Mueller                                *
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
#include <iterator>

#include <util/Assert.hpp>
#include <tokenize/Tokenize.hpp>


namespace
{
  /**
   * This enumeration represents the different types of known tokens.
   */
  enum TokenType
  {
    TOKEN_TYPE_MIN,
    TOKEN_TYPE_PLUS,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_MAX
  };

  struct TokenCreator
  {
    template<typename TokenT>
    static TokenT create(char const* begin, char const* end)
    {
      return TokenT(begin, end);
    }
  };

  struct Token
  {
    Token(TokenType type, int value = 0)
      : type(type),
        value(value)
    {
    }

    void print() const
    {
      switch (type)
      {
      case TOKEN_TYPE_PLUS:
        std::cout << "TOKEN_TYPE_PLUS" << std::endl;
        break;

      case TOKEN_TYPE_NUMBER:
        std::cout << "TOKEN_TYPE_NUMBER(" << value << ")" << std::endl;
        break;

      default:
        std::cerr << "unknown token type: " << type << std::endl;
        break;
      }
    }

    TokenType type;
    int       value;
  };

  std::ostream& operator << (std::ostream& lhs, Token const& rhs)
  {
    switch (rhs.type)
    {
    case TOKEN_TYPE_PLUS:
      lhs << "+";
      break;

    case TOKEN_TYPE_NUMBER:
      lhs << rhs.value;
      break;

    default:
      ASSERT(false);
    }
  }

  /**
   *
   */
  template<TokenType Symbol>
  struct SymbolToken: Token
  {
    SymbolToken(char const* begin, char const* end)
      : Token(Symbol)
    {
    }
  };

  /**
   *
   */
  struct DecimalNumber: Token
  {
    DecimalNumber(char const* begin, char const* end)
      : Token(TOKEN_TYPE_NUMBER, parse(begin, end))
    {
    }

    /**
     * This method parses a decimal number from the given string range.
     * @param begin begin of the string
     * @param end end of the string (pointing right after the last valid element)
     */
    static int parse(char const* begin, char const* end)
    {
      int value  = 0;
      int factor = 1;

      for (char const* it = end - 1; it != begin - 1; it--)
      {
        value  += (*it - '0') * factor;
        factor *= 10;
      }
      return value;
    }
  };


  typedef tok::SymbolStream<char, char const*>  Symbols;
  typedef tok::TokenStream<Token, TokenCreator> Tokens;
  typedef tok::RepeatCount<0, -1>               Inf;
  typedef tok::TerminalCreator<Symbols, Tokens> T;


  int evaluate(Tokens::IteratorType const& begin, Tokens::IteratorType const& end)
  {
    if (begin != end)
    {
      Tokens::IteratorType it = begin;

      switch (it->type)
      {
      case TOKEN_TYPE_NUMBER:
        int value = it->value;

        if (++it != end)
        {
          switch (it->type)
          {
          case TOKEN_TYPE_PLUS:
            return value + evaluate(++it, end);
          }
        }
        else
          return value;
      }
    }
    ASSERT(false);
  }

  int evaluate(Tokens const& tokens)
  {
    return evaluate(tokens.begin(), tokens.end());
  }
}


int main()
{
  using tok::makeToken;

  // simple symbols
  auto inf      = Inf();
  auto digit_nn = T::T<'1'>() | T::T<'2'>() | T::T<'3'>() |
                  T::T<'4'>() | T::T<'5'>() | T::T<'6'>() |
                  T::T<'7'>() | T::T<'8'>() | T::T<'9'>();
  auto digit    = T::T<'0'>() | digit_nn;
  auto skip     = (T::T<' '>() | T::T<'\t'>()) * inf;

  // tokens
  auto number = makeToken<DecimalNumber>((digit_nn + (digit * inf)) | digit);
  auto plus   = makeToken<SymbolToken<TOKEN_TYPE_PLUS> >(T::T<'+'>());

  // rules
  auto term  = skip + number + ((skip + plus + skip + number + skip) * inf);
  auto start = term;

  char const  string[] = "  123 +731+  312";
  char const* begin    = string;
  char const* end      = string + sizeof(string) - 1;

  Tokens tokens;
  auto n = start.scan(Symbols(begin, end), tokens);

  if (n.last < 0)
    std::cerr << "an error occurred while scanning" << std::endl;
  else if (n.last != end - begin)
  {
    std::cerr << "could not scan the whole stream, stopped at: "
              << "'" << *(begin + n.last) << "' (" << n.last << ")" << std::endl;
  }
  else
  {
    std::cout << "scanned the following tokens: " << std::endl;

    for (Tokens::IteratorType it = tokens.begin(); it != tokens.end(); ++it)
      it->print();

    std::copy(tokens.begin(), tokens.end(), std::ostream_iterator<Token>(std::cout, ""));
    std::cout << "=" << evaluate(tokens) << std::endl;
  }
}
