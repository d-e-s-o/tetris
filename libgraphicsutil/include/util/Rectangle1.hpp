// Rectangle1.hpp

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

#ifndef UTLRECTANGLE1_HPP
#define UTLRECTANGLE1_HPP


namespace utl
{
  /**
   * This class can be used for rectangles specified by a 2D position (x, y) and a size (w, h).
   */
  template<typename T, typename U>
  class Rectangle1
  {
  public:
    typedef T PositionT;
    typedef U SizeT;

    explicit Rectangle1(T x = T(), T y = T(), U w = U(), U h = U());

    T x;
    T y;
    U w;
    U h;
  };


  template<typename T, typename U>
  bool operator ==(Rectangle1<T, U> const& lhs, Rectangle1<T, U> const& rhs);

  template<typename T, typename U>
  bool operator !=(Rectangle1<T, U> const& lhs, Rectangle1<T, U> const& rhs);
}


namespace utl
{
  /**
   * @param x x coordinate of the rectangle
   * @param y y coordinate of the rectangle
   * @param w width of the rectangle
   * @param h height of the rectangle
   */
  template<typename T, typename U>
  inline Rectangle1<T, U>::Rectangle1(T x, T y, U w, U h)
    : x(x),
      y(y),
      w(w),
      h(h)
  {
  }

  /**
   * @return true if the two rectangles are equal, false if not
   */
  template<typename T, typename U>
  inline bool operator ==(Rectangle1<T, U> const& lhs, Rectangle1<T, U> const& rhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y &&
           lhs.w == rhs.w && lhs.h == rhs.h;
  }

  /**
   * @return true if the two rectangles are not equal, false if they are
   */
  template<typename T, typename U>
  inline bool operator !=(Rectangle1<T, U> const& lhs, Rectangle1<T, U> const& rhs)
  {
    return !(lhs == rhs);
  }
}


#endif
