// X11VisualCreatorBase.hpp

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

#ifndef WNDX11VISUALCREATORBASE_HPP
#define WNDX11VISUALCREATORBASE_HPP

#include <X11/Xlib.h>


namespace wnd
{
  class X11VisualCreatorBase
  {
  public:
    virtual ~X11VisualCreatorBase() = 0;

    virtual Visual* operator ()(Display* display, int screen, int& depth) const = 0;
  };
}


#endif
