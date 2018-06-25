// Stack.hpp

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

#ifndef CTRSTACK_HPP
#define CTRSTACK_HPP

#include <util/Assert.hpp>

#include "container/Config.hpp"
#include "container/Allocator.hpp"
#include "container/Array.hpp"


namespace ctr
{
  /**
   * @todo make the underlying container configurable
   */
  template<typename T, typename AllocatorT = Allocator<T> >
  class Stack: private Array<T, AllocatorT>
  {
  public:
    explicit Stack(AllocatorT allocator = Allocator<T>());

    Stack(Stack&& other) = default;
    Stack(Stack const& other) = default;

    Stack& operator =(Stack&& other) = default;
    Stack& operator =(Stack const& other) = default;

    T const& top() const;

    void push(T const& value);
    T pop();

    using Array<T, AllocatorT>::size;
  };
}


namespace ctr
{
  /**
   * @param allocator
   */
  template<typename T, typename AllocatorT>
  Stack<T, AllocatorT>::Stack(AllocatorT allocator)
    : Array<T, AllocatorT>(allocator)
  {
  }

  /**
   * @return
   */
  template<typename T, typename AllocatorT>
  T const& Stack<T, AllocatorT>::top() const
  {
    ASSERTOP(size(), gt, 0);
    return (*this)[size() - 1];
  }

  /**
   * @param value
   */
  template<typename T, typename AllocatorT>
  void Stack<T, AllocatorT>::push(T const& value)
  {
    this->replace(Array<T, AllocatorT>::end(), Array<T, AllocatorT>::end(), &value, &value + 1);
  }

  /**
   * @return
   */
  template<typename T, typename AllocatorT>
  T Stack<T, AllocatorT>::pop()
  {
    ASSERTOP(size(), gt, 0);

    T top = this->top();
    this->shrink(size() - 1);
    return top;
  }
}


#endif
