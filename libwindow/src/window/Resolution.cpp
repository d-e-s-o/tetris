// Resolution.cpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#include <iostream>

#include "window/Resolution.hpp"


namespace wnd
{
  /**
   * @param width horizontal resolution
   * @param height vertical resolution
   * @param color_depth color depth in bits
   * @param refresh_rate refresh rate in hertz
   */
  Resolution::Resolution(dimension_t width, dimension_t height, int color_depth, int refresh_rate)
    : width_(width),
      height_(height),
      color_depth_(color_depth),
      refresh_rate_(refresh_rate)
  {
    //ASSERT(color_depth_, gt, 0);
    //ASSERT(color_depth_, le, 32);
    //ASSERT(refresh_rate_, ge, 50);
    //ASSERT(refresh_rate_, lt, 200);
  }

  /**
   * @param lhs first resolution to compare to second
   * @param rhs second resolution to compare to first
   * @return true if the two resultions are equal, false otherwise
   */
  bool operator ==(Resolution const& lhs, Resolution const& rhs)
  {
    return lhs.width()       == rhs.width() &&
           lhs.height()      == rhs.height() &&
           lhs.colorDepth()  == rhs.colorDepth() &&
           lhs.refreshRate() == rhs.refreshRate();
  }

  /**
   * @param lhs
   * @param rhs
   * @return
   */
  bool operator !=(Resolution const& lhs, Resolution const& rhs)
  {
    return !(lhs == rhs);
  }

  /**
   * @param lhs first resolution to compare to second
   * @param rhs second resolution to compare to first
   * @return true if first resolution is less than second, false otherwise
   * @note less in this case means first the width is checked, then the height, next the color
   *       depth and last the refresh rate
   */
  bool operator <(Resolution const& lhs, Resolution const& rhs)
  {
    dimension_t w1 = lhs.width();
    dimension_t w2 = rhs.width();
    dimension_t h1 = lhs.height();
    dimension_t h2 = rhs.height();
    int         c1 = lhs.colorDepth();
    int         c2 = rhs.colorDepth();
    int         r1 = lhs.refreshRate();
    int         r2 = rhs.refreshRate();

    return w1 < w2 ||
           w1 == w2 && h1 < h2 ||
           w1 == w2 && h1 == h2 && c1 < c2 ||
           w1 == w2 && h1 == h2 && c1 == c2 && r1 < r2;
  }

  /**
   * @param lhs stream to print resolution to
   * @param rhs resolution to print to stream
   * @return stream used for output
   */
  std::ostream& operator <<(std::ostream& lhs, Resolution const& rhs)
  {
    lhs << rhs.width() << 'x'
        << rhs.height() << 'x'
        << rhs.colorDepth() << '@'
        << rhs.refreshRate();

    return lhs;
  }
}
