// Terminal.hpp

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

#ifndef TOKTERMINAL_HPP
#define TOKTERMINAL_HPP

#include "tokenize/Result.hpp"
#include "tokenize/Expression.hpp"


namespace tok
{
  /**
   *
   */
  template<typename SymbolStreamT, typename TokenStreamT, typename SymbolStreamT::SymbolType Symbol>
  struct Terminal: ExpressionImplBase
  {
    typedef SymbolStreamT SymbolStreamType;
    typedef TokenStreamT  TokenStreamType;

    Result scan(SymbolStreamType const& symbols, TokenStreamType& tokens) const;
  };

  /**
   * This class represents a special terminal symbol that only matches the beginning of the symbol
   * stream. Note, however, that this is just a symbolic match as no actual symbol is consumed and
   * will even match if the given symbol stream is empty.
   */
  template<typename SymbolStreamT, typename TokenStreamT>
  struct TerminalStreamBegin: ExpressionImplBase
  {
    typedef SymbolStreamT SymbolStreamType;
    typedef TokenStreamT  TokenStreamType;

    Result scan(SymbolStreamType const& symbols, TokenStreamType& tokens) const;
  };

  /**
   * This class represents a special terminal symbol that only matches the end of the symbol stream.
   * Note, however, that this is just a symbolic match as no actual symbol is consumed.
   */
  template<typename SymbolStreamT, typename TokenStreamT>
  struct TerminalStreamEnd: ExpressionImplBase
  {
    typedef SymbolStreamT SymbolStreamType;
    typedef TokenStreamT  TokenStreamType;

    Result scan(SymbolStreamType const& symbols, TokenStreamType& tokens) const;
  };

  /**
   * This helper template can be used to create Terminals the fast way.
   */
  template<typename SymbolStreamT, typename TokenStreamT>
  struct TerminalCreator
  {
    template<typename SymbolStreamT::SymbolType Symbol>
    static Terminal<SymbolStreamT, TokenStreamT, Symbol> T();
  };
}


namespace tok
{
  /**
   * @copydoc Expression::scan
   */
  template<typename SymbolStreamT, typename TokenStreamT, typename SymbolStreamT::SymbolType Symbol>
  Result Terminal<SymbolStreamT, TokenStreamT, Symbol>::scan(SymbolStreamType const& symbols,
                                                             TokenStreamType       & tokens) const
  {
    if (symbols.current() == symbols.end())
      return Result{-1, 0};

    if (symbols.dereference() == Symbol)
      return Result{1, 1};

    return Result{-1, 0};
  }

  /**
   * @copydoc Expression::scan
   */
  template<typename SymbolStreamT, typename TokenStreamT>
  Result TerminalStreamBegin<SymbolStreamT, TokenStreamT>::scan(SymbolStreamType const& symbols,
                                                                TokenStreamType       & tokens) const
  {
    if (symbols.current() == symbols.begin())
      return Result{0, 0};

    return Result{-1, 0};
  }

  /**
   * @copydoc Expression::scan
   */
  template<typename SymbolStreamT, typename TokenStreamT>
  Result TerminalStreamEnd<SymbolStreamT, TokenStreamT>::scan(SymbolStreamType const& symbols,
                                                              TokenStreamType       & tokens) const
  {
    if (symbols.current() == symbols.end())
      return Result{0, 0};

    return Result{-1, 0};
  }

  template<typename SymbolStreamT, typename TokenStreamT>
  template<typename SymbolStreamT::SymbolType Symbol>
  Terminal<SymbolStreamT, TokenStreamT, Symbol> TerminalCreator<SymbolStreamT, TokenStreamT>::T()
  {
    return Terminal<SymbolStreamT, TokenStreamT, Symbol>();
  }
}


#endif
