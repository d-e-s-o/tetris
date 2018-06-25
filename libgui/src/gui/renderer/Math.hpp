// Math.hpp

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

#ifndef GUIMATH_HPP
#define GUIMATH_HPP

#include <cmath>
#include <limits>


namespace gui
{
  template<typename T>
  T log2(T n);

  template<typename T>
  bool isPowerOfTwo(T n);

  template<typename T>
  T nextPowerOfTwo(T n);
}

namespace gui
{
  /**
   * @param n number to get exponent that if raised to two will be the given number
   * @return exponent which if raised two by it will give the given number
   */
  template<typename T>
  inline T log2(T n)
  {
    return static_cast<T>(std::log10(1.0 * n) / std::log10(2.0));
  }

  /**
   * @param n number to check if it is a power of two
   * @return true if it is a power of two, false if not
   */
  template<typename T>
  inline bool isPowerOfTwo(T n)
  {
    double exponent = log2(1.0f * n);

    return std::abs(exponent - std::floor(exponent)) <= std::numeric_limits<double>::epsilon();
  }

  /**
   * @param n number to get next power of two of
   * @return next power of two following the given number
   */
  template<typename T>
  inline T nextPowerOfTwo(T n)
  {
    if (n == 0)
      return 1;

    double exponent = log2(n);

    return static_cast<T>(std::pow(2.0, std::floor(exponent) + 1.0));
  }
}


#endif
