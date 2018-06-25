// NearestNeighbour.hpp

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

#ifndef IMGNEARESTNEIGHBOUR_HPP
#define IMGNEARESTNEIGHBOUR_HPP

#include <util/Assert.hpp>


namespace img
{
  /**
   * This class represents the so called Nearest Neighbour filtering method. That is probably the
   * simplest existing filter. It simply chooses the nearest source pixel for the destination and
   * uses that.
   */
  class LIBIMAGE_EXPORT NearestNeighbour
  {
  public:
    template<typename PixelT>
    void operator ()(Image<PixelT> const& src, Image<PixelT>& dst) const;
  };
}


namespace img
{
  /**
   * @copydoc FilterBase::Scale
   */
  template<typename PixelT>
  void NearestNeighbour::operator ()(Image<PixelT> const& src, Image<PixelT>& dst) const
  {
    float w_ratio = 1.0f * src.width()  / dst.width();
    float h_ratio = 1.0f * src.height() / dst.height();

    for (Size y = 0; y < dst.height(); ++y)
    {
      PixelT const* src_line = src.scanline(static_cast<int>(y * h_ratio));
      PixelT*       dst_line = dst.scanline(y);
      ASSERTOP(src_line != 0 && dst_line, ne, 0);

      for (Size x = 0; x < dst.width(); ++x)
        dst_line[x] = src_line[static_cast<int>(x * w_ratio)];
    }
  }
}


#endif
