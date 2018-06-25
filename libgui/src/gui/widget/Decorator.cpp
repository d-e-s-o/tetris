// Decorator.cpp

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

#include <util/Assert.hpp>
#include <util/RectangleFunctions.hpp>
#include <util/Rectangle1Functions.hpp>

#include "gui/renderer/Renderer.hpp"
#include "gui/event/PositionEvent.hpp"
#include "gui/widget/RootWidget.hpp"
#include "gui/widget/Decorator.hpp"


namespace gui
{
  /**
   * The constructor creates a new decorator object for a given widget. The decorator will
   * automatically be set as decorator for the widget (by adding it as last decorator in the list).
   * @param widget widget the decorator belongs to
   */
  Decorator::Decorator(Widget& widget)
    : WidgetBase(),
      next_(0),
      previous_(0),
      widget_(&widget)
  {
  }

  /**
   * The destructor destroys the decorator.
   * @note the Decorator is not automatically removed from the list of Decorators because Remove
   *       would call virtual methods which may (actually will) be fatal within the destructor -
   *       this behavior however is also intended, because Decorator did not add itself into the
   *       list
   */
  Decorator::~Decorator()
  {
    // do not call Remove
    //remove();
  }

  /**
   * @copydoc WidgetBase::onGainFocus
   */
  void Decorator::onGainFocus()
  {
  }

  /**
   * @copydoc WidgetBase::onLooseFocus
   */
  void Decorator::onLooseFocus()
  {
  }

  /**
   * @copydoc WidgetBase::onShow
   */
  void Decorator::onShow()
  {
  }

  /**
   * @copydoc WidgetBase::onHide
   */
  void Decorator::onHide()
  {
  }

  /**
   * @copydoc WidgetBase::onMouseDown
   */
  void Decorator::onMouseDown(Position const& position, MouseButton button)
  {
  }

  /**
   * @copydoc WidgetBase::onMouseUp
   */
  void Decorator::onMouseUp(Position const& position, MouseButton button)
  {
  }

  /**
   * @copydoc WidgetBase::onMouseMove
   */
  void Decorator::onMouseMove(Position const& position)
  {
  }

  /**
   * @copydoc WidgetBase::onMouseWheelDown
   */
  void Decorator::onMouseWheelDown(unsigned int units)
  {
  }

  /**
   * @copydoc WidgetBase::onMouseWheelUp
   */
  void Decorator::onMouseWheelUp(unsigned int units)
  {
  }

  /**
   * @copydoc WidgetBase::onKeyDown
   */
  void Decorator::onKeyDown(Key key, ModifierKey modifier)
  {
  }

  /**
   * @copydoc WidgetBase::onKeyUp
   */
  void Decorator::onKeyUp(Key key, ModifierKey modifier)
  {
  }

  /**
   * @copydoc WidgetBase::onChar
   */
  void Decorator::onChar(char_t character)
  {
  }

  /**
   * @copydoc WidgetBase::onCanResize
   */
  void Decorator::onCanResize(Size const& size, bool& can_resize)
  {
  }

  /**
   * @copydoc WidgetBase::onResize
   */
  void Decorator::onResize(Size const& size)
  {
  }

  /**
   * @copydoc WidgetBase::onMove
   */
  void Decorator::onMove(Position const& position)
  {
  }

  /**
   * @copydoc WidgetBase::rootWidget
   */
  RootWidget* Decorator::rootWidget() const
  {
    return getWidget().rootWidget();
  }

  /**
   * @copydoc WidgetBase::focusedWidget
   */
  Widget* Decorator::focusedWidget() const
  {
    return getWidget().focusedWidget();
  }

  /**
   * This method returns the client area of the Decorator. However it should only be called for
   * the first Decorator for a widget.
   * @return client area of the Decorator
   */
  Bounds Decorator::clientArea() const
  {
    ASSERTOP(getWidget().getFirst(), eq, this);

    Bounds bounds = getRectangle(Position(), getWidget().size());
    Decorator const* decorator = this;

    do
    {
      decorator->shrinkClientArea(bounds);
      decorator = decorator->getNext();
    }
    while (decorator != 0);

    return bounds;
  }

  /**
   *
   */
  Position Decorator::absolutePosition() const
  {
    Position position(this->position());
    position += getWidget().absolutePosition();
    position += utl::getPosition(nonClientArea());

    return position;
  }

  /**
   * @copydoc WidgetBase::position
   */
  Position Decorator::position() const
  {
    return Position();
  }

  /**
   * @copydoc WidgetBase::move
   */
  void Decorator::move(Position const& position)
  {
    // do nothing
  }

  /**
   * @copydoc WidgetBase::size
   */
  Size Decorator::size() const
  {
    return utl::getSize(nonClientArea());
  }

  /**
   * @copydoc WidgetBase::resize
   */
  void Decorator::resize(Size const& size)
  {
    // do nothing
  }

  /**
   * @copydoc WidgetBase::render
   */
  void Decorator::render(Size const& size) const
  {
    renderWidget(size);

    if (getNext() != 0)
    {
      Bounds bounds = getRectangle(Position(), size);
      shrinkClientArea(bounds);

      Renderer& renderer = rootWidget()->getRenderer();

      renderer.pushClippingRectangle(utl::convert(bounds));
      getNext()->render(utl::getSize(bounds));
      renderer.popClippingRectangle();
    }
  }

  /**
   * This method renders the actual decorator. Put in your rendering code here.
   * @param size
   */
  void Decorator::renderWidget(Size const& size) const
  {
  }

  /**
   * @copydoc Widget::handleFocusEvent
   */
  void Decorator::handleFocusEvent(FocusEvent const& event)
  {
    if (getPrevious() != 0)
      getPrevious()->handleFocusEvent(event);
  }

  /**
   * @copydoc Widget::handlePositionEvent
   */
  void Decorator::handlePositionEvent(PositionEvent const& event)
  {
    // for now do not call the handler; a decorator has to intercept that call (by overriding) and
    // call event.CallHandler itself
    //bool result = event.callHandler(*this);

    // note that if there is no Decorator left we need to call the handling method on the Widget,
    // that is because they are stacked
    // @see Widget::handlePositionEvent
    if (getPrevious() != 0)
      getPrevious()->handlePositionEvent(event);
    else
      event.callHandler(getWidget());
  }

  /**
   * @copydoc Widget::handleBroadcastEvent
   */
  void Decorator::handleBroadcastEvent(BroadcastEvent const& event)
  {
    if (getPrevious() != 0)
      getPrevious()->handleBroadcastEvent(event);
  }

  /**
   * @copydoc Widget::handleWidgetEvent
   * @note this method should never be called, because widget events only belong to the widget
   */
  void Decorator::handleWidgetEvent(WidgetEvent const& event)
  {
    if (getPrevious() != 0)
      getPrevious()->handleWidgetEvent(event);
  }

  /**
   * This method can be overwritten die resttrict the client area a widget has. That is for
   * example of importance for shadows or borders around widgets, so that nothing will be painted
   * above them.
   * @param[in,out] bounds bounds of the client area to shrink
   */
  void Decorator::shrinkClientArea(Bounds& bounds) const
  {
  }

  /**
   * This method is basically the opposite to clientArea(). It checks the previous Decorators and
   * sums up their restriction of the client area. So this is the area that this Decorator does NOT
   * cover. However since this method is only relevant for implementing Decorators (no Widget should
   * need this information) it is protected and non virtual.
   * @return bounds of the non client area
   * @note that if you want to know the non client area of the widget you should always call this
   *       method on the FIRST Decorator of it
   */
  Bounds Decorator::nonClientArea() const
  {
    Bounds bounds = utl::getRectangle(Position(), getWidget().size());

    Decorator* decorator = getPrevious();

    while (decorator != 0)
    {
      decorator->shrinkClientArea(bounds);
      decorator = decorator->getPrevious();
    }
    return bounds;
  }

  /**
   * This method has to return the first Decorator within the current one. This is only useful
   * if you create a Decorator that consists of multiple Decorators itself. Overwrite this method
   * accordingly if this is of interest to you. In this case you should also overwrite IsChild.
   * @return first Decorator within the current one
   * @see Decorator::getLast
   * @see Decorator::isChild
   */
  Decorator& Decorator::getFirst()
  {
    return *this;
  }

  /**
   * This method has to return the last Decorator within the current one.
   * @return last Decorator within the current one
   * @see Decorator::getFirst
   * @see Decorator::isChild
   */
  Decorator& Decorator::getLast()
  {
    return *this;
  }

  /**
   * This method is used to check whether a given Decorator is child of this one. This can
   * only happen if the user designed the Decorator so, that it consists of other Decorators. In
   * this case this method should be overwritten.
   * @param decorator decorator to check whether it is child of "this" one
   * @return true if the given decorator is child of this one
   */
  bool Decorator::isChild(Decorator const& decorator) const
  {
    return false;
  }

  /**
   * This method is used for inserting the decorator into the list before the given one.
   * @param decorator Decorator to insert "this" one before
   */
  void Decorator::insertBefore(Decorator& decorator)
  {
    if (!isChild(decorator) && !decorator.isChild(*this))
    {
      Decorator* first = &decorator.getFirst();

      getFirst().setPrevious(first->getPrevious());
      getLast().setNext(first);

      if (first->getPrevious() != 0)
        first->getPrevious()->setNext(&getFirst());

      first->setPrevious(&getLast());
    }
    else
    {
      setPrevious(decorator.getPrevious());
      setNext(&decorator);

      if (decorator.getPrevious() != 0)
        decorator.getPrevious()->setNext(this);

      decorator.setPrevious(this);
    }

    getWidget().updateFirst();
  }

  /**
   * This method is used for inserting the decorator into the list after the given one.
   * @param decorator Decorator to insert "this" one after
   */
  void Decorator::insertAfter(Decorator& decorator)
  {
    if (!isChild(decorator) && !decorator.isChild(*this))
    {
      Decorator* last = &decorator.getLast();

      getFirst().setPrevious(last);
      getLast().setNext(last->getNext());

      if (last->getNext() != 0)
        last->getNext()->setPrevious(&getLast());

      last->setNext(&getFirst());
    }
    else
    {
      setPrevious(&decorator);
      setNext(decorator.getNext());

      if (decorator.getNext() != 0)
        decorator.getNext()->setPrevious(this);

      decorator.setNext(this);
    }

    getWidget().updateLast();
  }

  /**
   * This method removes the current Decorator from the list. After that the next one in the list
   * will directly follow the previous one and "this" Decorator will not have a previous nor a
   * following Decorator.
   */
  void Decorator::remove()
  {
    Decorator* previous = getFirst().getPrevious();
    Decorator* next     = getLast().getNext();

    if (previous != 0)
      previous->setNext(next);

    if (next != 0)
      next->setPrevious(previous);

    getFirst().setPrevious(0);
    getLast().setNext(0);

    // removing a Decorator may affect the first and last pointer within the widget
    getWidget().updateFirst();
    getWidget().updateLast();
  }
}
