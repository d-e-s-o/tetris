// ImageAction.hpp

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

#ifndef IMGIMAGEACTION_HPP
#define IMGIMAGEACTION_HPP

#include "image/Config.hpp"


namespace img
{
  template<typename PixelT>
  class Image;

  struct PixelUByteRGBA;
  struct PixelUByteRGB;
  struct PixelUByteA;
  struct PixelUWordRGBA;
  struct PixelUWordRGB;
  struct PixelBitmap;


  /**
   *
   */
  class LIBIMAGE_EXPORT ImageAction
  {
  public:
    virtual ~ImageAction() = 0;

    virtual void use(Image<PixelUByteRGBA>& image) = 0;
    virtual void use(Image<PixelUByteRGB>& image) = 0;
    virtual void use(Image<PixelUByteA>& image) = 0;
    virtual void use(Image<PixelUWordRGBA>& image) = 0;
    virtual void use(Image<PixelUWordRGB>& image) = 0;
    virtual void use(Image<PixelBitmap>& image) = 0;
  };

  /**
   *
   */
  class LIBIMAGE_EXPORT ConstImageAction
  {
  public:
    virtual ~ConstImageAction() = 0;

    virtual void use(Image<PixelUByteRGBA> const& image) = 0;
    virtual void use(Image<PixelUByteRGB> const& image) = 0;
    virtual void use(Image<PixelUByteA> const& image) = 0;
    virtual void use(Image<PixelUWordRGBA> const& image) = 0;
    virtual void use(Image<PixelUWordRGB> const& image) = 0;
    virtual void use(Image<PixelBitmap> const& image) = 0;
  };
}


namespace img
{
  /**
   *
   */
  inline ImageAction::~ImageAction()
  {
  }

  /**
   *
   */
  inline ConstImageAction::~ConstImageAction()
  {
  }
}


#endif
