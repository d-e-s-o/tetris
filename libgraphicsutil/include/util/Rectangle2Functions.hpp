// Rectangle2Functions.hpp

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

#ifndef UTLRECTANGLE2FUNCTIONS_HPP
#define UTLRECTANGLE2FUNCTIONS_HPP

#include "util/Point.hpp"
#include "util/Rectangle2.hpp"


namespace utl
{
  template<typename T>
  bool contains(Rectangle2<T> const& r, Point<T> const& p);

  template<typename T>
  Rectangle2<T> getRectangle(Point<T> const& p1, Point<T> const& p2);

  template<typename T>
  void move(Rectangle2<T>& r, Point<T> const& position);
}


namespace utl
{
  /**
   * @param[in] p that should be checked if it inside the rect area
   * @return true if the point is in the rectangle (including the edges), false if not
   */
  template<typename T>
  inline bool contains(Rectangle2<T> const& r, Point<T> const& p)
  {
    return p.x >= r.x1_ && p.x <= r.x2_ && p.y >= r.y1_ && p.y <= r.y2_;
  }

  /**
   * @param first point of the rectangle
   * @param second point of the rectangle
   * @return rectangle consisting of the two given points
   */
  template<typename T>
  inline Rectangle2<T> getRectangle(Point<T> const& p1, Point<T> const& p2)
  {
    return Rectangle2<T>(p1.x, p1.y, p2.x, p2.y);
  }

  /**
   * @param[in,out] r rectangle to move by the given position
   * @param[in] p position to move the rectangle by (that means both points)
   */
  template<typename T>
  inline void move(Rectangle2<T>& r, Point<T> const& p)
  {
    r.x1_ += p.x;
    r.y1_ += p.y;
    r.x2_ += p.x;
    r.y2_ += p.y;
  }
}


#endif
