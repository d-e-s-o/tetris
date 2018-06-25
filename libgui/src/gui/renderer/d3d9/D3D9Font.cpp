// D3D9Font.cpp

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

#include <pointer/Deleter.hpp>
#include <pointer/ResourceGuard.hpp>
#include <util/Rectangle1Functions.hpp>

#include "gui/include/D3D9.hpp"
#include "gui/renderer/d3d9/D3D9Renderer.hpp"
#include "gui/renderer/d3d9/D3D9Font.hpp"


namespace gui
{
  /**
   * @copydoc Font::Font
   */
  D3D9Font::D3D9Font(D3D9Renderer& renderer, fnt::FontLoader const& loader)
    : TextureFont(loader.size(), 32, 96),
      renderer_(&renderer),
      texture_(0)
  {
    IDirect3DDevice9& device = renderer.getDevice();

    D3DCAPS9 capabilities = {};
    device.GetDeviceCaps(&capabilities);

    int max_width  = capabilities.MaxTextureWidth;
    int max_height = capabilities.MaxTextureHeight;

    TextureFontCreator font_creator(loader, max_width, max_height, getFirstChar(), getCharCount());

    texture_ = new D3D9Texture(renderer, font_creator.getImage(), false);
    ptr::ResourceGuard<D3D9Texture*, ptr::Deleter> guard(texture_);

    updateBounds(font_creator.getBounds());
    glyphs_ = font_creator.getGlyphs();

    guard.release();
  }

  /**
   *
   */
  D3D9Font::~D3D9Font()
  {
    delete texture_;
  }

  /**
   * @copydoc Font::render
   */
  void D3D9Font::render(String const& string, Position const& position) const
  {
    renderer_->pushTexture(texture_);

    int advance = 0;

    for (String::ConstIterator it = string.begin(), end = string.end(); it != end; ++it)
    {
      // @todo we probably should add some range checking here
      TexturedGlyph const& glyph  = glyphs_[*it - getFirstChar()];

      Rectangle rect(position.x + advance, position.y, 0, 0);
      rect.x1_ += glyph.x;
      rect.y1_ += glyph.y;
      rect.x2_  = rect.x1_ + glyph.w;
      rect.y2_  = rect.y1_ + glyph.h;

      advance += glyph.advance;

      renderer_->renderRectangle(rect, TextureRectangle(glyph.u1, glyph.v1, glyph.u2, glyph.v2));
    }
    renderer_->popTexture();
  }
}
