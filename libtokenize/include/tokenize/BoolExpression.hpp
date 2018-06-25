// BoolExpression.hpp

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

#ifndef TOKBOOLEXPRESSION_HPP
#define TOKBOOLEXPRESSION_HPP

#include "tokenize/Expression.hpp"


namespace tok
{
  /**
   *
   */
  template<typename ExpressionT>
  class BoolExpression: ExpressionImplBase
  {
  public:
    typedef typename ExpressionT::SymbolType SymbolType;

    BoolExpression(ExpressionT const& expression);

    bool operator ()(SymbolType symbol) const;

  private:
    ExpressionT expression_;
  };


  /**
   *
   */
  template<typename SymbolT, SymbolT Symbol>
  struct BoolTerminal: ExpressionImplBase
  {
    typedef SymbolT SymbolType;

    bool operator ()(SymbolType symbol) const;
  };


  /**
   * This class represents a terminal that evaluates every input to true.
   */
  template<typename SymbolT>
  struct BoolTerminalTrue: ExpressionImplBase
  {
    typedef SymbolT SymbolType;

    bool operator ()(SymbolType symbol) const;
  };


  /**
   * This class represents a terminal that evaluates every input to false.
   */
  template<typename SymbolT>
  struct BoolTerminalFalse: ExpressionImplBase
  {
    typedef SymbolT SymbolType;

    bool operator ()(SymbolType symbol) const;
  };


  /**
   *
   */
  template<typename SymbolT>
  struct BoolTerminalCreator
  {
    template<SymbolT Symbol>
    static BoolTerminal<SymbolT, Symbol> T();
  };


  /**
   * This class represents the negation operation.
   */
  template<typename ExpressionT>
  class Not: ExpressionImplBase
  {
  public:
    typedef typename ExpressionT::SymbolType SymbolType;

    Not(ExpressionT const& expression);

    bool operator ()(SymbolType symbol) const;

  private:
    ExpressionT expression_;
  };


  template<typename ExpressionT>
  BoolExpression<Not<ExpressionT> > operator !(ExpressionT const& expression);


  /**
   *
   */
  template<typename ExpressionT1, typename ExpressionT2>
  class And: ExpressionImplBase
  {
  public:
    typedef typename ExpressionT1::SymbolType SymbolType;

    And(ExpressionT1 const& expression1, ExpressionT2 const& expression2);

    bool operator ()(SymbolType symbol) const;

  private:
    ExpressionT1 expression1_;
    ExpressionT2 expression2_;
  };


  template<typename ExpressionT1, typename ExpressionT2>
  BoolExpression<And<ExpressionT1, ExpressionT2> >
  operator &&(ExpressionT1 const& expression1, ExpressionT2 const& expression2);


  /**
   *
   */
  template<typename ExpressionT1, typename ExpressionT2>
  class Or: ExpressionImplBase
  {
  public:
    typedef typename ExpressionT1::SymbolType SymbolType;

    Or(ExpressionT1 const& expression1, ExpressionT2 const& expression2);

    bool operator ()(SymbolType symbol) const;

  private:
    ExpressionT1 expression1_;
    ExpressionT2 expression2_;
  };


  template<typename ExpressionT1, typename ExpressionT2>
  BoolExpression<Or<ExpressionT1, ExpressionT2> >
  operator ||(ExpressionT1 const& expression1, ExpressionT2 const& expression2);
}


namespace tok
{
  /**
   * @param expression
   */
  template<typename ExpressionT>
  BoolExpression<ExpressionT>::BoolExpression(ExpressionT const& expression)
    : expression_(expression)
  {
  }

  /**
   * @param symbol
   * @return true if the given expression evaluates to true for the given symbol, false otherwise
   */
  template<typename ExpressionT>
  bool BoolExpression<ExpressionT>::operator ()(SymbolType symbol) const
  {
    return expression_(symbol);
  }

  /**
   * This terminal matches all input symbols.
   * @return true
   */
  template<typename SymbolT>
  bool BoolTerminalTrue<SymbolT>::operator ()(SymbolType symbol) const
  {
    return true;
  }

  /**
   * This terminal does not match any input symbols.
   * @return false
   */
  template<typename SymbolT>
  bool BoolTerminalFalse<SymbolT>::operator ()(SymbolType symbol) const
  {
    return false;
  }

  /**
   * @return
   */
  template<typename SymbolT>
  template<SymbolT Symbol>
  BoolTerminal<SymbolT, Symbol> BoolTerminalCreator<SymbolT>::T()
  {
    return BoolTerminal<SymbolT, Symbol>();
  }

  /**
   * @param symbol
   * @return true if the given symbol matches the terminal symbol
   */
  template<typename SymbolT, SymbolT Symbol>
  bool BoolTerminal<SymbolT, Symbol>::operator ()(SymbolType symbol) const
  {
    return symbol == Symbol;
  }

  /**
   * @param expression
   */
  template<typename ExpressionT>
  Not<ExpressionT>::Not(ExpressionT const& expression)
    : expression_(expression)
  {
  }

  /**
   * @param symbol
   * @return true if the expression evaluates to false for the given symbol, false otherwise
   */
  template<typename ExpressionT>
  bool Not<ExpressionT>::operator ()(SymbolType symbol) const
  {
    return !expression_(symbol);
  }

  /**
   * @param expression
   * @return
   */
  template<typename ExpressionT>
  BoolExpression<Not<ExpressionT> > operator !(ExpressionT const& expression)
  {
    typedef Not<ExpressionT> NotType;
    return BoolExpression<NotType>(NotType(expression));
  }

  /**
   * @param symbol
   * @return
   */
  template<typename ExpressionT1, typename ExpressionT2>
  bool And<ExpressionT1, ExpressionT2>::operator ()(SymbolType symbol) const
  {
    return expression1_(symbol) && expression2_(symbol);
  }

  template<typename ExpressionT1, typename ExpressionT2>
  And<ExpressionT1, ExpressionT2>::And(ExpressionT1 const& expression1, ExpressionT2 const& expression2)
    : expression1_(expression1),
      expression2_(expression2)
  {
  }

  /**
   * @param expression1
   * @param expression2
   * @return
   */
  template<typename ExpressionT1, typename ExpressionT2>
  BoolExpression<And<ExpressionT1, ExpressionT2> >
  operator &&(ExpressionT1 const& expression1, ExpressionT2 const& expression2)
  {
    typedef And<ExpressionT1, ExpressionT2> AndType;
    return BoolExpression<AndType>(AndType(expression1, expression2));
  }

  /**
   * @param symbol
   */
  template<typename ExpressionT1, typename ExpressionT2>
  bool Or<ExpressionT1, ExpressionT2>::operator ()(SymbolType symbol) const
  {
    return expression1_(symbol) || expression2_(symbol);
  }

  /**
   * @param expression1
   * @param expression2
   */
  template<typename ExpressionT1, typename ExpressionT2>
  Or<ExpressionT1, ExpressionT2>::Or(ExpressionT1 const& expression1, ExpressionT2 const& expression2)
    : expression1_(expression1),
      expression2_(expression2)
  {
  }

  /**
   * @param expression1
   * @param expression2
   * @return
   */
  template<typename ExpressionT1, typename ExpressionT2>
  BoolExpression<Or<ExpressionT1, ExpressionT2> >
  operator ||(ExpressionT1 const& expression1, ExpressionT2 const& expression2)
  {
    typedef Or<ExpressionT1, ExpressionT2> AndType;
    return BoolExpression<AndType>(AndType(expression1, expression2));
  }
}


#endif
