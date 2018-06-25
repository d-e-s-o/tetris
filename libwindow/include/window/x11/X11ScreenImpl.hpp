// X11ScreenImpl.hpp

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

#ifndef WNDX11SCREENIMPL_HPP
#define WNDX11SCREENIMPL_HPP

#include "window/ScreenImpl.hpp"


typedef struct _XDisplay Display;


namespace wnd
{
  class Resolution;


  /**
   * @todo currently we query and change resolution via XRandR extension, we should also support
   *       the XF86VidMode thing
   * @todo the X11 window class and the screen class should somehow function together - atm every
   *       class uses its own x-connection (display) and screen number
   */
  class LIBWINDOW_EXPORT X11ScreenImpl: public ScreenImpl
  {
  public:
    X11ScreenImpl(ScreenInterface& screen);
    virtual ~X11ScreenImpl();

    Resolution queryCurrentResolution() const;
    void queryAvailableResolutions();

    void changeResolution(Resolution const& resolution);

  private:
    Display* display_;
    int      screen_;

    Resolution last_resolution_;

    X11ScreenImpl(X11ScreenImpl const&);
    X11ScreenImpl& operator =(X11ScreenImpl const&);
  };
}


#endif
