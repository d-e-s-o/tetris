// WinFunctions.cpp

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

#include "window/Error.hpp"
#include "window/win32/Win32Functions.hpp"


namespace wnd
{
  /**
   * @throw Error if GetWindowRect failed
   */
  RECT getWindowRect(HWND window)
  {
    RECT rect = {};

    if (GetWindowRect(window, &rect) == 0)
      throw Error(TEXT("Error getting window position"), TEXT("GetWindowRect failed"));

    return rect;
  }

  /**
   * @throw Error if GetClientRect failed
   */
  RECT getClientRect(HWND window)
  {
    RECT rect = {};

    if (GetClientRect(window, &rect) == 0)
      throw Error(TEXT("Error getting window position"), TEXT("GetClientRect failed"));

    return rect;
  }

  /**
   * @throw Error if GetWindowPlacement failed
   */
  RECT getWindowPlacement(HWND window)
  {
    WINDOWPLACEMENT placement = {};
    placement.length = sizeof(placement);

    if (GetWindowPlacement(window, &placement) == 0)
      throw Error(TEXT("Error getting window position"), TEXT("GetWindowPlacement failed"));

    return placement.rcNormalPosition;
  }
}
