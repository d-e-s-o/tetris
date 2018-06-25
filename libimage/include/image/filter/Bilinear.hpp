// Bilinear.hpp

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

#ifndef IMGBILINEAR_HPP
#define IMGBILINEAR_HPP

#include <util/Assert.hpp>

#include "image/filter/Average.hpp"


namespace img
{
  /**
   * This class represents the bilinear filtering method. It first calculates the exact position of
   * a point thats colour should be taken (by linear interpolation) and then takes the closest four
   * pixels to this point and calculates the average color (it is a bit more, but too complicated to
   * explain...at least with my English skills :P).
   * @todo in case of shrink_src_ true there may be a bug, because the most right line still looks a
   *       bit different in some images (however only CalculateAllValues is called...)
   * @todo it seems, like I cannot export this class if it has a constructor (linker error if it is
   *       inline, warning if not). Find out why!  (same goes for NearestNeighbour...)
   */
  class Bilinear
  {
  public:
    bilinear(bool shrink_src = false);

    template<typename PixelT>
    void operator ()(Image<PixelT> const& src, Image<PixelT>& dst) const;

  private:
    bool shrink_src_;

    template<typename PixelT>
    void calculatePixel(Image<PixelT> const& src, float x_pos, float y_pos, PixelT& average) const;

    template<typename PixelT>
    PixelT calculateAllValues(Image<PixelT> const& src, Size x, Size y, float frac_u, float frac_v) const;

    template<typename PixelT>
    PixelT calculateHorizontalValues(Image<PixelT> const& src, Size x, Size y, float frac_u) const;

    template<typename PixelT>
    PixelT calculateVerticalValues(Image<PixelT> const& src, Size x, Size y, float frac_v) const;

    template<typename PixelT>
    PixelT calculateOneValue(Image<PixelT> const& src, Size x, Size y) const;
  };
}


namespace img
{
  /**
   * @param shrink_src on true the source image will be treated as if it was
   *        one line smaller and lower. This can lead to better results with
   *        special images.
   */
  inline Bilinear::bilinear(bool shrink_src)
    : shrink_src_(shrink_src)
  {
  }

  /**
   * @copydoc FilterBase::Scale
   */
  template<typename PixelT>
  void Bilinear::operator ()(Image<PixelT> const& src, Image<PixelT>& dst) const
  {
    int sub = (shrink_src_ ? 1 : 0);

    float w_ratio = 1.0f * (src.width()  - sub) / dst.width();
    float h_ratio = 1.0f * (src.height() - sub) / dst.height();

    for (Size y = 0; y < dst.height(); ++y)
    {
      float y_pos = y * h_ratio;

      PixelT const* src_line = src.scanline(static_cast<int>(y_pos));
      PixelT*       dst_line = dst.scanline(y);
      assert(src_line != 0 && dst_line != 0);

      for (Size x = 0; x < dst.width(); ++x)
      {
        float x_pos = x * w_ratio;
        calculatePixel(src, x_pos, y_pos, dst_line[x]);
      }
    }
  }

  /**
   * This method calculates the average color of a pixel by taking the colors
   * of the three neighbours.
   * @param src image to calculate average pixel color from
   * @param x x position of first pixel
   * @param y y position of first pixel
   */
  template<typename PixelT>
  void Bilinear::calculatePixel(Image<PixelT> const& src, float x, float y, PixelT& average) const
  {
    assert(x >= 0 && x < src.width());
    assert(y >= 0 && y < src.height());

    Size x1 = static_cast<Size>(x);
    Size y1 = static_cast<Size>(y);
    float frac_u = x - x1;
    float frac_v = y - y1;

    if (x + 1 < src.width())
    {
      if (y + 1 < src.height())
        average = calculateAllValues(src, x1, y1, frac_u, frac_v);
      else
        average = calculateHorizontalValues(src, x1, y1, frac_u);
    }
    else if (y + 1 < src.height())
      average = calculateVerticalValues(src, x1, y1, frac_v);
    else
      average = calculateOneValue(src, x1, y1);
  }

  template<typename PixelT>
  PixelT Bilinear::calculateAllValues(Image<PixelT> const& src, Size x, Size y, float frac_u, float frac_v) const
  {
    PixelT const* line1 = src.scanline(y);
    PixelT const* line2 = src.scanline(y + 1);

    PixelT const& ul = line1[x];
    PixelT const& ur = line1[x + 1];
    PixelT const& ll = line2[x];
    PixelT const& lr = line2[x + 1];

    float ul_ratio = (1.0f - frac_u) * (1.0f - frac_v);
    float ur_ratio = frac_u * (1.0f - frac_v);
    float ll_ratio = (1.0f - frac_u) * frac_v;
    float lr_ratio = frac_u * frac_v;

    return average(ul, ul_ratio, ur, ur_ratio, ll, ll_ratio, lr, lr_ratio);
  }

  template<typename PixelT>
  PixelT Bilinear::calculateHorizontalValues(Image<PixelT> const& src, Size x, Size y, float frac_u) const
  {
    PixelT const* line1 = src.scanline(y);

    PixelT const& ul = line1[x];
    PixelT const& ur = line1[x + 1];

    float ul_ratio = (1.0f - frac_u);
    float ur_ratio = frac_u;

    return average(ul, ul_ratio, ur, ur_ratio);
  }

  template<typename PixelT>
  PixelT Bilinear::calculateVerticalValues(Image<PixelT> const& src, Size x, Size y, float frac_v) const
  {
    PixelT const* line1 = src.scanline(y);
    PixelT const* line2 = src.scanline(y + 1);

    PixelT const& ul = line1[x];
    PixelT const& ll = line2[x];

    float ul_ratio = (1.0f - frac_v);
    float ll_ratio = frac_v;

    return average(ul, ul_ratio, ll, ll_ratio);
  }

  template<typename PixelT>
  PixelT Bilinear::calculateOneValue(Image<PixelT> const& src, Size x, Size y) const
  {
    PixelT const* line1 = src.scanline(y);
    return line1[x];
  }
}


#endif
