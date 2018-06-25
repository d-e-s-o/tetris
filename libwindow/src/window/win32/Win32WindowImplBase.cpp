// Win32WindowImplBase.cpp

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

#include <cctype>

#include <util/Assert.hpp>
#include <util/Rectangle1Functions.hpp>

#include "window/Error.hpp"
#include "window/win32/ClassRegisterer.hpp"
#include "window/win32/Win32Params.hpp"
#include "window/win32/Win32Functions.hpp"
#include "window/win32/Win32WindowImplBase.hpp"
#include "window/win32/KeyFunctions.hpp"


namespace wnd
{
  namespace
  {
    /**
     * @return screen resolution in pixel
     */
    inline Dimensions getResolution()
    {
      return dimensions(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    }

    /**
     * @param lparam value from wndProc (used as point storage)
     * @return Point with values from lparam
     */
    template<typename T>
    inline T extractPoint(LPARAM lparam)
    {
      SHORT x = static_cast<SHORt>(LOWORD(lparam));
      SHORT y = static_cast<SHORt>(HIWORD(lparam));

      return T(x, y);
    }

    /**
     * @param position positon to correct (wrong y; origin upper left edge)
     * @param size size of "thing" of which position is part
     * @return corrected position (origin lower left edge)
     */
    inline Coordinates correctPosition(Coordinates const& coordinates, Dimensions const& dimensions)
    {
      return Coordinates(position.x_, size.y_ - position.y_);
    }

    /**
     * @param position to correct in screen coordinates
     * @return corrected position
     */
    inline Coordinates correctAbsolutePosition(Coordinates const& coordinates)
    {
      return correctPosition(position, getResolution());
    }

    ///**
    // * @param window handle to the window to get position of
    // * @return position of the window with origin upper left edge or screen
    // */
    //inline Coordinates getRawPosition(HWND window)
    //{
    //  RECT const& rect = GetWindowPlacement(window);
    //  return coordinates(rect.left, rect.top);
    //}

    /**
     * @param[in] message message to get mouse button from
     * @param[out] button mouse button the message belongs to
     * @return true if conversion was successful, false if not
     */
    bool convertButton(UINT message, MouseButton& button)
    {
      switch(message)
      {
      case WM_LBUTTONDOWN:
      case WM_LBUTTONUP:
        button = MOUSE_BUTTON_LEFT;
        return true;

      case WM_MBUTTONDOWN:
      case WM_MBUTTONUP:
        button = MOUSE_BUTTON_MIDDLE;
        return true;

      case WM_RBUTTONDOWN:
      case WM_RBUTTONUP:
        button = MOUSE_BUTTON_RIGHT;
        return true;
      }
      return false;
    }

    /**
     * This string is the window class used for all windows.
     */
    char_t const* const window_class = TEXT("window_class");
  }


  /**
   * This variable can be used to map a window handle to the actual window
   * instances.
   */
  Win32WindowImplBase::Windows Win32WindowImplBase::windows_;

  /**
   *
   */
  Win32WindowImplBase::Win32Screen Win32WindowImplBase::screen_;


  /**
   * @param bounds desired bounds of the window (position and size)
   * @param title title of the window (in caption bar)
   * @param params additional parameters containing window styles to be used
   *        for the window
   * @throw Error if Windows fails creating the window
   */
  Win32WindowImplBase::Win32WindowImplBase(Bounds const& bounds, String const& title, Win32Params const& params)
    : window_(0),
      position_(0, 0),
      close_(false)
  {
    static ClassRegisterer registerer(window_class, &staticWndProc);

    if (!create(bounds, title, params.style_, params.style_ex_))
      throw Error(TEXT("Error creating window"), TEXT("CreateWindowEx failed"));
  }

  /**
   * The destructor destroys the window and unregisters the handle from the
   * map.
   */
  Win32WindowImplBase::~Win32WindowImplBase()
  {
    destroy();

#ifndef NDEBUG
    size_t count =
#endif
    windows_.remove(window_);
    ASSERTOP(count, gt, 0);
  }

  /**
   * @copydoc WindowInterface::handleEvents
   */
  bool Win32WindowImplBase::handleEvents()
  {
    MSG msg = {};

    while (PeekMessage(&msg, window_, 0, 0, PM_REMOVE) != 0)
    {
      ASSERTOP(msg.hwnd, eq, window_);
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    return !close_;
  }

  /**
   * @copydoc WindowInterface::close
   */
  void Win32WindowImplBase::close()
  {
    close_ = true;
  }

  /**
   * @copydoc WindowInterface::onMove
   */
  bool Win32WindowImplBase::onMove(Coordinates const& coordinates)
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::onResize
   */
  bool Win32WindowImplBase::onResize(Dimensions const& dimensions)
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::onClose
   */
  bool Win32WindowImplBase::onClose()
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::onMouseMove
   */
  bool Win32WindowImplBase::onMouseMove(Coordinates const& coordinates)
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::onMouseDown
   */
  bool Win32WindowImplBase::onMouseDown(Coordinates const& coordinates, MouseButton button)
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::onMouseUp
   */
  bool Win32WindowImplBase::onMouseUp(Coordinates const& coordinates, MouseButton button)
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::onMouseWheelDown
   */
  bool Win32WindowImplBase::onMouseWheelDown(int units)
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::onMouseWheelUp
   */
  bool Win32WindowImplBase::onMouseWheelUp(int units)
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::onKeyDown
   */
  bool Win32WindowImplBase::onKeyDown(Key key, ModifierKey modifiers, bool repeated)
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::onKeyUp
   */
  bool Win32WindowImplBase::onKeyUp(Key key, ModifierKey modifiers, bool repeated)
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::onChar
   */
  bool Win32WindowImplBase::onChar(char_t character)
  {
    return true;
  }

  /**
   * @todo Coordinates should contain coordinates relative to origin 0, 0 in lower
   *       left corner, not upper left corner!!!
   */
  Coordinates Win32WindowImplBase::position() const
  {
    // we could use GetWindowRect, but it does not work if the window is
    // minimized
    RECT const& rect = GetWindowPlacement(windowHandle());
    return correctAbsolutePosition(coordinates(rect.left, rect.bottom));
  }

  /**
   * @todo find out whether WM_MOVE message is sent
   * @todo if Coordinates is fixed (coordinate origin), this one must take care
   *       of this, too
   */
  bool Win32WindowImplBase::move(Coordinates const& coordinates)
  {
    Coordinates position = correctAbsolutePosition(coordinates);

    return SetWindowPos(windowHandle(), 0, position.x_, position.y_, 0, 0, SWP_NOSIZE) != 0;
  }

  /**
   * @todo find out whether it is true that rect.bottom and rect.right lie
   *       outside the window (MSDN says so)
   */
  Dimensions Win32WindowImplBase::size() const
  {
    RECT const& rect = GetWindowPlacement(windowHandle());
    return Dimensions(rect.right - rect.left, rect.bottom - rect.top);
  }

  /**
   * @todo find out whether WM_SIZE message is sent
   */
  bool Win32WindowImplBase::resize(Dimensions const& dimensions)
  {
    coordinate_t w = dimensions.x_;
    coordinate_t h = dimensions.y_;

    return SetWindowPos(windowHandle(), 0, 0, 0, w, h, SWP_NOMOVE) != 0;
  }

  /**
   * @copydoc WindowInterface::clientSize
   */
  Dimensions Win32WindowImplBase::clientSize() const
  {
    RECT const& rect = getClientRect(windowHandle());
    return Dimensions(rect.right - rect.left, rect.bottom - rect.top);
  }

  /**
   *
   */
  Win32WindowImplBase::Win32Screen& Win32WindowImplBase::screen()
  {
    return screen_;
  }

  /**
   *
   */
  Win32WindowImplBase::Win32Screen const& Win32WindowImplBase::screen() const
  {
    return screen_;
  }

  /**
   * @param message win32 message id from event
   * @param wparam wParam of message
   * @param lparam lParam of message
   * @return value indicating success, failure or handling status
   */
  LRESULT Win32WindowImplBase::wndProc(UINT message, WPARAM wparam, LPARAM lparam)
  {
    switch(message)
    {
    case WM_MOVE:
      {
        // we could use Coordinates, but we want position when the event
        // happened, so we have to apply some other sizes...
        Coordinates position = extractPoint<Coordinates>(lparam);
        position -= Coordinates(GetSystemMetrics(SM_CXSIZEFRAME),
                                GetSystemMetrics(SM_CYSIZEFRAME));
        position -= Coordinates(0, GetSystemMetrics(SM_CYCAPTION));
        position += Coordinates(0, size().y_);
        position  = correctAbsolutePosition(position);

        if (position != position_)
        {
          position_ = position;
          onMove(position_);
        }
      }
      return 0;

    // we do not care about minimizing because imo it does not resize the window, just hide it
    case WM_SIZE:
      if (wparam != SIZE_MINIMIZED)
      {
        Dimensions size = extractPoint<Dimensions>(lparam);
        size += dimensions(2 * GetSystemMetrics(SM_CXSIZEFRAME),
                           2 * GetSystemMetrics(SM_CYSIZEFRAME));
        size += dimensions(0,  GetSystemMetrics(SM_CYCAPTION));

        onResize(size);

        // we need to check for position change because our window origin is
        // the lower left edge, and windows does not treat a resize of the
        // lower border as WM_MOVE
        // @todo we are using the actual position, we should somehow calculate
        //       this from the event parameters to get the values from the
        //       moment when the event happened
        Coordinates position = position();

        if (position != position_)
        {
          position_ = position;
          onMove(position_);
        }
      }
      return 0;

    case WM_CLOSE:
      close_ = onClose();
      return 0;

    // we could also use WM_INPUT, it is said to be more precise than
    // WM_MOUSEMOVE, because it has not ballistics applied by the os
    // http://www.gamedev.net/community/forums/topic.asp?topic_id=496461
    // http://msdn.microsoft.com/en-us/library/bb206183.aspx
    case WM_MOUSEMOVE:
      onMouseMove(correctPosition(extractPoint<Coordinates>(lparam), clientSize()));
      return 0;

    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
      {
        MouseButton button;

        if (convertButton(message, button))
        {
          Coordinates position = correctPosition(extractPoint<Coordinates>(lparam), clientSize());

          switch (message)
          {
          case WM_LBUTTONDOWN:
          case WM_RBUTTONDOWN:
          case WM_MBUTTONDOWN:
            onMouseDown(position, button);
            break;

          case WM_LBUTTONUP:
          case WM_RBUTTONUP:
          case WM_MBUTTONUP:
            onMouseUp(position, button);
            break;
          }
        }
      }
      return 0;

    case WM_MOUSEWHEEL:
      {
        SHORT distance = GET_WHEEL_DELTA_WPARAM(wparam);
        distance /= WHEEL_DELTA;
        ASSERTOP(distance, ne, 0);

        // msdn says:
        // A positive value indicates that the wheel was rotated forward, away from the user; a negative value
        // indicates that the wheel was rotated backward, toward the user.
        if (distance < 0)
          onMouseWheelDown(-distance);
        else if (distance > 0)
          onMouseWheelUp(distance);
      }
      return 0;

    case WM_KEYDOWN:
    case WM_KEYUP:
      {
        Key key;

        if (virtKeyToKey(static_cast<int>(wparam), key))
        {
          // @todo the repeat behavior here differs for that for X11: a key up event is sent only
          //       in case of a real key up (and never due to auto-repeat) and only key down is
          //       issued due to auto-repeat - fix this!
          // @note I have also witnessed _very_ different behavior among WinXP versions; on one
          //       lparam never changes, even for auto-repetition
          switch (message)
          {
          case WM_KEYDOWN:
            // KF_REPEAT checks the previous-key-state bit, telling whether the key was already
            // down before this message was sent and, thus, effectively telling us whether the
            // auto-repeat feature is currently active
            onKeyDown(key, getModifierKeys(), (HIWORD(lparam) & KF_REPEAT) != 0);
            break;

          case WM_KEYUP:
            onKeyUp(key, getModifierKeys(), false);
            break;
          }
        }
      }
      return 0;

    //case WM_GETMINMAXINFO:
    //  {
    //    MINMAXINFO* min_max;
    //    min_max = reinterpret_cast<MINMAXINFO*>(lparam);
    //    min_max->ptMinTrackSize.x = 0;
    //    min_max->ptMinTrackSize.y = 0;
    //  }
    //  return 0;

    //case WM_SYSKEYDOWN:
    //  return 0;

    //case WM_SYSKEYUP:
    //  return 0;

    case WM_CHAR:
      {
        Char character = static_cast<Char>(wparam);

        if (std::isprint(character))
          onChar(character);
      }
      return 0;
    }
    return DefWindowProc(window_, message, wparam, lparam);
  }

  /**
   * The static wndProc is the one that receives all messages. It is registered
   * via RegisterClass. It forwards the message to the window instance it
   * belongs to.
   */
  LRESULT APIENTRY Win32WindowImplBase::staticWndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
  {
    Windows::ConstIterator it = windows_.find(window);

    if (it != windows_.end())
      return it->second->wndProc(message, wparam, lparam);

    return DefWindowProc(window, message, wparam, lparam);
  }

  /**
   * This method actually creates the window.
   * @param bounds desired position and size of the window
   * @param title title the window should have
   * @param style flags describing the window style (see CreateWindowEx)
   * @param style_ex flags describing the extended window style
   * @return true if creating the window was successful, false if not
   */
  bool Win32WindowImplBase::create(Bounds const& bounds, String const& title, DWORD style, DWORD style_ex)
  {
    int x = bounds.x_;
    int y = bounds.y_;
    int w = bounds.w_;
    int h = bounds.h_;

    y = correctAbsolutePosition(coordinates(x, y + h)).y_;

    window_ = CreateWindowEx(style_ex, window_class, title.toString(), style, x, y, w, h, 0, 0, 0, 0);

    if (window_ != 0)
    {
      windows_[window_] = this;

      position_ = position();

      ShowWindow(window_, SW_SHOW);
      UpdateWindow(window_);

      // @note windows seems to have a minimum window width of 123, that means that the last
      //       assertion will always fail if bounds.w_ is less than 123
      // @todo think about whether we throw exception if the position or size could not be set
      //       or whether to just go on
      // (same goes for height and probably for the position as well)
      ASSERT(position_  == Coordinates(bounds.x_, bounds.y_));
      ASSERT(position() == Coordinates(bounds.x_, bounds.y_));
      ASSERT(size()     == Dimensions(bounds.w_, bounds.h_));
      return true;
    }
    return false;
  }

  /**
   * This method destroys the window. It should not be called by the user but
   * only by the destructor.
   */
  void Win32WindowImplBase::destroy() const
  {
    DestroyWindow(window_);
  }
}
