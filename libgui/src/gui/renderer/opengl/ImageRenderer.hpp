// ImageRenderer.hpp

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

#ifndef GUIIMAGERENDERER_HPP
#define GUIIMAGERENDERER_HPP

#include <util/Assert.hpp>
#include <image/ImageAction.hpp>

#include "gui/renderer/opengl/OpenGlFunctions.hpp"


namespace gui
{
  class ImageRenderer: public img::ImageAction
  {
  public:
    ImageRenderer(int pen_x, int pen_y, int advance);

    virtual void use(img::Image<img::PixelUByteRGBA>& image);
    virtual void use(img::Image<img::PixelUByteRGB>& image);
    virtual void use(img::Image<img::PixelUByteA>& image);
    virtual void use(img::Image<img::PixelUWordRGBA>& image);
    virtual void use(img::Image<img::PixelUWordRGB>& image);
    virtual void use(img::Image<img::PixelBitmap>& image);

  private:
    int pen_x_;
    int pen_y_;
    int advance_;

    template<typename Pixel>
    void prepareImage(img::Image<Pixel> const& image) const;

    template<typename Pixel>
    void renderImage(img::Image<Pixel> const& image) const;
  };
}


namespace gui
{
  ImageRenderer::ImageRenderer(int pen_x, int pen_y, int advance)
    : pen_x_(pen_x),
      pen_y_(pen_y),
      advance_(advance)
  {
  }

  void ImageRenderer::use(img::Image<img::PixelUByteRGBA>& image)
  {
    prepareImage(image);
  }

  void ImageRenderer::use(img::Image<img::PixelUByteRGB>& image)
  {
    prepareImage(image);
  }

  void ImageRenderer::use(img::Image<img::PixelUByteA>& image)
  {
    prepareImage(image);
  }

  void ImageRenderer::use(img::Image<img::PixelUWordRGBA>& image)
  {
    prepareImage(image);
  }

  void ImageRenderer::use(img::Image<img::PixelUWordRGB>& image)
  {
    prepareImage(image);
  }

  void ImageRenderer::use(img::Image<img::PixelBitmap>& image)
  {
    prepareImage(image);
  }

  template<typename Pixel>
  void ImageRenderer::prepareImage(img::Image<Pixel> const& image) const
  {
    if (image.width() > 0 && image.height() > 0)
    {
      glPushAttrib(GL_PIXEL_MODE_BIT);
      glPixelStorei(GL_UNPACK_ALIGNMENT, static_cast<GLint>(image.alignment()));
      ASSERTOP(image.alignment(), le, 8);

      renderImage(image);

      glPopAttrib();
    }
    glBitmap(0, 0, 0.0f, 0.0f, 1.0f * advance_, 0.0f, 0);
  }

  template<typename Pixel>
  void ImageRenderer::renderImage(img::Image<Pixel> const& image) const
  {
    void const* data = static_cast<void const*>(image.scanline(0));
    ASSERTOP(data, ne, nullptr);

    GLenum pixel_format = getPixelFormat(image);
    GLenum color_format = getColorFormat(image);

    glBitmap(0, 0, 0.0f, 0.0f, 1.0f * pen_x_, 1.0f * pen_y_, 0);
    glDrawPixels(image.width(), image.height(), pixel_format, color_format, data);
    glBitmap(0, 0, 0.0f, 0.0f, -1.0f * pen_x_, -1.0f * pen_y_, 0);
  }

  /**
   * Specialization for PixelBitmaps. They can be rendered by a call to
   * glBitmap, no glDrawPixels call is necessary. However, it would work with
   * glDrawPixels as well.
   */
  template<>
  void ImageRenderer::renderImage(img::Image<img::PixelBitmap> const& image) const
  {
    GLubyte const* data   = reinterpret_cast<GLubyte const*>(image.scanline(0));
    GLsizei        width  = static_cast<GLsizei>(image.width());
    GLsizei        height = static_cast<GLsizei>(image.height());
    ASSERTOP(data, ne, nullptr);

    glBitmap(0, 0, 0.0f, 0.0f, 1.0f * pen_x_, 1.0f * pen_y_, 0);
    glBitmap(width, height, 0.0f, 0.0f, 0.0f, 0.0f, data);
    glBitmap(0, 0, 0.0f, 0.0f, -1.0f * pen_x_, -1.0f * pen_y_, 0);
  }
}


#endif
