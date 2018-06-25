// Alternative.hpp

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

#ifndef TOKALTERNATIVE_HPP
#define TOKALTERNATIVE_HPP

#include "tokenize/Result.hpp"
#include "tokenize/Expression.hpp"


namespace tok
{
  /**
   * This class represents an alternative of two expressions. One of them have to be scanned in
   * order for the scan to succeed.
   * @note the first expression is scanned first and only if it fails to scan the second
   *       expression will be scanned; this has the implication that the first expression should
   *       not be a prefix of the second one, because if it is, it will might match although the
   *       second one might be more appropriate; care should be taken to define the grammar to
   *       avoid problems like this
   */
  template<typename ExpressionT1, typename ExpressionT2>
  class Alternative: public ExpressionImplBase
  {
  public:
    typedef typename ExpressionT1::SymbolStreamType SymbolStreamType;
    typedef typename ExpressionT1::TokenStreamType  TokenStreamType;

    Alternative(ExpressionT1 const& expression1, ExpressionT2 const& expression2);

    Result scan(SymbolStreamType const& symbols, TokenStreamType& tokens) const;

  private:
    ExpressionT1 expression1_;
    ExpressionT2 expression2_;
  };


  template<typename ExpressionT1, typename ExpressionT2>
  Expression<Alternative<ExpressionT1, ExpressionT2> >
  operator | (ExpressionT1 const& expression1, ExpressionT2 const& expression2);
}


namespace tok
{
  /**
   *
   */
  template<typename ExpressionT1, typename ExpressionT2>
  Alternative<ExpressionT1, ExpressionT2>::Alternative(ExpressionT1 const& expression1,
                                                       ExpressionT2 const& expression2)
    : expression1_(expression1),
      expression2_(expression2)
  {
  }

  /**
   * @copydoc Expression::scan
   */
  template<typename ExpressionT1, typename ExpressionT2>
  Result Alternative<ExpressionT1, ExpressionT2>::scan(SymbolStreamType const& symbols,
                                                       TokenStreamType       & tokens) const
  {
    // first try to scan the first expression and only if it fails we scan the second one
    // one could also think of an approach where both expressions are scanned in either case, and
    // only that one that matched the longer string is actually used, however at closer thought this
    // could lead to other, more subtle, problems:
    // - what if both matched strings are equal in length? then we cannot say for sure what the
    //   user wanted to match
    // - the behavior would collide with the one from C, where the right element of an
    //   alternative is checked only if its left one evaluated to false

    Result::result_t max = 0;

    {
      TokenStreamType t;
      Result r = expression1_.scan(symbols, t);

      if (r.max > max)
        max = r.max;

      if (r.last >= 0)
        return tokens.add(t), r;
    }

    {
      TokenStreamType t;
      Result r = expression2_.scan(symbols, t);

      if (r.max > max)
        max = r.max;

      if (r.last >= 0)
        return tokens.add(t), r;
    }
    return Result{-1, max};
  }

  /**
   *
   */
  template<typename ExpressionT1, typename ExpressionT2>
  Expression<Alternative<ExpressionT1, ExpressionT2> >
  operator | (ExpressionT1 const& expression1, ExpressionT2 const& expression2)
  {
    typedef Alternative<ExpressionT1, ExpressionT2> AlternativeType;
    return Expression<AlternativeType>(AlternativeType(expression1, expression2));
  }
}


#endif
