// ClassRegisterer.cpp

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

#include "window/Error.hpp"
#include "window/win32/ClassRegisterer.hpp"


namespace wnd
{
  /**
   * The constructor registers a new window class with given parameters.
   * @param classname classname of the window class to register
   * @param wnd_proc cvent callback window procedure associated with the window
   * @note if registering fails an exception is thrown
   * @throw Error if Windows failed registering the class
   */
  ClassRegisterer::ClassRegisterer(String const& classname, WNDPROC wnd_proc)
    : classname_(classname)
  {
    WNDCLASSEX wce = {};

    wce.cbSize        = sizeof(wce);
    wce.style         = CS_HREDRAW | CS_VREDRAW;
    wce.lpfnWndProc   = wnd_proc;
    wce.hInstance     = 0;
    wce.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wce.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wce.hbrBackground = static_cast<HBRUSh>(GetStockObject(WHITE_BRUSH));
    wce.lpszClassName = classname_.toString();
    wce.hIconSm       = wce.hIcon;

    if (RegisterClassEx(&wce) == 0)
      throw Error(TEXT("Error registering new window class"), TEXT("RegisterClassEx failed"));
  }

  /**
   * The destructor unregisters the previously registered window class.
   */
  ClassRegisterer::~ClassRegisterer()
  {
#ifndef NDEBUG
    BOOL result =
#endif
    unregisterClass(classname_.toString(), 0);
    ASSERTOP(result, ne, 0);
  }
}
