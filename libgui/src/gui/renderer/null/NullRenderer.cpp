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

#include <image/Pixel.hpp>
#include <image/Image.hpp>

#include "gui/renderer/null/NullViewport.hpp"
#include "gui/renderer/null/NullTexture.hpp"
#include "gui/renderer/null/NullFont.hpp"
#include "gui/renderer/null/NullRenderer.hpp"


namespace gui
{
  namespace
  {
    NullViewport& getStaticViewport()
    {
      static NullViewport viewport;
      return viewport;
    }

    NullTexture* getStaticTexture()
    {
      static NullTexture texture;
      return &texture;
    }

    NullFont* getStaticFont()
    {
      static NullFont font;
      return &font;
    }
  }


  /**
   * @copydoc Renderer::render
   */
  NullRenderer::NullRenderer()
    : Renderer(getStaticViewport())
  {
  }

  /**
   * @copydoc Renderer::createTexture
   */
  Texture* NullRenderer::createTexture(String const& file)
  {
    return getStaticTexture();
  }

  /**
   * @copydoc Renderer::createFont
   */
  Font* NullRenderer::createFont(String const& name, SizeT size)
  {
    return getStaticFont();
  }

  /**
   * @copydoc Renderer::renderRectangle
   */
  void NullRenderer::renderRectangle(Rectangle const& rect) const
  {
  }

  /**
   * @copydoc Renderer::renderRectangle
   */
  void NullRenderer::renderRectangle(Rectangle const& rect, TextureRectangle const& tex_coords) const
  {
  }

  /**
   * @copydoc Renderer::renderString
   */
  void NullRenderer::renderString(String const& string, Point const& point) const
  {
  }
}
