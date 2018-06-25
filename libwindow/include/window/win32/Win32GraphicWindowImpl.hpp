// Win32GraphicWindowImpl.hpp

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

#ifndef WNDWIN32GRAPHICWINDOWIMPL_HPP
#define WNDWIN32GRAPHICWINDOWIMPL_HPP

#include <memory>

#include "window/win32/Win32WindowImplBase.hpp"
#include "window/WindowImpl.hpp"


namespace wnd
{
  class GraphicWindowBase;
  class FullscreenManager;


  /**
   * @todo going back to desktop with alt+tab does not work correclty - fix this!
   * @todo use the active_ variable and create getter for it
   */
  class LIBWINDOW_EXPORT Win32GraphicWindowImpl: public WindowImpl<GraphicWindowBase, Win32WindowImplBase, Win32Params>
  {
  public:
    Win32GraphicWindowImpl(GraphicWindowBase& window, Bounds const& bounds, String const& title);
    virtual ~Win32GraphicWindowImpl();

    bool isFullscreen() const;
    bool toggleFullscreen();

  protected:
    virtual LRESULt wndProc(UINT message, WPARAM wparam, LPARAM lparam);

  private:
    typedef std::auto_ptr<FullscreenManager> FsManagerPtr;

    FsManagerPtr fs_manager_;
    bool active_;
  };
}


#endif
