// TokenStream.hpp

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

#ifndef TOKTOKENSTREAM_HPP
#define TOKTOKENSTREAM_HPP

#include <container/Array.hpp>
#include <container/ArrayFunctions.hpp>


namespace tok
{
  /**
   *
   */
  template<typename TokenT, typename TokenCreatorT>
  class TokenStream
  {
  private:
    typedef ctr::Array<TokenT> Tokens;

  public:
    typedef typename Tokens::ConstIterator IteratorType;
    typedef TokenCreatorT                  TokenCreatorType;

    // use compiler generated copy constructor and assignment operator

    void push(TokenT const& token);
    void pop();

    bool empty() const;

    void add(TokenStream const& tokens);

    IteratorType begin() const;
    IteratorType end() const;

  private:
    Tokens tokens_;
  };


  template<typename TokenT, typename TokenCreatorT>
  bool operator ==(TokenStream<TokenT, TokenCreatorT> const& lhs,
                   TokenStream<TokenT, TokenCreatorT> const& rhs);

  template<typename TokenT, typename TokenCreatorT>
  bool operator !=(TokenStream<TokenT, TokenCreatorT> const& lhs,
                   TokenStream<TokenT, TokenCreatorT> const& rhs);
}


namespace tok
{
  /**
   *
   */
  template<typename TokenT, typename TokenCreatorT>
  void TokenStream<TokenT, TokenCreatorT>::push(TokenT const& token)
  {
    ctr::append(tokens_, token);
  }

  /**
   *
   */
  template<typename TokenT, typename TokenCreatorT>
  void TokenStream<TokenT, TokenCreatorT>::pop()
  {
    tokens_.shrink(tokens_.size() - 1);
  }

  /**
   * @return true if the TokenStream is empty, false if it contains elements
   */
  template<typename TokenT, typename TokenCreatorT>
  bool TokenStream<TokenT, TokenCreatorT>::empty() const
  {
    return tokens_.size() == 0;
  }

  /**
   *
   */
  template<typename TokenT, typename TokenCreatorT>
  void TokenStream<TokenT, TokenCreatorT>::add(TokenStream const& tokens)
  {
    tokens_.replace(tokens_.end(), tokens_.end(), tokens.begin(), tokens.end());
  }

  /**
   *
   */
  template<typename TokenT, typename TokenCreatorT>
  typename TokenStream<TokenT, TokenCreatorT>::IteratorType
  TokenStream<TokenT, TokenCreatorT>::begin() const
  {
    return tokens_.begin();
  }

  /**
   *
   */
  template<typename TokenT, typename TokenCreatorT>
  typename TokenStream<TokenT, TokenCreatorT>::IteratorType
  TokenStream<TokenT, TokenCreatorT>::end() const
  {
    return tokens_.end();
  }

  /**
   * @param lhs first TokenStream object
   * @param rhs second TokenStream object
   * @return true if the two given objects are equal, false if they are not
   */
  template<typename TokenT, typename TokenCreatorT>
  bool operator ==(TokenStream<TokenT, TokenCreatorT> const& lhs,
                   TokenStream<TokenT, TokenCreatorT> const& rhs)
  {
    auto it1 = lhs.begin();
    auto it2 = rhs.begin();

    for (; it1 != lhs.end() && it2 != rhs.end(); ++it1, ++it2)
    {
      if (*it1 != *it2)
        return false;
    }
    return it1 == lhs.end() && it2 == rhs.end();
  }

  /**
   * @param lhs first TokenStream object
   * @param rhs second TokenStream object
   * @return true if the two given objects are not equal, false if they are
   */
  template<typename TokenT, typename TokenCreatorT>
  bool operator !=(TokenStream<TokenT, TokenCreatorT> const& lhs,
                   TokenStream<TokenT, TokenCreatorT> const& rhs)
  {
    return !(lhs == rhs);
  }
}


#endif
