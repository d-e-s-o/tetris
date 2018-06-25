// GdiTexture.hpp

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

#ifndef GUIGDITEXTURE_HPP
#define GUIGDITEXTURE_HPP

#include "gui/include/Windows.hpp"
#include "gui/texture/Texture.hpp"


namespace gui
{
  class Image;
  class GdiRenderer;


  /**
   * This class represents a "texture" for Microsoft Windows GDI. That is
   * basically a pre-rendered bitmap, that can be blitted fast onto a given
   * device context.
   */
  class LIBGUI_EXPORT GdiTexture: public Texture
  {
  public:
    GdiTexture(Image const& image, GdiRenderer const& renderer);
    virtual ~GdiTexture();

    virtual void bind() const;
    virtual void unbind() const;

  private:
    GdiRenderer const* renderer_;

    HBITMAP bitmap_;
  };
}


#endif
