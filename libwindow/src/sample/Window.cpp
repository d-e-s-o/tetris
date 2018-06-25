// Window.cpp

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

#include <iostream>

#include <window/Error.hpp>
#include <window/Window.hpp>

#if defined(LIBWINDOW_WINDOWS)
#  include <window/win32/Win32WindowImpl.hpp>
typedef wnd::Win32WindowImpl SampleWindowImpl;
#  if defined(GetMessage)
#    undef GetMessage
#  endif
#elif defined(LIBWINDOW_LINUX)
#  include <window/x11/X11WindowImpl.hpp>
typedef wnd::X11WindowImpl SampleWindowImpl;
#endif


namespace wnd
{
  /**
   * The SampleWindow class is derived from wnd::Window to get its
   * functionality. It overwrites several event-methods (onXXX) to
   * produce some output in case of that event.
   */
  class SampleWindow: public Window<SampleWindowImpl>
  {
  public:
    sampleWindow(Bounds const& bounds, String const& title);

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
  };
}

namespace wnd
{
  template<typename T>
  std::ostream& operator <<(std::ostream& lhs, utl::Point<T> const& rhs)
  {
    lhs << '[' << rhs.x << '|' << rhs.y << ']';
    return lhs;
  }


  SampleWindow::sampleWindow(Bounds const& bounds, String const& title)
    : window(bounds, title)
  {
  }

  bool SampleWindow::onMove(Coordinates const& coordinates)
  {
    std::cout << "New position:\t" << coordinates << std::endl;
    return true;
  }

  bool SampleWindow::onResize(Dimensions const& dimensions)
  {
    std::cout << "New size:\t" << dimensions << std::endl;
    return true;
  }

  bool SampleWindow::onClose()
  {
    std::cout << "Do you want to close the window [0|1]?" << std::endl;

    int close = 0;
    std::cin >> close;

    return close != 0;
  }

  bool SampleWindow::onMouseMove(Coordinates const& coordinates)
  {
    std::cout << "Mouse Moved to:\t" << coordinates << std::endl;
    return true;
  }

  bool SampleWindow::onMouseDown(Coordinates const& coordinates, MouseButton button)
  {
    std::cout << "Mouse Down at:\t" << coordinates << std::endl;
    return true;
  }

  bool SampleWindow::onMouseUp(Coordinates const& coordinates, MouseButton button)
  {
    std::cout << "Mouse Up at:\t" << coordinates << std::endl;
    return true;
  }

  bool SampleWindow::onMouseWheelDown(int units)
  {
    std::cout << "Wheel Down " << units << " units" << std::endl;
    return true;
  }

  bool SampleWindow::onMouseWheelUp(int units)
  {
    std::cout << "Wheel Up " << units << " units" << std::endl;
    return true;
  }

  bool SampleWindow::onKeyDown(Key key, ModifierKey modifiers, bool repeated)
  {
    std::cout << "Key Down" << std::endl;
    return true;
  }

  bool SampleWindow::onKeyUp(Key key, ModifierKey modifiers, bool repeated)
  {
    std::cout << "Key Up" << std::endl;
    return true;
  }

  bool SampleWindow::onChar(char_t character)
  {
    std::cout << character;
    return true;
  }
}


int main(int argc, char* argv[])
{
  try
  {
    wnd::SampleWindow window(wnd::Bounds(100, 100, 640, 480),
	                         wnd::String(TEXT("SampleWindow")));

    while (window.handleEvents())
    {
    }
  }
  catch(wnd::Error const& error)
  {
    std::cerr << error.message() << std::endl;
  }
  catch(...)
  {
    std::cerr << "An unexpected error occurred" << std::endl;
  }
  return 0;
}
