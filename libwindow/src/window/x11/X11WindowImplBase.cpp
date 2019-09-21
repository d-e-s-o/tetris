// X11WindowImplBase.cpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014,2019 Daniel Mueller (deso@posteo.net)    *
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

#include <cctype>

#include <util/Assert.hpp>
#include <util/Rectangle1Functions.hpp>

#include "window/include/OpenGl.hpp"
#include "window/Error.hpp"
#include "window/x11/X11VisualCreatorBase.hpp"
#include "window/x11/X11WindowImplBase.hpp"
#include "window/x11/KeyFunctions.hpp"


namespace wnd
{
  namespace
  {
    /**
     * This function converts a X11 button from an XButtonEvent to an value
     * of type MouseButton.
     * @param button button value from XButtonEvent structure to convert
     * @return converted MouseButton
     * @see MouseButton
     */
    inline MouseButton convertButton(unsigned int button)
    {
      switch(button)
      {
      case Button1:
        return MOUSE_BUTTON_LEFT;

      case Button2:
        return MOUSE_BUTTON_MIDDLE;

      case Button3:
        return MOUSE_BUTTON_RIGHT;

      // the next two buttons represent the mouse wheel
//      case Button4:
//        return MOUSE_BUTTON_4;
//
//      case Button5:
//        return MOUSE_BUTTON_5;
      }
      ASSERT(false);
      return MOUSE_BUTTON_MIN;
    }

    /**
     * @param key_event received key event to extract modifier keys from
     * @return or'ed (|) modifier keys or MOD_KEY_NONE of none was found
     * @todo find a way to differ between left and right control or shift key
     * @todo find a way to get state of alt-key
     */
    ModifierKey getModifierKeys(XKeyEvent const& key_event)
    {
      int key = MOD_KEY_NONE;

      if ((key_event.state & ShiftMask) == ShiftMask)
        key |= MOD_KEY_LSHIFT | MOD_KEY_RSHIFT;

      if ((key_event.state & LockMask) == LockMask)
        key |= MOD_KEY_CAPS;

      if ((key_event.state & ControlMask) == ControlMask)
        key |= MOD_KEY_LCTRL | MOD_KEY_RCTRL;

      return static_cast<ModifierKey>(key);
    }

    /**
     * @param key_event Event structure for keypress
     * @param character character for the event
     * @return false if an error occurred, true if not
     * @todo we need a wchar_t version of this functions
     */
    inline bool lookupChar(XKeyEvent& key_event, char& character)
    {
      char buffer[2] = {};

      if (XLookupString(&key_event, &buffer[0], 2, 0, 0) == 1)
      {
        character = buffer[0];
        return true;
      }
      return false;
    }

    /**
     * @param coordinates coordinates to correct (wrong y; origin upper left edge)
     * @param dimensions dimensions of "thing" of which 'coordinates' is part
     * @return corrected coordinates (origin lower left edge)
     */
    inline Coordinates correctPosition(Coordinates const& coordinates, Dimensions const& dimensions)
    {
      return Coordinates(coordinates.x, dimensions.y - coordinates.y);
    }

    /**
     * @param display display the window belongs to
     * @param window handle of window to get parent of
     * @return parent of the given window
     */
    Window getParent(Display* display, Window window)
    {
      Window       root   = 0;
      Window       parent = 0;
      Window*      child  = 0;
      unsigned int count  = 0;

      XQueryTree(display, window, &root, &parent, &child, &count);
      XFree(child);

      return parent;
    }

    /**
     * @param display display to get delete atom from
     * @return delete atom
     */
    inline Atom getDeleteAtom(Display* display)
    {
      Atom wm_delete = XInternAtom(display, "WM_DELETE_WINDOW", True);
      ASSERTOP(wm_delete, ne, 0);

      return wm_delete;
    }

    void waitUntilMapped(Display* display, Window window)
    {
      XEvent event;
      do
      {
        XMaskEvent(display, StructureNotifyMask, &event);
      }
      while ((event.type != MapNotify) || (event.xmap.event != window));
    }

//    int lookupString(Display* display, XKeyEvent const& event)
//    {
//      XIM im = XOpenIM(display, 0, 0, 0);
//
//      wchar_t character = TEXT('\0');
//      KeySym key_sym    = 0;
//      int status = 0;
//
//      XwcLookupString(ic, &event, character, 1, key_sym, status);
//
//      if (status == XLookupBoth)
//        return true;
//
//      XCloseIM(im);
//
//      return 0;
//    }
  }


  X11WindowImplBase::X11Screen X11WindowImplBase::screen_;

  /**
   * @param bounds position and size of the window
   * @param title title of the window
   * @param creator special creator functor to create an X11 visual
   * @fixme woah this is fucked...i can create a window p.ex at 100,100...Coordinates returns these
   *       coordinates BUT the window may be at 500,0 or sth like that because the window manager said
   *       so oO
   */
  X11WindowImplBase::X11WindowImplBase(Bounds const& bounds, String const& title, X11VisualCreatorBase const& creator)
    : screen_nr_(0),
      display_(0),
      window_(0),
      parent_(0),
      close_(false),
      position_(0, 0),
      size_(0, 0)
  {
    display_ = XOpenDisplay(0);

    if (display_ == 0)
      throw Error(TEXT("Unable to connect to X server"), TEXT("XOpenDisplay returned 0"));

    screen_nr_ = XDefaultScreen(display_);

    createWindow(bounds, title, creator);
  }

  /**
   * The destructor destroy the window and frees all used resources. It is virtual to be used as
   * base class.
   */
  X11WindowImplBase::~X11WindowImplBase()
  {
    XDestroyWindow(display_, window_);
    XCloseDisplay(display_);
  }

  /**
   * @copydoc WindowInterface::handleEvents
   */
  bool X11WindowImplBase::handleEvents()
  {
    XEvent event;

    // check for unprocessed events (this is equal to XPending(display_))
    while (XEventsQueued(display_, QueuedAfterFlush) > 0)
    {
      XNextEvent(display_, &event);
      dispatchEvent(event);
    }
    return !close_;
  }

  /**
   * @copydoc WindowInterface::close
   */
  void X11WindowImplBase::close()
  {
    close_ = true;
  }

  /**
   * @copydoc WindowInterface::onMove
   */
  bool X11WindowImplBase::onMove(Coordinates const& coordinates)
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::onResize
   */
  bool X11WindowImplBase::onResize(Dimensions const& dimensions)
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::onClose
   */
  bool X11WindowImplBase::onClose()
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::onMouseMove
   */
  bool X11WindowImplBase::onMouseMove(Coordinates const& coordinates)
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::onMouseDown
   */
  bool X11WindowImplBase::onMouseDown(Coordinates const& coordinates, MouseButton button)
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::onMouseUp
   */
  bool X11WindowImplBase::onMouseUp(Coordinates const& coordinates, MouseButton button)
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::onMouseWheelDown
   */
  bool X11WindowImplBase::onMouseWheelDown(int units)
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::onMouseWheelUp
   */
  bool X11WindowImplBase::onMouseWheelUp(int units)
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::onKeyDown
   */
  bool X11WindowImplBase::onKeyDown(Key key, ModifierKey modifiers, bool repeated)
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::onKeyUp
   */
  bool X11WindowImplBase::onKeyUp(Key key, ModifierKey modifiers, bool repeated)
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::onChar
   */
  bool X11WindowImplBase::onChar(char_t character)
  {
    return true;
  }

  /**
   * @copydoc WindowInterface::position
   */
  Coordinates X11WindowImplBase::position() const
  {
    XWindowAttributes attributes = {};

#ifndef NDEBUG
    Status status =
#endif
    XGetWindowAttributes(display_, parent_, &attributes);
    ASSERTOP(status, ne, 0);

    Coordinates coordinates(attributes.x, attributes.y + attributes.height);
    return correctPosition(coordinates, desktopSize());
  }

  /**
   * @copydoc WindowInterface::move
   */
  bool X11WindowImplBase::move(Coordinates const& coordinates)
  {
    XMoveWindow(display_, window_, coordinates.x, coordinates.y);
    return true;
  }

  /**
   * @copydoc WindowInterface::size
   */
  Dimensions X11WindowImplBase::size() const
  {
    XWindowAttributes attributes;

#ifndef NDEBUG
    Status status =
#endif
    XGetWindowAttributes(display_, window_, &attributes);
    ASSERTOP(status, ne, 0);

    return Dimensions(attributes.width, attributes.height);
  }

  /**
   * @copydoc WindowInterface::resize
   */
  bool X11WindowImplBase::resize(Dimensions const& dimensions)
  {
    XResizeWindow(display_, window_, dimensions.x, dimensions.y);
    return true;
  }

  /**
   * @copydoc WindowInterface::clientSize
   */
  Dimensions X11WindowImplBase::clientSize() const
  {
    // with pure Xlib we cannot access any window manager dependent stuff
    // meaning we cannot get any information about the title bar height and
    // border width (well we can query infos about the latter but they are
    // most likely incorrect)
    return size();
  }

  /**
   * This method is used to react on received events. It calls the appropriate
   * onXXX() methods.
   * @param event event that was received and needs to be dispatched
   * @todo for key events we copy the event structure because XLookupString
   *       expects a non const pointer. Check if it is safe to cast constness
   *       away
   * @todo same goes for XMappingEvent in MappingNotify
   */
  void X11WindowImplBase::dispatchEvent(XEvent const& event)
  {
    switch (event.type)
    {
    // if the mouse was moved
    case MotionNotify:
      {
        Coordinates coordinates(event.xbutton.x, event.xbutton.y);
        onMouseMove(correctPosition(coordinates, clientSize()));
      }
      break;

    // if a mouse button was pressed or released
    case ButtonPress:
    case ButtonRelease:
      {
        // I don't know why but I got events with button > 5
        switch (event.xbutton.button)
        {
        case Button1:
        case Button2:
        case Button3:
          {
            Coordinates coordinates(event.xbutton.x, event.xbutton.y);
            MouseButton button = convertButton(event.xbutton.button);

            coordinates = correctPosition(coordinates, clientSize());

            if (event.type == ButtonPress)
              onMouseDown(coordinates, button);
            else if (event.type == ButtonRelease)
              onMouseUp(coordinates, button);
          }
          break;

        // mouse wheel up
        case Button4:
          // we only care for press events, because release always follows
          // immediately and would only duplicate the notification
          if (event.type == ButtonPress)
            onMouseWheelUp(1);
          break;

        // mouse wheel down
        case Button5:
          if (event.type == ButtonPress)
            onMouseWheelDown(1);
          break;
        }
      }
      break;

    // if some key was pressed or released
    // @note the X server does not provide any information whether a key press/release event is
    //       created due to auto-repeat or due to a real press/release; in case off auto-repeat it
    //       will generate a key-up and key-down event with the same timestamp; we use this
    //       information to detect when key-up is caused by auto-repeat; in order to check for
    //       auto-repeated for key-down we only have to remember the last key up event and check if
    //       it has the same timestamp and the same keycode
    case KeyPress:
    case KeyRelease:
      {
        XKeyEvent key_event = event.xkey;
        KeySym    key_sym   = XLookupKeysym(&key_event, 0);
        Key       key;

        if (key_sym != NoSymbol && translateKey(key_sym, key))
        {
          // we need to keep track of the last key up event in order to implement correct
          // auto-repeat behavior for key down events; I use a static variable here to keep the
          // scope minimal and not pollute the class with unnecessary member variables
          static XKeyEvent key_up_last = XKeyEvent();

          switch (event.type)
          {
          case KeyPress:
            {
              char character = 0;
              bool repeated  = key_up_last.time    == key_event.time &&
                               key_up_last.keycode == key_event.keycode;

              onKeyDown(key, getModifierKeys(event.xkey), repeated);

              if (lookupChar(key_event, character) && std::isprint(character))
                onChar(character);
            }
            break;

          case KeyRelease:
            bool repeated = false;

            if (XEventsQueued(display_, QueuedAfterReading))
            {
              XEvent next_event;
              XPeekEvent(display_, &next_event);

              repeated = next_event.type         == KeyPress &&
                         next_event.xkey.time    == key_event.time &&
                         next_event.xkey.keycode == key_event.keycode;
            }

            onKeyUp(key, getModifierKeys(event.xkey), repeated);

            key_up_last = key_event;
            break;
          }
        }
      }
      break;

    // if the window was moved or resized
    case ConfigureNotify:
      {
        // we cannot rely on the coordinate information in that event thats why we retrieve them
        // ourself
        Coordinates coordinates = position();
        Dimensions  dimensions(event.xconfigure.width, event.xconfigure.height);

        if (dimensions != size_)
        {
          size_ = dimensions;
          onResize(dimensions);
        }

        if (coordinates != position_)
        {
          position_ = coordinates;
          onMove(coordinates);
        }
      }
      break;

    // if some mapping (p.ex for keyboard: keycode -> keysym) is changed
    case MappingNotify:
      {
        XMappingEvent mapping_event = event.xmapping;

        if (mapping_event.request == MappingKeyboard ||
            mapping_event.request == MappingModifier)
        {
          // in this case we need to update this information for xlib
          XRefreshKeyboardMapping(&mapping_event);
        }
      }
      break;

    // all special messages go in here
    case ClientMessage:
      {
        // the close action ("WM_DELETE_WINDOW") we registered before is caught
        // and handled here
        Atom wm_delete = getDeleteAtom(display_);

        if (wm_delete != 0 && event.xclient.data.l[0] == wm_delete)
          close_ = onClose();
      }
      break;
    }
  }

  /**
   * This small helper method creates the window.
   * @param bounds position and size of the window
   * @param title title of the window
   * @param creator special creator functor to create an X11 visual
   */
  void X11WindowImplBase::createWindow(Bounds const& bounds, String const& title, X11VisualCreatorBase const& creator)
  {
    int           depth  = 0;
    Visual*       visual = creator(display_, screen_nr_, depth);
    Window        root   = XDefaultRootWindow(display_);
    unsigned long mask   = CWBackPixel |
                           CWBorderPixel |
                           CWOverrideRedirect |
                           CWEventMask |
                           CWColormap;

    if (visual == 0)
      throw Error(TEXT("No appropriate visual found"), TEXT("XDefaultVisual returned 0"));

    Colormap color_map = XCreateColormap(display_, root, visual, AllocNone);

    // note that for now we do not want any events (NoEventMask), later we will
    XSetWindowAttributes attributes = {};
    attributes.colormap          = color_map;
    attributes.background_pixel  = XWhitePixel(display_, screen_nr_);
    attributes.border_pixel      = XBlackPixel(display_, screen_nr_);
    attributes.override_redirect = False;
    attributes.event_mask        = NoEventMask;

    coordinate_t x = bounds.x;
    coordinate_t y = bounds.y;
    dimension_t  w = bounds.w;
    dimension_t  h = bounds.h;

    Coordinates position = correctPosition(Coordinates(x, y + h), desktopSize());
    y = position.x;

    window_ = XCreateWindow(display_, root, x, y, w, h, 0, depth, InputOutput, visual, mask, &attributes);

    setupWindow(bounds, title);
  }

  /**
   * This helper method sets some settings for this window and actually
   * displays it.
   * @param bounds position and size of the window
   * @param title title of the window
   * @todo we could/should (?) use XSetStandardProperties to set some more
   *       properties
   * @todo replace this usleep stuff with something that checks if the window
   *       manager has taken control over the window
   */
  void X11WindowImplBase::setupWindow(Bounds const& bounds, String const& title)
  {
    setSizeHints(bounds);

    // set window name (which most window managers will display in titlebar)
    XStoreName(display_, window_, title.toString());
    XSetIconName(display_, window_, title.toString());

    Atom wm_delete = getDeleteAtom(display_);

    if (wm_delete != 0)
      XSetWMProtocols(display_, window_, &wm_delete, 1);

    // display the window and redraw the content
    XMapRaised(display_, window_);
    XFlush(display_);

    //waitUntilMapped(getDisplay(), getWindow());

    // @todo what exactly was this usleep for?
    //usleep(5000);
    setRealParent();

    position_ = utl::getPosition(bounds);
    size_     = utl::getSize(bounds);

    setEventMask();
  }

  /**
   * This method sets the event mask for the window to the default values.
   */
  void X11WindowImplBase::setEventMask()
  {
    XSetWindowAttributes attributes = {};

    attributes.event_mask = ExposureMask |
                            KeyPressMask |
                            KeyReleaseMask |
                            ButtonReleaseMask |
                            ButtonPressMask |
                            StructureNotifyMask |
                            PointerMotionMask;

    XChangeWindowAttributes(display_, window_, CWEventMask, &attributes);
  }

  /**
   * This method sets the size hints for the window manager.
   * @param bounds bounds (size and position) of the window to set as hints
   */
  void X11WindowImplBase::setSizeHints(Bounds const& bounds)
  {
    XSizeHints* size_hints  = XAllocSizeHints();

    if (size_hints != 0)
    {
      // the documentation says that x and y are obsolete, however I could not
      // find out how to specify position somehow else
      size_hints->flags  = PPosition | PSize;
      size_hints->x      = bounds.x;
      size_hints->y      = bounds.y;
      size_hints->width  = bounds.w;
      size_hints->height = bounds.h;

      XSetWMNormalHints(display_, window_, size_hints);

      XFree(size_hints);
    }
  }

  /**
   * This method sets the parent_ member variable to a valid value. This is
   * necessary for position() to work correctly.
   * Background: It seems that some window managers (especially kwin) create
   * several parent windows and because of that determining the position
   * somehow fails.
   */
  void X11WindowImplBase::setRealParent()
  {
    ASSERTOP(window_, ne, 0);
    ASSERTOP(parent_, eq, 0);

    Window root = XDefaultRootWindow(display_);
    Window window = window_;
    ASSERTOP(window, ne, root);

    while (window != root)
    {
      parent_ = window;
      window  = getParent(display_, window);
    }
    ASSERTOP(parent_, ne, 0);
  }

  /**
   * @copydoc WindowInterface::desktopSize
   */
  Dimensions X11WindowImplBase::desktopSize() const
  {
    int width  = XDisplayWidth(display_,  screen_nr_);
    int height = XDisplayHeight(display_, screen_nr_);

    return Dimensions(width, height);
  }
}
