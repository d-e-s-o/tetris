// Vector2D.hpp

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

#ifndef UTLVECTOR2D_HPP
#define UTLVECTOR2D_HPP


namespace utl
{
  /**
   * This class template represents a vector in 2D space.
   */
  template<typename T>
  class Vector2D
  {
  public:
    explicit Vector2D(T x = T(), T y = T());

    Vector2D<T> const& operator +=(Vector2D<T> const& rhs);
    Vector2D<T> const& operator -=(Vector2D<T> const& rhs);
    Vector2D<T> const& operator *=(T rhs);
    Vector2D<T> const& operator /=(T rhs);
    Vector2D<T> const  operator -() const;

    T x;
    T y;
  };


  template<typename T>
  bool operator ==(Vector2D<T> const& lhs, Vector2D<T> const& rhs);

  template<typename T>
  bool operator !=(Vector2D<T> const& lhs, Vector2D<T> const& rhs);

  template<typename T>
  Vector2D<T> const operator +(Vector2D<T> const& lhs, Vector2D<T> const& rhs);

  template<typename T>
  Vector2D<T> const operator -(Vector2D<T> const& lhs, Vector2D<T> const& rhs);

  template<typename T>
  Vector2D<T> const operator *(Vector2D<T> const& lhs, T rhs);

  template<typename T>
  Vector2D<T> const operator / (Vector2D<T> const& lhs, T rhs);

  template<typename T>
  T operator *(Vector2D<T> const& lhs, Vector2D<T> const& rhs);
}


namespace utl
{
  template<typename T>
  inline Vector2D<T>::Vector2D(T x, T y)
    : x(x),
      y(y)
  {
  }

  template<typename T>
  inline Vector2D<T> const& Vector2D<T>::operator +=(Vector2D<T> const& rhs)
  {
    x += rhs.x;
    y += rhs.y;

    return *this;
  }

  template<typename T>
  inline Vector2D<T> const& Vector2D<T>::operator -=(Vector2D<T> const& rhs)
  {
    return *this += -rhs;
  }

  template<typename T>
  inline Vector2D<T> const& Vector2D<T>::operator *=(T rhs)
  {
    x *= rhs;
    y *= rhs;

    return *this;
  }

  template<typename T>
  inline Vector2D<T> const& Vector2D<T>::operator /=(T rhs)
  {
    x /= rhs;
    y /= rhs;

    return *this;
  }

  template<typename T>
  inline Vector2D<T> const Vector2D<T>::operator -() const
  {
    return Vector2D<T>(-x, -y);
  }

  template<typename T>
  inline bool operator ==(Vector2D<T> const& lhs, Vector2D<T> const& rhs)
  {
    return lhs.x == rhs.x &&
           lhs.y == rhs.y;
  }

  template<typename T>
  inline bool operator !=(Vector2D<T> const& lhs, Vector2D<T> const& rhs)
  {
    return !(lhs == rhs);
  }

  template<typename T>
  inline Vector2D<T> const operator +(Vector2D<T> const& lhs, Vector2D<T> const& rhs)
  {
    return Vector2D<T>(lhs) += rhs;
  }

  template<typename T>
  inline Vector2D<T> const operator -(Vector2D<T> const& lhs, Vector2D<T> const& rhs)
  {
    return Vector2D<T>(lhs) -= rhs;
  }

  template<typename T>
  inline Vector2D<T> const operator *(Vector2D<T> const& lhs, T rhs)
  {
    return Vector2D<T>(lhs) *= rhs;
  }

  template<typename T>
  inline Vector2D<T> const operator / (Vector2D<T> const& lhs, T rhs)
  {
    return Vector2D<T>(lhs) /= rhs;
  }

  template<typename T>
  inline T operator *(Vector2D<T> const& lhs, Vector2D<T> const& rhs)
  {
    return (lhs.x * rhs.x) + (lhs.y * rhs.y);
  }
}


#endif
