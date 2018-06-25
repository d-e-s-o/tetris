// FullscreenManager.cpp

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

#include "window/win32/Win32Functions.hpp"
#include "window/win32/FullscreenManager.hpp"


namespace wnd
{
  /**
   * The constructor creates a new Fullscreenmanager object.
   * @param window handle to window to manage
   */
  FullscreenManager::FullscreenManager(HWND window)
    : window_(window),
      last_style_(0),
      fullscreen_(false)
  {
  }

  /**
   * @return true if the window is in fullscreen mode, false if not
   */
  bool FullscreenManager::isFullscreen() const
  {
    return fullscreen_;
  }

  /**
   * @param fullscreen true if you want fullscreen mode, false for windowed mode
   * @return true of changing was successful, false if not
   */
  bool FullscreenManager::setFullscreen(bool fullscreen)
  {
    if (fullscreen != fullscreen_)
    {
      if (fullscreen)
      {
        if (!fullscreenMode())
          return false;
      }
      else
      {
        if (!windowMode())
          return false;
      }

      ShowWindow(window_, SW_SHOW);
      SetForegroundWindow(window_);
      SetFocus(window_);
      fullscreen_ = fullscreen;
      return true;
    }
    return false;
  }

  /**
   * This method changes the video mode to fullscreen.
   */
  bool FullscreenManager::fullscreenMode()
  {
    ASSERT(!fullscreen_);

    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    DEVMODE mode = {};
    mode.dmSize       = sizeof(mode);
    mode.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT;
    mode.dmPelsWidth  = w;
    mode.dmPelsHeight = h;

    if (ChangeDisplaySettings(&mode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
      return false;

    last_style_ = GetWindowLongPtr(window_, GWL_STYLE);;
    last_rect_  = GetWindowRect(window_);

    SetWindowLong(window_, GWL_STYLE, WS_POPUP);
    SetWindowPos(window_, HWND_TOPMOST, 0, 0, w, h, SWP_FRAMECHANGED);
    return true;
  }

  /**
   * This method can be used to change the current video mode back to
   * windowed mode.
   * @return true if changing to window mode was successful, false if not
   */
  bool FullscreenManager::windowMode()
  {
    ASSERT(fullscreen_);

    if (ChangeDisplaySettings(0, 0) != DISP_CHANGE_SUCCESSFUL)
      return false;

    SetWindowLong(window_, GWL_STYLE, last_style_);

    int x  = last_rect_.left;
    int y  = last_rect_.top;
    int cx = last_rect_.right  - last_rect_.left;
    int cy = last_rect_.bottom - last_rect_.top;

    SetWindowPos(window_, 0, x, y, cx, cy, SWP_FRAMECHANGED);
    return true;
  }
}
