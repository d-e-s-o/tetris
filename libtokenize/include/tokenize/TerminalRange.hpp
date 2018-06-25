// TerminalRange.hpp

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

#ifndef TOKTERMINALRANGE_HPP
#define TOKTERMINALRANGE_HPP

#include "tokenize/Result.hpp"
#include "tokenize/Expression.hpp"


namespace tok
{
  /**
   * This class represents a terminal that accepts a range of possible symbols. Although this
   * behavior could be achieved using a tok::Terminal in conjunction with tok::Alternative this
   * approach simplifies specification of such ranges (one does not have to name every terminal in
   * the range) and speeds things up (no backtracking but only two simple comparisons).
   */
  template<typename SymbolStreamT, typename TokenStreamT,
           typename SymbolStreamT::SymbolType SymbolFirst,
           typename SymbolStreamT::SymbolType SymbolLast>
  class TerminalRange: public ExpressionImplBase
  {
  public:
    typedef SymbolStreamT SymbolStreamType;
    typedef TokenStreamT  TokenStreamType;

    Result scan(SymbolStreamType const& symbols, TokenStreamType& tokens) const;
  };


  /**
   * This helper template can be used to create TerminalRanges the fast way.
   */
  template<typename SymbolStreamT, typename TokenStreamT>
  struct TerminalRangeCreator
  {
    template<typename SymbolStreamT::SymbolType SymbolFirst,
             typename SymbolStreamT::SymbolType SymbolLast>
    static TerminalRange<SymbolStreamT, TokenStreamT, SymbolFirst, SymbolLast> T();
  };
}


namespace tok
{
  /**
   * @copydoc Expression::scan
   */
  template<typename SymbolStreamT, typename TokenStreamT, typename SymbolStreamT::SymbolType SymbolFirst,
                                                          typename SymbolStreamT::SymbolType SymbolLast>
  Result TerminalRange<SymbolStreamT, TokenStreamT, SymbolFirst, SymbolLast>::scan(SymbolStreamType const& symbols,
                                                                                   TokenStreamType       & tokens) const
  {
    if (symbols.current() == symbols.end())
      return Result{-1, 0};

    typename SymbolStreamT::SymbolType symbol = symbols.dereference();

    if (SymbolFirst <= symbol && symbol <= SymbolLast)
      return Result{1, 1};

    return Result{-1, 0};
  }

  /**
   * @return
   */
  template<typename SymbolStreamT, typename TokenStreamT>
  template<typename SymbolStreamT::SymbolType SymbolFirst,
           typename SymbolStreamT::SymbolType SymbolLast>
  TerminalRange<SymbolStreamT, TokenStreamT, SymbolFirst, SymbolLast>
  TerminalRangeCreator<SymbolStreamT, TokenStreamT>::T()
  {
    return TerminalRange<SymbolStreamT, TokenStreamT, SymbolFirst, SymbolLast>();
  }
}


#endif
