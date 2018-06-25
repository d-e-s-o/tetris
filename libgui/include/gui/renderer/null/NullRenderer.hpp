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

#ifndef GUINULLRENDERER_HPP
#define GUINULLRENDERER_HPP

#include "gui/renderer/Renderer.hpp"


namespace gui
{
  /**
   * This class can be used as a dummy renderer, e.g., for testing purposes. It implements the
   * Renderer interface, but does not actually provide any service.
   */
  class LIBGUI_EXPORT NullRenderer: public Renderer
  {
  public:
    NullRenderer();

    virtual Texture* createTexture(String const& file);
    virtual Font*    createFont(String const& name, SizeT size);

    virtual void renderRectangle(Rectangle const& rect) const;
    virtual void renderRectangle(Rectangle const& rect, TextureRectangle const& tex_coords) const;

    virtual void renderString(String const& string, Point const& position) const;
  };
}


#endif
