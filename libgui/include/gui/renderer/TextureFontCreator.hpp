// TextureFontCreator.hpp

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

#ifndef GUITEXTUREFONTCREATOR_HPP
#define GUITEXTUREFONTCREATOR_HPP

#include <vector>

#include "gui/Config.hpp"
#include "gui/Allocator.hpp"
#include "gui/Bounds.hpp"


namespace img
{
  class ImageBase;
}

namespace fnt
{
  class FontLoader;
}

namespace gui
{
  /**
   * This structure represents a glyph on a texture.
   * @todo think about using Texture Rectangle and Rectangle here
   */
  struct TexturedGlyph
  {
    // x1 and y1 is the lower left vertex of the quad
    int x;
    int y;
    int w;
    int h;

    float u1;
    float v1;
    float u2;
    float v2;

    // number of units (in general pixels) to advance after drawing the glyph
    int advance;
  };

  /**
   * A vector with multiple textured glyphs, e.g. for a whole font
   * @todo replace std::vector with ctr::Array
   */
  typedef Allocator::rebind<TexturedGlyph>::other Allocator1;
  typedef std::vector<TexturedGlyph, Allocator1> TexturedGlyphs;

  /**
   *
   */
  typedef Allocator::rebind<Bounds>::other Allocator2;
  typedef std::vector<Bounds, Allocator2> GlyphBounds;


  /**
   *
   */
  class TextureFontCreator
  {
  public:
    TextureFontCreator(fnt::FontLoader const& loader, int max_width, int max_height, char_t first, char_t count);
    ~TextureFontCreator();

    img::ImageBase const& getImage() const;
    TexturedGlyphs const& getGlyphs() const;
    GlyphBounds    const& getBounds() const;

  private:
    char_t first_char_;
    char_t char_count_;

    /**
     * @todo use something from libpointer here to protect image_
     */
    img::ImageBase* image_;
    TexturedGlyphs  glyphs_;
    GlyphBounds     bounds_;

    void createTextureFont(fnt::FontLoader const& loader, int max_width, int max_height);
  };
}


namespace gui
{
  /**
   *
   */
  inline img::ImageBase const& TextureFontCreator::getImage() const
  {
    return *image_;
  }

  /**
   *
   */
  inline TexturedGlyphs const& TextureFontCreator::getGlyphs() const
  {
    return glyphs_;
  }

  /**
   *
   */
  inline GlyphBounds const& TextureFontCreator::getBounds() const
  {
    return bounds_;
  }
}


#endif
