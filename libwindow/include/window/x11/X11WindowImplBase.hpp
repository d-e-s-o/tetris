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

#ifndef WNDX11IMPLBASE_HPP
#define WNDX11IMPLBASE_HPP

#include "window/Config.hpp"
#include "window/Bounds.hpp"
#include "window/String.hpp"
#include "window/MouseButton.hpp"
#include "window/Key.hpp"
#include "window/Screen.hpp"
#include "window/x11/X11ScreenImpl.hpp"


typedef struct _XDisplay Display;
typedef unsigned long XID;
typedef XID Window;
typedef union _XEvent XEvent;


namespace wnd
{
  class X11VisualCreatorBase;


  /**
   * This class is the base class for all x11 implementations.
   * @todo there may be windows in different screens (different screen numbers) or even displays,
   *       in that case we must not have a static ScreenImpl, change this
   */
  class LIBWINDOW_EXPORT X11WindowImplBase
  {
  public:
    typedef Screen<X11ScreenImpl> X11Screen;

    X11WindowImplBase(Bounds const& bounds, String const& title, X11VisualCreatorBase const& creator);
    virtual ~X11WindowImplBase();

    bool handleEvents();

    void close();

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

    Coordinates position() const;
    bool move(Coordinates const& coordinates);

    Dimensions size() const;
    bool resize(Dimensions const& dimensions);

    Dimensions clientSize() const;

    X11Screen&       screen();
    X11Screen const& screen() const;

  protected:
    virtual void dispatchEvent(XEvent const& event);

    int      getScreenNumber() const;
    Display* getDisplay() const;
    ::Window getWindow() const;

  private:
    static X11Screen screen_;

    int      screen_nr_;
    Display* display_;
    ::Window window_;
    ::Window parent_;
    bool     close_;

    Coordinates position_;
    Dimensions  size_;

    X11WindowImplBase(X11WindowImplBase const&);
    X11WindowImplBase& operator =(X11WindowImplBase const&);

    void createWindow(Bounds const& bounds, String const& title, X11VisualCreatorBase const& creator);
    void setupWindow(Bounds const& bounds, String const& title);
    void setEventMask();
    void setSizeHints(Bounds const& bounds);
    void setRealParent();

    Dimensions desktopSize() const;
  };
}


namespace wnd
{
  /**
   * @copydoc WindowInterface::screen
   */
  inline X11WindowImplBase::X11Screen& X11WindowImplBase::screen()
  {
    return screen_;
  }

  /**
   * @copydoc WindowInterface::screen
   */
  inline X11WindowImplBase::X11Screen const& X11WindowImplBase::screen() const
  {
    return screen_;
  }

  /**
   * @return number of used screen
   */
  inline int X11WindowImplBase::getScreenNumber() const
  {
    return screen_nr_;
  }

  /**
   * @return pointer to display
   */
  inline Display* X11WindowImplBase::getDisplay() const
  {
    return display_;
  }

  /**
   * @return handle for window
   */
  inline ::Window X11WindowImplBase::getWindow() const
  {
    return window_;
  }
}


#endif
