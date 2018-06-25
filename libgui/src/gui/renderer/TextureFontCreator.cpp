// TextureFontCreator.cpp

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

#include <algorithm>

#include <util/Assert.hpp>
#include <pointer/Deleter.hpp>
#include <pointer/ResourceGuard.hpp>

#include <image/Pixel.hpp>
#include <image/Image.hpp>
#include <image/ImageFunctions.hpp>

#include <font/FontLoader.hpp>

#include "gui/Allocator.hpp"
#include "gui/Error.hpp"
#include "gui/renderer/Math.hpp"
#include "gui/renderer/TextureFontCreator.hpp"


namespace gui
{
  namespace
  {
    /**
     * This datatype is used for storing the information for the glyphs, that is:
     * - the prerendered image
     * - the metrics of the glyph
     * - the position within the texture
     */
    struct GlyphRecord
    {
      img::ImageBase*   image_;
      fnt::GlyphMetrics metrics_;
      Position          position_;

      GlyphRecord(img::ImageBase* image, fnt::GlyphMetrics const& metrics)
        : image_(image),
          metrics_(metrics),
          position_()
      {
      }
    };

    /**
     * @todo use ctr::Array here instead of std::vector
     */
    typedef Allocator::rebind<GlyphRecord>::other Allocator;
    typedef std::vector<GlyphRecord, Allocator> GlyphData;


    /**
     *
     */
    void renderGlyphData(fnt::FontLoader const& loader, GlyphData& data, char_t first_char, char_t char_count)
    {
      data.reserve(char_count);

      for (char_t i = 0; i < char_count; ++i)
      {
        fnt::GlyphMetrics metrics;
        img::ImageBase* image = loader.render(first_char + i, metrics);

        data.push_back(GlyphRecord(image, metrics));
      }
    }

    /**
     * @todo this is not the most size-efficient algorithm - we should try to make the
     *       texture size squarish
     *  //GLsizei broadest = 0;
     *  //GLsizei highest  = 0;
     *
     *  //for (Images::const_iterator it = glyph_data.begin(); it != glyph_data.end(); ++it)
     *  //{
     *  //  GlyphMetrics const& metrics = it->second;
     *
     *  //  if (it->second.width > broadest)
     *  //    broadest = it->second.width;
     *
     *  //  if (it->second.height > highest)
     *  //    highest = it->second.height;
     *  //}
     */
    void calculateGlyphPositions(GlyphData& data, int& width, int& height, int max_width, int max_height)
    {
      // the current height of the line, that is the highest glyph
      int line_height = 0;

      // the current x and y position of the glyph image to be rendered to the texture
      PositionT x = 0;
      PositionT y = 0;

      for (GlyphData::iterator it = data.begin(); it != data.end(); ++it)
      {
        fnt::GlyphMetrics const& metrics  = it->metrics_;
        Position&           position = it->position_;

        if (x + metrics.width > width)
        {
          if (x + metrics.width > max_width)
          {
            x  = 0;
            y += line_height;

            line_height = 0;
          }
          else
            width = x + metrics.width;
        }

        if (y + metrics.height > height)
          height = y + metrics.height;

        if (metrics.height > line_height)
          line_height = metrics.height;

        // if also height gets too much we cannot continue
        if (height > max_height)
          throw Error(TEXT("Error creating texture for font"), TEXT("The texture cannot contain all glyphs"));

        position.x = x;
        position.y = y;

        x += metrics.width;
      }
    }

    /**
     *
     */
    class EmptyImageCreator
    {
    public:
      EmptyImageCreator(size_t width, size_t height)
        : width_(width),
          height_(height)
      {
      }

      template<typename Pixel>
      img::ImageBase* operator()(img::Image<Pixel> const& image) const
      {
        return new img::Image<Pixel>(width_, height_);
      }

    private:
      size_t width_;
      size_t height_;
    };


    /**
     * @param image1 destination image to copy sub image to
     * @param image2 source image to copy on first one at given coordinates
     * @param x position on horizontal axis to copy source image to
     * @param y position on vertical axis to copy source image to
     * @return true if copying the second image onto the first succeded, false otherwise
     * @note this function only exists because SunStudio cannot specialize a template
     *       directly in ImageCopie::operator()
     */
    template<typename Pixel1, typename Pixel2>
    bool copyImage(img::Image<Pixel1>& image1, img::Image<Pixel2> const& image2, int x, int y)
    {
      // different types are not supported (and should not even be possible, because the big
      // image is created with the same format the pre-rendered glyphs have)
      ASSERT(false);
      return false;
    }

    /**
     * This is the specialization of CopyImage for Images with same pixel types. They can be copied
     * without any conversion.
     */
    template<typename Pixel>
    bool copyImage(img::Image<Pixel>& image1, img::Image<Pixel> const& image2, int x, int y)
    {
      size_t src_w = image2.width();
      size_t src_h = image2.height();

      if (src_w > 0 && src_h > 0 &&
          image1.width()  >= x + src_w &&
          image1.height() >= y + src_h)
      {
        for (size_t i = 0; i < src_h; ++i)
        {
          Pixel const* src = image2.scanline(i);
          Pixel*       dst = image1.scanline(y + i) + x;
          ASSERTOP(src, ne, nullptr);
          ASSERTOP(dst, ne, nullptr);

          std::copy(src, src + src_w, dst);
        }
        return true;
      }
      return false;
    }

    /**
     *
     */
    template<>
    bool copyImage(img::Image<img::PixelBitmap>& image1, img::Image<img::PixelBitmap> const& image2, int x, int y)
    {
      //size_t src_w = image2.width();
      //size_t src_h = image2.height();

      //if (src_w > 0 && src_h > 0 &&
      //    image1.width()  >= x + src_w &&
      //    image1.height() >= y + src_h)
      //{
      //  for (size_t i = 0; i < src_h; ++i)
      //  {
      //    PixelBitmap const* src = image2.scanline(i);
      //    PixelBitmap*       dst = image1.scanline(y + i) + x / CHAR_BIT;
      //    ASSERTOP(src, ne, nullptr);
      //    ASSERTOP(dst, ne, nullptr);

      //    std::copy(src, src + src_w / CHAR_BIT, dst);
      //  }
      //  return true;
      //}
      return false;
    }


    /**
     * This class is used for implementing SubImageRenderer.
     */
    template<typename Pixel>
    class ImageCopier
    {
    public:
      /**
       * @param image image to render on in operator()
       * @param x horizontal position the later supplied image should be rendered at
       * @param y vertical position the later supplied image should be rendered at
       */
      ImageCopier(img::Image<Pixel>& image, int x, int y)
        : image_(&image),
          x(x),
          y(y)
      {
      }

      /**
       * @param image image to be rendered onto the one given during construction
       * @note at the moment no type conversions are supported, meaning the class template
       *       parameter has to be the same as the method template parameter
       */
      template<typename Pixel2>
      void operator()(img::Image<Pixel2> const& image) const
      {
        copyImage(*image_, image, x, y);
      }

    private:
      img::Image<Pixel>* image_;
      int x;
      int y;
    };

    /**
     * This functor takes an image and a position and renderes another supplied image on it.
     */
    class SubImageRenderer
    {
    public:
      /**
       * @param image image to be rendered onto one supplied in operator()
       * @param x horizontal position the image should be rendered at
       * @param y vertical position the image should be rendered at
       */
      SubImageRenderer(img::ImageBase const& image, int x, int y)
        : image_(&image),
          x(x),
          y(y)
      {
      }

      /**
       * @param image[in,out] image the sub-image given during construction should be rendered to
       */
      template<typename Pixel>
      void operator()(img::Image<Pixel>& image) const
      {
        img::useImage<void>(*image_, ImageCopier<Pixel>(image, x, y));
      }

    private:
      img::ImageBase const* image_;
      int x;
      int y;
    };

    /**
     *
     */
    void renderGlyphsToImage(GlyphData const& data, img::ImageBase& image)
    {
      for (GlyphData::const_iterator it = data.begin(); it != data.end(); ++it)
      {
        int glyph_x = it->position_.x;
        int glyph_y = it->position_.y;

        img::useImage<void>(image, SubImageRenderer(*it->image_, glyph_x, glyph_y));
      }
    }

    /**
     *
     */
    class GlyphDataConverter
    {
    public:
      GlyphDataConverter(int texture_w, int texture_h)
        : texture_w_(1.0f / texture_w),
          texture_h_(1.0f / texture_h)
      {
      }

      TexturedGlyph operator()(GlyphRecord const& record) const
      {
        int glyph_x = record.position_.x;
        int glyph_y = record.position_.y;
        int glyph_w = record.metrics_.width;
        int glyph_h = record.metrics_.height;

        TexturedGlyph glyph;

        glyph.x = record.metrics_.pen_x;
        glyph.y = record.metrics_.pen_y;
        glyph.w = glyph_w;
        glyph.h = glyph_h;

        glyph.u1 = glyph_x * texture_w_;
        glyph.v1 = glyph_y * texture_h_;
        glyph.u2 = (glyph_x + glyph_w) * texture_w_;
        glyph.v2 = (glyph_y + glyph_h) * texture_h_;

        glyph.advance = record.metrics_.advance;

        return glyph;
      }

    private:
      float texture_w_;
      float texture_h_;
    };

    /**
     *
     */
    void updateGlyphsFromData(GlyphData const& data, int width, int height, TexturedGlyphs& glyphs)
    {
      glyphs.reserve(data.size());

      std::transform(data.begin(), data.end(), std::back_inserter(glyphs), GlyphDataConverter(width, height));
    }

    /**
     * @param record glyph record to create metrics bounds of
     */
    Bounds convertBounds(GlyphRecord const& record)
    {
      fnt::GlyphMetrics const& metrics = record.metrics_;

      return Bounds(metrics.pen_x, metrics.pen_y, metrics.advance, metrics.height);
    }

    /**
     *
     */
    void updateBoundsFromData(GlyphData const& data, GlyphBounds& bounds)
    {
      bounds.reserve(data.size());

      // create the bounds from the glyph data and store them
      std::transform(data.begin(), data.end(), back_inserter(bounds), &convertBounds);
    }

    /**
     * @param data glyph data with images to delete
     */
    void freeGlyphData(GlyphData const& data)
    {
      for (GlyphData::const_iterator it = data.begin(); it != data.end(); ++it)
        delete it->image_;
    }

    /**
     * @param[in,out] width value to make power of two (if not already)
     * @param[in,out] height value to make power of two (if not already)
     */
    template<typename T>
    T makePowerOfTwo(T n)
    {
      if (!isPowerOfTwo(n))
        return nextPowerOfTwo(n);

      return n;
    }
  }


  /**
   *
   */
  TextureFontCreator::TextureFontCreator(fnt::FontLoader const& loader, int max_width, int max_height, char_t first, char_t count)
    : first_char_(first),
      char_count_(count)
  {
    createTextureFont(loader, max_width, max_height);
  }

  /**
   *
   */
  TextureFontCreator::~TextureFontCreator()
  {
    delete image_;
  }

  /**
   * This method uses the font loader to create the texture font (that is the texture and the
   * display lists).
   * @param loader font loader used to render the glyphs
   */
  void TextureFontCreator::createTextureFont(fnt::FontLoader const& loader, int max_width, int max_height)
  {
    GlyphData data;
    data.reserve(char_count_);

    renderGlyphData(loader, data, first_char_, char_count_);
    ptr::ResourceGuard<GlyphData, void (*)(GlyphData const&)> guard(data, &freeGlyphData);

    int width  = 0;
    int height = 0;

    calculateGlyphPositions(data, width, height, max_width, max_height);

    width  = makePowerOfTwo(width);
    height = makePowerOfTwo(height);

    ASSERTOP(data.size(), gt, 0);

    image_ = img::useImage<img::ImageBase*>(*data[0].image_, EmptyImageCreator(width, height));
    ptr::ResourceGuard<img::ImageBase*, ptr::Deleter> guard1(image_);
    ASSERTOP(image_, ne, nullptr);

    renderGlyphsToImage(data, *image_);
    updateGlyphsFromData(data, width, height, glyphs_);
    updateBoundsFromData(data, bounds_);

    guard1.release();
  }
}
