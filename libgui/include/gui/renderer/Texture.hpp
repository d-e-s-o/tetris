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

#ifndef GUITEXTURE_HPP
#define GUITEXTURE_HPP

#include "gui/Config.hpp"
#include "gui/Size.hpp"


namespace gui
{
  /**
   * This is an abstract base class for texture objects. Texture objects are not meant to be copied
   */
  class LIBGUI_EXPORT Texture
  {
  public:
    Texture(Size const& size);
    virtual ~Texture() = 0;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    Size const& size() const;

  private:
    Size size_;

    Texture(Texture const&);
    Texture& operator =(Texture const&);
  };
}


namespace gui
{
  /**
   * The constructor creates a texture object.
   * @param[in] width width of the texture in pixels
   * @param[in] height height of the texture in pixels
   */
  inline Texture::Texture(Size const& size)
    : size_(size)
  {
  }

  /**
   * @return size of the original image data the texture was created from
   */
  inline Size const& Texture::size() const
  {
    return size_;
  }
}


#endif
