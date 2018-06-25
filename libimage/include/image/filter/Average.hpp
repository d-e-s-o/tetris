// Average.hpp

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

#ifndef IMGAVERAGE_HPP
#define IMGAVERAGE_HPP

#include "image/Pixel.hpp"


namespace img
{
  template<typename PixelT>
  PixelT average(PixelT const& p1, float p1_ratio, PixelT const& p2, float p2_ratio);

  template<typename PixelT>
  PixelT average(PixelT const& p1, float p1_ratio,
                 PixelT const& p2, float p2_ratio,
                 PixelT const& p3, float p3_ratio,
                 PixelT const& p4, float p4_ratio);
}


namespace img
{
  template<typename T>
  inline T weightedAverage(T v1, float v1_ratio, T v2, float v2_ratio)
  {
    return static_cast<T>(v1 * v1_ratio + v2 * v2_ratio);
  }

  template<typename T>
  inline T weightedAverage(T v1, float v1_ratio, T v2, float v2_ratio,
                           T v3, float v3_ratio, T v4, float v4_ratio)
  {
    return static_cast<T>(v1 * v1_ratio + v2 * v2_ratio + v3 * v3_ratio + v4 * v4_ratio);
  }

  template<>
  inline PixelUByteRGB average(PixelUByteRGB const& p1, float p1_ratio,
                               PixelUByteRGB const& p2, float p2_ratio)
  {
    PixelUByteRGB result;
    result.r = weightedAverage(p1.r, p1_ratio, p2.r, p2_ratio);
    result.g = weightedAverage(p1.g, p1_ratio, p2.g, p2_ratio);
    result.b = weightedAverage(p1.b, p1_ratio, p2.b, p2_ratio);

    return result;
  }

  template<>
  inline PixelUByteRGB average(PixelUByteRGB const& p1, float p1_ratio,
                               PixelUByteRGB const& p2, float p2_ratio,
                               PixelUByteRGB const& p3, float p3_ratio,
                               PixelUByteRGB const& p4, float p4_ratio)
  {
    PixelUByteRGB result;
    result.r = weightedAverage(p1.r, p1_ratio, p2.r, p2_ratio, p3.r, p3_ratio, p4.r, p4_ratio);
    result.g = weightedAverage(p1.g, p1_ratio, p2.g, p2_ratio, p3.g, p3_ratio, p4.g, p4_ratio);
    result.b = weightedAverage(p1.b, p1_ratio, p2.b, p2_ratio, p3.b, p3_ratio, p4.b, p4_ratio);

    return result;
  }
}


#endif
