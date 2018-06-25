// Container.cpp

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

#include <algorithm>
#include <functional>

#include <util/Assert.hpp>
#include <util/Algorithm.hpp>
#include <util/Rectangle1Functions.hpp>

#include "gui/Error.hpp"
#include "gui/Anchors.hpp"
#include "gui/widget/Container.hpp"


namespace gui
{
  /**
   * @copydoc Widget::~Widget
   */
  Container::~Container()
  {
    // if this widget is destroyed we make all children children of this widgets parent
    for (Iterator it = firstChild(), end = endFirstChild(); it != end; ++it)
      (*it)->setParent(getParent());
  }

  /**
   * This method is overwritten to support Anchors. If a Container is resized it moves/resizes
   * the children according to their anchors.
   * @see HAnchors
   * @see VAnchors
   */
  void Container::resize(Size const& size)
  {
    Size size_before = this->size();
    Widget::resize(size);
    Size size_after = this->size();

    if (size_after != size_before)
    {
      Size diff = size_after - size_before;

      for (Iterator it = firstChild(); it != endFirstChild(); ++it)
      {
        HAnchors h_anchors = (*it)->getHAnchors();
        VAnchors v_anchors = (*it)->getVAnchors();
        Position position  = (*it)->position();
        Size     size      = (*it)->size();

        // note: by default all widgets behave as if H_ANCHORS_LEFT and V_ANCHORS_BOTTOM are set
        //       (due to the relative positioning in combination with the lower left edge being
        //       origin), so we only have special cases if those are NOT set
        if (isAnchorSet(h_anchors, H_ANCHORS_RIGHT))
        {
          if (isAnchorSet(h_anchors, H_ANCHORS_LEFT))
            size.x += diff.x;
          else
            position.x += diff.x;
        }

        if (isAnchorSet(v_anchors, V_ANCHORS_TOP))
        {
          if (isAnchorSet(v_anchors, V_ANCHORS_BOTTOM))
            size.y += diff.y;
          else
            position.y += diff.y;
        }

        (*it)->move(position);
        (*it)->resize(size);
      }
    }
  }

  /**
   * This method can be used for focusing the containers next widget. That means that based on
   * the currently focused widget the one with the next higher focus index will be focused. This is
   * especially useful for 'tabbing' through the controls.
   * @return true if the next widget could be focused, false if not
   * @note it does not matter whether a children is directly focused or just a container containing
   *       the focused widget; the result is the same
   * @note if none of the containers children is focused the widget with the lowest focus index
   *       will get focused
   * @note this method ignores widgets that are not focusable, however it will also ignore
   *       containers that are focusable but jump to the first widget of containers that are not
   *       focusable
   */
  bool Container::focusNext()
  {
    return focusNext(true, false);
  }

  /**
   * This method can be used for focusing the containers previous widget.
   * The rules of FocusNext apply in an analogous way, but the direction of focusing is reversed.
   * @return true if the previous widget could be focused, false if not
   */
  bool Container::focusPrevious()
  {
    return focusNext(false, false);
  }

  /**
   * @copydoc Widget::renderChildren
   */
  void Container::renderChildren(Size const& size) const
  {
    // it is important to renderer children from last to first, so that the first can cover
    // the one before (with lower z-order)
    for (ConstRIterator it = lastConstChild(), end = endLastConstChild(); it != end; ++it)
      (*it)->render(size);
  }

  /**
   * @copydoc Widget::handleBroadcastEvent
   */
  void Container::handleBroadcastEvent(BroadcastEvent const& event)
  {
    Widget::handleBroadcastEvent(event);

    for (Iterator it = firstChild(), end = endFirstChild(); it != end; ++it)
      (*it)->handleBroadcastEvent(event);
  }

  /**
   * @copydoc Widget::findWidgetAtPosition
   */
  Widget* Container::findWidgetAtPosition(Position const& position)
  {
    if (Widget::findWidgetAtPosition(position) != nullptr)
    {
      Bounds bounds = clientArea();
      utl::move(bounds, absolutePosition());

      // children may only be found if within the client area
      if (contains(bounds, position))
      {
        for (Iterator it = firstChild(), end = endFirstChild(); it != end; ++it)
        {
          Widget* widget = (*it)->findWidgetAtPosition(position);

          if (widget != nullptr)
            return widget;
        }
      }
      return this;
    }
    return nullptr;
  }

  /**
   * @copydoc Widget::findFocusedWidget
   */
  Widget* Container::findFocusedWidget()
  {
    ASSERT(!focused() || visible() && focused());

    if (shown())
    {
      if (focused())
        return this;

      Iterator end = endFirstChild();
      Iterator it  = std::find_if(firstChild(), end, std::mem_fun(&Widget::findFocusedWidget));

      if (it != end)
        return *it;
    }
    return nullptr;
  }

  /**
   * @copydoc Widget::findFocusableChildWidget
   */
  Widget* Container::findFocusableChildWidget(Widget const* caller)
  {
    ASSERT(visible());

    int     index = getFirstIndex(true);
    Widget* child = nullptr;

    while (child = findWidgetByIndex(index++), child != nullptr)
    {
      if (child != caller)
      {
        Widget* widget = child->findFocusableWidget(this);

        if (widget != nullptr)
          return widget;
      }
    }
    return nullptr;
  }

  /**
   * @copydoc Widget::activate
   */
  bool Container::activate(bool focus)
  {
    if (Widget::activate(focus))
    {
      informChildren(true, false);
      return true;
    }
    return false;
  }

  /**
   * @copydoc Widget::deactivate
   */
  bool Container::deactivate()
  {
    // Deactivate returns true only if the widget was visible, only in this case we need
    // to inform the children
    if (Widget::deactivate())
    {
      informChildren(false, false);
      return true;
    }
    return false;
  }

  /**
   * @param show true if widgets should be informed via OnShow, false for OnHide
   * @param self true if this container should also be informed, false if not
   * @note this method is for implementation purposes only
   */
  void Container::informChildren(bool show, bool self)
  {
    ASSERT(!show && !visible() || show);

    if (show && shown() || !show && !visible())
    {
      if (self)
        Widget::informChildren(show, true);

      for (ConstIterator it = firstConstChild(), end = endFirstConstChild(); it != end; ++it)
      {
        // if not the widget itself was deactivated but the visible flag of a child is not
        // enabled, then this means the child was invisible before and needs no OnHide calls
        // @todo check if this part is correct
        if ((*it)->shown())
          (*it)->informChildren(show, true);
      }
    }
  }

  /**
   * This method adds a new widget to the list of children of this widget. This is necessary for
   * the container and widget to act with each other.
   * @param[in] child child that should be added to list of children
   * @throw Error if the child is already in the list
   * @note this method is for implementation purposes only
   */
  void Container::addChild(Widget& child)
  {
    ASSERTOP(&child, ne, this);

    ChildData data(&child, child_widgets_.size());
    insertChild(data, false);

    ASSERTOP(data.second, eq, *std::max_element(firstIndex(), endFirstIndex()));
  }

  /**
   * This method removes a widget from the list of children. The container and the widget will
   * no longer act with each other.
   * @param[in] child child to remove from list of children
   * @throw Error if the child was not found in the list
   * @note this method is for implementation purposes only; it does not set the parent of the
   *       widget!
   */
  void Container::removeChild(Widget& child)
  {
    ChildData data = eraseChild(child);

    // decrement the indices if they are greater than the one from the removed child
    for (IndexIterator it = firstIndex(), end = endFirstIndex(); it != end; ++it)
    {
      if (*it > data.second)
        --(*it);
    }
  }

  /**
   * This method makes the given widget the one with the highest z-order according to its state.
   * @param child child to move to the top of its section
   * @throw Error if the widget could not be found
   */
  void Container::moveToTop(Widget& child)
  {
    ChildData data = eraseChild(child);
    insertChild(data, true);
  }

  /**
   * This method makes the given widget the one with the lowest z-order according to its state.
   * @param child child to move to the bottom of its section
   * @throw Error if the widget could not be found
   */
  void Container::moveToBottom(Widget& child)
  {
    ChildData data = eraseChild(child);
    insertChild(data, false);
  }

  /**
   *
   */
  int Container::getChildFocusIndex(Widget const& child) const
  {
    ConstIterator it = utl::find(firstConstChild(), endFirstConstChild(), &child);
    ASSERT(it != endFirstConstChild());

    return it.getIterator()->second;
  }

  /**
   * @param child child whose focus index is to be increased/decreased
   * @param increase true to increase the index associated to the child, false to decrease it
   * @return true if changing the focus index was succesful, false otherwise
   */
  bool Container::changeChildFocusIndex(Widget const& child, bool increase)
  {
    // first search the child and get the index
    Iterator it1 = utl::find(firstChild(), endFirstChild(), &child);
    ASSERT(it1 != endFirstChild());

    int& index1 = it1.getIterator()->second;

    // next search for the new index the child should have
    IndexIterator end = endFirstIndex();
    IndexIterator it2 = utl::find(firstIndex(), end, index1 + (increase ? 1 : -1));

    // only if this new index already exists there is a child that has it and we can exchange
    // those, otherwise it is the maximum/minimum index and we do not do anything
    if (it2 != end)
    {
      int& index2 = *it2;

      std::swap(index1, index2);
      return true;
    }
    return false;
  }

  /**
   * @param forward true to focus widgets by increasing the focus index, false for decreasing it
   * @param stop_at_end true to do not start over focusing the first widget if no other widget
   *        "wants" the focus, false to loop once
   * @return true if a widget could be focused, false if not
   * @note there are three cases:
   *       1) the container itself is focused
   *         -> focus the first/last depending on direction
   *       2) a child is focused or contains the focused widget
   *         -> check whether this widget "wants" the focus, if it does not focus the next
   *       3) the focused widget is not within this container
   *         -> focus the first/last depending on direction
   */
  bool Container::focusNext(bool forward, bool stop_at_end)
  {
    int index;

    // 1)
    if (focused())
      index = getFirstIndex(forward);
    else
    {
      // search for the child that is focused or contains the focused widget
      Iterator end = endFirstChild();
      Iterator it  = std::find_if(firstChild(), end, std::mem_fun(&Widget::findFocusedWidget));

      // 2)
      if (it != end)
      {
        if ((*it)->checkedFocusNext(forward))
          return true;

        index = getNextIndex(it.getIterator()->second, forward);
      }
      // 3)
      else
        index = getFirstIndex(forward);
    }
    return focusWidgetByIndex(index, forward, stop_at_end);
  }

  /**
   * This method is called to check if a container has a child that "wants" the input focus.
   * @param forward true to focus the next, false to focus the previous widget
   * @return true if a widget wanted the focus, false if not
   * @note only not focusable containers will allow one of their children to get focused
   */
  bool Container::checkedFocusNext(bool forward)
  {
    if (shown() && !isFocusable())
      return focusNext(forward, true);

    return false;
  }

  /**
   * @param data child data to insert into the list of children
   * @param begin begin iterator of children range
   * @param end end iterator of children range
   * @param top true to insert the value on top of the section it belongs to, false to insert it
   *        at the bottom
   * @throw Error if the Widget ("first" of data) already exists in the list
   * @note the list of children is seperated into three sections, the first one contains all
   *       widgets that stay always on top, the second one widgets that are not always on top and
   *       not always on bottom and the third one all that are always on bottom; the top parameter
   *       only defines if the data should be inserted on top or bottom of the section, not the
   *       array
   * @note this method is for implementation purposes only!
   */
  template<typename IteratorT>
  void Container::insertChild(ChildData const& data, IteratorT begin, IteratorT end, bool top)
  {
    ASSERTOP(data.first, ne, nullptr);

    IteratorT it = utl::find(begin, end, data.first);

    if (it != end)
      throw Error(TEXT("Error adding new child"), TEXT("Child already exists"));

    if (data.first->isAlwaysOnBottom())
      it = std::find_if(begin, end, std::mem_fun(&Widget::isAlwaysOnBottom));
    else if (data.first->isAlwaysOnTop())
      it = std::find_if(begin, end, std::mem_fun(&Widget::isAlwaysOnTop));
    else
    {
      if (top)
        it = std::find_if(begin, end, std::not1(std::mem_fun(&Widget::isAlwaysOnTop)));
      else
        it = std::find_if(begin, end, std::not1(std::mem_fun(&Widget::isAlwaysOnBottom)));
    }

    child_widgets_.insert(getIterator(it), data);
  }

  /**
   * @param data ChildData to insert into the list of children
   * @param top true to insert the value on top of the section it belongs to, false to insert it
   *        at the bottom
   * @see Container::insertChild
   * @note this method is for implementation purposes only!
   */
  void Container::insertChild(ChildData const& data, bool top)
  {
    if (top)
      insertChild(data, firstChild(), endFirstChild(), top);
    else
      insertChild(data, lastChild(), endLastChild(), top);
  }

  /**
   * @param child child to be erased from list of children
   * @return ChildData object that was removed from the list
   * @note this method is for implementation purposes only!
   */
  Container::ChildData Container::eraseChild(Widget& child)
  {
    Iterator end = endFirstChild();
    Iterator it  = utl::find(firstChild(), end, &child);

    if (it == end)
      throw Error(TEXT("Error removing child from list"), TEXT("Child not found"));

    ChildData data = *it.getIterator();

    child_widgets_.erase(it.getIterator());

    return data;
  }

  /**
   * @param it iterator wrapper object
   * @return STL-iterator wrapped by the given one
   */
  inline Container::ChildWidgets::iterator Container::getIterator(Iterator it) const
  {
    return it.getIterator();
  }

  /**
   * @param it iterator wrapper object
   * @return STL-iterator wrapped by the given one
   */
  inline Container::ChildWidgets::iterator Container::getIterator(RIterator it) const
  {
    return it.getIterator().base();
  }

  /**
   * @param index focus index of the widget to focus
   * @param forward true to focus widgets by increasing the focus index, false for decreasing it
   * @param stop_at_end true to do not jump back to focusing the parent if none of the children
   *        could be focused, false to do so if necessary
   * @return true if a widget could be focused, false if not
   */
  bool Container::focusWidgetByIndex(int index, bool forward, bool stop_at_end)
  {
    if (!focusChildByIndex(index, forward))
    {
      if (stop_at_end)
        return false;

      Container* parent = getParent();

      // if the widget itself is focusable the focus must not "jump over" to the parent and so
      // we start over with the first/last
      // otherwise the focus might jump to the parent and we try focusing the next/previous
      // there
      if (parent == nullptr || isFocusable())
        return focusChildByIndex(getFirstIndex(forward), forward);
      else
        return parent->focusNext(forward, false);
    }
    return true;
  }

  /**
   * @param index focus index of the widget to focus
   * @param forward true to focus widgets by increasing the focus index, false for decreasing it
   * @return true if a widget could be focused, false if not
   */
  bool Container::focusChildByIndex(int index, bool forward)
  {
    Widget* widget = nullptr;

    while (widget = findWidgetByIndex(index), widget != nullptr)
    {
      if (widget->checkedFocusNext(forward))
        return true;

      index = getNextIndex(index, forward);
    }
    return false;
  }

  /**
   * @param index focus index of the widget to search for
   * @return widget with the given focus index or null if none could be found
   */
  Widget* Container::findWidgetByIndex(int index)
  {
    IndexIterator end = endFirstIndex();
    IndexIterator it  = utl::find(firstIndex(), end, index);

    ASSERT(0 <= index && index < static_cast<int>(child_widgets_.size()) || it == end);

    if (it != end)
      return it.getIterator()->first;

    return nullptr;
  }

  /**
   * @param forward true to get the index of the first widget when iterating forward, false to
   *        get the index of the first widget when iterating backwards
   * @return index of the first widget depending on iteration direction
   */
  inline int Container::getFirstIndex(bool forward)
  {
    if (!forward)
    {
      IndexIterator end = endFirstIndex();
      IndexIterator it  = std::max_element(firstIndex(), end);

      if (it != end)
        return *it;
    }
    return 0;
  }

  /**
   * @param index current index
   * @param forward true to get the following index, false to get the previous one
   * @return new index calculated from given one
   */
  inline int Container::getNextIndex(int index, bool forward)
  {
    return forward ? ++index : --index;
  }
}
