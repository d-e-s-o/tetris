// Repetition.hpp

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

#ifndef TOKREPETITION_HPP
#define TOKREPETITION_HPP

#include "tokenize/Result.hpp"
#include "tokenize/Expression.hpp"


namespace tok
{
  /**
   * @todo a repeat count with Max=-1 is meant to be used for an infinite amount of repititions,
   *       but at the moment it is only treated as (-1u) which is something like 0xFFFFFFFF
   *       (whatever size unsigned has), which is not quite infinite - fix this!
   */
  template<typename ExpressionT, unsigned int Min, unsigned int Max>
  class Repetition: public ExpressionImplBase
  {
  public:
    typedef typename ExpressionT::SymbolStreamType SymbolStreamType;
    typedef typename ExpressionT::TokenStreamType  TokenStreamType;

    Repetition(ExpressionT expression);

    Result scan(SymbolStreamType const& symbols, TokenStreamType& tokens) const;

  private:
    ExpressionT expression_;
  };


  /**
   * This template describes the amount of repetitions to make.
   * @param Min minimum number of repetitions
   * @param Max maximum number of repetitions (use -1 for infinity)
   */
  template<unsigned int Min, unsigned int Max = Min>
  struct RepeatCount
  {
  };


  template<typename ExpressionT, unsigned int Min, unsigned int Max>
  Expression<Repetition<ExpressionT, Min, Max> >
  operator * (ExpressionT const& expression, RepeatCount<Min, Max> const& count);
}


namespace tok
{
  /**
   *
   */
  template<typename ExpressionT, unsigned int Min, unsigned int Max>
  Repetition<ExpressionT, Min, Max>::Repetition(ExpressionT expression)
    : expression_(expression)
  {
  }

  /**
   * @copydoc Expression::scan
   */
  template<typename ExpressionT, unsigned int Min, unsigned int Max>
  Result Repetition<ExpressionT, Min, Max>::scan(SymbolStreamType const& symbols,
                                                 TokenStreamType       & tokens) const
  {
    TokenStreamType  t;
    SymbolStreamType s(symbols);

    Result::result_t n = 0;

    for (unsigned int i = 0; i < Max; i++)
    {
      Result r = expression_.scan(s, t);

      // note that here we treat a scan amount of zero as a possible cancelation criterion
      // (although strictly speaking this is no error) because a repeated scan would result just in
      // another scan of zero elements -- so if we have scanned the minimum amount we are finished
      if (r.last <= 0)
      {
        // if we have scanned at least the minimum amount of repetitions without an error
        if (i >= Min)
          return tokens.add(t), Result{n, n};

        return Result{r.last, static_cast<Result::result_t>(n + r.max)};
      }

      s.advance(r.last);
      n += r.last;
    }
    // we have Max amounts and are finished
    return tokens.add(t), Result{n, n};
  }

  /**
   *
   */
  template<typename ExpressionT, unsigned int Min, unsigned int Max>
  Expression<Repetition<ExpressionT, Min, Max> >
  operator * (ExpressionT const& expression, RepeatCount<Min, Max> const& count)
  {
    typedef Repetition<ExpressionT, Min, Max> RepetitionType;
    return Expression<RepetitionType>(RepetitionType(expression));
  }
}

#endif
