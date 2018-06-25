// FontLoader.hpp

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

#ifndef FNTFONTLOADER_HPP
#define FNTFONTLOADER_HPP

#include <type/Types.hpp>

#include "font/Config.hpp"
#include "font/GlyphMetrics.hpp"


namespace img
{
  class ImageBase;
}

namespace fnt
{
  /**
   * This class defines the interface for every font loader. A font loader can be used to load a
   * font from any ressource into memory and render glyphs with it to an image.
   * @note font loaders are not meant to be copied
   * @note a font may or may not be fixed in size, therefor no resize functionality is
   *       included, though a specialized loader may add it
   * @todo return ptr::SharedPointer in render() method
   */
  class LIBFONT_EXPORT FontLoader
  {
  public:
    FontLoader() = default;
    FontLoader(FontLoader&&) = delete;
    FontLoader(FontLoader const&) = delete;

    virtual ~FontLoader() = 0;

    FontLoader& operator =(FontLoader&&);
    FontLoader& operator =(FontLoader const&);

    /**
     * This method renders the glyphs with the given character code to an image. The image is not
     * flipped in any way, so unless you want it to be flipped or otherwise transformed it is
     * ready for use.
     * @param[in] character character code of glyph to render
     * @param[out] metrics metrics structure filled with glyph data
     * @return pointer to image with rendered glyph on it or 0 if an error occurred
     * @see GlyphMetrics
     */
    virtual img::ImageBase* render(char_t character, GlyphMetrics& metrics) const = 0;

    /**
     * @return size of the font in pixels
     */
    virtual size_t size() const = 0;
  };
}


#endif
