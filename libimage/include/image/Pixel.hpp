// Pixel.hpp

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

#ifndef IMGPIXEL_HPP
#define IMGPIXEL_HPP

#include <type/Limits.hpp>
#include <type/Padding.hpp>
#include <util/Assert.hpp>

#include "image/Config.hpp"


namespace img
{
  /**
   * @todo rename the pixel classes to something without the Byte and Word stuff and somehow use
   *       numbers 8 and 16 to instead
   */
  BEGIN_DISABLE_PADDING
  struct LIBIMAGE_EXPORT PixelUByteRGBA
  {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
  }
  END_DISABLE_PADDING

  BEGIN_DISABLE_PADDING
  struct LIBIMAGE_EXPORT PixelUByteRGB
  {
    uint8_t r;
    uint8_t g;
    uint8_t b;
  }
  END_DISABLE_PADDING

  BEGIN_DISABLE_PADDING
  struct LIBIMAGE_EXPORT PixelUByteA
  {
    uint8_t a;
  }
  END_DISABLE_PADDING

  BEGIN_DISABLE_PADDING
  struct LIBIMAGE_EXPORT PixelUWordRGBA
  {
    uint16_t r;
    uint16_t g;
    uint16_t b;
    uint16_t a;
  }
  END_DISABLE_PADDING

  BEGIN_DISABLE_PADDING
  struct LIBIMAGE_EXPORT PixelUWordRGB
  {
    uint16_t r;
    uint16_t g;
    uint16_t b;
  }
  END_DISABLE_PADDING

  BEGIN_DISABLE_PADDING
  struct LIBIMAGE_EXPORT PixelBitmap
  {
    uint8_t bits;
  }
  END_DISABLE_PADDING


  /**
   * This function converts a given pixel into another one with different format.
   * @param src source pixel
   * @param dst destination pixel
   */
  template<typename Pixel1T, typename Pixel2T>
  void convert(Pixel1T const& src, Pixel2T& dst);
}


namespace img
{
  /**
   * Alpha bits get lost
   */
  template<>
  inline void convert(PixelUByteRGBA const& src, PixelUByteRGB& dst)
  {
    dst.r = src.r;
    dst.g = src.g;
    dst.b = src.b;
  }

  /**
   * All color bits (rgb) get lost
   */
  template<>
  inline void convert(PixelUByteRGBA const& src, PixelUByteA& dst)
  {
    dst.a = src.a;
  }

  /**
   * New alpha bytes are set to max
   */
  template<>
  inline void convert(PixelUByteRGB const& src, PixelUByteRGBA& dst)
  {
    dst.r = src.r;
    dst.g = src.g;
    dst.b = src.b;
    dst.a = typ::Limits<uint8_t>::max;
  }

  /**
   * New color bytes are set to min
   */
  template<>
  inline void convert(PixelUByteA const& src, PixelUByteRGBA& dst)
  {
    /**
     * @todo use some limit trait from libtype here
     */
    dst.r = typ::Limits<uint8_t>::min;
    dst.g = typ::Limits<uint8_t>::min;
    dst.b = typ::Limits<uint8_t>::min;
    dst.a = src.a;
  }

  /**
   * Narrow all source channels
   */
  template<>
  inline void convert(PixelUWordRGBA const& src, PixelUByteRGBA& dst)
  {
    dst.r = static_cast<uint8_t>(src.r);
    dst.g = static_cast<uint8_t>(src.g);
    dst.b = static_cast<uint8_t>(src.b);
    dst.a = static_cast<uint8_t>(src.a);
  }

  /**
   * Narrow all source channels and set alpha channel to max
   */
  template<>
  inline void convert(PixelUWordRGB const& src, PixelUByteRGBA& dst)
  {
    dst.r = static_cast<uint8_t>(src.r);
    dst.g = static_cast<uint8_t>(src.g);
    dst.b = static_cast<uint8_t>(src.b);
    dst.a = typ::Limits<uint8_t>::max;
  }

  /**
   * Not possible for now
   */
  template<>
  inline void convert(PixelBitmap const& src, PixelUByteRGBA& dst)
  {
    ASSERT(false);
  }

  /**
   * Alpha bytes are set to max
   */
  template<>
  inline void convert(PixelUByteRGB const& src, PixelUByteA& dst)
  {
    dst.a = typ::Limits<uint8_t>::max;
  }

  /**
   * Alpha bytes are narrowed and copied
   */
  template<>
  inline void convert(PixelUWordRGBA const& src, PixelUByteA& dst)
  {
    dst.a = static_cast<uint8_t>(src.a);
  }

  /**
   * Alpha bytes are set to max
   */
  template<>
  inline void convert(PixelUWordRGB const& src, PixelUByteA& dst)
  {
    dst.a = typ::Limits<uint8_t>::max;
  }

  /**
   * Not possible for now
   */
  template<>
  inline void convert(PixelBitmap const& src, PixelUByteA& dst)
  {
    ASSERT(false);
  }
}


#endif
