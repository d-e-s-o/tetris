// OpenGlFont.cpp

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

#include <image/Pixel.hpp>
#include <image/Image.hpp>

#include <font/FontLoader.hpp>

#include "gui/renderer/opengl/ImageRenderer.hpp"
#include "gui/renderer/opengl/OpenGlConstants.hpp"
#include "gui/renderer/opengl/OpenGlFont.hpp"


namespace gui
{
  /**
   * @throw Error if rendering the glyphs failed
   */
  OpenGlFont::OpenGlFont(OpenGlRenderer& renderer, fnt::FontLoader const& loader)
    : Font(),
      first_char_(32),
      char_count_(96),
      lists_(char_count_),
      bounds_(char_count_),
      size_(12)
  {
    if (first_char_ < 0)
      throw Error(TEXT("Error creating bitmap font"), TEXT("Character code cannot be 0"));

    if (char_count_ <= 0)
      throw Error(TEXT("Error creating bitmap font"), TEXT("Character count to create is zero"));

    for (char_t i = 0; i < char_count_; ++i)
    {
      glNewList(lists_.getBase() + i, GL_COMPILE);
      renderGlyph(loader, first_char_ + i);
      glEndList();
    }
  }

  /**
   * @copydoc Font::render
   * @todo the color stuff only works for raster fonts! fix this!
   * @todo try this for coloring the text:
   *       glPixelTransferf( GL_RED_SCALE, 0.0 ); glPixelTransferf( GL_RED_BIAS, c.red );
   *       glPixelTransferf( GL_GREEN_SCALE, 0.0 ); glPixelTransferf( GL_GREEN_BIAS, c.green );
   *       glPixelTransferf( GL_BLUE_SCALE, 0.0 ); glPixelTransferf( GL_BLUE_BIAS, c.blue );
   *       glPixelTransferf( GL_ALPHA_SCALE, c.alpha ); glPixelTransferf( GL_ALPHA_BIAS, 0.0 );
   * @see http://www.gamedev.net/community/forums/topic.asp?topic_id=299883
   */
  void OpenGlFont::render(String const& string, Position const& position) const
  {
    //glColor4ub(color_.getRed(), color_.getGreen(), color_.getBlue(), color_.getAlpha());
    glPushAttrib(GL_TRANSFORM_BIT | GL_LIST_BIT);
    glRasterPos2i(position.x, position.y);

    GLboolean valid = 0;
    glGetBooleanv(GL_CURRENT_RASTER_POSITION_VALID, &valid);

    // if the raster position is not valid the actual window position is negative and we need to
    // use glBitmap as a workaround to renderer the text (but for that we need to get pixel
    // coordinates...)
    if (valid == 0)
    {
      GLdouble modelview[16];
      glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

      GLdouble projection[16];
      glGetDoublev(GL_PROJECTION_MATRIX, projection);

      GLint viewport[4];
      glGetIntegerv(GL_VIEWPORT, viewport);

      GLdouble x = 1.0 * position.x;
      GLdouble y = 1.0 * position.y;
      GLdouble z = 0.0;
      gluProject(x, y, z, modelview, projection, viewport, &x, &y, &z);

      glLoadIdentity();
      glRasterPos2i(0, 0);
      glBitmap(0, 0, 0.0f, 0.0f, static_cast<GLfloat>(x), static_cast<GLfloat>(y), 0);
    }

    GLsizei length = static_cast<GLsizei>(string.size());

    glListBase(lists_.getBase() - first_char_);
    glCallLists(length, getOpenGlConstant<char_t>(0), string.toString());
    glPopAttrib();
  }

  /**
   * @copydoc Font::getBounds
   */
  Bounds OpenGlFont::getBounds(char_t character) const
  {
    return getGlyphBounds(character);
  }

  /**
   * @copydoc Font::getBounds
   */
  Bounds OpenGlFont::getBounds(String const& string) const
  {
    Bounds bounds;

    for (String::ConstIterator it = string.begin(); it != string.end(); ++it)
    {
      Bounds const& glyph_bounds = getGlyphBounds(*it);

      if (it == string.begin())
        bounds.x = glyph_bounds.x;

      bounds.w += glyph_bounds.w;

      if (glyph_bounds.y < bounds.y)
      {
        // if the y position changed we need to adjust the height, because latter is relative to it
        bounds.h += bounds.y - glyph_bounds.y;
        bounds.y  = glyph_bounds.y;
      }

      if (glyph_bounds.h > bounds.h)
        bounds.h = glyph_bounds.h;
    }
    return bounds;
  }

  /**
   * @copydoc Font::size
   */
  SizeT OpenGlFont::size() const
  {
    return size_;
  }

  /**
   * This method renders a given character as a glyph.
   * @param loader font loader to use to render glyph
   * @param character character code of character to render glyph from
   */
  void OpenGlFont::renderGlyph(fnt::FontLoader const& loader, char_t character)
  {
    fnt::GlyphMetrics metrics;

    img::ImageBase* image = loader.render(character, metrics);
    ptr::ResourceGuard<img::ImageBase*, ptr::Deleter> guard(image);

    if (image != 0)
    {
      ImageRenderer renderer(metrics.pen_x, metrics.pen_y, metrics.advance);
      image->use(renderer);

      Bounds& bounds = getGlyphBounds(character);
      bounds = Bounds(metrics.pen_x, metrics.pen_y, metrics.advance, metrics.height);
    }
  }

  /**
   * @param character character code to get bounds from
   */
  Bounds& OpenGlFont::getGlyphBounds(char_t character)
  {
    OpenGlFont const* font = this;
    return const_cast<Bounds&>(font->getGlyphBounds(character));
  }

  /**
   * @param character character code to get bounds from
   * @throw Error if no bounds are found for the given character code
   */
  Bounds const& OpenGlFont::getGlyphBounds(char_t character) const
  {
    GlyphBounds::difference_type i = character - first_char_;
    ASSERTOP(i, ge, 0);
    ASSERTOP(i, lt, bounds_.size());

    if (i <= 0 && i >= bounds_.size())
      throw Error(TEXT("Error retrieving glyph bounds"), TEXT("Invalid character code"));

    return bounds_[i];
  }
}
