// WindowInterface.hpp

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

#ifndef WNDWINDOWINTERFACE_HPP
#define WNDWINDOWINTERFACE_HPP

#include "window/Config.hpp"
#include "window/Dimensions.hpp"
#include "window/Coordinates.hpp"
#include "window/String.hpp"
#include "window/MouseButton.hpp"
#include "window/Key.hpp"


namespace wnd
{
  class ScreenInterface;


  /**
   * This class is the base class for all window classes. It declares methods that have to be
   * implemented by every window.
   * @note all dimensions and coordinates are given in pixels
   * @todo think about renaming clientSize() to size() (after removing the latter), because on x11
   *       we cannot get any information about decorations and therefore always retrieve the client
   *       size; this means nothing should depend on this, which means we can remove it
   * @todo think about adding some functionality to set mouse capture for a given window
   * @todo all the windows should not take caption in constructor, instead they should offer a
   *       method to set it
   * @todo add onMinimize() and/or onHide() or onActivate()/onDeactivate()
   */
  class LIBWINDOW_EXPORT WindowInterface
  {
  public:
    WindowInterface();

    /**
     * The destructor is virtual to allow other classes to inherited from this
     * one.
     */
    virtual ~WindowInterface() = 0;

    /**
     * This method checks for new messages that arrived and handles them. E.g. if the user clicked
     * the close button there will be a close message, a move message of the window is moved etc.
     * @return false if window should be destroyed, true otherwise
     */
    virtual bool handleEvents() = 0;

    /**
     * This method closes the window by making the next invocation of handleEvents() return false.
     * @note that this method does not immediatly destroy the window, this can only be achieved by
     *       invoking the destructor
     */
    virtual void close() = 0;

    /**
     * This method gets called everytime the window is moved. The origin of the coordinates is the
     * lower left edge of the screen.
     * @param coordinates new position of the window (absolute)
     * @return true if handling was successful, false if not
     */
    virtual bool onMove(Coordinates const& coordinates) = 0;

    /**
     * This method gets called everytime the window is resized.
     * @param size new size of the window
     * @return true if handling successful, false if not
     */
    virtual bool onResize(Dimensions const& dimensions) = 0;

    /**
     * This method gets called, if the window should be closed (-> destroyed). It can be
     * overwritten to close or keep the window, depending on the return value.
     * @return true if window should be closed, false otherwise
     */
    virtual bool onClose() = 0;

    /**
     * This method gets called everytime the mouse is moved within the window. The origin of the
     * coordinates is the lower left edge or the window.
     * @param coordinates current position of the mouse cursor
     * @return true if handling was successful, false if not
     */
    virtual bool onMouseMove(Coordinates const& coordinates) = 0;

    /**
     * This method gets called everytime a mouse button is pressed. The origin of the coordinates
     * is the lower left edge or the window.
     * @param coordinates position of the mouse at the moment of the press event
     * @param button mouse button that was pressed
     * @return true if handling was successful, false otherwise
     */
    virtual bool onMouseDown(Coordinates const& coordinates, MouseButton button) = 0;

    /**
     * This method gets called everytime a mouse button is released. The origin of the coordinates
     * is the lower left edge or the window.
     * @param coordinates position of the mouse at the moment of the release event
     * @param button mouse button that was released
     * @return true if handling was successful, false otherwise
     */
    virtual bool onMouseUp(Coordinates const& coordinates, MouseButton button) = 0;

    /**
     * This method gets called everytime the user moves the mouse wheel with direction towards the
     * user.
     * @param units number of units the mouse wheel was moved
     * @return true if handling was successful, false otherwise
     */
    virtual bool onMouseWheelDown(int units) = 0;

    /**
     * This method gets called everytime the user moves the mouse wheel with direction away from
     * the user.
     * @param units number of units the mouse wheel was moved
     * @return true if handling was successful, false otherwise
     */
    virtual bool onMouseWheelUp(int units) = 0;

    /**
     * This method gets called whenever a key is pressed.
     * @param key constant for the key that was pressed
     * @param modifiers pressed modifiers keys or'ed (|) together
     * @param repeated true if the given key was pressed by auto-repeat, false if an actual key
     *        down happened
     * @return true if handling was successful, false otherwise
     */
    virtual bool onKeyDown(Key key, ModifierKey modifiers, bool repeated) = 0;

    /**
     * This method gets called everytime a key is released.
     * @param key constant for the key that was released
     * @param modifiers pressed modifiers keys or'ed (|) together
     * @param repeated true if the given key was released by auto-repeat, false if an actual key
     *        up happened
     * @return true if handling was successful, false otherwise
     */
    virtual bool onKeyUp(Key key, ModifierKey modifiers, bool repeated) = 0;

    /**
     * This method gets called whenever the user presses a key that can be represented by a
     * character and that can be displayed.
     * @note this method gets called after OnKeyDown (if the key represents a valid character and
     *       was translated) and before OnKeyUp
     * @param character character code of key pressed
     * @return true if handling was successful, false if not
     * @todo do we really need this method? if we supply a nice key-code conversion function this
     *       method should become obsolete
     */
    virtual bool onChar(char_t character) = 0;

    /**
     * This method retrieves the current position of the window. The origin of the coordinates is
     * the lower left edge of the screen.
     * @return position of the window
     */
    virtual Coordinates position() const = 0;

    /**
     * This method sets the new position of the window. The origin of the coordinates is the lower
     * left edge of the screen.
     * @param coordinates new position the window should have
     * @return true if repositioning was successful, false if not
     */
    virtual bool move(Coordinates const& coordinates) = 0;

    /**
     * @return size of the window
     */
    virtual Dimensions size() const = 0;

    /**
     * @return size of the window client area (where stuff is drawn)
     */
    virtual Dimensions clientSize() const = 0;

    /**
     * @param size new size the window should have
     * @return true if resizing was successful, false if not
     */
    virtual bool resize(Dimensions const& dimensions) = 0;

    /**
     * @return screen the window belongs to
     */
    virtual ScreenInterface& screen() = 0;

    /**
     * @return screen the window belongs to
     */
    virtual ScreenInterface const& screen() const = 0;

  private:
    WindowInterface(WindowInterface const&);
    WindowInterface& operator =(WindowInterface const&);
  };
}


namespace wnd
{
  inline WindowInterface::WindowInterface()
  {
  }
}


#endif
