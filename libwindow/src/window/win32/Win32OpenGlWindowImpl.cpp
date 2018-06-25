// Win32OpenGlWindowImpl.cpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#include "window/Error.hpp"
#include "window/GraphicWindowBase.hpp"
#include "window/win32/Win32OpenGlWindowImpl.hpp"


namespace wnd
{
  /**
   * @copydoc Win32WindowImpl::Win32WindowImpl
   * @throw Error if setting up the OpenGl context failed
   */
  Win32OpenGlWindowImpl::Win32OpenGlWindowImpl(GraphicWindowBase& window, Bounds const& bounds, String const& title)
    : Win32GraphicWindowImpl(window, bounds, title),
      rc_(0),
      dc_(0)
  {
    dc_ = GetDC(windowHandle());

    if (dc_ == 0)
      throw Error(TEXT("Error creating Win32OpenGlWindowImpl"), TEXT("GetDC failed"));

    if (!setPixelFormat())
      throw Error(TEXT("Error creating Win32OpenGlWindowImpl"), TEXT("Could not set pixel format"));

    rc_ = wglCreateContext(dc_);

    if (rc_ == 0)
      throw Error(TEXT("Error creating Win32OpenGlWindowImpl"), TEXT("wglCreateContext failed"));

    if (wglMakeCurrent(dc_, rc_) == 0)
      throw Error(TEXT("Error creating Win32OpenGlWindowImpl"), TEXT("wglMakeCurrent failed"));
  }

  /**
   * The destructor destroys the OpenGl window and release the OpenGl context.
   */
  Win32OpenGlWindowImpl::~Win32OpenGlWindowImpl()
  {
    destroy();
  }

  /**
   * @copydoc OpenGlWindow::render
   */
  void Win32OpenGlWindowImpl::render() const
  {
    SwapBuffers(dc_);
  }

  /**
   * This method destroys the rendering context and the device context. If
   * the window is in fullscreen mode, it will change back to window mode
   * before actually destroying the window.
   */
  void Win32OpenGlWindowImpl::destroy()
  {
    wglMakeCurrent(0, 0);
    wglDeleteContext(rc_);

    ReleaseDC(windowHandle(), dc_);
  }

  /**
   * This method sets the pixel format used for the OpenGl scene.
   * @return true if setting pixel format was successful, false if not
   */
  bool Win32OpenGlWindowImpl::setPixelFormat() const
  {
    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize      = sizeof(pfd);
    pfd.nVersion   = 1;
    pfd.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int format = ChoosePixelFormat(dc_, &pfd);
    return ::SetPixelFormat(dc_, format, &pfd) != 0;
  }
}
