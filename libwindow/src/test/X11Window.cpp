// X11Window.cpp

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

#include "X11Window.hpp"


namespace test
{
  int X11Window::on_move_called_       = 0;
  int X11Window::on_resize_called_     = 0;
  int X11Window::on_close_called_      = 0;
  int X11Window::on_mouse_move_called_ = 0;
  int X11Window::on_mouse_down_called_ = 0;
  int X11Window::on_mouse_up_called_   = 0;
  int X11Window::on_wheel_down_called_ = 0;
  int X11Window::on_wheel_up_called_   = 0;
  int X11Window::on_key_down_called_   = 0;
  int X11Window::on_key_up_called_     = 0;
  int X11Window::on_char_called_       = 0;


  X11Window::X11Window(wnd::Bounds const& bounds, wnd::String const& title)
    : Window<wnd::X11WindowImpl>(bounds, title)
  {
  }

  bool X11Window::onMove(wnd::Coordinates const& coordinates)
  {
    ++on_move_called_;
    return true;
  }

  bool X11Window::onResize(wnd::Dimensions const& dimensions)
  {
    ++on_resize_called_;
    return true;
  }

  bool X11Window::onClose()
  {
    ++on_close_called_;
    return true;
  }

  bool X11Window::onMouseMove(wnd::Coordinates const& coordinates)
  {
    ++on_mouse_move_called_;
    return true;
  }

  bool X11Window::onMouseDown(wnd::Coordinates const& coordinates, wnd::MouseButton button)
  {
    ++on_mouse_down_called_;
    return true;
  }

  bool X11Window::onMouseUp(wnd::Coordinates const& coordinates, wnd::MouseButton button)
  {
    ++on_mouse_up_called_;
    return true;
  }

  bool X11Window::onMouseWheelDown(int units)
  {
    ++on_wheel_down_called_;
    return true;
  }

  bool X11Window::onMouseWheelUp(int units)
  {
    ++on_wheel_up_called_;
    return true;
  }

  bool X11Window::onKeyDown(wnd::Key key, wnd::ModifierKey modifiers, bool repeated)
  {
    ++on_key_down_called_;
    return true;
  }

  bool X11Window::onKeyUp(wnd::Key key, wnd::ModifierKey modifiers, bool repeated)
  {
    ++on_key_up_called_;
    return true;
  }

  bool X11Window::onChar(char_t character)
  {
    ++on_char_called_;
    return true;
  }
}
