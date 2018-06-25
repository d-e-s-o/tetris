// AbstractStone.cpp

/***************************************************************************
 *   Copyright (C) 2013-2014 Daniel Mueller (deso@posteo.net)              *
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

#include <cmath>
#include <util/Assert.hpp>

#include "tetris/game/AbstractStone.hpp"


namespace ttrs
{
  namespace
  {
    double const PI = 3.1415926535897932384626433832795;


    /**
     * @param value angle in degrees
     * @return radian value of given angle
     */
    template<typename T>
    T deg2Rad(T value)
    {
      return static_cast<T>(value * PI * 1.0 / 180.0);
    }

    /**
     * @param poin
     * @param angle
     */
    template<typename T>
    utl::Point<T> rotatePoint(utl::Point<T> const& point, T const& angle)
    {
      // get the distance from origin
      T distance = std::sqrt(point.x * point.x + point.y * point.y);
      ASSERT(distance >= 0);

      if (distance > 0)
      {
        // calculate the angle the stone has currently and add the angle to rotate to the old one
        T new_angle = (point.x < 0 ? -1.0f : 1.0f) * std::acos(point.y / distance) + angle;

        T x = std::sin(new_angle) * distance;
        T y = std::cos(new_angle) * distance;

        return utl::Point<T>(x, y);
      }
      return point;
    }
  }


  /**
   * This function rotates a given piece around the point given during construction either
   * left or right. It takes care about the fact that the GetX and GetY functions of a piece
   * return the position of the lower left corner, not the center of the piece.
   * @param point
   * @param center
   * @param left
   */
  Coordinates rotatePoint(Coordinates const& coordinates, Center const& center, bool left)
  {
    Center p(coordinates.x + 0.5f, coordinates.y + 0.5f);

    p = rotatePoint(p - center, deg2Rad(left ? -90.0f : 90.0f)) + center;

    return Coordinates(static_cast<coordinate_t>(p.x - 0.5f),
                       static_cast<coordinate_t>(p.y - 0.5f));
  }
}
