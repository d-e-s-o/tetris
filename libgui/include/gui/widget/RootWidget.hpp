// RootWidget.hpp

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

#ifndef GUIROOTWIDGET_HPP
#define GUIROOTWIDGET_HPP

#include <vector>

#include <util/Assert.hpp>
#include <pointer/Deleter.hpp>
#include <pointer/UniquePointer.hpp>

//#include "gui/Allocator.hpp"
//#include "gui/widget/EventHook.hpp"
#include "gui/widget/Container.hpp"


namespace gui
{
  class EventBase;
  class Renderer;
  class ThemeFactory;
  class Theme;
  class RootWidgetEvent;


  /**
   * This class represents the root window, which is (directly or indirectly) the parent to all
   * other widgets. It somehow represents the "real" window in which the whole system runs, and
   * is therefor the receiver of all events from it (which it then passes to the children).
   * @note there can only be one root widget instance at a time
   * @todo find a way to use a multimap for storing the event hook stuff
   *       with sun studio (it seems to be broken)
   * @todo if we need finer grained hook types (like hooks for mouse move only)
   *       we need to dispatch the events to more special ones (meaning
   *       event.DispatchEvent had to call the OnXXX method of root widget
   *       and root widget would search the appropriate widget and call its
   *       method)
   * @todo think about moving HandleRootWidgetEvent into WidgetBase like all other event
   *       handling functions
   * @todo when setting a new theme, we should actually pass in a ThemeFactory for creating it
   * @todo maybe we should remove the getRenderer() thing completely, the access should only be
   *       granted via the Theme
   * @todo it would probably make sense to also replace the ThemeFactory stuff with an actual Theme
   *       instance that is created outside and only stored as a reference -- think about this!
   */
  class LIBGUI_EXPORT RootWidget: public Container
  {
  public:
    RootWidget(Renderer& renderer, ThemeFactory const& theme_factory, Bounds const& bounds);
    virtual ~RootWidget();

    void render() const;

    void handleEvent(EventBase const& event);

    virtual void handleFocusEvent(FocusEvent const& event);
    virtual void handlePositionEvent(PositionEvent const& event);
    virtual void handleBroadcastEvent(BroadcastEvent const& event);
    virtual void handleWidgetEvent(WidgetEvent const& event);
    virtual void handleRootWidgetEvent(RootWidgetEvent const& event);

//    bool registerEventHook(Widget& widget, EventHook hook_type);
//    bool unregisterAllEventHooks(Widget& widget);

    virtual void onResize(Size const& size);

    Renderer&       getRenderer();
    Renderer const& getRenderer() const;

    Theme const& getTheme() const;
    //void setTheme(Theme const& theme);

    WidgetBase* getMouseCapture() const;
    void setMouseCapture(WidgetBase* widget);

  private:
    //typedef std::pair<Widget*, EventHook> EventHookData;
    //typedef Allocator::rebind<EventHookData>::other Allocator;
    //typedef std::vector<EventHookData, Allocator> EventHooks;

    typedef ptr::UniquePointer<Theme> ThemePointer;

    Renderer*    renderer_;
    ThemePointer theme_;

    //EventHooks  hooks_;
    WidgetBase* mouse_receiver_;

    // there cannot exist two root widget at the same time so it cannot be copyable
    RootWidget(RootWidget const&);
    RootWidget& operator =(RootWidget const&);

    void setRootWidget();

    //void callHooks(EventHook hook_type, EventBase const& event) const;
  };
}


namespace gui
{
  /**
   * @return renderer object for this root widget and all child widgets
   */
  inline Renderer& RootWidget::getRenderer()
  {
    ASSERTOP(renderer_, ne, nullptr);
    return *renderer_;
  }

  /**
   * @return renderer object for this root widget and all child widgets
   */
  inline Renderer const& RootWidget::getRenderer() const
  {
    ASSERTOP(renderer_, ne, nullptr);
    return *renderer_;
  }

  /**
   * @return theme currently in use
   */
  inline Theme const& RootWidget::getTheme() const
  {
    ASSERTOP(theme_.pointer(), ne, nullptr);
    return *theme_;
  }

  /**
   * This method can be used to set a new theme for all child widgets of this
   * widget.
   * @param theme new theme to be used
   * @todo send message to all children for changing theme
   * @todo implement me
   */
  //inline void RootWidget::setTheme(Theme const& theme)
  //{
  //  ASSERT(false);
  //}
}


#endif
