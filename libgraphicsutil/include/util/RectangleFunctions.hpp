// RectangleFunctions.hpp

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

#ifndef UTLRECTANGLEFUNCTIONS_HPP
#define UTLRECTANGLEFUNCTIONS_HPP

#include "util/Rectangle1.hpp"
#include "util/Rectangle2.hpp"


namespace utl
{
  template<typename T, typename U>
  Rectangle2<T> convert(Rectangle1<T, U> const& r);

  template<typename T, typename U>
  Rectangle1<T, U> convert(Rectangle2<T> const& r);
}


namespace utl
{
  template<typename T, typename U>
  Rectangle2<T> convert(Rectangle1<T, U> const& r)
  {
    return Rectangle2<T>(r.x, r.y, r.x + r.w, r.y + r.h);
  }

  template<typename T, typename U>
  Rectangle1<T, U> convert(Rectangle2<T> const& r)
  {
    return Rectangle1<T, U>(r.x1_, r.y1, r.x2_ - r.x1_, r.y2_ - r.y1_);
  }
}


#endif
