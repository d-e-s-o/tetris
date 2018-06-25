// TestX11.cpp

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

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <util/Assert.hpp>
#include <pointer/ResourceGuard.hpp>

#include "X11Window.hpp"
#include "TestX11.hpp"


namespace test
{
  namespace
  {
    /**
     * @todo check if it is actual valid C++ to set the reference 'name' to a temporary variable
     */
    bool getWindowName(Display* display, ::Window const& window, wnd::String& name)
    {
      char* atom_name = nullptr;

      if (XFetchName(display, window, &atom_name) != 0)
      {
        ASSERTOP(atom_name, ne, nullptr);

        name = wnd::String(atom_name);
        XFree(atom_name);

        return true;
      }
      return false;
    }

    ::Window findWindowInternal(Display* display, wnd::String const& name, ::Window root)
    {
      ASSERTOP(display, ne, nullptr);
      ASSERTOP(root, ne, 0);

      wnd::String tmp_name;

      // check if the root window itself has the desired name
      if (getWindowName(display, root, tmp_name) && tmp_name == name)
        return root;

      ::Window dummy = 0;
      ::Window* children = 0;
      unsigned int count = 0;

      if (XQueryTree(display, root, &dummy, &dummy, &children, &count) != 0 && count > 0)
      {
        typedef int (*Free)(void*);
        typedef ptr::ResourceGuard< ::Window*, Free> Guard;

        Guard guard(children, reinterpret_cast<Free>(&XFree));

        for (::Window* child = children; child != children + count; ++child)
        {
          ::Window window = findWindowInternal(display, name, *child);

          if (window != 0)
            return window;
        }
      }
      return 0;
    }

    /**
     * This function recursivly searched all windows for one with the given name
     * and returns a handle to it. Note that there may exist multiple windows with
     * that name, but only the first one will be returned.
     * @param display pointer to the used display
     * @param name name of the window to look for
     * @return handle of found window or 0 if none was found
     */
    ::Window findWindow(Display* display, wnd::String const& name)
    {
      ASSERTOP(display, ne, nullptr);

      return findWindowInternal(display, name, XDefaultRootWindow(display));
    }
  }


  TestX11::TestX11()
    : tst::TestCase<TestX11>(*this, "TestX11")
  {
    add(&TestX11::testCreate);
    add(&TestX11::testMove);
    add(&TestX11::testResize);
    add(&TestX11::testClose);
    add(&TestX11::testMouseMove);
    add(&TestX11::testMouseDown);
    add(&TestX11::testMouseUp);
    add(&TestX11::testMouseWheelDown);
    add(&TestX11::testMouseWheelUp);
    add(&TestX11::testKeyDown);
    add(&TestX11::testKeyUp);
    add(&TestX11::testChar);
  }

  void TestX11::setUp()
  {
    X11Window::on_move_called_       = 0;
    X11Window::on_resize_called_     = 0;
    X11Window::on_close_called_      = 0;
    X11Window::on_mouse_move_called_ = 0;
    X11Window::on_mouse_down_called_ = 0;
    X11Window::on_mouse_up_called_   = 0;
    X11Window::on_wheel_down_called_ = 0;
    X11Window::on_wheel_up_called_   = 0;
    X11Window::on_key_down_called_   = 0;
    X11Window::on_key_up_called_     = 0;
    X11Window::on_char_called_       = 0;
  }

  void TestX11::testCreate(tst::TestResult& result)
  {
  }

  void TestX11::moveFn(tst::TestResult& result, Display* display, ::Window window)
  {
    TESTASSERTOP(X11Window::on_move_called_, eq, 0);

    // it seems that now matter how often we move the window, if there is no
    // call to HandleEvents we only get one event - but that's ok
    XMoveWindow(display, window, 0, 0);
    XMoveWindow(display, window, 100, 100);
    XMoveWindow(display, window, 120, 100);
    XMoveWindow(display, window, 150, 100);
  }

  /**
   * @todo find out why this test method sometimes fails (the assertions fail)
   */
  void TestX11::testMove(tst::TestResult& result)
  {
    X11Window::on_move_called_ = 0;
    doTest(result, &TestX11::moveFn);
    TESTASSERTOP(X11Window::on_move_called_, eq, 1);
  }

  void TestX11::resizeFn(tst::TestResult& result, Display* display, ::Window window)
  {
    TESTASSERTOP(X11Window::on_resize_called_, eq, 0);

//    XWindowChanges changes = {};
//    changes.width  = 320;
//    changes.height = 240;
//    XConfigureWindow(display, window, CWWidth | CWHeight, &changes);

    XResizeWindow(display, window, 320, 240);
    XResizeWindow(display, window, 640, 480);
  }

  void TestX11::testResize(tst::TestResult& result)
  {
    X11Window::on_resize_called_ = 0;
    doTest(result, &TestX11::resizeFn);
    TESTASSERTOP(X11Window::on_resize_called_, eq, 2);
  }

  void TestX11::closeFn(tst::TestResult& result, Display* display, ::Window window)
  {
    TESTASSERTOP(X11Window::on_close_called_, eq, 0);

    Atom close_atom = XInternAtom(display, "WM_DELETE_WINDOW", True);

    XEvent event;
    event.xclient.type         = ClientMessage;
    event.xclient.message_type = close_atom;
    event.xclient.format       = 32;
    event.xclient.data.l[0]    = close_atom;

    XSendEvent(display, window, 0, 0, &event);
  }

  void TestX11::testClose(tst::TestResult& result)
  {
    X11Window::on_close_called_ = 0;
    doTest(result, &TestX11::closeFn);
    TESTASSERTOP(X11Window::on_close_called_, eq, 1);
  }

  void TestX11::mouseMoveFn(tst::TestResult& result, Display* display, ::Window window)
  {
    TESTASSERTOP(X11Window::on_mouse_move_called_, eq, 0);

    XWarpPointer(display, None, window, 0, 0, 0, 0, 0, 0);
    XWarpPointer(display, None, window, 0, 0, 0, 0, 100, 100);
  }

  /**
   * @note if the mouse is moved while the test runs it might fail
   */
  void TestX11::testMouseMove(tst::TestResult& result)
  {
    X11Window::on_mouse_move_called_ = 0;
    doTest(result, &TestX11::mouseMoveFn);
    TESTASSERTOP(X11Window::on_mouse_move_called_, ge, 1);
  }

  void TestX11::mouseDownFn(tst::TestResult& result, Display* display, ::Window window)
  {
    TESTASSERTOP(X11Window::on_mouse_down_called_, eq, 0);

    XEvent event;
    event.xbutton.type   = ButtonPress;
    event.xbutton.window = window;
    event.xbutton.button = Button1;

    XSendEvent(display, window, 0, 0, &event);
  }

  void TestX11::testMouseDown(tst::TestResult& result)
  {
    X11Window::on_mouse_down_called_ = 0;
    doTest(result, &TestX11::mouseDownFn);
    TESTASSERTOP(X11Window::on_mouse_down_called_, eq, 1);
  }

  void TestX11::mouseUpFn(tst::TestResult& result, Display* display, ::Window window)
  {
    TESTASSERTOP(X11Window::on_mouse_up_called_, eq, 0);

    XEvent event;
    event.xbutton.type   = ButtonRelease;
    event.xbutton.window = window;
    event.xbutton.button = Button1;

    XSendEvent(display, window, 0, 0, &event);
  }

  void TestX11::testMouseUp(tst::TestResult& result)
  {
    X11Window::on_mouse_up_called_ = 0;
    doTest(result, &TestX11::mouseUpFn);
    TESTASSERTOP(X11Window::on_mouse_up_called_, eq, 1);
  }

  void TestX11::mouseWheelDownFn(tst::TestResult& result, Display* display, ::Window window)
  {
    TESTASSERTOP(X11Window::on_wheel_down_called_, eq, 0);

    XEvent event;
    event.xbutton.type   = ButtonPress;
    event.xbutton.window = window;
    event.xbutton.button = Button5;

    XSendEvent(display, window, 0, 0, &event);

    event.xbutton.type   = ButtonRelease;
    XSendEvent(display, window, 0, 0, &event);
  }

  void TestX11::testMouseWheelDown(tst::TestResult& result)
  {
    X11Window::on_wheel_down_called_ = 0;
    doTest(result, &TestX11::mouseWheelDownFn);
    TESTASSERTOP(X11Window::on_wheel_down_called_, eq, 1);
  }

  void TestX11::mouseWheelUpFn(tst::TestResult& result, Display* display, ::Window window)
  {
    TESTASSERTOP(X11Window::on_wheel_up_called_, eq, 0);

    XEvent event;
    event.xbutton.type   = ButtonPress;
    event.xbutton.window = window;
    event.xbutton.button = Button4;

    XSendEvent(display, window, 0, 0, &event);

    event.xbutton.type   = ButtonRelease;
    XSendEvent(display, window, 0, 0, &event);
  }

  void TestX11::testMouseWheelUp(tst::TestResult& result)
  {
    X11Window::on_wheel_up_called_ = 0;
    doTest(result, &TestX11::mouseWheelUpFn);
    TESTASSERTOP(X11Window::on_wheel_up_called_, eq, 1);
  }

  void TestX11::keyDownFn(tst::TestResult& result, Display* display, ::Window window)
  {
    TESTASSERTOP(X11Window::on_key_down_called_, eq, 0);

    XEvent event;
    event.xkey.type    = KeyPress;
    event.xkey.keycode = XKeysymToKeycode(display, XK_a);
    event.xkey.window  = window;

    XSendEvent(display, window, 0, 0, &event);
  }

  void TestX11::testKeyDown(tst::TestResult& result)
  {
    X11Window::on_key_down_called_ = 0;
    doTest(result, &TestX11::keyDownFn);
    TESTASSERTOP(X11Window::on_key_down_called_, eq, 1);
  }

  void TestX11::keyUpFn(tst::TestResult& result, Display* display, ::Window window)
  {
    TESTASSERTOP(X11Window::on_key_up_called_, eq, 0);

    XEvent event;
    event.xkey.type    = KeyRelease;
    event.xkey.keycode = XKeysymToKeycode(display, XK_a);
    event.xkey.window  = window;

    XSendEvent(display, window, 0, 0, &event);
  }

  void TestX11::testKeyUp(tst::TestResult& result)
  {
    X11Window::on_key_up_called_ = 0;
    doTest(result, &TestX11::keyUpFn);
    TESTASSERTOP(X11Window::on_key_up_called_, eq, 1);
  }

  void TestX11::charFn(tst::TestResult& result, Display* display, ::Window window)
  {
    TESTASSERTOP(X11Window::on_char_called_, eq, 0);

    XEvent event;
    event.xkey.type    = KeyPress;
    event.xkey.keycode = XKeysymToKeycode(display, XK_a);
    event.xkey.window  = window;

    XSendEvent(display, window, 0, 0, &event);
  }

  void TestX11::testChar(tst::TestResult& result)
  {
    X11Window::on_char_called_ = 0;
    doTest(result, &TestX11::charFn);
    TESTASSERTOP(X11Window::on_char_called_, eq, 1);
  }

  /**
   * @todo most (all?) of the functions do not actually work with wide character, which might be the
   *       case depending on the UNICODE setting -- check and fix this!
   */
  void TestX11::doTest(tst::TestResult& result, TestFunction const& function)
  {
    X11Window window(wnd::Bounds(100, 100, 640, 480), wnd::String(TEXT("TestX11")));

    Display* display = XOpenDisplay(0);
    ::Window handle  = findWindow(display, wnd::String(TEXT("TestX11")));

    XSync(display, False);
    window.handleEvents();

    (this->*function)(result, display, handle);

    XSync(display, False);
    XCloseDisplay(display);

    window.handleEvents();
  }
}
