// Window.hpp

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

#ifndef WNDWINDOW_HPP
#define WNDWINDOW_HPP

#include "window/Bounds.hpp"
#include "window/String.hpp"
#include "window/WindowBase.hpp"


namespace wnd
{
  /**
   * This class represents an "ordinary" window. A window is created when its
   * constructor is called and destroyed by its destructor.
   */
  template<typename ImplT>
  class Window: public WindowBase
  {
  public:
    Window(Bounds const& bounds, String const& title = String(TEXT("")));

    virtual bool handleEvents();

    virtual void close();

    virtual bool onDraw();
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

    virtual Coordinates position() const;
    virtual bool move(Coordinates const& coordinates);

    virtual Dimensions size() const;
    virtual bool resize(Dimensions const& dimensions);

    virtual Dimensions clientSize() const;

    virtual ScreenInterface&       screen();
    virtual ScreenInterface const& screen() const;

  private:
    ImplT impl_;
  };
}


namespace wnd
{
  /**
   * @param bounds position and size of the window
   * @param title title of the window (in the caption bar)
   */
  template<typename ImplT>
  inline Window<ImplT>::Window(Bounds const& bounds, String const& title)
    : WindowBase(),
      impl_(*this, bounds, title)
  {
  }

  /**
   * @copydoc WindowBase::handleEvents
   */
  template<typename ImplT>
  bool Window<ImplT>::handleEvents()
  {
    return impl_.handleEvents();
  }

  /**
   * @copydoc WindowBase::close
   */
  template<typename ImplT>
  void Window<ImplT>::close()
  {
    impl_.close();
  }

  /**
   * @copydoc WindowBase::onDraw
   */
  template<typename ImplT>
  bool Window<ImplT>::onDraw()
  {
    return true;
  }

  /**
   * @copydoc WindowBase::onMove
   */
  template<typename ImplT>
  bool Window<ImplT>::onMove(Coordinates const& coordinates)
  {
    return true;
  }

  /**
   * @copydoc WindowBase::onResize
   */
  template<typename ImplT>
  bool Window<ImplT>::onResize(Dimensions const& dimensions)
  {
    return true;
  }

  /**
   * @copydoc WindowBase::onClose
   */
  template<typename ImplT>
  bool Window<ImplT>::onClose()
  {
    return true;
  }

  /**
   * @copydoc WindowBase::onMouseMove
   */
  template<typename ImplT>
  bool Window<ImplT>::onMouseMove(Coordinates const& coordinates)
  {
    return true;
  }

  /**
   * @copydoc WindowBase::onMouseDown
   */
  template<typename ImplT>
  bool Window<ImplT>::onMouseDown(Coordinates const& coordinates, MouseButton button)
  {
    return true;
  }

  /**
   * @copydoc WindowBase::onMouseUp
   */
  template<typename ImplT>
  bool Window<ImplT>::onMouseUp(Coordinates const& coordinates, MouseButton button)
  {
    return true;
  }

  /**
   * @copydoc WindowBase::onMouseWheelDown
   */
  template<typename ImplT>
  bool Window<ImplT>::onMouseWheelDown(int units)
  {
    return true;
  }

  /**
   * @copydoc WindowBase::onMouseWheelUp
   */
  template<typename ImplT>
  bool Window<ImplT>::onMouseWheelUp(int units)
  {
    return true;
  }

  /**
   * @copydoc WindowBase::onKeyDown
   */
  template<typename ImplT>
  bool Window<ImplT>::onKeyDown(Key key, ModifierKey modifiers, bool repeated)
  {
    return true;
  }

  /**
   * @copydoc WindowBase::onKeyUp
   */
  template<typename ImplT>
  bool Window<ImplT>::onKeyUp(Key key, ModifierKey modifiers, bool repeated)
  {
    return true;
  }

  /**
   * @copydoc WindowBase::onChar
   */
  template<typename ImplT>
  bool Window<ImplT>::onChar(char_t character)
  {
    return true;
  }

  /**
   * @copydoc WindowBase::position
   */
  template<typename ImplT>
  Coordinates Window<ImplT>::position() const
  {
    return impl_.position();
  }

  /**
   * @copydoc WindowBase::move
   */
  template<typename ImplT>
  bool Window<ImplT>::move(Coordinates const& coordinates)
  {
    return impl_.move(coordinates);
  }

  /**
   * @copydoc WindowBase::size
   */
  template<typename ImplT>
  Dimensions Window<ImplT>::size() const
  {
    return impl_.size();
  }

  /**
   * @copydoc WindowBase::resize
   */
  template<typename ImplT>
  bool Window<ImplT>::resize(Dimensions const& dimensions)
  {
    return impl_.resize(dimensions);
  }

  /**
   * @copydoc WindowBase::clientSize
   */
  template<typename ImplT>
  Dimensions Window<ImplT>::clientSize() const
  {
    return impl_.clientSize();
  }

  /**
   * @copydoc WindowBase::screen
   */
  template<typename ImplT>
  ScreenInterface& Window<ImplT>::screen()
  {
    return impl_.screen();
  }

  /**
   * @copydoc WindowBase::screen
   */
  template<typename ImplT>
  ScreenInterface const& Window<ImplT>::screen() const
  {
    return impl_.screen();
  }
}


#endif
