// GdiRenderer.hpp

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

#ifndef GUIGDIRENDERER_HPP
#define GUIGDIRENDERER_HPP

#include "gui/include/Windows.hpp"
#include "gui/renderer/gdi/GdiTexture.hpp"
#include "gui/renderer/SpecificRenderer.hpp"


namespace gui
{
  template class LIBGUI_EXPORT SpecificRenderer<GdiTexture>;


  /**
   * This class is the renderer for all Microsoft Windows GDI drawing
   * operations.
   */
  class LIBGUI_EXPORT GdiRenderer: public SpecificRenderer<GdiTexture>
  {
  public:
    GdiRenderer(HDC dc);

    virtual void renderSprite(Dimensions const& dimensions, Color const& color) const;
    virtual void renderSprite(Dimensions const& dimensions, Texture const& texture) const;
    virtual void renderSprite(Dimensions const& dimensions, Texture const& texture, Color const& color) const;

    inline HDC getDeviceContext() const;

  private:
    friend GdiTexture;

    HDC dc_;

    mutable GdiTexture* texture_;

    inline void bindTexture(GdiTexture* texture) const;
  };
}


namespace gui
{
  /**
   * This function is mainly used by GdiTexture to implement the Bind
   * method.
   * @param[in] texture pointer to the texture that will get rendererd on the
   *            sprite, or NULL if you want to remove binding
   */
  void GdiRenderer::bindTexture(GdiTexture* texture) const
  {
    texture_ = texture;
  }

  /**
   * @return HDC object to renderer stuff onto
   */
  HDC GdiRenderer::getDeviceContext() const
  {
    return dc_;
  }
}


#endif
