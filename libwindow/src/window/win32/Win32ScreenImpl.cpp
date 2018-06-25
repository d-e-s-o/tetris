// Win32ScreenImpl.cpp

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

#include "window/include/Windows.hpp"
#include "window/Error.hpp"
#include "window/Resolution.hpp"
#include "window/win32/Win32ScreenImpl.hpp"


namespace wnd
{
  namespace
  {
    /**
     * @param mode devmode structure to check if needed fields are set
     * @return true if fields are set, false otherwise
     */
    bool isValidMode(DEVMODE const& mode)
    {
      return (mode.dmFields & DM_PELSWIDTH)  == DM_PELSWIDTH &&
             (mode.dmFields & DM_PELSHEIGHT) == DM_PELSHEIGHT &&
             (mode.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL &&
             (mode.dmFields & DM_DISPLAYFREQUENCY) == DM_DISPLAYFREQUENCY &&
              mode.dmDisplayFrequency > 1; // 0 and 1 means display default value, we do not care
    }
  }


  /**
   *
   */
  Win32ScreenImpl::~Win32ScreenImpl()
  {
    // return to previous display settings
    // @note every change we do with ChangeDisplaySettingsEx() and dwFlags set to 0 is a "dynamic"
    //       change, this is why windows can restore the "real" previous settings
    ChangeDisplaySettingsEx(0, 0, 0, 0, 0);
  }

  /**
   * @copydoc ScreenInterface::queryCurrentResolution
   */
  Resolution Win32ScreenImpl::queryCurrentResolution() const
  {
    DEVMODE mode = {};
    mode.dmSize        = sizeof(mode);
    mode.dmDriverExtra = 0;

    if (EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode) == FALSE || !isValidMode(mode))
      throw Error(TEXT("Error retrieving current resolution"), TEXT("EnumDisplaySettings failed"));

    return createResolution(mode);
  }

  /**
   * @copydoc ScreenInterface::queryAvailableResolutions
   */
  void Win32ScreenImpl::queryAvailableResolutions()
  {
    removeAllResolutions();

    int i = 0;

    DEVMODE mode = {};
    mode.dmSize        = sizeof(mode);
    mode.dmDriverExtra = 0;

    // starting i with zero will query all resolutions and cache them for calls with > 0
    while (EnumDisplaySettings(0, i++, &mode) != FALSE)
    {
      if (isValidMode(mode))
        addResolution(createResolution(mode));
    }
  }

  /**
   * @copydoc ScreenInterface::changeResolution
   */
  void Win32ScreenImpl::changeResolution(Resolution const& resolution)
  {
    DEVMODE mode = {};
    mode.dmSize             = sizeof(mode);
    mode.dmFields           = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY;
    mode.dmPelsWidth        = resolution.getWidth();
    mode.dmPelsHeight       = resolution.getHeight();
    mode.dmBitsPerPel       = resolution.getColorDepth();
    mode.dmDisplayFrequency = resolution.getRefreshRate();

    if (ChangeDisplaySettingsEx(0, &mode, 0, 0, 0) != DISP_CHANGE_SUCCESSFUL)
      throw Error(TEXT("Error setting resolution"), TEXT("ChangeDisplaySettingsEx failed"));
  }

  /**
   * @param mode devmode structure to create resolution from
   * @return resolution created from devmode structure
   */
  Resolution Win32ScreenImpl::createResolution(DEVMODE const& mode) const
  {
    dimension_t width        = mode.dmPelsWidth;
    dimension_t height       = mode.dmPelsHeight;
    int         color_depth  = mode.dmBitsPerPel;
    int         refresh_rate = mode.dmDisplayFrequency;

    return ScreenImpl::createResolution(width, height, color_depth, refresh_rate);
  }
}
