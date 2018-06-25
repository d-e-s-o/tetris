// Point.hpp

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

#ifndef UTLPOINT_HPP
#define UTLPOINT_HPP


namespace utl
{
  /**
   * This class template represents a simple point in 2D space.
   */
  template<typename T>
  struct Point
  {
  public:
    typedef T Type;

    explicit Point(T const& x = T(), T const& y = T());

    template<typename U>
    explicit Point(Point<U> const& rhs);

    Point const& operator +=(Point const& rhs);
    Point const& operator -=(Point const& rhs);

    Point const operator -() const;

    T x;
    T y;
  };


  template<typename T>
  bool operator ==(Point<T> const& lhs, Point<T> const& rhs);

  template<typename T>
  bool operator !=(Point<T> const& lhs, Point<T> const& rhs);

  template<typename T>
  Point<T> const operator +(Point<T> const& lhs, Point<T> const& rhs);

  template<typename T>
  Point<T> const operator -(Point<T> const& lhs, Point<T> const& rhs);
}


namespace utl
{
  /**
   * @param x x coordinate of the point
   * @param y y coordinate of the point
   */
  template<typename T>
  inline Point<T>::Point(T const& x, T const& y)
    : x(x),
      y(y)
  {
  }

  template<typename T>
  template<typename U>
  inline Point<T>::Point(Point<U> const& rhs)
    : x(static_cast<T>(rhs.x)),
      y(static_cast<T>(rhs.y))
  {
  }

  template<typename T>
  inline Point<T> const& Point<T>::operator +=(Point const& rhs)
  {
    x += rhs.x;
    y += rhs.y;

    return *this;
  }

  template<typename T>
  inline Point<T> const& Point<T>::operator -=(Point const& rhs)
  {
    return *this += -rhs;
  }

  template<typename T>
  inline Point<T> const Point<T>::operator -() const
  {
    return Point(-x, -y);
  }

  template<typename T>
  inline bool operator ==(Point<T> const& lhs, Point<T> const& rhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  template<typename T>
  inline bool operator !=(Point<T> const& lhs, Point<T> const& rhs)
  {
    return !(lhs == rhs);
  }

  template<typename T>
  inline Point<T> const operator +(Point<T> const& lhs, Point<T> const& rhs)
  {
    return Point<T>(lhs) += rhs;
  }

  template<typename T>
  inline Point<T> const operator -(Point<T> const& lhs, Point<T> const& rhs)
  {
    return Point<T>(lhs) -= rhs;
  }
}


#endif
