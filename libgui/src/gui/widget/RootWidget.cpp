// RootWidget.cpp

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

#include "gui/Error.hpp"
#include "gui/renderer/Renderer.hpp"
#include "gui/event/FocusEvent.hpp"
#include "gui/event/PositionEvent.hpp"
#include "gui/event/BroadcastEvent.hpp"
#include "gui/event/WidgetEvent.hpp"
#include "gui/event/RootWidgetEvent.hpp"
#include "gui/widget/control/theme/ThemeFactory.hpp"
#include "gui/widget/control/theme/Theme.hpp"
#include "gui/widget/RootWidget.hpp"


namespace gui
{
  //namespace
  //{
  //  /**
  //   * @param widget widget to send the given event to (including its children)
  //   * @param event broadcast event to be sent to the widget itself and its
  //   *        children
  //   */
  //  void eventBroadcast(Container& container, BroadcastEvent const& event)
  //  {
  //    event.callHandler(container);

  //    for (Container::Iterator it = container.firstChild(); it != container.endChild(); ++it)
  //      eventBroadcast(**it, event);
  //  }
  //}


  /**
   * The constructor creates a new RootWidget. A renderer factory for creating the desired
   * renderer has to be supplied.
   * @param renderer_factory factory for creating the used renderer
   * @param bounds bounds of the root widget (if you want the gui to cover the whole window, use
   *        (0, 0, cw, ch), where cw is the client area width and ch the client area height
   * @throw Error if creating the renderer failed, if the given real size is negative or zero or
   *        if there exists another root widget
   */
  RootWidget::RootWidget(Renderer& renderer, ThemeFactory const& theme_factory, Bounds const& bounds)
    : Container((setRootWidget(), bounds)), // use of the comma operator
      renderer_(&renderer),
      theme_(theme_factory.createTheme(*this)),
      mouse_receiver_(nullptr)
  {
    if (bounds.w <= 0 || bounds.h <= 0)
      throw Error(TEXT("Error creating root widget"), TEXT("Width and height of root widget must not be null"));

    if (!theme_)
      throw Error(TEXT("Error creating new root widget"), TEXT("Factory failed creating theme"));

    ASSERTOP(rootWidget(), eq, this);
  }

  /**
   * The destructor destroys the root widget and releases all resources.
   */
  RootWidget::~RootWidget()
  {
    // all children must have been destroyed before the root widget
    ASSERT(firstChild() == endFirstChild());

    // reset the root widget pointer, so another root widget can be created
    ASSERTOP(root_widget_, ne, nullptr);
    root_widget_ = nullptr;
  }

  /**
   * This method recursively renders all registered widgets (the registration is
   * done automatically for every widget).
   * @see Widget
   */
  void RootWidget::render() const
  {
    ASSERTOP(renderer_, ne, nullptr);

    renderer_->onPreRender();
    Container::render(size());
    renderer_->onPostRender();
  }

  /**
   * @param event event to be handled by the root widget (or the gui in general)
   * @param true on success, false otherwise
   */
  void RootWidget::handleEvent(EventBase const& event)
  {
    event.dispatchEvent(*this);
  }

  /**
   * This method takes a focus event and passes it to the widget with the input
   * focus.
   * @param event focus event to be passed to the widget with the input focus
   * @return true on success, false otherwise
   */
  void RootWidget::handleFocusEvent(FocusEvent const& event)
  {
    //callHooks(EVENT_HOOK_FOCUS, event);

    Widget* widget = focusedWidget();

    // it is important to call Widget::HandleFocusEvent because the RootWidget itself can have the
    // input focus and in that case we would get an endless recursion
    if (widget != nullptr)
    {
      if (widget != this)
        widget->handleFocusEvent(event);
      else
        Widget::handleFocusEvent(event);
    }
  }

  /**
   * This method takes a position event and passes it to the widget at the
   * given position. Mouse events (Up, Down, Move) are position events.
   * @param event position event to be passed to widget at stored position
   * @return true on success, false otherwise
   * @todo here we assume that position events are always mouse related - this is a bad assumption
   */
  void RootWidget::handlePositionEvent(PositionEvent const& event)
  {
    //callHooks(EVENT_HOOK_POSITION, event);

    WidgetBase* widget = nullptr;

    if (mouse_receiver_ != nullptr)
      widget = mouse_receiver_;
    else
      widget = findWidgetAtPosition(event.position());

    //ASSERTOP(widget, ne, nullptr);

    if (widget != nullptr)
    {
      if (widget != this)
        widget->handlePositionEvent(event);
      else
        Widget::handlePositionEvent(event);
    }
  }

  /**
   * This method broadcasts the given event to all subwidgets of this root
   * widget.
   * @param event event to be sent to all widgets
   * @return true on success, false otherwise
   */
  void RootWidget::handleBroadcastEvent(BroadcastEvent const& event)
  {
    Widget::handleBroadcastEvent(event);
  }

  /**
   * This method sends the given event to the desired widget.
   * @param event event to be sent to a given widget
   * @return true on success, false otherwise
   */
  void RootWidget::handleWidgetEvent(WidgetEvent const& event)
  {
    Widget& widget = event.getWidget();

    if (&widget != this)
      widget.handleWidgetEvent(event);
    else
      Widget::handleWidgetEvent(event);
  }

  /**
   * This method handles all events that are only treated by the RootWidget
   * itself.
   * @param event event to be handled only by the root widget
   */
  void RootWidget::handleRootWidgetEvent(RootWidgetEvent const& event)
  {
    event.callHandler(*this);
  }

  /**
   * This method overwrites the one of Widget. It is used for storing the new size which is needed
   * by the RootWidget for several conversions.
   * @note the intention of this method slightly differs from the one of widget because the resize
   *       is not meant for the RootWidget but for the "real" window
   * @param size new size of the "real" window in pixel
   */
  void RootWidget::onResize(Size const& size)
  {
    ASSERTOP(size.x, gt, 0);
    ASSERTOP(size.y, gt, 0);

    Container::onResize(size);
  }

  /**
   * This method registers a new event hook for a widget.
   * Note that a widget can install several hooks as long as they have
   * different types.
   * @param widget widget that gets the events
   * @param hook_type type of hook that will be installed
   * @return true on success, false otherwise
   */
//  bool RootWidget::registerEventHook(Widget& widget, EventHook hook_type)
//  {
//    ASSERTOP(hook_type, gt, EVENT_HOOK_MIN);
//    ASSERTOP(hook_type, lt, EVENT_HOOK_MAX);
//    EventHookData data(std::make_pair(&widget, hook_type));
//
//    if (std::find(hooks_.begin(), hooks_.end(), data) == hooks_.end())
//    {
//      hooks_.push_back(data);
//      return true;
//    }
//    return false;
//  }

  /// Unregister all event hooks for a widget
  /**
   * This method removes all event hooks for the given widget.
   * @param widget pointer to the widget that has registered a hook
   * @return true on success, false otherwise
   */
//  bool RootWidget::unregisterAllEventHooks(Widget& widget)
//  {
//    bool found = false;
//
//    for (EventHooks::iterator it = hooks_.begin(); it != hooks_.end(); )
//    {
//      if (it->first == &widget)
//      {
//        it = hooks_.erase(it);
//        found = true;
//      }
//      else
//        ++it;
//    }
//    return found;
//  }

  /**
   * @return pointer to widget that receives all mouse messages or null if no
   *         capture is set
   */
  WidgetBase* RootWidget::getMouseCapture() const
  {
    return mouse_receiver_;
  }

  /**
   * This methods registers a new mouse capture widget. This widget will receive
   * all mouse events directly.
   * The capture can be removed by calling this method with widget null.
   * @param widget pointer to widget that receives all mouse events or null if you
   *        want to remove the capture
   * @throw Error if another widget has captured the mouse and widget points to a valid widget
   */
  void RootWidget::setMouseCapture(WidgetBase* widget)
  {
    ASSERT(widget == nullptr || mouse_receiver_ == nullptr);

    if (widget != nullptr && mouse_receiver_ != nullptr)
    {
      throw Error(TEXT("Error setting new mouse capture"),
                  TEXT("Another widget already has captured the mouse"));
    }

    mouse_receiver_ = widget;
  }

  /**
   * This method sets the static root_widget_ variable from Widget to the value of this.
   * @note this method only exists to be called before the Container constructor is called
   * @throw Error if one root widget was created earlier and still exists
   */
  void RootWidget::setRootWidget()
  {
    if (root_widget_ != nullptr)
      throw Error(TEXT("Error creating root widget"), TEXT("Only one root widget can be created"));

    root_widget_ = this;
  }

  /**
   * This method sends the current event to all registered hookers if the given
   * hook type matches a stored one. The order in which the hooks are called is
   * the same order in which they were registered.
   * @param hook_type hook type belonging to the event (p.ex. if event is a
   *        KeyDownEvent (which is a FocusEvent) then hook_type must be
   *        EVENT_TYPE_FOCUS
   * @param event event belonging to the hook_type
   */
  //void RootWidget::callHooks(EventHook hook_type, EventBase const& event) const
  //{
  //  for (EventHooks::const_iterator it = hooks_.begin(); it != hooks_.end(); ++it)
  //  {
  //    if (it->second == hook_type || it->second == EVENT_HOOK_ALL)
  //    {
  //      Widget* widget = it->first;
  //      ASSERTOP(widget, ne, nullptr);

  //      event.callHandler(*widget);
  //    }
  //  }
  //}
}
