// Widget.cpp

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

#include "gui/Error.hpp"
#include "gui/renderer/Renderer.hpp"
#include "gui/event/FocusEvent.hpp"
#include "gui/event/PositionEvent.hpp"
#include "gui/event/BroadcastEvent.hpp"
#include "gui/event/WidgetEvent.hpp"
#include "gui/widget/WidgetFunctions.hpp"
#include "gui/widget/Decorator.hpp"
#include "gui/widget/RootWidget.hpp"
#include "gui/widget/DummyWidget.hpp"
#include "gui/widget/control/theme/Theme.hpp"
#include "gui/widget/Widget.hpp"


namespace gui
{
  namespace
  {
    /**
     * This class is used for checking if a given position event is a MouseDown event.
     */
    class MouseDownDispatcher: public DummyWidget
    {
    public:
      MouseDownDispatcher()
        : button_(wnd::MOUSE_BUTTON_MIN),
          mouse_down_(false)
      {
      }

      virtual void onMouseDown(Position const& position, MouseButton button)
      {
        button_     = button;
        mouse_down_ = true;
      }

      wnd::MouseButton getButton() const
      {
        return button_;
      }

      bool isMouseDown() const
      {
        return mouse_down_;
      }

    private:
      wnd::MouseButton button_;

      bool mouse_down_;
    };

    class KeyDownDispatcher: public DummyWidget
    {
    public:
      KeyDownDispatcher()
        : key_(wnd::KEY_MIN),
          modifier_(wnd::MOD_KEY_MIN),
          key_down_(false)
      {
      }

      virtual void onKeyDown(Key key, ModifierKey modifier)
      {
        key_      = key;
        modifier_ = modifier;
        key_down_ = true;
      }

      wnd::Key getKey() const
      {
        return key_;
      }

      wnd::ModifierKey getModifier() const
      {
        return modifier_;
      }

      bool isKeyDown() const
      {
        return key_down_;
      }

    private:
      wnd::Key         key_;
      wnd::ModifierKey modifier_;

      bool key_down_;
    };
  }


  /**
   * Pointer to the root widget
   * @note there can only be one root widget and it sets this pointer automatically itself during
   *       construction
   * @see RootWidget
   */
  RootWidget* Widget::root_widget_ = nullptr;

  /**
   * Pointer to the widget that currently has the focus or null if none has
   */
  Widget* Widget::focused_ = nullptr;


  /**
   * The constructor creates a new widget and registers it at its parent. By default the root
   * widget will become the parent.
   * After creation a widgets visible flag is set to true, meaning it will be
   * displayed if the parent is displayed, too.
   * @param bounds bounds of the widget (position and size)
   * @note the constructor should not contain any widget focusing or activating code (any call to
   *       Activate) because this can lead to access violations, because widgets that are
   *       not ready constructed get accessed. The same goes for the destructor.
   * @throw Error if bounds are invalid (negative or zero width or height) or if there was no root
   *        widget created earlier
   */
  Widget::Widget(Bounds const& bounds)
    : WidgetBase(),
      parent_(nullptr),
      first_(nullptr),
      last_(nullptr),
      bounds_(bounds),
      h_anchors_(H_ANCHORS_LEFT),
      v_anchors_(V_ANCHORS_BOTTOM),
      visible_(true),
      focusable_(true),
      always_top_(false),
      always_bottom_(false)
  {
    if (bounds.w <= 0 || bounds.h <= 0)
      throw Error(TEXT("Error creating new widget"), TEXT("Width and height must not be 0"));

    // root widget also uses this constructor, it has no parent though
    if (root_widget_ != this)
    {
      if (root_widget_ == nullptr)
        throw Error(TEXT("Error creating new widget"), TEXT("No root widget found"));

      parent_ = root_widget_;
      addChildToParent(*parent_, *this);
    }

    ASSERT(shown());
    ASSERT(!focused());
  }

  /// Copy constructor is not defined
  //Widget::Widget(Widget const& widget)
  //{
  //  parent_ = widget.parent_;
  //  dimensions_ = widget.dimensions_;
  //  visible_ = widget.visible_;
  //
  //  ChildWidgets const& childs = widget.child_widgets_;
  //
  //  for (ChildWidgets::const_iterator it = childs.begin();
  //       it != childs.end(); ++it)
  //  {
  //    // create new childs from old ones (recursive call of copy constructor
  //    // the only problem is that we would have to allocate new memory
  //    // but then we would have to release it, too
  //  }
  //}

  /**
   * The destructor free's all used resources and unregisteres the widget at its parent so that
   * it will not use the invalid pointer anymore.
   * If the widget is focused then no widget will have focus after it is destroyed.
   */
  Widget::~Widget()
  {
    // do not call OnLooseFocus here, because we are in destructor and virtual functions may not
    // work as expected
    if (focused())
      resetFocused();

    // if there is no parent it is the root widget
    if (parent_ != nullptr)
    {
      ASSERTOP(root_widget_, ne, this);
      removeChildFromParent(*parent_, *this);
    }
  }

  /**
   * This method gets called moments after the widget got focused.
   * @return true on success, false otherwise
   * @note the return value is not processed internally, it can freely be used by the user
   */
  void Widget::onGainFocus()
  {
    ASSERT(shown() && visible() && focused());
  }

  /**
   * This method gets called right after the widget lost its input focus.
   * @return true on success, false otherwise
   * @note the return value is not processed internally, it can freely be used by the user
   */
  void Widget::onLooseFocus()
  {
    ASSERT(shown() && visible() && !focused());
  }

  /**
   * This method gets called right after the widget got visible.
   * @return true on success, false otherwise
   * @note the return value is not processed internally, it can freely be used by the user
   */
  void Widget::onShow()
  {
    ASSERT(shown() && visible());
  }

  /**
   * This method gets called right after the widget got invisible.
   * @return true on success, false otherwise
   * @note the return value is not processed internally, it can freely be used by the user
   */
  void Widget::onHide()
  {
    ASSERT(!visible());
  }

  /**
   * @param position absolute mouse coordinates
   * @param button the mouse button pressed
   * @return true on success, false otherwise
   */
  void Widget::onMouseDown(Position const& position, MouseButton button)
  {
    ASSERT(shown() && visible());
#ifndef NDEBUG
    if (rootWidget()->getMouseCapture() != this)
    {
      ASSERTOP(position.x, ge, 0);
      ASSERTOP(position.x, le, size().x);
      ASSERTOP(position.y, ge, 0);
      ASSERTOP(position.y, le, size().y);
    }
#endif
  }

  /**
   * @param position absolute mouse coordinates
   * @param button the mouse button released
   * @return true on success, false otherwise
   * @note the return value is not processed internally, it can freely be used by the user
   */
  void Widget::onMouseUp(Position const& position, MouseButton button)
  {
    ASSERT(shown() && visible());
#ifndef NDEBUG
    if (rootWidget()->getMouseCapture() != this)
    {
      ASSERTOP(position.x, ge, 0);
      ASSERTOP(position.x, le, size().x);
      ASSERTOP(position.y, ge, 0);
      ASSERTOP(position.y, le, size().y);
    }
#endif
  }

  /**
   * @param position absolute mouse coordinates
   * @return true on success, false otherwise
   * @note the return value is not processed internally, it can freely be used by the user
   */
  void Widget::onMouseMove(Position const& position)
  {
    ASSERT(shown() && visible());
#ifndef NDEBUG
    if (rootWidget()->getMouseCapture() != this)
    {
      ASSERTOP(position.x, ge, 0);
      ASSERTOP(position.x, le, size().x);
      ASSERTOP(position.y, ge, 0);
      ASSERTOP(position.y, le, size().y);
    }
#endif
  }

  /**
   * @param units number of units the wheel was scrolled towards the user
   * @return true on success, false otherwise
   * @note the return value is not processed internally, it can freely be used by the user
   */
  void Widget::onMouseWheelDown(unsigned int units)
  {
    ASSERT(shown() && visible());
  }

  /**
   * @param units number of units the wheel was scrolled away from the user
   * @return true on success, false otherwise
   * @note the return value is not processed internally, it can freely be used by the user
   */
  void Widget::onMouseWheelUp(unsigned int units)
  {
    ASSERT(shown() && visible());
  }

  /**
   * @param key the key that was pressed
   * @param modifier modifier keys pressed during the event (several may be combined via bitwise
   *        or)
   * @return true on success, false otherwise
   * @note the return value is not processed internally, it can freely be used by the user
   */
  void Widget::onKeyDown(Key key, ModifierKey modifier)
  {
    ASSERT(shown() && visible() && focused());
  }

  /**
   * @param key the key was was released
   * @param modifier modifier keys pressed during the event (several may be combined via bitwise
   *        or)
   * @return true on success, false otherwise
   * @note the return value is not processed internally, it can freely be used by the user
   */
  void Widget::onKeyUp(Key key, ModifierKey modifier)
  {
    ASSERT(shown() && visible() && focused());
  }

  /**
   * This method gets called right after OnKeyDown if the pressed key can be represented by a
   * character.
   * @param character character code of the key pressed
   * @return true on success, false otherwise
   * @note the return value is not processed internally, it can freely be used by the user
   */
  void Widget::onChar(char_t character)
  {
    ASSERT(shown() && visible() && focused());
  }

  /**
   * @param size desired new size
   * @param can_resize[in,out] set it to false if you do not want resizing to happen, default is
   *        true
   */
  void Widget::onCanResize(Size const& size, bool& can_resize)
  {
    ASSERT(size != this->size());
  }

  /**
   * This method gets called right after the widget changed its size.
   * @param size the widgets new width and height
   */
  void Widget::onResize(Size const& size)
  {
    ASSERT(size == this->size());
  }

  /**
   * This method gets called right after the widget was moved.
   * @param position the widgets new position relative to its parent
   */
  void Widget::onMove(Position const& position)
  {
    ASSERT(position == this->position());
  }

  /**
   * @return pointer to the RootWidget of this widget
   */
  RootWidget* Widget::rootWidget() const
  {
    ASSERTOP(root_widget_, ne, nullptr);
    return root_widget_;
  }

  /**
   * @return pointer to the currently focused widget or null
   */
  Widget* Widget::focusedWidget() const
  {
    ASSERT(focused_ != nullptr && focused_->visible() || focused_ == nullptr);
    return focused_;
  }

  /**
   * @return bounds of the client area (relative to the bounds of the widget)
   * @note the client area may only be narrowed by Decorators
   * @see Decorator
   */
  Bounds Widget::clientArea() const
  {
    if (getFirst() != nullptr)
      return getFirst()->clientArea();

    return getRectangle(Position(), size());
  }

  /**
   * @return absolute position of the widget
   */
  Position Widget::absolutePosition() const
  {
    Position position = this->position();
    Widget*  parent   = getParent();

    while (parent != nullptr)
    {
      position += parent->position();
      position += utl::getPosition(parent->clientArea());

      parent = parent->getParent();
    }
    return position;
  }

  /**
   * @return position of the widget (relative coordinates)
   */
  Position Widget::position() const
  {
    return utl::getPosition(bounds_);
  }

  /**
   * @param position new position relative to parent
   */
  void Widget::move(Position const& position)
  {
    if (position == this->position())
      return;

    utl::setPosition(bounds_, position);
    onMove(position);
  }

  /**
   * @return size of the widget
   */
  Size Widget::size() const
  {
    return utl::getSize(bounds_);
  }

  /**
   * Set the width and height of the widget
   * @param size new width and height of the widget
   */
  void Widget::resize(Size const& size)
  {
    if (size == this->size())
      return;

    bool can_resize = true;
    onCanResize(size, can_resize);

    if (can_resize)
    {
      utl::setSize(bounds_, size);
      onResize(size);
    }
  }

  /**
   * @return pointer to the parent widget, or null if no parent exists
   */
  Container* Widget::getParent() const
  {
    return parent_;
  }

  /**
   * @param container new container widget that will be parent or null for the root widget
   */
  void Widget::setParent(Container* parent)
  {
    ASSERTOP(parent, ne, this);

    if (parent != parent_)
    {
      if (parent == nullptr)
        parent = rootWidget();

      ASSERTOP(parent,  ne, nullptr);
      ASSERTOP(parent_, ne, nullptr);

      addChildToParent(*parent, *this);
      removeChildFromParent(*parent_, *this);

      parent_ = parent;
    }
  }

  /**
   * This function returns the current value of the visible flag.
   * @note this function does NOT check, whether this widget is actually rendered, because this
   *       depends on whether the parent widget is visible (and its parent and so on). If you
   *       want to know whether it is rendered you should call visible().
   * @return true if the visible flag is set, false if not
   * @see Widget::visible
   */
  bool Widget::shown() const
  {
    return visible_;
  }

  /**
   * This method makes the widget visible. It sets the visible flag and activates the parents if
   * necessary. It also informs all children with an show event (onShow()).
   * @return true if visible flag could be set to true or false if not
   */
  bool Widget::show()
  {
    if (!shown())
      return activate(false);

    return false;
  }

  /**
   * @return true if the widget is rendered or false if not
   * @see Widget::shown
   */
  bool Widget::visible() const
  {
    Widget const* widget = this;

    while (widget->shown())
    {
      if (widget->getParent() != nullptr)
        widget = widget->getParent();
      else
        return true;
    }
    return false;
  }

  /**
   * This method makes the widget invisible. It also informs all children that
   * they got invisible by sending the onHide() event.
   * @return true if the widget was visible (IsVisible == true) and is now hidden, false if it
   *         was not visible
   */
  bool Widget::hide()
  {
    if (shown())
      return deactivate();

    return false;
  }

  /**
   * @return true if the widget has the focus, false if not
   */
  bool Widget::focused() const
  {
    bool result = (focused_ == this);
    ASSERT(result && shown() && visible() && isFocusable() || !result);
    return result;
  }

  /**
   * This method focuses the widget. If any of the parent widgets is not yet visible it makes it
   * so.
   * @return true if focusing the widget was successful, false otherwise
   * @note if a widget cannot be focused (not focusable) this method will look for the next parent
   *       that can be focused and focus it, in that case the return value is false
   */
  bool Widget::focus()
  {
    if (!focused())
    {
#ifndef NDEBUG
      bool result =
#endif
      activate(true);

      ASSERT(result && shown() && visible() || !result);
      return focused();
    }
    return false;
  }

  /**
   *
   */
  void Widget::moveToTop()
  {
    Widget* parent = getParent();

    if (parent != nullptr)
      parent->moveToTop(*this);
  }

  /**
   *
   */
  void Widget::moveToBottom()
  {
    Widget* parent = getParent();

    if (parent != nullptr)
      parent->moveToBottom(*this);
  }

  /**
   * This method can be used to retrieve the focus index of the widget.
   * @return focus index the widget has at its parent
   */
  int Widget::focusIndex() const
  {
    Widget* parent = getParent();

    if (parent != nullptr)
      return parent->getChildFocusIndex(*this);

    return 0;
  }

  /**
   *
   */
  bool Widget::increaseFocusIndex()
  {
    Widget* parent = getParent();

    if (parent != nullptr)
      return parent->changeChildFocusIndex(*this, true);

    return false;
  }

  /**
   *
   */
  bool Widget::decreaseFocusIndex()
  {
    Widget* parent = getParent();

    if (parent != nullptr)
      return parent->changeChildFocusIndex(*this, false);

    return false;
  }

  /**
   *
   */
  HAnchors Widget::getHAnchors() const
  {
    ASSERTOP(h_anchors_, gt, H_ANCHORS_MIN);
    ASSERTOP(h_anchors_, lt, H_ANCHORS_MAX);
    return h_anchors_;
  }

  /**
   *
   */
  void Widget::setHAnchors(HAnchors h_anchors)
  {
    ASSERTOP(h_anchors_, gt, H_ANCHORS_MIN);
    ASSERTOP(h_anchors_, lt, H_ANCHORS_MAX);
    h_anchors_ = h_anchors;
  }

  /**
   *
   */
  VAnchors Widget::getVAnchors() const
  {
    ASSERTOP(v_anchors_, gt, V_ANCHORS_MIN);
    ASSERTOP(v_anchors_, lt, V_ANCHORS_MAX);
    return v_anchors_;
  }

  /**
   *
   */
  void Widget::setVAnchors(VAnchors v_anchors)
  {
    ASSERTOP(v_anchors_, gt, V_ANCHORS_MIN);
    ASSERTOP(v_anchors_, lt, V_ANCHORS_MAX);
    v_anchors_ = v_anchors;
  }

  /**
   * This method is called whenever the widget should be rendered. It then first calls RenderWidget,
   * then RenderContent, RenderChildren and after this it renders the decorator if any.
   * Do not overwrite it unless you really know what you are doing. Your rendering stuff should
   * most likely go into RenderContent (or maybe RenderWidget).
   * It will automatically be called by the root widget, do not call it yourself.
   * @param[in] renderer renderer object that can be used for rendering
   */
  void Widget::render(Size const& size) const
  {
    if (shown())
    {
      ASSERT(visible());

      Bounds const& bounds        = getRectangle(this->position(), this->size());
      Bounds const& client_bounds = clientArea();

      Renderer& renderer = rootWidget()->getRenderer();
      renderer.pushClippingRectangle(utl::convert(bounds));

      renderWidget(utl::getSize(bounds));

  // @todo remove this if no longer needed
  if (focused())
  {
    Renderer& renderer = rootWidget()->getRenderer();

    renderer.pushColor(Color(0x00, 0x00, 0x00, 0x40));
    renderer.renderRectangle(utl::convert(utl::getRectangle(Position(), utl::getSize(bounds))));
    renderer.popColor();
  }

      // only decorators may change the client area, if none is present the client area is not
      // restricted
      if (getFirst() != nullptr)
        renderer.pushClippingRectangle(utl::convert(client_bounds));

      renderContent(utl::getSize(client_bounds));
      renderChildren(utl::getSize(client_bounds));

      if (getFirst() != nullptr)
      {
        renderer.popClippingRectangle();

        // the decorator can render to the whole widget
        getFirst()->render(utl::getSize(bounds));
      }
      renderer.popClippingRectangle();
    }
  }

  /**
   * This method is for implementation matters and is overwritten by Container to render the
   * children.
   * @param[in] renderer renderer object that can be used for rendering the children
   */
  void Widget::renderChildren(Size const& size) const
  {
  }

  /**
   * This method is called whenever the widget itself should be rendered. No more check for
   * visibility has to be done within here.
   * @param[in] renderer renderer object that can be used for rendering the widget
   */
  void Widget::renderWidget(Size const& size) const
  {
  }

  /**
   * This method gets called if the content is to be drawn. That is, right after the widget rendered
   * itself. The drawable area equal clientArea(). User specific rendering code should go in here.
   * @param[in] renderer renderer object that can be used for rendering to the client area
   */
  void Widget::renderContent(Size const& size) const
  {
  }

  /**
   *
   */
  void Widget::handleFocusEvent(FocusEvent const& event)
  {
    ASSERT(focused());

    if (getLast() != nullptr)
      getLast()->handleFocusEvent(event);

    event.callHandler(*this);

    checkFocusEvent(event);
  }

  /**
   *
   */
  void Widget::handlePositionEvent(PositionEvent const& event)
  {
    // note that if there is a Decorator the event is passed to it and after that we return - this
    // is necessary because the Decorator "lies" over the widget and decides whether the widget gets
    // the event or not
    if (getLast() != nullptr)
      getLast()->handlePositionEvent(event);
    else
      event.callHandler(*this);

    checkPositionEvent(event);
  }

  /**
   *
   */
  void Widget::handleBroadcastEvent(BroadcastEvent const& event)
  {
    if (getLast() != nullptr)
      getLast()->handleBroadcastEvent(event);

    event.callHandler(*this);
  }

  /**
   *
   */
  void Widget::handleWidgetEvent(WidgetEvent const& event)
  {
    event.callHandler(*this);
  }

  /**
   * This method searches all widgets beginning with this one and looks for one within the given
   * coordinates. Note that it does not search its parents, only the children. However, every
   * widget has at least the root widget as its parent widget - so calling this method on it will
   * always return a valid pointer.
   * @param[in] position position to find widget at
   * @return pointer to the found widget, or null if none was found
   */
  Widget* Widget::findWidgetAtPosition(Position const& position)
  {
    if (shown())
    {
      ASSERT(visible());

      if (contains(getAbsoluteBounds(*this), position))
        return this;
    }
    return nullptr;
  }

  /**
   * This functions searches for the focused widget in the children of this widget.
   * @return pointer to the focused widget or null if it was not found.
   * @note we could just look at focused_ to get the pointer to the focused widget - however this
   *       function can be used if you want to know if the focused widget is one of the children
   *       of another widget
   */
  Widget* Widget::findFocusedWidget()
  {
    ASSERT(!focused() || visible() && focused());

    if (focused())
    {
      ASSERT(visible());
      return this;
    }
    return nullptr;
  }

  /**
   * This method searches for a visible and focusable widget that may receive the next input focus
   * in the following order:
   * 1) first check yourself
   * 2) than check your children if any
   * 3) after that check your parent if any
   * @param caller widget the function was called from
   * @return first widget found that is focusable
   */
  Widget* Widget::findFocusableWidget(Widget const* caller)
  {
    ASSERT(visible());

    if (shown())
    {
      if (isFocusable())
        return this;

      Widget* widget = findFocusableChildWidget(this);

      if (widget != nullptr)
        return widget;

      Widget* parent = getParent();

      if (parent != nullptr && parent != caller)
        return parent->findFocusableWidget(this);
    }
    return nullptr;
  }

  /**
   * This method is intended for searching the children of a container for a focusable widget. It
   * does nothing on a widget.
   * @param caller widget the function was called from
   * @return null as a widget does not have any children
   */
  Widget* Widget::findFocusableChildWidget(Widget const* caller)
  {
    return nullptr;
  }

  /**
   * @return true if the widget can get the input focus, false if not
   */
  bool Widget::isFocusable() const
  {
    return focusable_;
  }

  /**
   * @param focusable true to make the widget focusable, false if not
   */
  void Widget::setFocusable(bool focusable)
  {
    focusable_ = focusable;
  }

  /**
   * @return true if the widget is always above widgets without this flag set, false if not
   */
  bool Widget::isAlwaysOnTop() const
  {
    return always_top_;
  }

  /**
   * @param always_top true to make the widget stay above others not having this flag set, false for
   *        normal behavior
   * @note setting this to true will set the always on bottom flag to false
   */
  void Widget::setAlwaysOnTop(bool always_top)
  {
    if (always_top != always_top_)
    {
      if (always_top)
        setAlwaysOnBottom(false);

      always_top_ = always_top;

      moveToTop();
    }
  }

  /**
   * @param true if the widget is always above other widgets not having this flag set, false if not
   */
  bool Widget::isAlwaysOnBottom() const
  {
    return always_bottom_;
  }

  /**
   * @param always_bottom true to make the widget stay below others not having this flag set, false
   *        for normal behavior
   * @note setting this to true will set the always on top flag to false
   */
  void Widget::setAlwaysOnBottom(bool always_bottom)
  {
    if (always_bottom != always_bottom_)
    {
      if (always_bottom)
        setAlwaysOnTop(false);

      always_bottom_ = always_bottom;

      moveToTop();
    }
  }

  /**
   *
   */
  void Widget::updateFirst()
  {
    if (first_ == nullptr)
      first_ = last_;

    if (first_ != nullptr)
    {
      while (first_->getPrevious() != nullptr)
        first_ = first_->getPrevious();

      ASSERTOP(first_, ne, nullptr);
    }
  }

  /**
   *
   */
  void Widget::updateLast()
  {
    if (last_ == nullptr)
      last_ = first_;

    if (last_ != nullptr)
    {
      while (last_->getNext() != nullptr)
        last_ = last_->getNext();

      ASSERTOP(last_, ne, nullptr);
    }
  }

  /**
   * This function recursively activates all parent widgets (read: the parent and its parent and its
   * parent and ...) and itself. It takes care for every event that has to be sent, while doing this
   * (focusing, activating, deactivating etc.).
   * It is pretty much THE function that does focus, activate, deactivate, unfocus and is therefore
   * pretty complex.
   * @param focus not only activate but also focus the current widget
   * @return true if widget was invisible and is now visible, false otherwise
   * @note This function is for internal use only!
   */
  bool Widget::activate(bool focus)
  {
    Widget* parent = getParent();

    if (parent != nullptr)
    {
      // make all parents active, meaning they will get the highest z-order and get visible if
      // they are not
      parent->activate(false);

      moveToTop();
    }

    bool result = false;

    if (!shown())
    {
      visible_ = true;
      result   = true;

      onShow();
    }

    if (focus && !focused())
    {
      Widget* focusable = findFocusableWidget(this);
      Widget* focused   = focusedWidget();

      if (focused != focusable)
      {
        focused_ = focusable;
        focused_->onGainFocus();

        if (focused != nullptr)
          focused->onLooseFocus();
      }
    }
    return result;
  }

  /**
   * This function hides the current widget and takes care for sending the correct events.
   * @return true if widget was visible and is now invisible, false otherwise
   * @note This function is for internal use only!
   */
  bool Widget::deactivate()
  {
    if (shown())
    {
      // if the focused widget is somehow a child of us, we need to unfocus it
      Widget* focused = findFocusedWidget();
      ASSERT(focused == nullptr || focused->focused());

      if (focused != nullptr)
      {
        ASSERTOP(focused, eq, focused_);

        // if the root widget is to be deactivated set focused_ to null, because no widget must be
        // focused
        if (rootWidget() != this)
          resetFocused();
        else
          focused_ = nullptr;

        focused->onLooseFocus();
      }

      bool was_visible = visible();

      visible_ = false;

      if (was_visible)
        onHide();

      return was_visible;
    }
    return false;
  }

  /**
   * @param show true if widgets should be informed via onShow, false for onHide
   * @param self false to only act on children, not yourself, true to include self
   * @note This function is for internal use only!
   * @see Container
   */
  void Widget::informChildren(bool show, bool self)
  {
    if (self)
    {
      if (show)
      {
        ASSERT(visible());
        onShow();
      }
      else
      {
        ASSERT(!visible());
        onHide();
      }
    }
  }

  /**
   * This is overwritten by Container to implement the 'add child' functionality. It does nothing on
   * non-container widgets.
   * @param child child to add to container
   */
  void Widget::addChild(Widget& child)
  {
    // nothing to be done here
  }

  /**
   * This is overwritten by Container to implement the 'remove child' functionality. It does nothing
   * on non-container widgets.
   * @param child child to remove from container
   */
  void Widget::removeChild(Widget& child)
  {
    // nothing to be done here
  }

  /**
   * This is overwritten by Container to implement the 'move to top' functionality. It does
   * nothing on non-container widgets.
   * @param child child to increase the z-order to be on top of the section
   * @see Container::moveToTop
   */
  void Widget::moveToTop(Widget& child)
  {
    // nothing to be done here
  }

  /**
   * This is overwritten by Container to implement the 'move to bottom' functionality. It does
   * nothing on non-container widgets.
   * @param child child to decrease the z-order to be on bottom of the section
   * @see Container::moveToBottom
   */
  void Widget::moveToBottom(Widget& child)
  {
    // nothing to be done here
  }

  /**
   * This is overwritten by Container to implement the 'get focus index' functionality. It does
   * nothing on non-container widgets.
   */
  int Widget::getChildFocusIndex(Widget const& child) const
  {
    return 0;
  }

  /**
   * This is overwritten by Container to implement the 'change focus index' functionality. It does
   * nothing on non-container widgets.
   */
  bool Widget::changeChildFocusIndex(Widget const& child, bool increase)
  {
    return false;
  }

  /**
   * @param forward true to focus the next, false to focus the previous
   * @param stop_at_end this parameter is only used by containers
   */
  bool Widget::focusNext(bool forward, bool stop_at_end)
  {
    ASSERT(focused());

    Container* parent = getParent();

    if (parent != nullptr)
      return forward ? parent->focusNext() : parent->focusPrevious();

    return false;
  }

  /**
   * This method is called to check if a widget "wants" to get the input focus.
   * @param forward not needed for widgets
   * @return true if the widget is now focused, false if not
   */
  bool Widget::checkedFocusNext(bool forward)
  {
    if (shown() && isFocusable() && !focused())
      return focus();

    return false;
  }

  /**
   * @param parent parent to add given child to
   * @param child child to add to parent
   */
  inline void Widget::addChildToParent(Container& parent, Widget& child)
  {
    Widget& widget = parent;
    widget.addChild(child);
  }

  /**
   * @param parent parent to remove given child from
   * @param child child to remove from given parent
   */
  inline void Widget::removeChildFromParent(Container& parent, Widget& child)
  {
    Widget& widget = parent;
    widget.removeChild(child);
  }

  /**
   * This method checks the type and data of the given event and if necessary focuses the next or
   * previous widget.
   * @param event focus event to dispatch
   */
  inline void Widget::checkFocusEvent(FocusEvent const& event)
  {
    if (focused())
    {
      KeyDownDispatcher dispatcher;
      event.callHandler(dispatcher);

      if (dispatcher.isKeyDown() && dispatcher.getKey() == wnd::KEY_TAB)
      {
        if (wnd::checkForModifier(dispatcher.getModifier(), wnd::MOD_KEY_NONE))
        {
          focusNext(true, false);
        }
        else
        if (wnd::checkForModifier(dispatcher.getModifier(), wnd::MOD_KEY_LSHIFT) ||
            wnd::checkForModifier(dispatcher.getModifier(), wnd::MOD_KEY_RSHIFT))
        {
          focusNext(false, false);
        }
      }
    }
  }

  /**
   * This method checks the type and data of the given event and if necessary focuses the
   * current widget.
   * @param event position event to dispatch
   */
  inline void Widget::checkPositionEvent(PositionEvent const& event)
  {
    // check if the "activating" mouse button was pressed, in that case focus the widget
    MouseDownDispatcher dispatcher;
    event.callHandler(dispatcher);

    if (dispatcher.isMouseDown() &&
        dispatcher.getButton() == rootWidget()->getTheme().actionButton())
    {
      // check that the widget has not become invisible after handling the event
      if (visible())
        focus();
    }
  }

  /**
   *
   */
  void Widget::resetFocused() const
  {
    Widget* root_widget = root_widget_;

    // this method is also called during destruction; in that case root_widget_ may be zero (if
    // root widget itself is destroyed) so we need to check for this here
    focused_ = root_widget != nullptr ? root_widget->findFocusableWidget(this) : nullptr;

    if (focused_ != nullptr)
      focused_->onGainFocus();
  }
}
