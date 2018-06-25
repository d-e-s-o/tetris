// GdiTexture.cpp

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

#include "Image.hpp"

#include "Error.hpp"
#include "GdiRenderer.hpp"
#include "GdiTexture.hpp"


namespace gui
{
  /**
   * The constructor creates a GDI texture from a given image.
   * @param[in] image image to create the texture from.
   * @param[in] renderer GDI renderer object to be stored and used internally
   */
  GdiTexture::GdiTexture(Image const& image, GdiRenderer const& renderer)
    : renderer_(&renderer),
      bitmap_(0)
  {
    HDC dc = renderer.getDeviceContext();

    if (dc != 0)
    {
      bitmap_ = CreateCompatibleBitmap(dc, image.width(), image.height());

      if (bitmap_ != 0)
      {
      }
      else
        throw Error("Error creating GDI texture", "Error creating new bitmap");
    }
    else
      throw Error("Error creating GDI texture", "Renderer has no device context");
  }

  /**
   * The destructor free's the texture, releasing the allocated GDI bitmap.
   */
  GdiTexture::~GdiTexture()
  {
    DeleteObject(bitmap_);
  }
}
