// Color.hpp

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

#ifndef GUICOLOR_HPP
#define GUICOLOR_HPP

#include <util/Color.hpp>

#include "gui/Config.hpp"


namespace utl
{
  template<>
  struct LIBGUI_EXPORT ColorTrait<unsigned char>
  {
    static unsigned char const min;
    static unsigned char const max;
  };
}

namespace gui
{
  //template class LIBGUI_EXPORT utl::Color<unsigned char>;


  /**
   * This typedef is used for all colors within this library. Colors consist out of four channels,
   * each represented by the smallest addressable unit on the platform - namely a byte.
   */
  typedef utl::Color<unsigned char> Color;
}


#endif
