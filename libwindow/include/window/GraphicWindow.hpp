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

#ifndef WNDGRAPHICWINDOW_HPP
#define WNDGRAPHICWINDOW_HPP

#include "window/GraphicWindowBase.hpp"


namespace wnd
{
  /**
   * @todo GraphicWindow has to derive from Window and just add some methods
   */
  template<typename ImplT>
  class GraphicWindow: public GraphicWindowBase
  {
  public:
    GraphicWindow(Bounds const& bounds, String const& title);

    virtual bool handleEvents();

    virtual void close();

    virtual void initialize() = 0;
    virtual void render() const = 0;

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
    virtual bool onChar(char_t character);

    virtual Coordinates position() const;
    virtual bool move(Coordinates const& coordinates);

    virtual Dimensions size() const;
    virtual bool resize(Dimensions const& dimensions);

    virtual Dimensions clientSize() const;

    virtual ScreenInterface&       screen();
    virtual ScreenInterface const& screen() const;

    virtual bool isFullscreen() const;
    virtual bool toggleFullscreen();

  protected:
    virtual void initializeView() const = 0;

    ImplT&       impl();
    ImplT const& impl() const;

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
  GraphicWindow<ImplT>::GraphicWindow(Bounds const& bounds, String const& title)
    : GraphicWindowBase(),
      impl_(*this, bounds, title)
  {
  }

  /**
   * @copydoc GraphicWindowBase::handleEvents
   */
  template<typename ImplT>
  bool GraphicWindow<ImplT>::handleEvents()
  {
    return impl_.handleEvents();
  }

  /**
   * @copydoc GraphicWindowBase::close
   */
  template<typename ImplT>
  void GraphicWindow<ImplT>::close()
  {
    impl_.close();
  }

  /**
   * @copydoc GraphicWindowBase::initialize
   */
  template<typename ImplT>
  void GraphicWindow<ImplT>::initialize()
  {
    initializeView();
  }

  /**
   * @copydoc GraphicWindowBase::render
   */
  template<typename ImplT>
  void GraphicWindow<ImplT>::render() const
  {
    return impl_.render();
  }

  /**
   * @copydoc GraphicWindowBase::onMove
   */
  template<typename ImplT>
  bool GraphicWindow<ImplT>::onMove(Coordinates const& coordinates)
  {
    return true;
  }

  /**
   * @copydoc GraphicWindowBase::onResize
   */
  template<typename ImplT>
  bool GraphicWindow<ImplT>::onResize(Dimensions const& dimensions)
  {
    initializeView();
    return true;
  }

  /**
   * @copydoc GraphicWindowBase::onClose
   */
  template<typename ImplT>
  bool GraphicWindow<ImplT>::onClose()
  {
    return true;
  }

  /**
   * @copydoc GraphicWindowBase::onMouseMove
   */
  template<typename ImplT>
  bool GraphicWindow<ImplT>::onMouseMove(Coordinates const& coordinates)
  {
    return true;
  }

  /**
   * @copydoc GraphicWindowBase::onMouseDown
   */
  template<typename ImplT>
  bool GraphicWindow<ImplT>::onMouseDown(Coordinates const& coordinates, MouseButton button)
  {
    return true;
  }

  /**
   * @copydoc GraphicWindowBase::onMouseUp
   */
  template<typename ImplT>
  bool GraphicWindow<ImplT>::onMouseUp(Coordinates const& coordinates, MouseButton button)
  {
    return true;
  }

  /**
   * @copydoc GraphicWindowBase::onMouseWheelDown
   */
  template<typename ImplT>
  bool GraphicWindow<ImplT>::onMouseWheelDown(int units)
  {
    return true;
  }

  /**
   * @copydoc GraphicWindowBase::onMouseWheelUp
   */
  template<typename ImplT>
  bool GraphicWindow<ImplT>::onMouseWheelUp(int units)
  {
    return true;
  }

  /**
   * @copydoc GraphicWindowBase::onKeyDown
   */
  template<typename ImplT>
  bool GraphicWindow<ImplT>::onKeyDown(Key key, ModifierKey modifiers)
  {
    return true;
  }

  /**
   * @copydoc GraphicWindowBase::onKeyUp
   */
  template<typename ImplT>
  bool GraphicWindow<ImplT>::onKeyUp(Key key, ModifierKey modifiers)
  {
    return true;
  }

  /**
   * @copydoc GraphicWindowBase::onChar
   */
  template<typename ImplT>
  bool GraphicWindow<ImplT>::onChar(char_t character)
  {
    return true;
  }

  /**
   * @copydoc GraphicWindowBase::position
   */
  template<typename ImplT>
  Coordinates GraphicWindow<ImplT>::position() const
  {
    return impl_.position();
  }

  /**
   * @copydoc GraphicWindowBase::move
   */
  template<typename ImplT>
  bool GraphicWindow<ImplT>::move(Coordinates const& coordinates)
  {
    return impl_.move(coordinates);
  }

  /**
   * @copydoc GraphicWindowBase::size
   */
  template<typename ImplT>
  Dimensions GraphicWindow<ImplT>::size() const
  {
    return impl_.size();
  }

  /**
   * @copydoc GraphicWindowBase::resize
   */
  template<typename ImplT>
  bool GraphicWindow<ImplT>::resize(Dimensions const& dimensions)
  {
    return impl_.resize(dimensions);
  }

  /**
   * @copydoc GraphicWindowBase::clientSize
   */
  template<typename ImplT>
  Dimensions GraphicWindow<ImplT>::clientSize() const
  {
    return impl_.clientSize();
  }

  /**
   * @copydoc GraphicWindowBase::screen
   */
  template<typename ImplT>
  ScreenInterface& GraphicWindow<ImplT>::screen()
  {
    return impl_.screen();
  }

  /**
   * @copydoc GraphicWindowBase::screen
   */
  template<typename ImplT>
  ScreenInterface const& GraphicWindow<ImplT>::screen() const
  {
    return impl_.screen();
  }

  /**
   * @copydoc GraphicWindowBase::isFullscreen
   */
  template<typename ImplT>
  bool GraphicWindow<ImplT>::isFullscreen() const
  {
    return impl_.isFullscreen();
  }

  /**
   * @copydoc GraphicWindowBase::toggleFullscreen
   * @todo find out if we should also call onResize()
   */
  template<typename ImplT>
  bool GraphicWindow<ImplT>::toggleFullscreen()
  {
    bool result = impl_.toggleFullscreen();

    // changing to fullscreen or back to window mode requires the view to be adjusted
    initializeView();

    return result;
  }

  template<typename ImplT>
  ImplT& GraphicWindow<ImplT>::impl()
  {
    return impl_;
  }

  template<typename ImplT>
  ImplT const& GraphicWindow<ImplT>::impl() const
  {
    return impl_;
  }
}


#endif
