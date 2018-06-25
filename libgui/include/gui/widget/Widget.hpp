// Widget.hpp

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

#ifndef GUIWIDGET_HPP
#define GUIWIDGET_HPP

#include "gui/Anchors.hpp"
#include "gui/widget/WidgetBase.hpp"


namespace gui
{
  class Decorator;


  /**
   * This class is the base class for all graphical objects. Widgets have a parent, a position
   * (which is relative to the parent widget), a size and some other attributes.
   * They may also have a list of Decorators that may alter the look or behavior of the widget.
   * Decorators are like layers that are stacked on top of the widget. They can render above it
   * and the widget will forward messages to them (if not told otherwise).
   * @todo create copy constructor that copies the current widget but not the
   *       child widgets (do it for all other controls too of course)
   * @todo think about moving all the onXXX() event methods in protected area
   * @todo think about moving clientArea() into protected area
   * @todo shown() should be renamed to something more explicit
   * @todo remove the size parameter from all Render methods
   */
  class LIBGUI_EXPORT Widget: public WidgetBase
  {
  public:
    Widget(Bounds const& bounds);
    virtual ~Widget() = 0;

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

    Container* getParent() const;
    void setParent(Container* parent);

    bool shown() const;
    bool show();

    bool visible() const;
    bool hide();

    bool focused() const;
    bool focus();

    void moveToTop();
    void moveToBottom();

    int focusIndex() const;

    bool increaseFocusIndex();
    bool decreaseFocusIndex();

    HAnchors getHAnchors() const;
    void setHAnchors(HAnchors h_anchors);

    VAnchors getVAnchors() const;
    void setVAnchors(VAnchors v_anchors);

  protected:
    virtual void render(Size const& size) const;
    virtual void renderChildren(Size const& size) const;
    virtual void renderWidget(Size const& size) const;
    virtual void renderContent(Size const& size) const;

    virtual void handleFocusEvent(FocusEvent const& event);
    virtual void handlePositionEvent(PositionEvent const& event);
    virtual void handleBroadcastEvent(BroadcastEvent const& event);
    virtual void handleWidgetEvent(WidgetEvent const& event);

    virtual Widget* findWidgetAtPosition(Position const& position);
    virtual Widget* findFocusedWidget();
    virtual Widget* findFocusableWidget(Widget const* caller);
    virtual Widget* findFocusableChildWidget(Widget const* caller);

    bool isFocusable() const;
    void setFocusable(bool focusable);

    bool isAlwaysOnTop() const;
    void setAlwaysOnTop(bool always_top);

    bool isAlwaysOnBottom() const;
    void setAlwaysOnBottom(bool always_bottom);

    Decorator* getFirst() const;
    void setFirst(Decorator* first);

    Decorator* getLast() const;
    void setLast(Decorator* last);

    void updateFirst();
    void updateLast();

  private:
    friend class RootWidget;
    friend class Container;
    friend class Decorator;

    static RootWidget* root_widget_;
    static Widget*     focused_;

    Container* parent_;
    Decorator* first_;
    Decorator* last_;

    Bounds   bounds_;
    HAnchors h_anchors_;
    VAnchors v_anchors_;

    bool visible_;
    bool focusable_;
    bool always_top_;
    bool always_bottom_;

    Widget(Widget const&);
    Widget& operator =(Widget const&);

    virtual bool activate(bool focus);
    virtual bool deactivate();

    virtual void informChildren(bool show, bool self);

    virtual void addChild(Widget& child);
    virtual void removeChild(Widget& child);

    virtual void moveToTop(Widget& child);
    virtual void moveToBottom(Widget& child);

    virtual int getChildFocusIndex(Widget const& child) const;
    virtual bool changeChildFocusIndex(Widget const& child, bool increase);

    virtual bool focusNext(bool forward, bool stop_at_end);
    virtual bool checkedFocusNext(bool forward);

    void addChildToParent(Container& parent, Widget& child);
    void removeChildFromParent(Container& parent, Widget& child);

    void checkFocusEvent(FocusEvent const& event);
    void checkPositionEvent(PositionEvent const& event);

    void resetFocused() const;
  };
}


namespace gui
{
  /**
   * @return first Decorator in the list of Decorators or 0 if the list is empty
   * @note the first Decorator in the list is the one with the lowest z-order
   */
  inline Decorator* Widget::getFirst() const
  {
    return first_;
  }

  /**
   * @param first Decorator to set as the first one in the list of Decorators
   * @note the first Decorator in the list is the one with the lowest z-order
   */
  inline void Widget::setFirst(Decorator* first)
  {
    first_ = first;
    last_  = 0;

    updateFirst();
    updateLast();
  }

  /**
   * @return last Decorator in the list of Decorators or 0 if the list is empty
   * @note the last Decorator in the list is the one with the highest z-order
   */
  inline Decorator* Widget::getLast() const
  {
    return last_;
  }

  /**
   * @param last Decorator to set as the last one in the list of Decorators
   * @note the last Decorator in the list is the one with the highest z-order
   */
  inline void Widget::setLast(Decorator* last)
  {
    first_ = 0;
    last_  = last;

    updateFirst();
    updateLast();
  }
}


#endif
