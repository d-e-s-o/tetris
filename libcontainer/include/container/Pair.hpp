// Pair.hpp

/***************************************************************************
 *   Copyright (C) 2013 Daniel Mueller (deso@posteo.net)                   *
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

#ifndef CTRPAIR_HPP
#define CTRPAIR_HPP


namespace ctr
{
   /**
    * @param T
    * @param U
    * @todo make Pair a wrapper around typ::Tuple
    */
  template<typename T, typename U>
  struct Pair
  {
    T first;
    U second;

    Pair() = default;
    Pair(T const& first, U const& second);

    Pair(Pair&&) = default;
    Pair(Pair const&) = default;

    Pair& operator =(Pair&&) = default;
    Pair& operator =(Pair const&) = default;
  };


  template<typename T, typename U>
  bool operator ==(Pair<T, U> lhs, Pair<T, U> rhs);

  template<typename T, typename U>
  bool operator !=(Pair<T, U> lhs, Pair<T, U> rhs);

  template<typename T, typename U>
  Pair<T, U> makePair(T const& first, U const& second);
}


namespace ctr
{
  /**
   * @param first
   * @param second
   */
  template<typename T, typename U>
  Pair<T, U>::Pair(T const& first, U const& second)
    : first(first),
      second(second)
  {
  }

  /**
   * @param lhs
   * @param rhs
   * @return
   */
  template<typename T, typename U>
  bool operator ==(Pair<T, U> lhs, Pair<T, U> rhs)
  {
    return (lhs.first == rhs.first) && (lhs.second == rhs.second);
  }

  /**
   * @param lhs
   * @param rhs
   * @return
   */
  template<typename T, typename U>
  bool operator !=(Pair<T, U> lhs, Pair<T, U> rhs)
  {
    return !(lhs == rhs);
  }

  /**
   * @param first
   * @param second
   * @return
   */
  template<typename T, typename U>
  Pair<T, U> makePair(T const& first, U const& second)
  {
    return Pair<T, U>(first, second);
  }
}


#endif
