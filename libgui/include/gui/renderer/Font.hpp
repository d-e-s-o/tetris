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

#ifndef GUIFONT_HPP
#define GUIFONT_HPP

#include "gui/Config.hpp"
#include "gui/String.hpp"
#include "gui/Position.hpp"
#include "gui/Bounds.hpp"


namespace gui
{
  /**
   * Abstract base class for every font within this library. It defines the interface that has to
   * be implemented by every subclass.
   * @note fonts are not meant to be copied
   */
  class LIBGUI_EXPORT Font
  {
  public:
    Font();
    virtual ~Font() = 0;

    /**
     * @param[in] string string to render to screen
     * @param[in] position position to render the string at
     */
    virtual void render(String const& string, Position const& position) const = 0;

    /**
     * @param[in] character character to calculate bounds from
     * @return bounds of the given string
     */
    virtual Bounds getBounds(char_t character) const = 0;

    /**
     * @param[in] string string to calculate bounds from
     * @return bounds of the given string
     */
    virtual Bounds getBounds(String const& string) const = 0;

    /**
     * This method can be used to determine the maximum bounds calculated from all the glyphs
     * represented by this font. This can be seen as a bounding box where every glyph of this font
     * fits in. The individual values are:
     * x_: the minimum x value a glyph may have
     * y_: the minimum y value a glyph may have
     * w_: the maximum width a glyph may have
     * h_: the maximum height a glyph may have
     * @return maximum bounds calculated from all glyphs
     */
    virtual Bounds getMaxBounds() const = 0;

    /**
     * @return size of the font in pixels
     */
    virtual SizeT size() const = 0;

  private:
    Font(Font const&);
    Font& operator =(Font const&);
  };
}


#endif
