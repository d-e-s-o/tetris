// OpenGlFunctions.hpp

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

#ifndef GUIOPENGLFUNCTIONS_HPP
#define GUIOPENGLFUNCTIONS_HPP

#include "gui/include/OpenGl.hpp"


namespace img
{
  template<typename Pixel>
  class Image;
}

namespace gui
{
  template<typename Pixel>
  GLint getColors(img::Image<Pixel> const& image);

  template<typename Pixel>
  GLint getFormat(img::Image<Pixel> const& image);

  template<typename Pixel>
  GLenum getPixelFormat(img::Image<Pixel> const& image);

  template<typename Pixel>
  GLenum getColorFormat(img::Image<Pixel> const& image);

  bool isTextureSizeSupported(GLsizei width, GLsizei height, GLint colors, GLenum pixel_format, GLenum color_format);
}


#endif
