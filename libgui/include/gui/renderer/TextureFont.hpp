// TextureFont.hpp

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

#ifndef GUITEXTUREFONT_HPP
#define GUITEXTUREFONT_HPP

#include "gui/renderer/TextureFontCreator.hpp"
#include "gui/renderer/Font.hpp"


namespace gui
{
  /**
   *
   */
  class LIBGUI_EXPORT TextureFont: public Font
  {
  public:
    TextureFont(SizeT size, char_t first_char, char_t char_count);

    virtual Bounds getBounds(char_t character) const;
    virtual Bounds getBounds(String const& string) const;

    virtual Bounds getMaxBounds() const;

    virtual SizeT size() const;

  protected:
    void updateBounds(GlyphBounds const& bounds);

    char_t getFirstChar() const;
    char_t getCharCount() const;

    Bounds const& getGlyphBounds(char_t character) const;

  private:
    char_t first_char_;
    char_t char_count_;

    GlyphBounds bounds_;

    Bounds max_bounds_;
    SizeT  size_;

    TextureFont(TextureFont const&);
    TextureFont& operator =(TextureFont const&);

    void updateMaxBounds(GlyphBounds const& bounds);
  };
}


namespace gui
{
  /**
   *
   */
  inline char_t TextureFont::getFirstChar() const
  {
    return first_char_;
  }

  /**
   *
   */
  inline char_t TextureFont::getCharCount() const
  {
    return char_count_;
  }
}


#endif
