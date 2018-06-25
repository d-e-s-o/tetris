// OpenGlFont.hpp

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

#ifndef GUIOPENGLFONT_HPP
#define GUIOPENGLFONT_HPP

#include <vector>

#include "gui/Allocator.hpp"
#include "gui/Color.hpp"
#include "gui/renderer/opengl/OpenGlDisplayLists.hpp"
#include "gui/renderer/Font.hpp"


namespace fnt
{
  class FontLoader;
}

namespace gui
{
  class OpenGlRenderer;


  /**
   * This class implements the Font interface for an OpenGL font.
   */
  class LIBGUI_EXPORT OpenGlFont: public Font
  {
  public:
    OpenGlFont(OpenGlRenderer& renderer, fnt::FontLoader const& loader);

    virtual void render(String const& string, Position const& position) const;

    virtual Bounds getBounds(char_t character) const;
    virtual Bounds getBounds(String const& string) const;

    virtual SizeT size() const;

  private:
    typedef gui::Allocator::rebind<Bounds>::other Allocator;
    typedef std::vector<Bounds, Allocator> GlyphBounds;

    char_t first_char_;
    char_t char_count_;
    OpenGlDisplayLists lists_;
    GlyphBounds bounds_;
    SizeT size_;

    void renderGlyph(fnt::FontLoader const& loader, char_t character);

    Bounds&       getGlyphBounds(char_t character);
    Bounds const& getGlyphBounds(char_t character) const;
  };
}


#endif
