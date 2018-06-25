// X11OpenGlWindowImpl.cpp

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

#include <GL/glx.h>
#include <util/Assert.hpp>

#include "window/Error.hpp"
#include "window/GraphicWindowBase.hpp"
#include "window/x11/X11OpenGlVisualCreator.hpp"
#include "window/x11/X11OpenGlWindowImpl.hpp"


namespace wnd
{
  /**
   * @param window reference to base window, it is stored for later access
   * @param bounds position and size of the window
   * @param title title of the window
   */
  X11OpenGlWindowImpl::X11OpenGlWindowImpl(GraphicWindowBase& window,
                                           Bounds const& bounds,
                                           String const& title)
    : WindowImpl<GraphicWindowBase,
                 X11WindowImplBase,
                 OpenGlX11VisualCreator>(window, bounds, title, getVisualCreator()),
      context_(nullptr),
      fullscreen_(false)
  {
    XVisualInfo* visual_info = getVisualCreator().getVisualInfo();
    ASSERTOP(visual_info, ne, nullptr);

    context_ = glXCreateContext(getDisplay(), visual_info, 0, True);

    if (context_ == nullptr)
    {
      throw Error(TEXT("Error creating OpenGL rendering context"),
                  TEXT("glXCreateContext returned Null"));
    }

    glXMakeCurrent(getDisplay(), getWindow(), context_);
  }

  /**
   * @copydoc X11WindowImplBase::~X11WindowImplBase
   */
  X11OpenGlWindowImpl::~X11OpenGlWindowImpl()
  {
    if (isFullscreen())
      toggleFullscreen();

    ASSERT(!isFullscreen());

    glXMakeCurrent(getDisplay(), None, 0);
    glXDestroyContext(getDisplay(), context_);
  }

  /**
   * This method displays the rendered scene on the screen. This is neccesarry
   * because we use double buffering. It should therefor be called every frame.
   */
  void X11OpenGlWindowImpl::render() const
  {
    glXSwapBuffers(getDisplay(), getWindow());
  }

  /**
   * @copydoc OpenGlWindowBase::isFullscreen
   */
  bool X11OpenGlWindowImpl::isFullscreen() const
  {
    return fullscreen_;
  }

  /**
   * @copydoc OpenGlWindowBase::toggleFullscreen
   * @todo find a way to do this stuff with pure xlib, without relating on any
   *       window manager to implement _NET_WM_STATE_FULLSCREEN handling
   */
  bool X11OpenGlWindowImpl::toggleFullscreen()
  {
    Display* display = getDisplay();
    ASSERTOP(display, ne, nullptr);

    Atom wm_state = XInternAtom(display, "_NET_WM_STATE", False);
    Atom wm_fullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);

    if (wm_state != 0 && wm_fullscreen != 0)
    {
      XEvent event = {0};
      event.type                 = ClientMessage;
      event.xclient.window       = getWindow();
      event.xclient.message_type = wm_state;
      event.xclient.format       = 32;
      // we could also use 2 for toggling
      event.xclient.data.l[0]    = fullscreen_ ? 0 : 1;
      event.xclient.data.l[1]    = wm_fullscreen;

      Window root = XDefaultRootWindow(display);
      ASSERTOP(root, ne, 0);

      if (root != 0 && XSendEvent(display, root, False, SubstructureNotifyMask, &event) != 0)
      {
        fullscreen_ = !fullscreen_;
        return true;
      }
    }
    return false;
  }

  /**
   * We need some OpenGlX11VisualCreator variable that is created before
   * an object of X11OpenGlWindowImpl is created.
   * @return an instance of OpenGlX11VisualCreator
   */
  OpenGlX11VisualCreator const& X11OpenGlWindowImpl::getVisualCreator() const
  {
    static OpenGlX11VisualCreator visual_creator;
    return visual_creator;
  }
}
