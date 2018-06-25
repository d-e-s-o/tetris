// VectorFunctions.hpp

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

#ifndef UTLVECTORFUNCTIONS_HPP
#define UTLVECTORFUNCTIONS_HPP

#include <cmath>


namespace utl
{
  template<typename T, template <typename> class VectorT>
  T length(VectorT<T> const& vector);

  template<typename T, template <typename> class VectorT>
  void normalize(VectorT<T>& vector);
}


namespace utl
{
  /**
   * @param vector vector to calculate length from
   * @return length of vector
   * @todo we could create specializations for double and long double and
   *       use sqrt(float) on every other type
   */
  template<typename T, template <typename> class VectorT>
  inline T length(VectorT<T> const& vector)
  {
    float result = std::sqrt(1.0f * lengthSquare(vector));
    return static_cast<T>(result);
  }

  /**
   * @param vector vector to normalize
   */
  template<typename T, template <typename> class VectorT>
  inline void normalize(VectorT<T>& vector)
  {
    vector /= length(vector);
  }
}


#endif
