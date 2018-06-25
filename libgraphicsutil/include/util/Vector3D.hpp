// Vector3D.hpp

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

#ifndef UTLVECTOR3D_HPP
#define UTLVECTOR3D_HPP


namespace utl
{
  /**
   * This class template represents a vector in 3D space.
   */
  template<typename T>
  class Vector3D
  {
  public:
    explicit Vector3D(T x = T(), T y = T(), T z = T());

    Vector3D<T> const& operator +=(Vector3D<T> const& rhs);
    Vector3D<T> const& operator -=(Vector3D<T> const& rhs);
    Vector3D<T> const& operator *=(T rhs);
    Vector3D<T> const& operator /=(T rhs);
    Vector3D<T> const& operator %= (Vector3D<T> const& rhs);
    Vector3D<T> const  operator -() const;

    T x;
    T y;
    T z;
  };

  template<typename T>
  bool operator ==(Vector3D<T> const& lhs, Vector3D<T> const& rhs);

  template<typename T>
  bool operator !=(Vector3D<T> const& lhs, Vector3D<T> const& rhs);

  template<typename T>
  Vector3D<T> const operator +(Vector3D<T> const& lhs, Vector3D<T> const& rhs);

  template<typename T>
  Vector3D<T> const operator -(Vector3D<T> const& lhs, Vector3D<T> const& rhs);

  template<typename T>
  Vector3D<T> const operator *(Vector3D<T> const& lhs, T rhs);

  template<typename T>
  Vector3D<T> const operator / (Vector3D<T> const& lhs, T rhs);

  template<typename T>
  Vector3D<T> const operator % (Vector3D<T> const& lhs, Vector3D<T> const& rhs);

  template<typename T>
  T operator *(Vector3D<T> const& lhs, Vector3D<T> const& rhs);
}


namespace utl
{
  template<typename T>
  inline Vector3D<T>::Vector3D(T x, T y, T z)
    : x(x),
      y(y),
      z(z)
  {
  }

  template<typename T>
  inline Vector3D<T> const& Vector3D<T>::operator +=(Vector3D<T> const& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;

    return *this;
  }

  template<typename T>
  inline Vector3D<T> const& Vector3D<T>::operator -=(Vector3D<T> const& rhs)
  {
    return *this += -rhs;
  }

  /**
   * This operator is used for multiplying the vector with a scalar value.
   */
  template<typename T>
  inline Vector3D<T> const& Vector3D<T>::operator *=(T rhs)
  {
    x *= rhs;
    y *= rhs;
    z *= rhs;

    return *this;
  }

  template<typename T>
  inline Vector3D<T> const& Vector3D<T>::operator /=(T rhs)
  {
    x /= rhs;
    y /= rhs;
    z /= rhs;

    return *this;
  }

  /**
   * This operator represents the cross product for vectores.
   */
  template<typename T>
  inline Vector3D<T> const& Vector3D<T>::operator %= (Vector3D<T> const& rhs)
  {
    T xx = x;
    T yy = y;
    T zz = z;

    x = (yy * rhs.z) - (zz * rhs.y);
    y = (zz * rhs.x) - (xx * rhs.z);
    z = (xx * rhs.y) - (yy * rhs.x);

    return *this;
  }

  template<typename T>
  inline Vector3D<T> const Vector3D<T>::operator -() const
  {
    return Vector3D<T>(-x, -y, -z);
  }

  template<typename T>
  inline bool operator ==(Vector3D<T> const& lhs, Vector3D<T> const& rhs)
  {
    return lhs.x == rhs.x &&
           lhs.y == rhs.y &&
           lhs.z == rhs.z;
  }

  template<typename T>
  inline bool operator !=(Vector3D<T> const& lhs, Vector3D<T> const& rhs)
  {
    return !(lhs == rhs);
  }

  template<typename T>
  inline Vector3D<T> const operator +(Vector3D<T> const& lhs, Vector3D<T> const& rhs)
  {
    return Vector3D<T>(lhs) += rhs;
  }

  template<typename T>
  inline Vector3D<T> const operator -(Vector3D<T> const& lhs, Vector3D<T> const& rhs)
  {
    return Vector3D<T>(lhs) -= rhs;
  }

  template<typename T>
  inline Vector3D<T> const operator *(Vector3D<T> const& lhs, T rhs)
  {
    return Vector3D<T>(lhs) *= rhs;
  }

  template<typename T>
  inline Vector3D<T> const operator / (Vector3D<T> const& lhs, T rhs)
  {
    return Vector3D<T>(lhs) /= rhs;
  }

  template<typename T>
  inline Vector3D<T> const operator % (Vector3D<T> const& lhs, Vector3D<T> const& rhs)
  {
    return Vector3D<T>(lhs) %= rhs;
  }

  template<typename T>
  inline T operator *(Vector3D<T> const& lhs, Vector3D<T> const& rhs)
  {
    return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
  }
}


#endif
