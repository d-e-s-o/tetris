// ColorFunctions.hpp

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

#ifndef UTLCOLORFUNCTIONS_HPP
#define UTLCOLORFUNCTIONS_HPP

#include "util/Color.hpp"


namespace utl
{
  template<typename T>
  void invert(Color<T>& color);

  template<typename T>
  Color<T> red();

  template<typename T>
  Color<T> green();

  template<typename T>
  Color<T> blue();

  template<typename T>
  Color<T> white();

  template<typename T>
  Color<T> black();

  template<typename T>
  Color<T> yellow();

  template<typename T>
  Color<T> violet();

  template<typename T>
  Color<T> cyan();
}


namespace utl
{
  template<typename T>
  inline void invert(Color<T>& color)
  {
    color.setRed(ColorTrait<T>::max   - color.getRed());
    color.setGreen(ColorTrait<T>::max - color.getGreen());
    color.setBlue(ColorTrait<T>::max  - color.getBlue());
    color.setAlpha(ColorTrait<T>::max - color.getAlpha());
  }

  template<typename T>
  inline Color<T> red()
  {
    return Color<T>(ColorTrait<T>::max, ColorTrait<T>::min, ColorTrait<T>::min);
  }

  template<typename T>
  inline Color<T> green()
  {
    return Color<T>(ColorTrait<T>::min, ColorTrait<T>::max, ColorTrait<T>::min);
  }

  template<typename T>
  inline Color<T> blue()
  {
    return Color<T>(ColorTrait<T>::min, ColorTrait<T>::min, ColorTrait<T>::max);
  }

  template<typename T>
  inline Color<T> white()
  {
    return Color<T>(ColorTrait<T>::max, ColorTrait<T>::max, ColorTrait<T>::max);
  }

  template<typename T>
  inline Color<T> black()
  {
    return Color<T>(ColorTrait<T>::min, ColorTrait<T>::min, ColorTrait<T>::min);
  }

  template<typename T>
  inline Color<T> yellow()
  {
    return red<T>() + green<T>();
  }

  template<typename T>
  inline Color<T> violet()
  {
    return red<T>() + blue<T>();
  }

  template<typename T>
  inline Color<T> cyan()
  {
    return green<T>() + blue<T>();
  }
}


#endif
