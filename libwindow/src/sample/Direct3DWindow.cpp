// Direct3DWindow.cpp

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
#include <window/Direct3DWindow.hpp>

#if defined(LIBWINDOW_WINDOWS)
#  include <d3d9.h>
#  include <window/win32/Win32D3D9WindowImpl.hpp>
typedef wnd::Win32D3D9WindowImpl WindowImpl;
#  if defined(GetMessage)
#    undef GetMessage
#  endif
#else
#  error "Only Windows supports Direct3D"
#endif


namespace wnd
{
  /**
   *
   */
  class SampleDirect3DWindow: public Direct3DWindow<WindowImpl>
  {
  public:
    SampleDirect3DWindow(Bounds const& bounds, String const& title);

    virtual void render() const;
  };
}

namespace wnd
{
  /**
   *
   */
  SampleDirect3DWindow::SampleDirect3DWindow(Bounds const& bounds, String const& title)
    : Direct3DWindow(bounds, title)
  {
    initialize();
  }

  /**
   * All rendering code (also including e.g. glClear) goes in here.
   */
  void SampleDirect3DWindow::render() const
  {
    Direct3DDevice& device = getD3DDevice();

    device.Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOr_XRGB(127, 127, 255), 1.0f, 0);
    device.BeginScene();

    device.EndScene();

    Direct3DWindow::render();
  }
}


int main(int argc, char* argv[])
{
  try
  {
    wnd::SampleDirect3DWindow window(wnd::Bounds(100, 100, 640, 480),
                                     wnd::String(TEXT("SampleDirect3DWindow")));

    while (window.handleEvents())
      window.render();
  }
  catch(wnd::Error const& error)
  {
    std::cerr << error.message() << std::endl;
  }
  catch(...)
  {
    std::cerr << TEXT("An unexpected error occurred") << std::endl;
  }
  return 0;
}
