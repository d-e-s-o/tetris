// Win32WindowImpl.hpp

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

#ifndef WNDWIN32WINDOWIMPL_HPP
#define WNDWIN32WINDOWIMPL_HPP

#include "window/win32/Win32Params.hpp"
#include "window/win32/Win32WindowImplBase.hpp"
#include "window/WindowImpl.hpp"


namespace wnd
{
  class WindowBase;


  /**
   *
   */
  class LIBWINDOW_EXPORT Win32WindowImpl: public WindowImpl<WindowBase, Win32WindowImplBase, Win32Params>
  {
  public:
    Win32WindowImpl(WindowBase& window, Bounds const& bounds, String const& title);

    virtual bool onDraw();

  protected:
    virtual LRESULt wndProc(UINT message, WPARAM wparam, LPARAM lparam);
  };
}


#endif
