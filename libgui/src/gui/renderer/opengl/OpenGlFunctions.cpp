// OpenGlFunctions.cpp

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

#include <util/Assert.hpp>
#include <image/Pixel.hpp>
using namespace img;

#include "OpenGlFunctions.hpp"


namespace gui
{
  template<>
  GLint getColors(Image<PixelUByteRGBA> const& image)
  {
    return 4;
  }

  template<>
  GLint getColors(Image<PixelUByteRGB> const& image)
  {
    return 3;
  }

  template<>
  GLint getColors(Image<PixelUByteA> const& image)
  {
    return 1;
  }

  template<>
  GLint getColors(Image<PixelUWordRGBA> const& image)
  {
    return 4;
  }

  template<>
  GLint getColors(Image<PixelUWordRGB> const& image)
  {
    return 3;
  }

  template<>
  GLint getColors(Image<PixelBitmap> const& image)
  {
    return 1;
  }

  template<>
  GLint getFormat(Image<PixelUByteRGBA> const& image)
  {
    return GL_RGBA8;
  }

  template<>
  GLint getFormat(Image<PixelUByteRGB> const& image)
  {
    return GL_RGB8;
  }

  template<>
  GLint getFormat(Image<PixelUByteA> const& image)
  {
    return GL_ALPHA8;
  }

  template<>
  GLint getFormat(Image<PixelUWordRGBA> const& image)
  {
    return GL_RGBA16;
  }

  template<>
  GLint getFormat(Image<PixelUWordRGB> const& image)
  {
    return GL_RGB16;
  }

  template<>
  GLint getFormat(Image<PixelBitmap> const& image)
  {
    return 1;
  }

  template<>
  GLenum getPixelFormat(Image<PixelUByteRGBA> const& image)
  {
    return GL_RGBA;
  }

  template<>
  GLenum getPixelFormat(Image<PixelUByteRGB> const& image)
  {
    return GL_RGB;
  }

  template<>
  GLenum getPixelFormat(Image<PixelUByteA> const& image)
  {
    return GL_ALPHA;
  }

  template<>
  GLenum getPixelFormat(Image<PixelUWordRGBA> const& image)
  {
    return GL_RGBA;
  }

  template<>
  GLenum getPixelFormat(Image<PixelUWordRGB> const& image)
  {
    return GL_RGB;
  }

  template<>
  GLenum getPixelFormat(Image<PixelBitmap> const& image)
  {
    // I think this is bullshit, only COLOR_INDEX and STENCIL_INDEX are valid
    // for bitmaps
    return GL_ALPHA;
  }

  template<>
  GLenum getColorFormat(Image<PixelUByteRGBA> const& image)
  {
    return GL_UNSIGNED_BYTE;
  }

  template<>
  GLenum getColorFormat(Image<PixelUByteRGB> const& image)
  {
    return GL_UNSIGNED_BYTE;
  }

  template<>
  GLenum getColorFormat(Image<PixelUByteA> const& image)
  {
    return GL_UNSIGNED_BYTE;
  }

  template<>
  GLenum getColorFormat(Image<PixelUWordRGBA> const& image)
  {
    return GL_UNSIGNED_SHORT;
  }

  template<>
  GLenum getColorFormat(Image<PixelUWordRGB> const& image)
  {
    return GL_UNSIGNED_SHORT;
  }

  template<>
  GLenum getColorFormat(Image<PixelBitmap> const& image)
  {
    return GL_BITMAP;
  }

  /**
   * @param width desired width of the texture
   * @param height desired height of the texture
   * @param colors 3rd parameter to glTexImage2D
   * @param pixel_format 7th parameter to glTexImage2D
   * @param color_format 8th parameter to glTexImage2D
   * @return true if OpenGL supports that texture size, false if not
   */
  bool isTextureSizeSupported(GLsizei width, GLsizei height, GLint colors, GLenum pixel_format, GLenum color_format)
  {
    ASSERTOP(glGetError(), eq, GL_NO_ERROR);

    // glGetIntegerv with GL_MAX_TEXTURE_SIZE is buggy or whatever (simply returns 0 for me),
    // we use texture proxies instead:
    // http://www.opengl.org/resources/faq/technical/texture.htm#text0030
    glTexImage2D(GL_PROXY_TEXTURE_2D, 0, colors, width, height, 0, pixel_format, color_format, 0);

    GLint w = 0, h = 0;
    glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
    glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);

    ASSERTOP(glGetError(), eq, GL_NO_ERROR);

    return (w != 0) && (h != 0);
  }
}
