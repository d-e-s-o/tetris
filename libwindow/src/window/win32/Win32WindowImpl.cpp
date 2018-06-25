// Win32WindowImpl.cpp

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

#include "window/WindowBase.hpp"
#include "window/win32/Win32WindowImpl.hpp"


namespace wnd
{
  /**
   * @param window window that this object acts as implementation for
   * @param bounds desired bounds (position and size) of the window
   * @param title desired title of the window
   * @todo check if we really need the "little trick" below
   */
  Win32WindowImpl::Win32WindowImpl(WindowBase& window, Bounds const& bounds, String const& title)
    : windowImpl(window, bounds, title, Win32Params(WS_OVERLAPPEDWINDOW, 0))
  {
    // little "trick" to release WM_PAINT message, that will be triggered after
    // finishing construction, so the REAL OnDraw will be called
    invalidateRect(windowHandle(), 0, TRUE);
  }

  /**
   * @copydoc WindowBase::onDraw
   * @note we need to call BeginPaint() and EndPaint() to not get an infinite
   *       number of WM_PAINT messages
   */
  bool Win32WindowImpl::onDraw()
  {
    PAINTSTRUCT ps;
    BeginPaint(windowHandle(), &ps);
    EndPaint(windowHandle(), &ps);

    return owner().onDraw();
  }

  /**
   * @copydoc Win32WindowImplBase::wndProc
   */
  LRESULT Win32WindowImpl::wndProc(UINT message, WPARAM wparam, LPARAM lparam)
  {
    switch(message)
    {
    case WM_PAINT:
      onDraw();
      return 0;
    }
    return WindowImpl<WindowBase, Win32WindowImplBase, Win32Params>::wndProc(message, wparam, lparam);
  }
}
