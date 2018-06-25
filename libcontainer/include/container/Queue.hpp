// Queue.hpp

/***************************************************************************
 *   Copyright (C) 2012,2014 Daniel Mueller (deso@posteo.net)              *
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

#ifndef CTRQUEUE_HPP
#define CTRQUEUE_HPP

#include <util/Assert.hpp>

#include "container/Config.hpp"
#include "container/Allocator.hpp"
#include "container/Array.hpp"
#include "container/QueueFunctions.hpp"


namespace ctr
{
  /**
   * @todo make the underlying container configurable
   */
  template<typename T, typename AllocatorT = Allocator<T> >
  class Queue: private Array<T, AllocatorT>
  {
  public:
    using Array<T, AllocatorT>::Iterator;
    using Array<T, AllocatorT>::ConstIterator;

    explicit Queue(AllocatorT allocator = Allocator<T>());
    Queue(Queue&&) = default;
    Queue(Queue const&) = default;

    Queue& operator =(Queue&&) = default;
    Queue& operator =(Queue const&) = default;

    T const& front() const;
    T const& back() const;

    void pushFront(T const& value);
    void pushBack(T const& value);

    T popFront();
    T popBack();

    using Array<T, AllocatorT>::begin;
    using Array<T, AllocatorT>::end;
    using Array<T, AllocatorT>::size;

  private:
    Array<T, AllocatorT>& array();
  };
}


namespace ctr
{
  /**
   * @param allocator
   */
  template<typename T, typename AllocatorT>
  Queue<T, AllocatorT>::Queue(AllocatorT allocator)
    : Array<T, AllocatorT>(allocator)
  {
  }

  /**
   * @return front element of the queue
   */
  template<typename T, typename AllocatorT>
  T const& Queue<T, AllocatorT>::front() const
  {
    ASSERTOP(size(), gt, 0);
    return (*this)[0];
  }

  /**
   * @return back element of the queue
   */
  template<typename T, typename AllocatorT>
  T const& Queue<T, AllocatorT>::back() const
  {
    ASSERTOP(size(), gt, 0);
    return (*this)[size() - 1];
  }

  /**
   * @param value value to add to the front of the queue
   */
  template<typename T, typename AllocatorT>
  void Queue<T, AllocatorT>::pushFront(T const& value)
  {
    ctr::pushFront(array(), value);
  }

  /**
   * @param value value to add to the back of the queue
   */
  template<typename T, typename AllocatorT>
  void Queue<T, AllocatorT>::pushBack(T const& value)
  {
    ctr::pushBack(array(), value);
  }

  /**
   * @return element popped from the front of the queue
   */
  template<typename T, typename AllocatorT>
  T Queue<T, AllocatorT>::popFront()
  {
    ASSERTOP(size(), gt, 0);

    return ctr::popFront(array());
  }

  /**
   * @return element popped from the back of the queue
   */
  template<typename T, typename AllocatorT>
  T Queue<T, AllocatorT>::popBack()
  {
    ASSERTOP(size(), gt, 0);

    return ctr::popBack(array());
  }

  /**
   * @return
   */
  template<typename T, typename AllocatorT>
  Array<T, AllocatorT>& Queue<T, AllocatorT>::array()
  {
    return *static_cast<Array<T, AllocatorT>*>(this);
  }
}


#endif
