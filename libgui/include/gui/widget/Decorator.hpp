// Decorator.hpp

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

#ifndef GUIDECORATOR_HPP
#define GUIDECORATOR_HPP

#include <util/Assert.hpp>

#include "gui/widget/WidgetBase.hpp"


namespace gui
{
  /**
   * This class can be used as the base class for objects that decorate other widgets. That means
   * every decorator belongs to a widget and may change its behavior in some way.
   * As it belongs to exactly one widget any call to a non-event and non-render method will be
   * redirected to the widget. The event and render methods however will be called by widget and
   * can be overwritten and customized.
   * @todo optimization: think about giving all HandleXXXEvent methods a bool return value to
   *       signal whether it should continue handling; then events with position within the
   *       decorators bounds will be handled and others will be passed along; if the position
   *       appears to be outside of the client area then directly call the widget method
   * @todo find a generic way to handle the check whether a position event is within a decorator,
   *       like in Border and CaptionBar
   */
  class LIBGUI_EXPORT Decorator: public WidgetBase
  {
  public:
    Decorator(Widget& widget);
    virtual ~Decorator() = 0;

    virtual void onGainFocus();
    virtual void onLooseFocus();
    virtual void onShow();
    virtual void onHide();
    virtual void onMouseDown(Position const& position, MouseButton button);
    virtual void onMouseUp(Position const& position, MouseButton button);
    virtual void onMouseMove(Position const& position);
    virtual void onMouseWheelDown(unsigned int units);
    virtual void onMouseWheelUp(unsigned int units);
    virtual void onKeyDown(Key key, ModifierKey modifier);
    virtual void onKeyUp(Key key, ModifierKey modifier);
    virtual void onChar(char_t character);
    virtual void onCanResize(Size const& size, bool& can_resize);
    virtual void onResize(Size const& size);
    virtual void onMove(Position const& position);

    virtual RootWidget* rootWidget() const;
    virtual Widget*     focusedWidget() const;

    virtual Bounds clientArea() const;

    virtual Position absolutePosition() const;
    virtual Position position() const;
    virtual void move(Position const& position);

    virtual Size size() const;
    virtual void resize(Size const& size);

    void insertBefore(Decorator& decorator);
    void insertAfter(Decorator& decorator);
    void remove();

  protected:
    virtual void render(Size const& size) const;
    virtual void renderWidget(Size const& size) const;

    virtual void handleFocusEvent(FocusEvent const& event);
    virtual void handlePositionEvent(PositionEvent const& event);
    virtual void handleBroadcastEvent(BroadcastEvent const& event);
    virtual void handleWidgetEvent(WidgetEvent const& event);

    virtual void shrinkClientArea(Bounds& bounds) const;

    Bounds nonClientArea() const;

    virtual Decorator& getFirst();
    virtual Decorator& getLast();

    virtual bool isChild(Decorator const& decorator) const;

    Decorator* getNext() const;
    void setNext(Decorator* next);

    Decorator* getPrevious() const;
    void setPrevious(Decorator* previous);

    Widget& getWidget() const;

  private:
    friend class Widget;

    Decorator* next_;
    Decorator* previous_;
    Widget*    widget_;

    Decorator(Decorator const&);
    Decorator& operator =(Decorator const&);
  };
}


namespace gui
{
  /**
   * @return next Decorator "after" this one
   */
  inline Decorator* Decorator::getNext() const
  {
    return next_;
  }

  /**
   * @param next Decorator to set following this one
   */
  inline void Decorator::setNext(Decorator* next)
  {
    next_ = next;
  }

  /**
   * @return previous Decorator "before" this one
   */
  inline Decorator* Decorator::getPrevious() const
  {
    return previous_;
  }

  /**
   * @param previous Decorator to be "before" this one
   */
  inline void Decorator::setPrevious(Decorator* previous)
  {
    previous_ = previous;
  }

  /**
   * @return widget the decorator belongs to
   */
  inline Widget& Decorator::getWidget() const
  {
    ASSERTOP(widget_, ne, nullptr);
    return *widget_;
  }
}


#endif
