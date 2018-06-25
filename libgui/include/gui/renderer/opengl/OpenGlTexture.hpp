// OpenGlTexture.hpp

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

#ifndef GUIOPENGLTEXTURE_HPP
#define GUIOPENGLTEXTURE_HPP

#include "gui/include/OpenGl.hpp"
#include "gui/renderer/Texture.hpp"


namespace img
{
  class ImageBase;
}

namespace gui
{
  class OpenGlRenderer;


  /**
   * This class represents a texture in OpenGL.
   * @todo find a good way to specify which filtering method to use for scaling the texture
   */
  class LIBGUI_EXPORT OpenGlTexture: public Texture
  {
  public:
    OpenGlTexture(OpenGlRenderer& renderer, img::ImageBase const& image, bool flip, bool mip_maps = false);
    virtual ~OpenGlTexture();

    virtual void bind() const;
    virtual void unbind() const;

  private:
    GLuint id_;

    OpenGlTexture(OpenGlTexture const&);
    OpenGlTexture& operator =(OpenGlTexture const&);

    void generateTextureId();
    void deleteTextureId();
  };
}


#endif
