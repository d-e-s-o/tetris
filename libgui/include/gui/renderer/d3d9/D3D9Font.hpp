// D3D9Font.hpp

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

#ifndef GUID3D9FONT_HPP
#define GUID3D9FONT_HPP

#include "gui/renderer/TextureFont.hpp"


namespace fnt
{
  class FontLoader;
}

namespace gui
{
  class D3D9Renderer;
  class D3D9Texture;


  /**
   * This class implements the Font interface for an OpenGL font.
   */
  class LIBGUI_EXPORT D3D9Font: public TextureFont
  {
  public:
    D3D9Font(D3D9Renderer& renderer, fnt::FontLoader const& loader);
    virtual ~D3D9Font();

    virtual void render(String const& string, Position const& position) const;

  private:
    D3D9Renderer* renderer_;
    D3D9Texture*  texture_;

    TexturedGlyphs glyphs_;
  };
}


#endif
