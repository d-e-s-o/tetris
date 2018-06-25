// Win32ScreenImpl.hpp

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

#ifndef WNDWIN32SCREENIMPL_HPP
#define WNDWIN32SCREENIMPL_HPP

#include "window/ScreenImpl.hpp"


namespace wnd
{
  class Resolution;


  /**
   *
   */
  class LIBWINDOW_EXPORT Win32ScreenImpl: public ScreenImpl
  {
  public:
    Win32ScreenImpl(ScreenInterface& screen);
    virtual ~Win32ScreenImpl();

    Resolution queryCurrentResolution() const;
    void queryAvailableResolutions();

    void changeResolution(Resolution const& resolution);

  private:
    Resolution createResolution(DEVMODE const& mode) const;
  };
}


namespace wnd
{
  /**
   * @copydoc ScreenImpl::ScreenImpl
   */
  inline Win32ScreenImpl::Win32ScreenImpl(ScreenInterface& screen)
    : ScreenImpl(screen)
  {
  }
}


#endif
