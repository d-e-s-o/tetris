// Image.hpp

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

#ifndef IMGIMAGE_HPP
#define IMGIMAGE_HPP

#include <type/Limits.hpp>
#include <util/Util.hpp>
#include <util/Assert.hpp>
#include <util/Algorithm.hpp>
#include <container/Array.hpp>
#include <container/ArrayFunctions.hpp>

#include "image/Config.hpp"
#include "image/ImageBase.hpp"
#include "image/ImageAction.hpp"


namespace img
{
  /**
   * This class represents any pixel/raster graphic within this library.
   * @note objects of this type are copyable
   * @note this class is not meant to be used as a base class
   * @note no plans to support any svg format were made since it is not needed
   *       yet and the implementation would be some more time consuming
   * @todo add method for scaling (with bilinear filtering p.ex.)
   * @todo add support for palettes
   * @todo if width OR height is zero there should be no additional memory used and all methods
   *       have to act as expected
   */
  template<typename PixelT>
  class Image: public ImageBase
  {
  public:
    Image(size_t width, size_t height, size_t alignment = sizeof(void*));

    template<typename Pixel2T>
    Image(Image<Pixel2T> const& image);

    virtual void use(ImageAction& action) override;
    virtual void use(ConstImageAction& action) const override;

    template<typename FilterT>
    void resize(size_t width, size_t height, FilterT const& filter);

    virtual size_t width() const override;
    virtual size_t height() const override;
    virtual size_t alignment() const override;

    PixelT*       scanline(size_t line);
    PixelT const* scanline(size_t line) const;

  private:
    typedef ctr::Array<byte_t> Bytes;

    size_t width_;
    size_t height_;
    size_t alignment_;

    Bytes bytes_;

    void initialize();
    void resize();
  };

  template<typename PixelT>
  size_t usedLineBytes(Image<PixelT> const& image);

  template<typename PixelT>
  size_t entireLineBytes(Image<PixelT> const& image);

  template<typename PixelT>
  ctr::Array<PixelT*> get2DData(Image<PixelT>& image);

  template<typename PixelT>
  ctr::Array<PixelT const*> get2DData(Image<PixelT> const& image);

  template<typename PixelT>
  void flipHorizontal(Image<PixelT>& image);
}


namespace img
{
  /**
   * The constructor creates a new empty image with the given specification.
   * @param width number of pixels the image has in horizontal direction
   * @param height number of pixels the image has in vertical direction
   * @param alignment bytenumber to which scanlines are aligned to (p.ex 4 means a scanline always
   *        starts at an address that is divisible by 4)
   */
  template<typename PixelT>
  Image<PixelT>::Image(size_t width, size_t height, size_t alignment)
    : width_(width),
      height_(height),
      alignment_(alignment)
  {
    resize();
    initialize();
  }

  /**
   * The constructor creates a new image by creating a copy of an existing one.
   * @note this "copy"-constructor is only called, if the template parameters PixelT and Pixel2T are
   *       not equal; otherwise the compiler generated copy-ctor is used
   */
  template<typename PixelT>
  template<typename Pixel2T>
  Image<PixelT>::Image(Image<Pixel2T> const& image)
    : width_(image.width()),
      height_(image.height()),
      alignment_(image.alignment())
  {
    resize();

    for (size_t i = 0; i < height(); ++i)
    {
      Pixel2T const* src = image.scanline(i);
      PixelT*        dst = scanline(i);

      for (size_t  j = 0; j < width(); ++j)
      {
        convert(*src, *dst);
        ++src;
        ++dst;
      }
    }
  }

  /**
   * @copydoc ImageBase::Use
   */
  template<typename PixelT>
  void Image<PixelT>::use(ImageAction& action)
  {
    action.use(*this);
  }

  /**
   * @copydoc ImageBase::Use
   */
  template<typename PixelT>
  void Image<PixelT>::use(ConstImageAction& action) const
  {
    action.use(*this);
  }

  /**
   * This method is used to resize the image. Because there are different filter algorithms for
   * resizing raster graphics it is supplied by the user.
   * @param[in] width new width of the image
   * @param[in] height new height of the image
   * @param[in] filter object used to do actual scaling
   * @todo implement me!
   */
  template<typename PixelT>
  template<typename FilterT>
  void Image<PixelT>::resize(size_t width, size_t height, FilterT const& filter)
  {
    if (width != this->width() || height != this->height())
    {
      Image<PixelT> image(*this);

      width_  = width;
      height_ = height;
      resize();

      filter(image, *this);
    }
  }

  /**
   * @return horizontal number of pixels in the image
   */
  template<typename PixelT>
  size_t Image<PixelT>::width() const
  {
    return width_;
  }

  /**
   * @return vertical number of pixels in the image
   */
  template<typename PixelT>
  size_t Image<PixelT>::height() const
  {
    return height_;
  }

  /**
   * @return alignment value
   */
  template<typename PixelT>
  size_t Image<PixelT>::alignment() const
  {
    return alignment_;
  }

  /**
   * @copydoc Image::GetScanline
   */
  template<typename PixelT>
  PixelT* Image<PixelT>::scanline(size_t line)
  {
    Image const& image = *this;
    return const_cast<PixelT*>(image.scanline(line));
  }

  /**
   * @param line number of scanline to get (0..height() - 1)
   * @return pointer to the desired scanline or 0 if out of bounds
   */
  template<typename PixelT>
  PixelT const* Image<PixelT>::scanline(size_t line) const
  {
    if (bytes_.size() > 0)
    {
      auto aligned = utl::roundUp(&bytes_[0], alignment_);
      auto offset  = entireLineBytes(*this) * line;
      auto bytes   = aligned + offset;

      ASSERTOP((bytes - static_cast<byte_t*>(0)) % alignment_, eq, 0);

      if (bytes < &bytes_[bytes_.size() - 1])
        return reinterpret_cast<PixelT const*>(bytes);
    }
    return 0;
  }

  /**
   * This helper method sets the array to values it would have gotten by
   * default-construction of PixelT (it did not because it consists of bytes
   * not PixelT, because otherwise we could not handle alignment).
   */
  template<typename PixelT>
  void Image<PixelT>::initialize()
  {
    for (size_t i = 0; i < height(); ++i)
    {
      PixelT* pixels = scanline(i);
      ASSERTOP(pixels, ne, nullptr);

      ASSERTOP(usedLineBytes(*this), eq, usedLineBytes(*this) / sizeof(PixelT) * sizeof(PixelT));
      utl::fill(pixels, pixels + usedLineBytes(*this) / sizeof(PixelT), PixelT());
    }
  }

  template<typename PixelT>
  void Image<PixelT>::resize()
  {
    if (width_ > 0 && height_ > 0)
    {
      // we cannot tell now what alignment the memory in the vector will have so we need to allocate
      // enough so that it can store the image no matter what the actual alignment is
      ctr::resize(bytes_, alignment_ + entireLineBytes(*this) * height_, byte_t());
    }
  }

  /**
   * This function calculates the number of bytes that are actually used for
   * image data on a scanline. That means any padding bytes are not taken into
   * calculation.
   * @param image image to calculate used bytes per scanline
   * @return number of bytes used on a scanline or 0 if image has no width
   */
  template<typename PixelT>
  size_t usedLineBytes(Image<PixelT> const& image)
  {
    return image.width() * sizeof(PixelT);
  }

  /**
   * Specialization for bitmaps. In case of a bitmap the calculation of the
   * used bytes is different, because width() would specifiy bits (actually
   * still pixels, but a pixel is represented by a single bit).
   */
  template<>
  inline size_t usedLineBytes(Image<PixelBitmap> const& image)
  {
    return (image.width() + BITS_PER_BYTE - 1) / BITS_PER_BYTE;
  }

  /**
   * This function calculates the number of bytes one scanline of the image has
   * including padding bytes.
   * @param image image to calculate scanline size from
   * @return number of bytes a scanline has or 0 if image has no width
   */
  template<typename PixelT>
  size_t entireLineBytes(Image<PixelT> const& image)
  {
    size_t bytes = usedLineBytes(image);

    if (bytes > 0)
      return utl::roundUp(bytes, image.alignment());

    return 0;
  }

  /**
   * @copydoc Get2DData
   */
  template<typename PixelT>
  ctr::Array<PixelT*> get2DData(Image<PixelT>& image)
  {
    Image<PixelT> const& img = image;
    ctr::Array<PixelT const*> pixel = get2DData(img);
    return *reinterpret_cast< ctr::Array<PixelT*>* >(&pixel);
  }

  /**
   * This function creates an two dimensional array with the pixel data. Each
   * element in the vector is a scanline.
   * @param image image to create 2D data from
   * @return vector with 2D data for the image
   */
  template<typename PixelT>
  ctr::Array<PixelT const*> get2DData(Image<PixelT> const& image)
  {
    ctr::Array<PixelT const*> pixel;
    pixel.reserve(image.height());

    for (size_t i = 0; i < image.height(); ++i)
    {
      PixelT const* scanline = image.scanline(i);
      ASSERTOP(scanline, ne, nullptr);

      ctr::append(pixel, scanline);
    }
    return pixel;
  }

  /**
   * This function can be used to flip the contents of the image on a virtual
   * vertical axis at half height.
   */
  template<typename PixelT>
  void flipHorizontal(Image<PixelT>& image)
  {
    size_t width  = usedLineBytes(image) / sizeof(PixelT);
    size_t height = image.height();

    if (width > 0 && height > 1)
    {
      // iterate through all lines of the image up to the vertical half
      for (size_t line = 0; line < height / 2; ++line)
      {
        PixelT* src = image.scanline(line);
        PixelT* dst = image.scanline(height - 1 - line);

        size_t i = 0;
        while (i < width)
        {
          utl::swap(*src, *dst);
          ++src;
          ++dst;
          ++i;
        }
      }
    }
  }
}


#endif
