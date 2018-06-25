// Color.hpp

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

#ifndef UTLCOLOR_HPP
#define UTLCOLOR_HPP

#include "util/Config.hpp"


namespace utl
{
  /**
   *
   */
  template<typename T>
  struct ColorTrait
  {
    static T const min;
    static T const max;
  };


  /**
   * This class represents an RGB(A) color.
   * @note colors are copyable
   */
  template<typename T>
  class Color
  {
  public:
    typedef T ChannelType;

    static T min();
    static T max();

    explicit Color(T r = ColorTrait<T>::min, T g = ColorTrait<T>::min, T b = ColorTrait<T>::min, T a = ColorTrait<T>::max);

    T getRed() const;
    void setRed(T r);

    T getGreen() const;
    void setGreen(T g);

    T getBlue() const;
    void setBlue(T b);

    T getAlpha() const;
    void setAlpha(T a);

    Color const& operator +=(Color const& rhs);
    Color const& operator -=(Color const& rhs);

  private:
    T color_[4];

    T validate(T value) const;

    T add(T t1, T t2) const;
    T sub(T t1, T t2) const;
  };


  template<typename T>
  Color<T> const operator +(Color<T> const& lhs, Color<T> const& rhs);

  template<typename T>
  Color<T> const operator -(Color<T> const& lhs, Color<T> const& rhs);

  template<typename T>
  bool operator ==(Color<T> const& lhs, Color<T> const& rhs);

  template<typename T>
  bool operator !=(Color<T> const& lhs, Color<T> const& rhs);

  template<typename T>
  bool operator <(Color<T> const& lhs, Color<T> const& rhs);

  template<typename T>
  bool operator >(Color<T> const& lhs, Color<T> const& rhs);

  template<typename T>
  bool operator <=(Color<T> const& lhs, Color<T> const& rhs);

  template<typename T>
  bool operator >=(Color<T> const& lhs, Color<T> const& rhs);
}


namespace utl
{
  /**
   * @return the minimum value a color channel may have
   */
  template<typename T>
  inline T Color<T>::min()
  {
    return ColorTrait<T>::min;
  }

  /**
   * @return the maximum value a color channel may have
   */
  template<typename T>
  inline T Color<T>::max()
  {
    return ColorTrait<T>::max;
  }

  /**
   * The default constructor creates an color object from the given values.
   * @param[in] red value for red channel
   * @param[in] green value for green channel
   * @param[in] blue value for blue channel
   * @param[in] alpha value for alpha channel
   */
  template<typename T>
  inline Color<T>::Color(T red, T green, T blue, T alpha)
  {
    color_[0] = validate(red);
    color_[1] = validate(green);
    color_[2] = validate(blue);
    color_[3] = validate(alpha);
  }

  /**
   * @return value of red channel
   */
  template<typename T>
  inline T Color<T>::getRed() const
  {
    return color_[0];
  }

  /**
   * @param r value of red channel
   */
  template<typename T>
  inline void Color<T>::setRed(T r)
  {
    color_[0] = validate(r);
  }

  /**
   * @return value of green channel
   */
  template<typename T>
  inline T Color<T>::getGreen() const
  {
    return color_[1];
  }

  /**
   * @param g value of green channel
   */
  template<typename T>
  inline void Color<T>::setGreen(T g)
  {
    color_[1] = validate(g);
  }

  /**
   * @return value of blue channel
   */
  template<typename T>
  inline T Color<T>::getBlue() const
  {
    return color_[2];
  }

  /**
   * @param b value of blue channel
   */
  template<typename T>
  inline void Color<T>::setBlue(T b)
  {
    color_[2] = validate(b);
  }

  /**
   * @return value of alpha channel
   */
  template<typename T>
  inline T Color<T>::getAlpha() const
  {
    return color_[3];
  }

  /**
   * @param a value of alpha channel
   */
  template<typename T>
  inline void Color<T>::setAlpha(T a)
  {
    color_[3] = validate(a);
  }

  template<typename T>
  inline Color<T> const& Color<T>::operator +=(Color<T> const& rhs)
  {
    color_[0] = add(color_[0], rhs.color_[0]);
    color_[1] = add(color_[1], rhs.color_[1]);
    color_[2] = add(color_[2], rhs.color_[2]);
    color_[3] = add(color_[3], rhs.color_[3]);

    return *this;
  }

  template<typename T>
  inline Color<T> const& Color<T>::operator -=(Color<T> const& rhs)
  {
    color_[0] = sub(color_[0], rhs.color_[0]);
    color_[1] = sub(color_[1], rhs.color_[1]);
    color_[2] = sub(color_[2], rhs.color_[2]);
    color_[3] = sub(color_[3], rhs.color_[3]);

    return *this;
  }

  /**
   * This method validates the color value by checking for the min and max
   * value and correcting it if necessary.
   * @param value value to correct
   * @return corrected value or same as value if not out of bounds
   */
  template<typename T>
  inline T Color<T>::validate(T value) const
  {
    if (value < ColorTrait<T>::min)
      return ColorTrait<T>::min;
    if (value > ColorTrait<T>::max)
      return ColorTrait<T>::max;
    else
      return value;
  }

  template<typename T>
  inline T Color<T>::add(T t1, T t2) const
  {
    if (t1 + t2 > ColorTrait<T>::max)
      return ColorTrait<T>::max;

    return t1 + t2;
  }

  template<typename T>
  inline T Color<T>::sub(T t1, T t2) const
  {
    if (t1 - t2 < ColorTrait<T>::min)
      return ColorTrait<T>::min;

    return t1 - t2;
  }

  template<typename T>
  inline Color<T> const operator +(Color<T> const& lhs, Color<T> const& rhs)
  {
    Color<T> c(lhs);
    return c += rhs;
  }

  template<typename T>
  inline Color<T> const operator -(Color<T> const& lhs, Color<T> const& rhs)
  {
    Color<T> c(lhs);
    return c -= rhs;
  }

  /**
   * @return true if the two colors are equal, false if not
   * @todo this will not always work for floats (because comparing those
   *       for equality with == is really bad) - fix it!
   */
  template<typename T>
  inline bool operator ==(Color<T> const& lhs, Color<T> const& rhs)
  {
    return lhs.getRed()   == rhs.getRed() &&
           lhs.getGreen() == rhs.getGreen() &&
           lhs.getBlue()  == rhs.getBlue() &&
           lhs.getAlpha() == rhs.getAlpha();
  }

  /**
   * @return true if the two colors are different, false if they are equal
   */
  template<typename T>
  inline bool operator !=(Color<T> const& lhs, Color<T> const& rhs)
  {
    return !(lhs == rhs);
  }

  /**
   * @return true if the first color is less than the second
   */
  template<typename T>
  bool operator <(Color<T> const& lhs, Color<T> const& rhs)
  {
    if (lhs.getRed() < rhs.getRed())
      return true;

    if (lhs.getRed() == rhs.getRed())
    {
      if (lhs.getGreen() < rhs.getGreen())
        return true;

      if (lhs.getGreen() == rhs.getGreen())
      {
        if (lhs.getBlue() < rhs.getBlue())
          return true;

        if (lhs.getBlue() == rhs.getBlue())
        {
          if (lhs.getAlpha() < rhs.getAlpha())
            return true;
        }
      }
    }
    return false;
  }

  template<typename T>
  inline bool operator >(Color<T> const& lhs, Color<T> const& rhs)
  {
    return !(lhs <= rhs);
  }

  template<typename T>
  inline bool operator <=(Color<T> const& lhs, Color<T> const& rhs)
  {
    return lhs < rhs || lhs == rhs;
  }

  template<typename T>
  inline bool operator >=(Color<T> const& lhs, Color<T> const& rhs)
  {
    return !(lhs < rhs);
  }
}


#endif
