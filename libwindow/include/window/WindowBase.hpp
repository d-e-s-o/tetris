// WindowBase.hpp

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

#ifndef WNDWINDOWBASE_HPP
#define WNDWINDOWBASE_HPP

#include "window/WindowInterface.hpp"


namespace wnd
{
  /**
   * This class is the base class for every regular window.
   */
  class LIBWINDOW_EXPORT WindowBase: public WindowInterface
  {
  public:
    /**
     * This method gets called everytime the content of the window got invalid
     * and has to be redrawn.
     * @return true if handling was successful, false if not
     */
    virtual bool onDraw() = 0;
  };
}


#endif
