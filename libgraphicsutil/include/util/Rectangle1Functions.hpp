// Rectangle1Functions.hpp

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

#ifndef UTLRECTANGLE1FUNCTIONS_HPP
#define UTLRECTANGLE1FUNCTIONS_HPP

#include "util/Point.hpp"
#include "util/Rectangle1.hpp"


namespace utl
{
  template<typename T, typename U>
  bool contains(Rectangle1<T, U> const& r, Point<T> const& p);

  template<typename T, typename U>
  Rectangle1<T, U> getRectangle(Point<T> const& p, Point<U> const& s);

  template<typename T, typename U>
  void setPosition(Rectangle1<T, U>& r, Point<T> const& position);

  template<typename T, typename U>
  void move(Rectangle1<T, U>& r, Point<T> const& position);

  template<typename T, typename U>
  void setSize(Rectangle1<T, U>& r, Point<U> const& size);

  template<typename T, typename U>
  void grow(Rectangle1<T, U>& r, Point<U> const& size);

  template<typename T, typename U>
  Point<T> getPosition(Rectangle1<T, U> const& r);

  template<typename T, typename U>
  Point<U> getSize(Rectangle1<T, U> const& r);
}


namespace utl
{
  /**
   * @param[in] point that should be checked if it inside the rectangle area
   * @return true if the point is in the rect (including the edges), false if not
   */
  template<typename T, typename U>
  inline bool contains(Rectangle1<T, U> const& r, Point<T> const& p)
  {
    // it is important to cast to signed value if position type is signed but size type is not
    return p.x >= r.x && p.x <= r.x + static_cast<T>(r.w) &&
           p.y >= r.y && p.y <= r.y + static_cast<T>(r.h);
  }

  template<typename T, typename U>
  inline Rectangle1<T, U> getRectangle(Point<T> const& p, Point<U> const& s)
  {
    return Rectangle1<T, U>(p.x, p.y, s.x, s.y);
  }

  template<typename T, typename U>
  inline void setPosition(Rectangle1<T, U>& r, Point<T> const& position)
  {
    r.x = position.x;
    r.y = position.y;
  }

  template<typename T, typename U>
  inline void move(Rectangle1<T, U>& r, Point<T> const& position)
  {
    r.x += position.x;
    r.y += position.y;
  }

  template<typename T, typename U>
  inline void setSize(Rectangle1<T, U>& r, Point<U> const& size)
  {
    r.w = size.x;
    r.h = size.y;
  }

  template<typename T, typename U>
  inline void grow(Rectangle1<T, U>& r, Point<U> const& size)
  {
    r.w += size.x;
    r.h += size.y;
  }

  template<typename T, typename U>
  inline Point<T> getPosition(Rectangle1<T, U> const& r)
  {
    return Point<T>(r.x, r.y);
  }

  template<typename T, typename U>
  inline Point<U> getSize(Rectangle1<T, U> const& r)
  {
    return Point<U>(r.w, r.h);
  }
}


#endif
