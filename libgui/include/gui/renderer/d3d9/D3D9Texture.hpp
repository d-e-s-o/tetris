// D3D9Texture.hpp

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

#ifndef GUID3D9TEXTURE_HPP
#define GUID3D9TEXTURE_HPP

#include "gui/renderer/Texture.hpp"


struct IDirect3DTexture9;

namespace img
{
  class ImageBase;
}

namespace gui
{
  class D3D9Renderer;


  /**
   *
   */
  class LIBGUI_EXPORT D3D9Texture: public Texture
  {
  public:
    D3D9Texture(D3D9Renderer& renderer, img::ImageBase const& image, bool flip);
    virtual ~D3D9Texture();

    virtual void bind() const;
    virtual void unbind() const;

  private:
    D3D9Texture(D3D9Texture const&);
    D3D9Texture& operator =(D3D9Texture const&);

    D3D9Renderer* renderer_;
    IDirect3DTexture9* texture_;
  };
}


#endif
