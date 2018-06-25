// X11Window.hpp

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

#ifndef TESTX11WINDOW_HPP
#define TESTX11WINDOW_HPP

#include <window/Window.hpp>
#include <window/x11/X11WindowImpl.hpp>


namespace test
{
  class X11Window: public wnd::Window<wnd::X11WindowImpl>
  {
  public:
    static int on_move_called_;
    static int on_resize_called_;
    static int on_close_called_;
    static int on_mouse_move_called_;
    static int on_mouse_down_called_;
    static int on_mouse_up_called_;
    static int on_wheel_down_called_;
    static int on_wheel_up_called_;
    static int on_key_down_called_;
    static int on_key_up_called_;
    static int on_char_called_;

    X11Window(wnd::Bounds const& bounds, wnd::String const& title);

    virtual bool onMove(wnd::Coordinates const& coordinates);
    virtual bool onResize(wnd::Dimensions const& dimensions);
    virtual bool onClose();
    virtual bool onMouseMove(wnd::Coordinates const& coordinates);
    virtual bool onMouseDown(wnd::Coordinates const& coordinates, wnd::MouseButton button);
    virtual bool onMouseUp(wnd::Coordinates const& coordinates, wnd::MouseButton button);
    virtual bool onMouseWheelDown(int units);
    virtual bool onMouseWheelUp(int units);
    virtual bool onKeyDown(wnd::Key key, wnd::ModifierKey modifiers, bool repeated);
    virtual bool onKeyUp(wnd::Key key, wnd::ModifierKey modifiers, bool repeated);
    virtual bool onChar(char_t character);
  };
}


#endif
