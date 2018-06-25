// WindowImpl.hpp

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

#ifndef WNDWINOWIMPL_HPP
#define WNDWINOWIMPL_HPP

#include "window/Bounds.hpp"
#include "window/String.hpp"


namespace wnd
{
  /**
   * This class template acts as a message forwarder from the implementation
   * (which is the base of this class) to the actual window. It therefor keeps
   * a reference to it and implements the onXXX() methods, making each call the
   * appropriate method.
   * Note that this class is neither bottom nor top of the hierarchy. It has a
   * base class that depends on the template parameter and the actual
   * implementation class should be derived by this one to not have to forward
   * all the events manually.
   * @param T type of actual window
   * @param BaseT type of implementation (which will act as a base class)
   * @param ParamT type of parameter to be passed to the base class's constructor
   */
  template<typename T, typename BaseT, typename ParamT>
  class WindowImpl: public BaseT
  {
  public:
    WindowImpl(T& window, Bounds const& bounds, String const& title, ParamT const& param);

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

  protected:
    T&       owner();
    T const& owner() const;

  private:
    T* window_;
  };
}


namespace wnd
{
  /**
   * The constructor creates a new WindowImpl object, keeping a reference to
   * the actual window.
   * @param window actual window object this one acts only as implementation for
   * @param bounds desired bounds (position and size) of the window
   * @param title title the window should have
   * @param param variable parameter to be passed to the implementation base
   */
  template<typename T, typename BaseT, typename ParamT>
  inline WindowImpl<T, BaseT, ParamT>::WindowImpl(T& window, Bounds const& bounds, String const& title, ParamT const& param)
    : BaseT(bounds, title, param),
      window_(&window)
  {
  }

  /**
   * @copydoc WindowInterface::onMove
   */
  template<typename T, typename BaseT, typename ParamT>
  bool WindowImpl<T, BaseT, ParamT>::onMove(Coordinates const& coordinates)
  {
    return window_->onMove(coordinates);
  }

  /**
   * @copydoc WindowInterface::onResize
   */
  template<typename T, typename BaseT, typename ParamT>
  bool WindowImpl<T, BaseT, ParamT>::onResize(Dimensions const& dimensions)
  {
    return window_->onResize(dimensions);
  }

  /**
   * @copydoc WindowInterface::onClose
   */
  template<typename T, typename BaseT, typename ParamT>
  bool WindowImpl<T, BaseT, ParamT>::onClose()
  {
    return window_->onClose();
  }

  /**
   * @copydoc WindowInterface::onMouseMove
   */
  template<typename T, typename BaseT, typename ParamT>
  bool WindowImpl<T, BaseT, ParamT>::onMouseMove(Coordinates const& coordinates)
  {
    return window_->onMouseMove(coordinates);
  }

  /**
   * @copydoc WindowInterface::onMouseDown
   */
  template<typename T, typename BaseT, typename ParamT>
  bool WindowImpl<T, BaseT, ParamT>::onMouseDown(Coordinates const& coordinates, MouseButton button)
  {
    return window_->onMouseDown(coordinates, button);
  }

  /**
   * @copydoc WindowInterface::onMouseUp
   */
  template<typename T, typename BaseT, typename ParamT>
  bool WindowImpl<T, BaseT, ParamT>::onMouseUp(Coordinates const& coordinates, MouseButton button)
  {
    return window_->onMouseUp(coordinates, button);
  }

  /**
   * @copydoc WindowInterface::onMouseWheelDown
   */
  template<typename T, typename BaseT, typename ParamT>
  bool WindowImpl<T, BaseT, ParamT>::onMouseWheelDown(int units)
  {
    return window_->onMouseWheelDown(units);
  }

  /**
   * @copydoc WindowInterface::onMouseWheelUp
   */
  template<typename T, typename BaseT, typename ParamT>
  bool WindowImpl<T, BaseT, ParamT>::onMouseWheelUp(int units)
  {
    return window_->onMouseWheelUp(units);
  }

  /**
   * @copydoc WindowInterface::onKeyDown
   */
  template<typename T, typename BaseT, typename ParamT>
  bool WindowImpl<T, BaseT, ParamT>::onKeyDown(Key key, ModifierKey modifiers, bool repeated)
  {
    return window_->onKeyDown(key, modifiers, repeated);
  }

  /**
   * @copydoc WindowInterface::onKeyUp
   */
  template<typename T, typename BaseT, typename ParamT>
  bool WindowImpl<T, BaseT, ParamT>::onKeyUp(Key key, ModifierKey modifiers, bool repeated)
  {
    return window_->onKeyUp(key, modifiers, repeated);
  }

  /**
   * @copydoc WindowInterface::onChar
   */
  template<typename T, typename BaseT, typename ParamT>
  bool WindowImpl<T, BaseT, ParamT>::onChar(char_t character)
  {
    return window_->onChar(character);
  }

  /**
   * @return reference to "real" window
   */
  template<typename T, typename BaseT, typename ParamT>
  inline T& WindowImpl<T, BaseT, ParamT>::owner()
  {
    return *window_;
  }

  /**
   * @return reference to "real" window
   */
  template<typename T, typename BaseT, typename ParamT>
  inline T const& WindowImpl<T, BaseT, ParamT>::owner() const
  {
    return *window_;
  }
}


#endif
