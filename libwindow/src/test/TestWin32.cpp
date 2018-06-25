// TestWin32.cpp

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

#include "TestWin32.hpp"

#include <window/Error.hpp>
#include <window/Window.hpp>
#include <window/win32/Win32WindowImpl.hpp>


namespace test
{
  namespace
  {
    int on_move_called       = 0;
    int on_resize_called     = 0;
    int on_close_called      = 0;
    int on_mouse_move_called = 0;
    int on_mouse_down_called = 0;
    int on_mouse_up_called   = 0;
    int on_wheel_down_called = 0;
    int on_wheel_up_called   = 0;
    int on_key_down_called   = 0;
    int on_key_up_called     = 0;
    int on_char_called       = 0;


    class Win32Window: public wnd::Window<wnd::Win32WindowImpl>
    {
    public:
      Win32Window(wnd::Bounds const& bounds, wnd::String const& title);

      //virtual bool onDraw();
      virtual bool onMove(Coordinates const& coordinates);
      virtual bool onResize(Dimensions const& dimensions);
      virtual bool onClose();
      virtual bool onMouseMove(Coordinates const& coordinates);
      virtual bool onMouseDown(Coordinates const& coordinates, MouseButton button);
      virtual bool onMouseUp(Coordinates const& coordinates, MouseButton button);
      virtual bool onMouseWheelDown(int units);
      virtual bool onMouseWheelUp(int units);
      virtual bool onKeyDown(Key key, ModifierKey modifiers);
      virtual bool onKeyUp(Key key, ModifierKey modifiers);
      virtual bool onChar(wnd::char_t character);
    };

    Win32Window::Win32Window(wnd::Bounds const& bounds, wnd::String const& title)
      : window(bounds, title)
    {
    }

    bool Win32Window::onMove(Coordinates const& coordinates)
    {
      ++on_move_called;
      return true;
    }

    bool Win32Window::onResize(Dimensions const& dimensions)
    {
      ++on_resize_called;
      return true;
    }

    bool Win32Window::onClose()
    {
      ++on_close_called;
      return true;
    }

    bool Win32Window::onMouseMove(Coordinates const& coordinates)
    {
      ++on_mouse_move_called;
      return true;
    }

    bool Win32Window::onMouseDown(Coordinates const& coordinates, MouseButton button)
    {
      ++on_mouse_down_called;
      return true;
    }

    bool Win32Window::onMouseUp(Coordinates const& coordinates, MouseButton button)
    {
      ++on_mouse_up_called;
      return true;
    }

    bool Win32Window::onMouseWheelDown(int units)
    {
      ++on_wheel_down_called;
      return true;
    }

    bool Win32Window::onMouseWheelUp(int units)
    {
      ++on_wheel_up_called;
      return true;
    }

    bool Win32Window::onKeyDown(Key key, ModifierKey modifiers)
    {
      ++on_key_down_called;
      return true;
    }

    bool Win32Window::onKeyUp(Key key, ModifierKey modifiers)
    {
      ++on_key_up_called;
      return true;
    }

    bool Win32Window::onChar(wnd::char_t character)
    {
      ++on_char_called;
      return true;
    }

    void virtualMouseClick(bool press)
    {
      INPUT input = {};
      input.type       = INPUT_MOUSE;
      input.mi.dwFlags = (press ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP);
      SendInput(1, &input, sizeof(input));
    }

    void virtualKeyPress(BYTE key, bool press)
    {
      INPUT input = {};
      input.type       = INPUT_KEYBOARD;
      input.ki.wVk     = key;
      input.ki.dwFlags = press ? 0L : KEYEVENTF_KEYUP;
      SendInput(1, &input, sizeof(input));
    }

    void virtualWheelRotate(bool down)
    {
      INPUT input = {};
      input.type         = INPUT_MOUSE;
      input.mi.dwFlags   = MOUSEEVENTF_WHEEL;
      input.mi.mouseData = down ? -WHEEL_DELTA : WHEEL_DELTA;
      SendInput(1, &input, sizeof(input));
    }
  }


  TestWin32::testWin32()
  {
    add(TestWin32::testCreate);
    add(TestWin32::testMove);
    add(TestWin32::testResize);
    add(TestWin32::testClose);
    add(TestWin32::testMouseMove);
    add(TestWin32::testMouseDown);
    add(TestWin32::testMouseUp);
    add(TestWin32::testMouseWheelDown);
    add(TestWin32::testMouseWheelUp);
    add(TestWin32::testKeyDown);
    add(TestWin32::testKeyUp);
    add(TestWin32::testChar);
  }

  void TestWin32::testCreate()
  {
    Win32Window window(wnd::Bounds(100, 100, 640, 480), TEXT("TestWin32"));

    HWND handle = FindWindow(0, TEXT("TestWin32"));
    TESTASSERTOP(handle, ne, 0);

    window.handleEvents();
  }

  void TestWin32::testMove()
  {
    on_move_called = 0;

    {
      Win32Window window(wnd::Bounds(100, 100, 640, 480), TEXT("TestWin32"));
      TESTASSERTOP(on_move_called, eq, 0);

      HWND handle = FindWindow(0, TEXT("TestWin32"));
      TESTASSERTOP(handle, ne, 0);

      moveWindow(handle, 200, 200, 640, 480, TRUE);

      window.handleEvents();
    }
    TESTASSERTOP(on_move_called, eq, 1);
  }

  void TestWin32::testResize()
  {
    on_resize_called = 0;

    {
      Win32Window window(wnd::Bounds(100, 100, 640, 480), TEXT("TestWin32"));
      TESTASSERTOP(on_resize_called, eq, 0);

      HWND handle = FindWindow(0, TEXT("TestWin32"));
      TESTASSERTOP(handle, ne, 0);

      moveWindow(handle, 100, 100, 320, 240, TRUE);

      window.handleEvents();
    }
    TESTASSERTOP(on_resize_called, eq, 1);
  }

  void TestWin32::testClose()
  {
    on_close_called = 0;

    {
      Win32Window window(wnd::Bounds(100, 100, 640, 480), TEXT("TestWin32"));
      TESTASSERTOP(on_close_called, eq, 0);

      HWND handle = FindWindow(0, TEXT("TestWin32"));
      TESTASSERTOP(handle, ne, 0);

      sendMessage(handle, WM_CLOSE, 0, 0);

      window.handleEvents();
    }
    TESTASSERTOP(on_close_called, eq, 1);
  }

  void TestWin32::testMouseMove()
  {
    on_mouse_move_called = 0;

    {
      Win32Window window(wnd::Bounds(100, 100, 640, 480), TEXT("TestWin32"));
      TESTASSERTOP(on_mouse_move_called, eq, 0);

      setCursorPos(200, 200);
      setCursorPos(300, 300);

      window.handleEvents();
    }
    TESTASSERTOP(on_mouse_move_called, ge, 1);
  }

  void TestWin32::testMouseDown()
  {
    on_mouse_down_called = 0;

    {
      Win32Window window(wnd::Bounds(100, 100, 640, 480), TEXT("TestWin32"));
      TESTASSERTOP(on_mouse_down_called, eq, 0);

      setCursorPos(200, 200);
      virtualMouseClick(true);

      window.handleEvents();
    }
    TESTASSERTOP(on_mouse_down_called, ge, 1);
  }

  void TestWin32::testMouseUp()
  {
    on_mouse_up_called = 0;

    {
      Win32Window window(wnd::Bounds(100, 100, 640, 480), TEXT("TestWin32"));
      TESTASSERTOP(on_mouse_up_called, eq, 0);

      setCursorPos(200, 200);
      virtualMouseClick(false);

      window.handleEvents();
    }
    TESTASSERTOP(on_mouse_up_called, ge, 1);
  }

  void TestWin32::testMouseWheelDown()
  {
    on_wheel_down_called = 0;

    {
      Win32Window window(wnd::Bounds(100, 100, 640, 480), TEXT("TestWin32"));
      TESTASSERTOP(on_wheel_down_called, eq, 0);

      virtualWheelRotate(true);

      window.handleEvents();
    }
    TESTASSERTOP(on_wheel_down_called, ge, 1);
  }

  void TestWin32::testMouseWheelUp()
  {
    on_wheel_up_called = 0;

    {
      Win32Window window(wnd::Bounds(100, 100, 640, 480), TEXT("TestWin32"));
      TESTASSERTOP(on_wheel_up_called, eq, 0);

      virtualWheelRotate(false);

      window.handleEvents();
    }
    TESTASSERTOP(on_wheel_up_called, ge, 1);
  }

  void TestWin32::testKeyDown()
  {
    on_key_down_called = 0;

    {
      Win32Window window(wnd::Bounds(100, 100, 640, 480), TEXT("TestWin32"));
      TESTASSERTOP(on_key_down_called, eq, 0);

      virtualKeyPress('A', true);

      window.handleEvents();
    }
    TESTASSERTOP(on_key_down_called, ge, 1);
  }

  void TestWin32::testKeyUp()
  {
    on_key_up_called = 0;

    {
      Win32Window window(wnd::Bounds(100, 100, 640, 480), TEXT("TestWin32"));
      TESTASSERTOP(on_key_up_called, eq, 0);

      virtualKeyPress('A', false);

      window.handleEvents();
    }
    TESTASSERTOP(on_key_up_called, ge, 1);
  }

  void TestWin32::testChar()
  {
    on_char_called = 0;

    {
      Win32Window window(wnd::Bounds(100, 100, 640, 480), TEXT("TestWin32"));
      TESTASSERTOP(on_char_called, eq, 0);

      virtualKeyPress('A', true);

      window.handleEvents();
    }
    TESTASSERTOP(on_char_called, ge, 1);
  }
}
