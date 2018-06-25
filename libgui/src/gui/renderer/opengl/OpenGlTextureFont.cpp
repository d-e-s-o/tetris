// OpenGlTextureFont.cpp

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
#include <pointer/Deleter.hpp>
#include <pointer/ResourceGuard.hpp>

#include <font/FontLoader.hpp>

#include "gui/Error.hpp"
#include "gui/renderer/Math.hpp"
#include "gui/renderer/opengl/OpenGlRenderer.hpp"
#include "gui/renderer/opengl/OpenGlFunctions.hpp"
#include "gui/renderer/opengl/OpenGlTexture.hpp"
#include "gui/renderer/opengl/OpenGlTextureFont.hpp"


namespace gui
{
  namespace
  {
    /**
     * @param[out] max_width maximal width in pixel a texture can have
     * @param[out] max_height maximal height in pixel a texture can have
     * @return true if retrieving the maximal texture size succeded, false otherwise
     * @note getting the maximal texture size may fail if the given color, pixel format and
     *       color format combination is invalid; it may also fail if no window with OpenGl
     *       context is created
     */
    bool getMaxTextureSize(GLsizei& max_width, GLsizei& max_height, GLint colors, GLenum pixel_format, GLenum color_format)
    {
      // OpenGL guarantees a minimal texture size of 64x64 pixels
      GLsizei width  = max_width  = 64;
      GLsizei height = max_height = 64;

      // if OpenGL claims that this size is not supported however, the combination of colors,
      // pixel_format and color_format is likely to be invalid
      if (!isTextureSizeSupported(width, height, colors, pixel_format, color_format))
        return false;

      do
      {
        max_width = width;
        width = nextPowerOfTwo(max_width);
      }
      while (isTextureSizeSupported(width, max_height, colors, pixel_format, color_format));

      do
      {
        max_height = height;
        height = nextPowerOfTwo(max_height);
      }
      while (isTextureSizeSupported(max_width, height, colors, pixel_format, color_format));

      ASSERT(isTextureSizeSupported(max_width, max_height, colors, pixel_format, color_format));
      ASSERTOP(max_width, ge, 64);
      ASSERTOP(max_height, ge, 64);

      return true;
    }
  }


  /**
   * @throw Error if rendering the glyphs failed
   */
  OpenGlTextureFont::OpenGlTextureFont(OpenGlRenderer& renderer, fnt::FontLoader const& loader)
    : TextureFont(loader.size(), 32, 96),
      renderer_(&renderer),
      texture_(0)
  {
    int max_width  = 0;
    int max_height = 0;

    // @todo we should check here for the actual texture format
    if (!getMaxTextureSize(max_width, max_height, 1, GL_ALPHA, GL_UNSIGNED_BYTE))
    {
      throw Error(TEXT("Error getting maximal texture size"),
                  TEXT("The given texture format is probably invalid"));
    }

    TextureFontCreator font_creator(loader, max_width, max_height, getFirstChar(), getCharCount());

    // @note a texture font is already rendered with lower left edge coordinate origin, so no
    //       flipping of the picture is needed
    texture_ = new OpenGlTexture(renderer, font_creator.getImage(), false);
    ptr::ResourceGuard<OpenGlTexture*, ptr::Deleter> guard(texture_);

    updateBounds(font_creator.getBounds());
    glyphs_ = font_creator.getGlyphs();

    guard.release();

    ASSERTOP(glGetError(), eq, GL_NO_ERROR);
  }

  /**
   * Destroy the texture font, free the texture and the display lists.
   */
  OpenGlTextureFont::~OpenGlTextureFont()
  {
    delete texture_;
  }

  /**
   * @copydoc Font::render
   */
  void OpenGlTextureFont::render(String const& string, Position const& position) const
  {
    renderer_->pushTexture(texture_);

    int advance = 0;

    for (String::ConstIterator it = string.begin(), end = string.end(); it != end; ++it)
    {
      // @todo we probably should add some range checking here
      TexturedGlyph const& glyph = glyphs_[*it - getFirstChar()];

      Rectangle rect(position.x + advance, position.y, 0, 0);
      rect.x1_ += glyph.x;
      rect.y1_ += glyph.y;
      rect.x2_  = rect.x1_ + glyph.w;
      rect.y2_  = rect.y1_ + glyph.h;

      advance += glyph.advance;

      renderer_->renderRectangle(rect, TextureRectangle(glyph.u1, glyph.v1, glyph.u2, glyph.v2));
    }
    renderer_->popTexture();

    ASSERTOP(glGetError(), eq, GL_NO_ERROR);
  }
}
