// DynamicImage.hpp

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

#ifndef IMGDYNAMICIMAGE_HPP
#define IMGDYNAMICIMAGE_HPP

#include "image/Config.hpp"
#include "image/Error.hpp"
#include "image/Image.hpp"


namespace img
{
  /**
   * @note objects of this type are not copyable
   */
  class LIBIMAGE_EXPORT DynamicImage
  {
  public:
    template<typename PixelT>
    DynamicImage(Image<PixelT> const& image);

    DynamicImage(DynamicImage&& other) = delete;
    DynamicImage(DynamicImage const& other) = delete;

    ~DynamicImage();

    DynamicImage& operator =(DynamicImage&& other) = delete;
    DynamicImage& operator =(DynamicImage const& other) = delete;

    template<typename PixelT>
    Image<PixelT>& as();

    template<typename PixelT>
    Image<PixelT> const& as() const;

    unsigned int type() const;

  private:
    void*        image_;
    unsigned int type_;
  };
}


namespace img
{
  template<typename PixelT>
  inline DynamicImage::DynamicImage(Image<PixelT> const& image)
    : image_(new Image<PixelT>(image)),
      type_(image.type())
  {
  }

  inline DynamicImage::~DynamicImage()
  {
    delete image_;
  }

  template<typename PixelT>
  Image<PixelT>& DynamicImage::as()
  {
    DynamicImage const& image = *this;
    return const_cast< Image<PixelT>& >(image.As<PixelT>());
  }

  template<typename PixelT>
  Image<PixelT> const& DynamicImage::as() const
  {
    if (type_ != Image<PixelT>::type())
      throw Error(TEXT("Error converting image"), TEXT("Static and dynamic type do not match"));

    return *static_cast< Image<PixelT> const* >(image_);
  }

  inline unsigned int DynamicImage::type() const
  {
    return type_;
  }
}


#endif
