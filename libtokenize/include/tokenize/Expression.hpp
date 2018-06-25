// Expression.hpp

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

#ifndef TOKEXPRESSION_HPP
#define TOKEXPRESSION_HPP

#include "tokenize/Config.hpp"
#include "tokenize/Result.hpp"


namespace tok
{
  /**
   * This class is meant to be used as the base class for all types of expressions. It prohibits
   * dynamic object creation and assignment, as those operations should not be used on expressions.
   */
  class ExpressionImplBase
  {
  private:
    void operator = (ExpressionImplBase const&);

    void* operator new(size_t);
    void  operator delete(void*);
  };


  /**
   * This class defines the interface of all valid expression types. Every derived type has to
   * provide the typedefs SymbolStreamType and TokenStreamType. The former being the stream from
   * which to read symbols that are meant to be scanned, the latter being a stream to write
   * successfully scanned tokens to. A token can be any user defined type that has a special meaning
   * to the user.
   * SymbolStreamType can be any user defined type that provides the same interface as
   * tok::SymbolStream. TokenStreamType can be any user defined type that provides the same
   * interface as tok::TokenStream.
   * @see tok::SymbolStream
   * @see tok::TokenStream
   * @see tok::Token
   */
  template<typename ExpressionT>
  class Expression: public ExpressionImplBase
  {
  public:
    typedef typename ExpressionT::SymbolStreamType SymbolStreamType;
    typedef typename ExpressionT::TokenStreamType  TokenStreamType;

    Expression(ExpressionT const& expression);

    Result scan(SymbolStreamType const& symbols, TokenStreamType& tokens) const;

  private:
    ExpressionT expression_;
  };
}


namespace tok
{
  /**
   * @param expression
   */
  template<typename ExpressionT>
  Expression<ExpressionT>::Expression(ExpressionT const& expression)
    : expression_(expression)
  {
  }

  /**
   * This method can be used to scan a symbol stream for expressions and fill a token stream out of
   * the recognized tokens.
   * @param symbols symbol stream to scan
   * @param tokens stream of tokens to fill
   * @return number of scanned symbols from the given symbol stream, values less than 0 indicate an
   *         error, e.g., if a token failed to parse and no alternative path could be found
   * @note it depends on the use case to determine if a scan() operation was actually successful;
   *       typically you would describe it as successful, if every symbol from the input stream was
   *       successfully parsed; it is up to the user to check for that
   */
  template<typename ExpressionT>
  Result Expression<ExpressionT>::scan(SymbolStreamType const& symbols,
                                       TokenStreamType       & tokens) const
  {
    return expression_.scan(symbols, tokens);
  }
}


#endif
