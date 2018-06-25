// RendererFunctions.hpp

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

#ifndef GUIRENDERERFUNCTIONS_HPP
#define GUIRENDERERFUNCTIONS_HPP

#include <util/Assert.hpp>

#include "gui/renderer/Rectangle.hpp"


namespace gui
{
  bool clipRectangle(Rectangle const& clipper, Rectangle& to_clip);
  bool clipRectangle(Rectangle const& clipper, Rectangle& to_clip, TextureRectangle& tex_coords);
}


namespace gui
{
  /**
   * This clipper does nothing.
   */
  template<bool X, bool First, typename T>
  struct EmptyClipper
  {
    void operator()(Rectangle const& clipper, Rectangle const& to_clip, T dummy) const
    {
      // do nothing
    }
  };

  /**
   * This clipper is meant to be passed texture coordinates (that ones with normal range 0..1)
   * that will be clipped in ratio to the removed pixels.
   */
  template<bool X, bool First, typename T>
  struct RatioClipper;

  template<typename T>
  struct RatioClipper<true, true, T>
  {
    void operator()(Rectangle const& clipper, Rectangle const& to_clip, T tex_coords) const
    {
      Rectangle::Type new_dif = to_clip.x2_ - clipper.x1_;
      Rectangle::Type old_dif = to_clip.x2_ - to_clip.x1_;

      TextureRectangle::Type tex_dif = tex_coords.x2_ - tex_coords.x1_;
      TextureRectangle::Type ratio   = 1.0f * new_dif / old_dif;

      tex_coords.x1_ = tex_coords.x2_ - tex_dif * ratio;
    }
  };

  template<typename T>
  struct RatioClipper<false, true, T>
  {
    void operator()(Rectangle const& clipper, Rectangle const& to_clip, T tex_coords) const
    {
      Rectangle::Type new_dif = to_clip.y2_ - clipper.y1_;
      Rectangle::Type old_dif = to_clip.y2_ - to_clip.y1_;

      TextureRectangle::Type tex_dif = tex_coords.y2_ - tex_coords.y1_;
      TextureRectangle::Type ratio   = 1.0f * new_dif / old_dif;

      tex_coords.y1_ = tex_coords.y2_ - tex_dif * ratio;
    }
  };

  template<typename T>
  struct RatioClipper<true, false, T>
  {
    void operator()(Rectangle const& clipper, Rectangle const& to_clip, T tex_coords) const
    {
      Rectangle::Type new_dif = to_clip.x1_ - clipper.x2_;
      Rectangle::Type old_dif = to_clip.x1_ - to_clip.x2_;

      TextureRectangle::Type tex_dif = tex_coords.x2_ - tex_coords.x1_;
      TextureRectangle::Type ratio   = 1.0f * new_dif / old_dif;

      tex_coords.x2_ = tex_coords.x1_ + tex_dif * ratio;
    }
  };

  template<typename T>
  struct RatioClipper<false, false, T>
  {
    void operator()(Rectangle const& clipper, Rectangle const& to_clip, T tex_coords) const
    {
      Rectangle::Type new_dif = to_clip.y1_ - clipper.y2_;
      Rectangle::Type old_dif = to_clip.y1_ - to_clip.y2_;

      TextureRectangle::Type tex_dif = tex_coords.y2_ - tex_coords.y1_;
      TextureRectangle::Type ratio   = 1.0f * new_dif / old_dif;

      tex_coords.y2_ = tex_coords.y1_ + tex_dif * ratio;
    }
  };


  /**
   * This function is for implementation uses only. Do not use it unless you know what you are
   * doing and how to use it correctly.
   */
  template<typename T, template <bool, bool, typename> class Clipper>
  inline bool clipRectangleImpl(Rectangle const& clipper, Rectangle& to_clip, T tex_coords)
  {
    ASSERTOP(clipper.x1_, le, clipper.x2_);
    ASSERTOP(clipper.y1_, le, clipper.y2_);

    ASSERTOP(to_clip.x1_, le, to_clip.x2_);
    ASSERTOP(to_clip.y1_, le, to_clip.y2_);

    // clip left side
    if (to_clip.x1_ < clipper.x1_)
    {
      // this is intentionally > and not >= because otherwise we had to check for division by
      // zero in case we want also clip texture coordinates
      if (to_clip.x2_ > clipper.x1_)
        Clipper<true, true, T>()(clipper, to_clip, tex_coords);
      else
        to_clip.x2_ = clipper.x1_;

      to_clip.x1_ = clipper.x1_;
    }

    // clip bottom
    if (to_clip.y1_ < clipper.y1_)
    {
      if (to_clip.y2_ > clipper.y1_)
        Clipper<false, true, T>()(clipper, to_clip, tex_coords);
      else
        to_clip.y2_ = clipper.y1_;

      to_clip.y1_ = clipper.y1_;
    }

    // clip right side
    if (to_clip.x2_ > clipper.x2_)
    {
      if (to_clip.x1_ < clipper.x2_)
        Clipper<true, false, T>()(clipper, to_clip, tex_coords);
      else
        to_clip.x1_ = clipper.x2_;

      to_clip.x2_ = clipper.x2_;
    }

    // clip top
    if (to_clip.y2_ > clipper.y2_)
    {
      if (to_clip.y1_ < clipper.y2_)
        Clipper<false, false, T>()(clipper, to_clip, tex_coords);
      else
        to_clip.y1_ = clipper.y2_;

      to_clip.y2_ = clipper.y2_;
    }

    ASSERTOP(to_clip.x1_, ge, clipper.x1_);
    ASSERTOP(to_clip.y1_, ge, clipper.y1_);

    ASSERTOP(to_clip.x2_, le, clipper.x2_);
    ASSERTOP(to_clip.y2_, le, clipper.y2_);

    ASSERTOP(to_clip.x1_, le, to_clip.x2_);
    ASSERTOP(to_clip.y1_, le, to_clip.y2_);

    // if rectangle has no width and height it is empty and therefor not visible
    return (to_clip.x2_ > to_clip.x1_) && (to_clip.y2_ > to_clip.y1_);
  }

  /**
   * @param[in] clipper clipping rectangle
   * @param[in,out] to_clip rectangle that has to be clipped by given clipping rectangle
   * @return false if the given rectangle is outside the clipping rect and therefor not visible,
   *         true otherwise
   */
  inline bool clipRectangle(Rectangle const& clipper, Rectangle& to_clip)
  {
    return clipRectangleImpl<void*, EmptyClipper>(clipper, to_clip, 0);
  }

  /**
   * @param[in] clipper clipping rectangle
   * @param[in,out] to_clip rectangle that has to be clipped by given clipping rectangle
   * @param[in,out] tex_coords texture coordinates that will be clipped in the same ratio the
   *                pixel are clipped
   * @return false if the given rectangle is outside the clipping rect and therefor not visible,
   *         true otherwise
   */
  inline bool clipRectangle(Rectangle const& clipper, Rectangle& to_clip, TextureRectangle& tex_coords)
  {
    return clipRectangleImpl<TextureRectangle&, RatioClipper>(clipper, to_clip, tex_coords);
  }
}


#endif
