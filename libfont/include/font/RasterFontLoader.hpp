// RasterFontLoader.hpp

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

#ifndef FNTRASTERFONTLOADER_HPP
#define FNTRASTERFONTLOADER_HPP

#include <container/Algorithm.hpp>

#include <image/Pixel.hpp>
#include <image/Image.hpp>

#include "font/Error.hpp"
#include "font/FontLoader.hpp"


namespace fnt
{
  /**
   * @param First character code of first character in array
   * @param Count number of characters in array
   * @param Width width of one character (they have to have fixed width)
   * @param Height height of one character (they have to have fixed height)
   * @param Baseline y-value telling at which height in the glyph the baseline, that is the line
   *        where all characters stand on, is
   */
  template<size_t First, size_t Count, size_t Width, size_t Height, size_t Baseline>
  class RasterFontLoader: public FontLoader
  {
  public:
    RasterFontLoader(byte_t const (*glyphs)[Count][Height], int const (*spaces)[Count]);

    virtual img::ImageBase* render(char_t character, GlyphMetrics& metrics) const override;

    virtual size_t size() const override;

  private:
    byte_t const (*glyphs_)[Count][Height];
    int const    (*spaces_)[Count];

    size_t glyphWidth(char_t character) const;
  };
}


namespace fnt
{
  /**
   * @param glyphs pointer to two dimensional array with glyph bits (with fixed width and fixed
   *        height)
   * @param spaces pointer to array with spaces after each glyph
   */
  template<size_t First, size_t Count, size_t Width, size_t Height, size_t Baseline>
  RasterFontLoader<First, Count, Width, Height, Baseline>::rasterFontLoader(byte_t const (*glyphs)[Count][Height], int const (*spaces)[Count])
    : glyphs_(glyphs),
      spaces_(spaces)
  {
    if (glyphs_ == 0)
      throw Error(TEXT("Error creating RasterFontLoader"), TEXT("No glyph array supplied"));
  }

  /**
   * @copydoc FontLoader::Render
   */
  template<size_t First, size_t Count, size_t Width, size_t Height, size_t Baseline>
  img::ImageBase* RasterFontLoader<First, Count, Width, Height, Baseline>::render(char_t character, GlyphMetrics& metrics) const
  {
    if (character >= First && character < First + Count)
    {
      img::Image<img::PixelBitmap>* image = new img::Image<img::PixelBitmap>(Width, Height);

      for (size_t i = 0; i < image->height(); ++i)
      {
        auto bytes = Width / CHAR_BIT;
        auto src   = (*glyphs_)[character - First] + bytes * i;
        auto dst   = reinterpret_cast<byte_t*>(image->scanline(i));
        assert(dst != 0);
        assert(bytes > 0);

        ctr::copy(src, src + bytes + 1, dst);
      }

      metrics.pen_x   = 0;
      metrics.pen_y   = -static_cast<int>(Baseline);
      metrics.height  = Height;
      metrics.width   = Width;
      metrics.advance = glyphWidth(character);

      return image;
    }
    return 0;
  }

  /**
   * @copydoc FontLoader::GetSize
   */
  template<size_t First, size_t Count, size_t Width, size_t Height, size_t Baseline>
  size_t RasterFontLoader<First, Count, Width, Height, Baseline>::size() const
  {
    return Height;
  }

  /**
   * @param character to get effective width of
   * @return effective width of character (including the space data)
   */
  template<size_t First, size_t Count, size_t Width, size_t Height, size_t Baseline>
  size_t RasterFontLoader<First, Count, Width, Height, Baseline>::glyphWidth(char_t character) const
  {
    return Width - (spaces_ != 0 ? (*spaces_)[character - First] : 0);
  }
}


#endif
