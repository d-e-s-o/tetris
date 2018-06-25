// OpenGlWindow.cpp

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
#include <window/OpenGlWindow.hpp>

// depending on the operating system we compile for we need another implementation
#if defined(LIBWINDOW_WINDOWS)
#  include <window/win32/Win32OpenGlWindowImpl.hpp>
typedef wnd::Win32OpenGlWindowImpl WindowImpl;
#  if defined(GetMessage)
#    undef GetMessage
#  endif
#elif defined(LIBWINDOW_LINUX)
#  include <window/x11/X11OpenGlWindowImpl.hpp>
typedef wnd::X11OpenGlWindowImpl WindowImpl;
#endif


namespace wnd
{
  /**
   * The SampleOpenGlWindow class is derived from wnd::Window to get its
   * functionality.
   */
  class SampleOpenGlWindow: public OpenGlWindow<WindowImpl>
  {
  public:
    SampleOpenGlWindow(Bounds const& bounds, String const& title);

    virtual void render() const;

    virtual bool onKeyDown(Key key, ModifierKey modifiers);
  };
}

namespace wnd
{
  /**
   * The constructor calls the base class constructor which actually creates the window. You will
   * most likely want to call Initialize in here to do some one-time-initializations (like setting
   * clear color, loading textures, ...). Also note that Initialize calls initializeView.
   * @see OpenGlWindow::initialize
   * @see OpenGlWindow::initializeView
   */
  SampleOpenGlWindow::SampleOpenGlWindow(Bounds const& bounds, String const& title)
    : OpenGlWindow(bounds, title)
  {
    initialize();
  }

  /**
   * All rendering code (also including e.g. glClear) goes in here.
   */
  void SampleOpenGlWindow::render() const
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glEnd();

    OpenGlWindow::render();
  }

  /**
   * If you want to react on key presses, overwrite this method.
   * @copydoc OpenGlWindow::onKeyDown
   */
  bool SampleOpenGlWindow::onKeyDown(Key key, ModifierKey modifiers)
  {
    if (key == KEY_F1)
      toggleFullscreen();

    return true;
  }
}


int main(int argc, char* argv[])
{
  try
  {
    // create a new OpenGlWindow at (100, 100) (with origin lower left corner of screen) and size
    // (640, 480)
    wnd::SampleOpenGlWindow window(wnd::Bounds(100, 100, 640, 480),
                                   wnd::String(TEXT("SampleOpenGlWindow")));

    // HandleEvents reads all events that occurred until now and calls the appropriate handler
    // if it processed all events for now it returns false
    while (window.handleEvents())
      // in that case we can render the scene
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
