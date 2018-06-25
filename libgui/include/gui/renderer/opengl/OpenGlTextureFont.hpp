// OpenGlTextureFont.hpp

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

#ifndef GUIOPENGLTEXTUREFONT_HPP
#define GUIOPENGLTEXTUREFONT_HPP

#include "gui/renderer/TextureFont.hpp"


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
  class OpenGlRenderer;
  class OpenGlTexture;


  /**
   * @todo use ptr::ResourceGuard here to protect the OpenGlTexture!
   */
  class LIBGUI_EXPORT OpenGlTextureFont: public TextureFont
  {
  public:
    OpenGlTextureFont(OpenGlRenderer& renderer, fnt::FontLoader const& loader);
    virtual ~OpenGlTextureFont();

    virtual void render(String const& string, Position const& position) const;

  private:
    OpenGlRenderer* renderer_;
    OpenGlTexture*  texture_;

    TexturedGlyphs glyphs_;

    OpenGlTextureFont(OpenGlTextureFont const&);
    OpenGlTextureFont& operator =(OpenGlTextureFont const&);
  };
}


#endif
