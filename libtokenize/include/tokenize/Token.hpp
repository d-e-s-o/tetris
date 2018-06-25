// Token.hpp

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

#ifndef TOKTOKEN_HPP
#define TOKTOKEN_HPP

#include "tokenize/Result.hpp"
#include "tokenize/Expression.hpp"


namespace tok
{
  /**
   *
   */
  template<typename TokenT, typename ExpressionT>
  class Token: public ExpressionImplBase
  {
  public:
    typedef typename ExpressionT::SymbolStreamType SymbolStreamType;
    typedef typename ExpressionT::TokenStreamType  TokenStreamType;

    Token(ExpressionT const& expression);

    Result scan(SymbolStreamType const& symbols, TokenStreamType& tokens) const;

  private:
    ExpressionT expression_;
  };


  template<typename TokenT, typename ExpressionT>
  Token<TokenT, ExpressionT> makeToken(ExpressionT expression);
}


namespace tok
{
  /**
   * @param expression
   */
  template<typename TokenT, typename ExpressionT>
  Token<TokenT, ExpressionT>::Token(ExpressionT const& expression)
    : expression_(expression)
  {
  }

  /**
   * @copydoc Expression::scan
   */
  template<typename TokenT, typename ExpressionT>
  Result Token<TokenT, ExpressionT>::scan(SymbolStreamType const& symbols,
                                          TokenStreamType       & tokens) const
  {
    typedef typename TokenStreamType::TokenCreatorType TokenCreatorType;

    TokenStreamType t;
    Result r = expression_.scan(symbols, t);

    if (r.last >= 0)
      tokens.push(TokenCreatorType::template create<TokenT>(symbols.current(), symbols.current() + r.last));

    return r;
  }

  /**
   * This function can be used to create a new token without specifying the type of expression to
   * create it from.
   */
  template<typename TokenT, typename ExpressionT>
  Token<TokenT, ExpressionT> makeToken(ExpressionT expression)
  {
    return Token<TokenT, ExpressionT>(expression);
  }
}


#endif
