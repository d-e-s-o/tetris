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

#ifndef WNDWIN32WINDOWIMPLBASE_HPP
#define WNDWIN32WINDOWIMPLBASE_HPP

#include <container/Map.hpp>

#include "window/include/Windows.hpp"
#include "window/Config.hpp"
#include "window/String.hpp"
#include "window/MouseButton.hpp"
#include "window/Key.hpp"
#include "window/Bounds.hpp"
#include "window/Screen.hpp"
#include "window/win32/Win32ScreenImpl.hpp"


namespace wnd
{
  struct Win32Params;


  /**
   * @todo make a difference between normal window and graphic window in
   *       message handling; graphic window should should always poll and
   *       normal window should block until there are new messages
   * @todo if i fullscreen a not maximized window and unfullscreen it again and click to maximize
   *       it is working correctly
   *       however if i take a not maximized window and maximize it and then fullscreen itm
   *       unfullscreen it and unmaximize it, the new unmaxized size is not the one as before
   *       (not sure if thats not even a windows bug, think about that)
   */
  class LIBWINDOW_EXPORT Win32WindowImplBase
  {
  public:
    typedef Screen<Win32ScreenImpl> Win32Screen;

    Win32WindowImplBase(Bounds const& bounds, String const& title, Win32Params const& params);
    virtual ~Win32WindowImplBase();

    bool handleEvents();

    void close();

    virtual bool onMove(Coordinates const& coordinates);
    virtual bool onResize(Dimensions const& dimensions);
    virtual bool onClose();

    virtual bool onMouseMove(Coordinates const& coordinates);
    virtual bool onMouseDown(Coordinates const& coordinates, MouseButton button);
    virtual bool onMouseUp(Coordinates const& coordinates, MouseButton button);

    virtual bool onMouseWheelDown(int units);
    virtual bool onMouseWheelUp(int units);

    virtual bool onKeyDown(Key key, ModifierKey modifiers, bool repeated);
    virtual bool onKeyUp(Key key, ModifierKey modifiers, bool repeated);
    virtual bool onChar(char_t character);

    Coordinates position() const;
    bool move(Coordinates const& coordinates);

    Dimensions size() const;
    bool resize(Dimensions const& dimensions);

    Dimensions clientSize() const;

    Win32Screen&       screen();
    Win32Screen const& screen() const;

  protected:
    virtual LRESULt wndProc(UINT message, WPARAM wparam, LPARAM lparam);

    HWNd WindowHandle() const;

  private:
    typedef ctr::Map<HWND, Win32WindowImplBase*> Windows;

    static Windows     windows_;
    static Win32Screen screen_;

    static LRESULT APIENTRy staticWndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

    HWND        window_;
    Coordinates position_;
    bool        close_;

    Win32WindowImplBase(Win32WindowImplBase const&);
    Win32WindowImplBase& operator =(Win32WindowImplBase const&);

    bool create(Bounds const& bounds, String const& title, DWORD style, DWORD style_ex);
    void destroy() const;
  };
}


namespace wnd
{
  inline HWND Win32WindowImplBase::windowHandle() const
  {
    return window_;
  }
}


#endif
