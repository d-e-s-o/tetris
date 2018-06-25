// SymbolStream.hpp

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

#ifndef TOKSYMBOLSTREAM_HPP
#define TOKSYMBOLSTREAM_HPP

#include <util/Assert.hpp>


namespace tok
{
  /**
   * This class essentially represents a sequence of symbols. It is used throughout this library to
   * keep track of the remaining symbols to scan.
   */
  template<typename SymbolT, typename IteratorT>
  class SymbolStream
  {
  public:
    typedef SymbolT   SymbolType;
    typedef IteratorT IteratorType;

    SymbolStream(IteratorT begin, IteratorT end);

    // use compiler generated copy constructor and assignment operator

    SymbolT const& dereference() const;

    void advance(int n);

    IteratorT begin() const;
    IteratorT end() const;
    IteratorT current() const;

  private:
    IteratorT begin_;
    IteratorT end_;
    IteratorT current_;
  };
}


namespace tok
{
  /**
   * The constructor creates a new symbol stream ranging from 'begin' to 'end' (exclusively).
   * @param begin
   * @param end
   */
  template<typename SymbolT, typename IteratorT>
  SymbolStream<SymbolT, IteratorT>::SymbolStream(IteratorT begin, IteratorT end)
    : begin_(begin),
      end_(end),
      current_(begin)
  {
  }

  /**
   * @return
   */
  template<typename SymbolT, typename IteratorT>
  SymbolT const& SymbolStream<SymbolT, IteratorT>::dereference() const
  {
    ASSERTOP(current_, ge, begin_);
    ASSERTOP(current_, lt, end_);
    return *current_;
  }

  /**
   * @param n number of symbols to advance by
   */
  template<typename SymbolT, typename IteratorT>
  void SymbolStream<SymbolT, IteratorT>::advance(int n)
  {
    ASSERTOP(n, ge, 0);
    ASSERTOP(n, le, end_ - current_);
    current_ += n;
  }

  /**
   * @return iterator pointing to the beginning of the stream
   */
  template<typename SymbolT, typename IteratorT>
  IteratorT SymbolStream<SymbolT, IteratorT>::begin() const
  {
    return begin_;
  }

  /**
   * @return iterator pointing right behind the last symbol of the stream
   */
  template<typename SymbolT, typename IteratorT>
  IteratorT SymbolStream<SymbolT, IteratorT>::end() const
  {
    return end_;
  }

  /**
   * @return iterator pointing to current symbol within the stream
   */
  template<typename SymbolT, typename IteratorT>
  IteratorT SymbolStream<SymbolT, IteratorT>::current() const
  {
    return current_;
  }
}


#endif
