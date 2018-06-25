// Sequence.hpp

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

#ifndef TOKSEQUENCE_HPP
#define TOKSEQUENCE_HPP

#include "tokenize/Result.hpp"
#include "tokenize/Expression.hpp"


namespace tok
{
  /**
   * This class represents a sequence of two expressions. Both have to be scanned in order for the
   * scan to succeed.
   */
  template<typename ExpressionT1, typename ExpressionT2>
  class Sequence: public ExpressionImplBase
  {
  public:
    typedef typename ExpressionT1::SymbolStreamType SymbolStreamType;
    typedef typename ExpressionT1::TokenStreamType  TokenStreamType;

    Sequence(ExpressionT1 const& expression1, ExpressionT2 const& expression2);

    Result scan(SymbolStreamType const& symbols, TokenStreamType& tokens) const;

  private:
    ExpressionT1 expression1_;
    ExpressionT2 expression2_;
  };


  template<typename ExpressionT1, typename ExpressionT2>
  Expression<Sequence<ExpressionT1, ExpressionT2> >
  operator + (ExpressionT1 const& expression1, ExpressionT2 const& expression2);
}


namespace tok
{
  /**
   *
   */
  template<typename ExpressionT1, typename ExpressionT2>
  Sequence<ExpressionT1, ExpressionT2>::Sequence(ExpressionT1 const& expression1,
                                                 ExpressionT2 const& expression2)
    : expression1_(expression1),
      expression2_(expression2)
  {
  }

  /**
   * @copydoc Expression::scan
   */
  template<typename ExpressionT1, typename ExpressionT2>
  Result Sequence<ExpressionT1, ExpressionT2>::scan(SymbolStreamType const& symbols, TokenStreamType& tokens) const
  {
    TokenStreamType  t;
    SymbolStreamType s(symbols);

    Result r1 = expression1_.scan(s, t);

    if (r1.last < 0)
      return r1;

    s.advance(r1.last);

    Result r2 = expression2_.scan(s, t);

    if (r2.last < 0)
      return r2;

    Result::result_t n = r1.last + r2.last;
    return tokens.add(t), Result{n, n};
  }

  /**
   *
   */
  template<typename ExpressionT1, typename ExpressionT2>
  Expression<Sequence<ExpressionT1, ExpressionT2> >
  operator + (ExpressionT1 const& expression1, ExpressionT2 const& expression2)
  {
    typedef Sequence<ExpressionT1, ExpressionT2> SequenceType;
    return Expression<SequenceType>(SequenceType(expression1, expression2));
  }
}


#endif
