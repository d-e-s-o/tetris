// Win32GraphicWindowImpl.cpp

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

#include "window/GraphicWindowBase.hpp"
#include "window/win32/Win32Params.hpp"
#include "window/win32/FullscreenManager.hpp"
#include "window/win32/Win32GraphicWindowImpl.hpp"


namespace wnd
{
  /**
   * @copydoc Win32WindowImpl::Win32WindowImpl
   * @throw Error if setting up the OpenGl context failed
   */
  Win32GraphicWindowImpl::Win32GraphicWindowImpl(GraphicWindowBase& window, Bounds const& bounds, String const& title)
    : windowImpl(window, bounds, title, Win32Params(WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)),
      fs_manager_(new fullscreenManager(windowHandle())),
      active_(true)
  {
  }

  /**
   * The destructor destroys the OpenGl window and release the OpenGl context.
   * @todo move the whole fullscreen thing into the window base class, this would also allow to
   *       remove the strange effect that ToggleFullscreen will cause events to be sent (resize
   *       etc.) and because the HWND is still registered and might cause actions on objects within
   *       the window that are already destroyed (!) [=> access violation]
   */
  Win32GraphicWindowImpl::~Win32GraphicWindowImpl()
  {
    if (isFullscreen())
      toggleFullscreen();

    ASSERT(!isFullscreen());
  }

  /**
   * @return true if window is in fullscreen mode, false if not
   */
  bool Win32GraphicWindowImpl::isFullscreen() const
  {
    return fs_manager_->isFullscreen();
  }

  /**
   * @return true if changing state was successful, false if not
   */
  bool Win32GraphicWindowImpl::toggleFullscreen()
  {
    return fs_manager_->setFullscreen(!fs_manager_->isFullscreen());
  }

  /**
   * @copydoc Win32WindowImpl::wndProc
   */
  LRESULT Win32GraphicWindowImpl::wndProc(UINT message, WPARAM wparam, LPARAM lparam)
  {
    switch(message)
    {
    case WM_SYSCOMMAND:
      switch (wparam)
      {
      case SC_SCREENSAVE:
      case SC_MONITORPOWER:
        return 0;
      }
      break;

    case WM_SIZE:
      active_ = (wparam != SIZE_MINIMIZED);
      break;

    case WM_ENTERSIZEMOVE:
    case WM_ENTERMENULOOP:
      active_ = false;
      break;

    case WM_EXITSIZEMOVE:
    case WM_EXITMENULOOP:
      active_ = true;
      break;

    case WM_ACTIVATEAPP:
      active_ = (wparam != FALSE);
      break;
    }
    return WindowImpl::wndProc(message, wparam, lparam);
  }
}
