// X11ScreenImpl.cpp

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

#include <X11/Xlib.h>
//#include <X11/Xutil.h>
#include <X11/extensions/Xrandr.h>
//#include <X11/extensions/xf86vmode.h>

#include <pointer/ResourceGuard.hpp>

#include "window/Error.hpp"
#include "window/Resolution.hpp"
#include "window/x11/X11ScreenImpl.hpp"


namespace wnd
{
  namespace
  {
    typedef void (*FreeConfig)(XRRScreenConfiguration*);
    typedef ptr::ResourceGuard<XRRScreenConfiguration*, FreeConfig> ConfigGuard;
  }


  /**
   * @copydoc ScreenImpl::ScreenImpl
   */
  X11ScreenImpl::X11ScreenImpl(ScreenInterface& screen)
    : ScreenImpl(screen),
      display_(0),
      screen_(0),
      last_resolution_(createDummyResolution())
  {
    display_ = XOpenDisplay(0);
    screen_  = XDefaultScreen(display_);
  }

  /**
   * @copydoc ScreenImpl::~ScreenImpl
   */
  X11ScreenImpl::~X11ScreenImpl()
  {
    try
    {
      // ChangeResolution may throw Error, but we should not let it propagate out of the destructor
      if (last_resolution_ != createDummyResolution())
        changeResolution(last_resolution_);
    }
    catch(...) { }

    XCloseDisplay(display_);
  }

  /**
   * @copydoc ScreenInterface::queryCurrentResolution
   */
  Resolution X11ScreenImpl::queryCurrentResolution() const
  {
//    int clock = 0;
//    XF86VidModeModeLine mode = {};
//
//    if (XF86VidModeGetModeLine(display_, screen_, &clock, &mode) != True)
//      throw Error(TEXT("Error retrieving current resolution"), TEXT("XF86VidModeGetModeLine failed"));

    dimension_t width        = 0;
    dimension_t height       = 0;
    int         color_depth  = XDefaultDepth(display_, screen_);
    int         refresh_rate = 0;

    XRRScreenConfiguration* config = XRRGetScreenInfo(display_, XDefaultRootWindow(display_));
    ConfigGuard guard(config, reinterpret_cast<FreeConfig>(&XRRFreeScreenConfigInfo));

    int count = 0;
    XRRScreenSize* sizes = XRRConfigSizes(config, &count);

    if (count > 0)
    {
      Rotation rotation;
      SizeID   current = XRRConfigCurrentConfiguration(config, &rotation);

      if (current >= 0 && current < count)
      {
        width  = sizes[current].width;
        height = sizes[current].height;

        refresh_rate = XRRConfigCurrentRate(config);
      }
      else
      {
        throw Error(TEXT("Error retrieving current resolution"),
                    TEXT("XRRConfigCurrentConfiguration returned invalid index"));
      }
    }
    else
      throw Error(TEXT("Error retrieving current resolution"), TEXT("XRRConfigSizes returned zero"));

    return createResolution(width, height, color_depth, refresh_rate);
  }

  /**
   * @copydoc ScreenInterface::queryAvailableResolutions
   * @todo we need code that also queries the supported color depths for each resolution, find out
   *       how to do that
   */
  void X11ScreenImpl::queryAvailableResolutions()
  {
//    int count = 0;
//    XF86VidModeModeInfo** modes;
//    XF86VidModeGetAllModeLines(display_, screen_, &count, &modes);
//    XFree(&modes);

    removeAllResolutions();

    int color_depth = XDefaultDepth(display_, screen_);
    int count_size  = 0;

    XRRScreenSize* sizes = XRRSizes(display_, screen_, &count_size);

    for (int i = 0; i < count_size; ++i)
    {
      dimension_t width  = sizes[i].width;
      dimension_t height = sizes[i].height;

      int count_rate = 0;
      short* rates   = XRRRates(display_, screen_, i, &count_rate);

      for (int j = 0; j < count_rate; ++j)
        addResolution(createResolution(width, height, color_depth, rates[j]));
    }
  }

  /**
   * @copydoc ScreenInterface::changeResolution
   */
  void X11ScreenImpl::changeResolution(Resolution const& resolution)
  {
    //XF86VidModeSwitchToMode

    XRRScreenConfiguration* config = XRRGetScreenInfo(display_, XDefaultRootWindow(display_));
    ConfigGuard guard(config, reinterpret_cast<FreeConfig>(&XRRFreeScreenConfigInfo));

    int index  = 0;
    int count  = 0;
    XRRScreenSize* sizes = XRRConfigSizes(config, &count);

    // look for the given resolution within the array of available ones (we need the index)
    for (; index < count; ++index)
    {
      dimension_t width  = sizes[index].width;
      dimension_t height = sizes[index].height;
      int         depth  = resolution.colorDepth();
      int         rate   = resolution.refreshRate();

      if (resolution == createResolution(width, height, depth, rate))
        break;
    }

    // check whether an index was found and set it
    if (index >= 0 && index < count)
    {
      // store current resolution if this is the first change
      if (last_resolution_ == createDummyResolution())
        last_resolution_ = queryCurrentResolution();

      // we need timestamp of server and current rotation
      Time dummy = 0;
      Time time = XRRTimes(display_, screen_, &dummy);

      Rotation rotation = 0;
      XRRConfigCurrentConfiguration(config, &rotation);

      if (XRRSetScreenConfigAndRate(display_, config,
                                    XDefaultRootWindow(display_),
                                    index,
                                    rotation,
                                    resolution.refreshRate(),
                                    time) != Success)
      {
        throw Error(TEXT("Error changing resolution"),
                    TEXT("XRRSetScreenConfigAndRate returned error code"));
      }
    }
    else
      throw Error(TEXT("Error changing resolution"), TEXT("Given resolution not found in list"));
  }
}
