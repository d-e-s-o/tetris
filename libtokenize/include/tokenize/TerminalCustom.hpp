// TerminalCustom.hpp

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

#ifndef TOKTERMINALCUSTOM_HPP
#define TOKTERMINALCUSTOM_HPP

#include "tokenize/Result.hpp"
#include "tokenize/Expression.hpp"
#include "tokenize/BoolExpression.hpp"


namespace tok
{
  /**
   * @param SymbolStreamT
   * @param TokenStreamT
   * @param ExpressionT typically a BoolExpression that is to be evluated for a given symbol to scan
   * @see BoolExpression
   * @todo check if we could actually remove the expression_ member variable and just use the
   *       template parameter -- this would relief us from having to create a constructor and
   *       simplify many other things; if this works out this would affect pretty much all other
   *       classes within this library as well
   */
  template<typename SymbolStreamT, typename TokenStreamT, typename ExpressionT>
  struct TerminalCustom: ExpressionImplBase
  {
  public:
    typedef SymbolStreamT SymbolStreamType;
    typedef TokenStreamT  TokenStreamType;

    TerminalCustom(ExpressionT const& expression);

    Result scan(SymbolStreamType const& symbols, TokenStreamType& tokens) const;

  private:
    ExpressionT expression_;
  };


  /**
   * This helper template can be used to create TerminalCustom instances the fast way.
   */
  template<typename SymbolStreamT, typename TokenStreamT>
  struct TerminalCustomCreator
  {
    template<typename ExpressionT>
    static TerminalCustom<SymbolStreamT, TokenStreamT, ExpressionT> T(ExpressionT expression);
  };
}


namespace tok
{
  /**
   * @param expression
   */
  template<typename SymbolStreamT, typename TokenStreamT, typename ExpressionT>
  TerminalCustom<SymbolStreamT, TokenStreamT, ExpressionT>::TerminalCustom(ExpressionT const& expression)
    : expression_(expression)
  {
  }

  /**
   * @copydoc Expression::scan
   */
  template<typename SymbolStreamT, typename TokenStreamT, typename ExpressionT>
  Result TerminalCustom<SymbolStreamT, TokenStreamT, ExpressionT>::scan(SymbolStreamType const& symbols,
                                                                        TokenStreamType       & tokens) const
  {
    if (symbols.current() == symbols.end())
      return Result{-1, 0};

    if (expression_(symbols.dereference()))
      return Result{1, 1};

    return Result{-1, 0};
  }

  /**
   *
   */
  template<typename SymbolStreamT, typename TokenStreamT>
  template<typename ExpressionT>
  TerminalCustom<SymbolStreamT, TokenStreamT, ExpressionT>
  TerminalCustomCreator<SymbolStreamT, TokenStreamT>::T(ExpressionT expression)
  {
    return TerminalCustom<SymbolStreamT, TokenStreamT, ExpressionT>(expression);
  }
}


#endif
