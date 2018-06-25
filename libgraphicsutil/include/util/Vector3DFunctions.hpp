// Vector3DFunctions.hpp

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

#ifndef UTLVECTOR3DFUNCTIONS_HPP
#define UTLVECTOR3DFUNCTIONS_HPP

#include "util/Vector3D.hpp"
#include "util/VectorFunctions.hpp"


namespace utl
{
  template<typename T>
  T lengthSquare(Vector3D<T> const& vector);
}


namespace utl
{
  /**
   * @param vector vector to calculate square of length from
   * @return square of length of vector
   */
  template<typename T>
  T lengthSquare(Vector3D<T> const& vector)
  {
    return (vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z);
  }
}


#endif
