// D3D9Functions.cpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#include <util/Assert.hpp>
#include <image/Pixel.hpp>
using namespace img;

#include "gui/include/D3D9.hpp"
#include "gui/renderer/d3d9/D3D9Functions.hpp"


namespace gui
{
  template<>
  D3DFORMAT getPixelFormat(Image<PixelUByteRGBA> const& image)
  {
    return D3DFMT_A8R8G8B8;
  }

  template<>
  D3DFORMAT getPixelFormat(Image<PixelUByteRGB> const& image)
  {
    return D3DFMT_R8G8B8;
  }

  template<>
  D3DFORMAT getPixelFormat(Image<PixelUByteA> const& image)
  {
    return D3DFMT_A8;
  }

  template<>
  D3DFORMAT getPixelFormat(Image<PixelUWordRGBA> const& image)
  {
    return D3DFMT_A16B16G16R16;
  }

  template<>
  D3DFORMAT getPixelFormat(Image<PixelUWordRGB> const& image)
  {
    // not supported
    ASSERT(false);
    return D3DFMT_UNKNOWN;
  }

  template<>
  D3DFORMAT getPixelFormat(Image<PixelBitmap> const& image)
  {
    // not supported
    ASSERT(false);
    return D3DFMT_UNKNOWN;
  }
}
