// FullscreenManager.hpp

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

#ifndef WNDFULLSCREENMANAGER_HPP
#define WNDFULLSCREENMANAGER_HPP

#include "window/include/Windows.hpp"


namespace wnd
{
  /**
   * This class handles setting a window to fullscreen mode and back to window
   * mode. It takes care for the position and size before and after state
   * change and the different window styles.
   * @todo this class should be told which resolution we want in fullscreen
   *       mode
   * @todo change the SetFullscreen function to ToggleFullscreen
   * @todo use ChangeDisplaySettingsEx instead of ChangeDisplaySettings? I could not find any
   *       documentation about the latter
   */
  class FullscreenManager
  {
  public:
    FullscreenManager(HWND window);

    bool isFullscreen() const;
    bool setFullscreen(bool fullscreen);

  private:
    HWND  window_;
    DWORD last_style_;
    RECT  last_rect_;
    bool  fullscreen_;

    FullscreenManager(FullscreenManager const&);
    FullscreenManager& operator =(FullscreenManager const&);

    bool fullscreenMode();
    bool windowMode();
  };
}


#endif
