// Win32OpenGlWindowImpl.hpp

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

#ifndef WNDWIN32OPENGLWINDOWIMPL_HPP
#define WNDWIN32OPENGLWINDOWIMPL_HPP

#include "window/win32/Win32GraphicWindowImpl.hpp"


namespace wnd
{
  /**
   * @todo going back to desktop with alt+tab does not work correclty - fix this!
   */
  class LIBWINDOW_EXPORT Win32OpenGlWindowImpl: public Win32GraphicWindowImpl
  {
  public:
    Win32OpenGlWindowImpl(GraphicWindowBase& window, Bounds const& bounds, String const& title);
    virtual ~Win32OpenGlWindowImpl();

    void render() const;

  private:
    HDC   dc_;
    HGLRC rc_;

    void destroy();

    bool setPixelFormat() const;
  };
}


#endif
