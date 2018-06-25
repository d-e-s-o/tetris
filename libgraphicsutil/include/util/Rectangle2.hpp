// Rectangle2.hpp

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

#ifndef UTLRECTANGLE2_HPP
#define UTLRECTANGLE2_HPP


namespace utl
{
  /**
   * This class can be used for specified by two points.
   */
  template<typename T>
  class Rectangle2
  {
  public:
    typedef T Type;

    explicit Rectangle2(T x1 = T(), T y1 = T(), T x2 = T(), T y2 = T());

    template<typename U>
    explicit Rectangle2(Rectangle2<U> const& rhs);

    T x1_;
    T y1_;
    T x2_;
    T y2_;
  };


  template<typename T>
  bool operator ==(Rectangle2<T> const& lhs, Rectangle2<T> const& rhs);

  template<typename T>
  bool operator !=(Rectangle2<T> const& lhs, Rectangle2<T> const& rhs);
}


namespace utl
{
  /**
   * @param x1 first x coordinate of the rectangle
   * @param y1 first y coordinate of the rectangle
   * @param x2 second x coordinate of the rectangle
   * @param y2 second y coordinate of the rectangle
   */
  template<typename T>
  inline Rectangle2<T>::Rectangle2(T x1, T y1, T x2, T y2)
    : x1_(x1),
      y1_(y1),
      x2_(x2),
      y2_(y2)
  {
  }

  template<typename T>
  template<typename U>
  inline Rectangle2<T>::Rectangle2(Rectangle2<U> const& rhs)
    : x1_(static_cast<T>(rhs.x1_)),
      y1_(static_cast<T>(rhs.y1_)),
      x2_(static_cast<T>(rhs.x2_)),
      y2_(static_cast<T>(rhs.y2_))
  {
  }

  /**
   * @return true if the two rectangles are equal, false if not
   */
  template<typename T>
  inline bool operator ==(Rectangle2<T> const& lhs, Rectangle2<T> const& rhs)
  {
    return lhs.x1_ == rhs.x1_ && lhs.y1_ == rhs.y1_ &&
           lhs.x2_ == rhs.x2_ && lhs.y2_ == rhs.y2_;
  }

  /**
   * @return true if the two rectangles are not equal, false if they are
   */
  template<typename T>
  inline bool operator !=(Rectangle2<T> const& lhs, Rectangle2<T> const& rhs)
  {
    return !(lhs == rhs);
  }
}


#endif
