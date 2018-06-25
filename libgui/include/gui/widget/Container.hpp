// Container.hpp

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

#ifndef GUICONTAINER_HPP
#define GUICONTAINER_HPP

#include <deque>

#include <base/PairAccessor.hpp>
#include <base/IteratorWrapper.hpp>

#include "gui/Allocator.hpp"
#include "gui/widget/Widget.hpp"


namespace gui
{
  /**
   * Containers are widgets that may contain other widgets. Every parent to another widget has to
   * be a Container (also the RootWidget is one). Containers have methods for adding and removing
   * children and iterating over them.
   * Beside the actual widget a Container also stores a focus index. The focus index defines in
   * which order the different children are to be focused when calling FocusNext/FocusPrevious.
   * The first index is always 0, the last is the number of children - 1. A lower index means the
   * child will get the before another with a higher index when iterating forward. With backwards
   * iteration the behavior is the other way round.
   * @note Containers do not own the children
   * @todo check whether we get problems in client software due to the Iterator returning functions
   *       being inline (returning internals of STL-container?)
   */
  class LIBGUI_EXPORT Container: public Widget
  {
  private:
    typedef std::pair<Widget*, int> ChildData;
    typedef gui::Allocator::rebind<ChildData>::other Allocator;
    typedef std::deque<ChildData, Allocator> ChildWidgets;

    typedef base::IteratorWrapper<ChildWidgets::iterator, base::PairAccessorSecond> IndexIterator;

  public:
    typedef base::IteratorWrapper<ChildWidgets::iterator, base::PairAccessorFirst>       Iterator;
    typedef base::IteratorWrapper<ChildWidgets::const_iterator, base::PairAccessorFirst> ConstIterator;

    typedef base::IteratorWrapper<ChildWidgets::reverse_iterator, base::PairAccessorFirst>       RIterator;
    typedef base::IteratorWrapper<ChildWidgets::const_reverse_iterator, base::PairAccessorFirst> ConstRIterator;

    Container(Bounds const& bounds);
    Container(Container&) = delete;
    Container(Container const&) = delete;

    virtual ~Container() = 0;

    Container& operator =(Container&&) = delete;
    Container& operator =(Container const&) = delete;

    virtual void resize(Size const& size);

    bool focusNext();
    bool focusPrevious();

    Iterator firstChild();
    Iterator endFirstChild();

    ConstIterator firstConstChild() const;
    ConstIterator endFirstConstChild() const;

    RIterator lastChild();
    RIterator endLastChild();

    ConstRIterator lastConstChild() const;
    ConstRIterator endLastConstChild() const;

  protected:
    virtual void renderChildren(Size const& size) const;

    virtual void handleBroadcastEvent(BroadcastEvent const& event);

    virtual Widget* findWidgetAtPosition(Position const& position);
    virtual Widget* findFocusedWidget();
    virtual Widget* findFocusableChildWidget(Widget const* caller);

  private:
    /**
     * This is a list of all child widgets. The first one in the list is the one with the highest
     * z-order, the last one the one with the lowest.
     */
    ChildWidgets child_widgets_;

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

    template<typename IteratorT>
    void insertChild(ChildData const& data, IteratorT begin, IteratorT end, bool top);
    void insertChild(ChildData const& data, bool top);
    ChildData eraseChild(Widget& child);

    ChildWidgets::iterator getIterator(Iterator it) const;
    ChildWidgets::iterator getIterator(RIterator it) const;

    IndexIterator firstIndex();
    IndexIterator endFirstIndex();

    bool focusWidgetByIndex(int index, bool forward, bool stop_at_end);
    bool focusChildByIndex(int index, bool forward);

    Widget* findWidgetByIndex(int index);

    int getFirstIndex(bool forward);
    int getNextIndex(int index, bool forward);
  };
}


namespace gui
{
  /**
   * @copydoc Widget::Widget
   */
  inline Container::Container(Bounds const& bounds)
    : Widget(bounds)
  {
  }

  /**
   * @return iterator pointing to first child widget of this widget
   * @note the first child also is the one with the highest z-order
   */
  inline Container::Iterator Container::firstChild()
  {
    return Iterator(child_widgets_.begin());
  }

  /**
   * @return first invalid iterator when going from first to last child
   */
  inline Container::Iterator Container::endFirstChild()
  {
    return Iterator(child_widgets_.end());
  }

  /**
   * @copydoc Container::firstChild
   */
  inline Container::ConstIterator Container::firstConstChild() const
  {
    return ConstIterator(child_widgets_.begin());
  }

  /**
   * @copydoc Container::endFirstChild
   */
  inline Container::ConstIterator Container::endFirstConstChild() const
  {
    return ConstIterator(child_widgets_.end());
  }

  /**
   * @return iterator pointing to last child widget of this widget
   * @note the last child also is the one with the lowest z-order
   */
  inline Container::RIterator Container::lastChild()
  {
    return RIterator(child_widgets_.rbegin());
  }

  /**
   * @return first invalid iterator when going from last widget to first one
   */
  inline Container::RIterator Container::endLastChild()
  {
    return RIterator(child_widgets_.rend());
  }

  /**
   * @copydoc Container::lastChild
   */
  inline Container::ConstRIterator Container::lastConstChild() const
  {
    return ConstRIterator(child_widgets_.rbegin());
  }

  /**
   * @copydoc Container::endLastChild
   */
  inline Container::ConstRIterator Container::endLastConstChild() const
  {
    return ConstRIterator(child_widgets_.rend());
  }

  /**
   *
   */
  inline Container::IndexIterator Container::firstIndex()
  {
    return IndexIterator(child_widgets_.begin());
  }

  /**
   *
   */
  inline Container::IndexIterator Container::endFirstIndex()
  {
    return IndexIterator(child_widgets_.end());
  }
}


#endif
