// Iterator.hpp

/***************************************************************************
 *   Copyright (C) 2006-2012 Daniel Mueller (deso@posteo.net)              *
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

#ifndef BASEITERATOR_HPP
#define BASEITERATOR_HPP


namespace base
{
  /**
   * The Iterator template can be used for iterating over a range of values, either in "correct"
   * or in reverse order.
   * Depending on the last two template parameters this can be:
   * - [first, last] for true and true
   * - [first, last) for true and false
   * - (first, last] for false and true
   * - (first, last) for false and false
   */
  template<typename T, bool IncludeFirst, bool IncludeLast>
  class Iterator
  {
  public:
    Iterator(T const& first, T const& last, bool reverse);

    bool            operator ()() const;
    Iterator const& operator ++();

    T const& getValue() const;

  private:
    T first_;
    T last_;
    T value_;

    bool reverse_;

    static t GetStartValue(T const& first, T const& last, bool reverse);
  };
}


namespace base
{
  /**
   * @param first lowest value in range
   * @param last highest value in range
   * @param reverse true if the iteration should go in reverse order, false if not
   */
  template<typename T, bool IncludeFirst, bool IncludeLast>
  inline Iterator<T, IncludeFirst, IncludeLast>::Iterator(T const& first, T const& last, bool reverse)
    : first_(first),
      last_(last),
      value_(getStartValue(first, last, reverse)),
      reverse_(reverse)
  {
  }

  /**
   * @return true if the current value is within the valid range, false if not
   */
  template<typename T, bool IncludeFirst, bool IncludeLast>
  bool Iterator<T, IncludeFirst, IncludeLast>::operator ()() const
  {
    if (reverse_)
      return IncludeFirst ? value_ >= first_ : value_ > first_;
    else
      return IncludeLast ? value_ <= last_ : value_ < last_;
  }

  /**
   * @return self after increasing
   */
  template<typename T, bool IncludeFirst, bool IncludeLast>
  Iterator<T, IncludeFirst, IncludeLast> const& Iterator<T, IncludeFirst, IncludeLast>::operator ++ ()
  {
    reverse_ ? --value_ : ++value_;
    return *this;
  }

  /**
   * @return current iteration value
   */
  template<typename T, bool IncludeFirst, bool IncludeLast>
  T const& Iterator<T, IncludeFirst, IncludeLast>::getValue() const
  {
    return value_;
  }

  /**
   * @return value to start the iteration with, depending on reverse and IncludeFirst and
   *         IncludeLast
   */
  template<typename T, bool IncludeFirst, bool IncludeLast>
  T Iterator<T, IncludeFirst, IncludeLast>::getStartValue(T const& first, T const& last, bool reverse)
  {
    if (reverse)
      return IncludeLast ? last : last - 1;
    else
      return IncludeFirst ? first : first + 1;
  }
}


#endif
