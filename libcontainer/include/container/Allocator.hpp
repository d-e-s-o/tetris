// Allocator.hpp

/***************************************************************************
 *   Copyright (C) 2010-2012 Daniel Mueller (deso@posteo.net)              *
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

#ifndef CTRALLOCATOR_HPP
#define CTRALLOCATOR_HPP

#include <new>
#include <type/Move.hpp>


namespace ctr
{
  /**
   * @todo this should go into a separate header
   */
  template<template<class> class ToBindT>
  struct Rebindable
  {
    template<typename U>
    struct Rebind
    {
      typedef ToBindT<U> Other;
    };
  };


  /**
   * @todo strictly speaking we also need to implement templated assignment operator (as we have
   *       such a copy constructor) - think about that
   * @todo however I would prefer an approach without this template copy constructor thing - try
   *       finding one
   */
  template<typename T>
  class Allocator: public Rebindable<Allocator>
  {
  public:
    explicit Allocator();
    Allocator(Allocator&&) = default;
    Allocator(Allocator const&) = default;

    template<typename U>
    explicit Allocator(Allocator<U>&& other);

    template<typename U>
    explicit Allocator(Allocator<U> const& other);

    Allocator& operator =(Allocator&&) = default;
    Allocator& operator =(Allocator const&) = default;

    T* allocate(size_t n, T const* hint = 0, T const* data = 0);
    void deallocate(T const* p);

    void construct(T* p, T&& copy);
    void construct(T* p, T const& copy);
    void destruct(T* p);
  };
}

namespace ctr
{
  /**
   * The default constructor creates a new allocator.
   */
  template<typename T>
  Allocator<T>::Allocator()
  {
  }

  /**
   *
   */
  template<typename T>
  template<typename U>
  Allocator<T>::Allocator(Allocator<U>&& other)
  {
  }

  /**
   * This constructor can be used to create a new allocator from another one bound to other type.
   */
  template<typename T>
  template<typename U>
  Allocator<T>::Allocator(Allocator<U> const& other)
  {
  }

  /**
   * @param n number of elements for which space is to be allocated
   * @param hint pointer to some data previously allocated by that allocator that can be seen as a
   *        hint for locality, or 0 if no hint is given
   * @param data pointer to some node that can be used by the allocator (typically to allocate
   *        memory "in-place", or 0 if no such data is to be given
   * @return pointer to memory allocated to store n objects of type T
   */
  template<typename T>
  T* Allocator<T>::allocate(size_t n, T const* hint, T const* data)
  {
    return static_cast<T*>(::operator new(n * sizeof(T)));
  }

  /**
   * @param p pointer whose memory referenced by to deallocate
   */
  template<typename T>
  void Allocator<T>::deallocate(T const* p)
  {
    ::operator delete(const_cast<void*>(reinterpret_cast<void const*>(p)));
  }

  /**
   * This method can be used to constructor a new object at the given place as copy of the other
   * given object.
   * @param p pointer pointing to memory where to construct object at
   * @param copy object to create copy of
   */
  template<typename T>
  void Allocator<T>::construct(T* p, T const& copy)
  {
    new (p) T(copy);
  }

  /**
   * @param p pointer pointing to memory where to construct object at
   * @param copy object to move from
   */
  template<typename T>
  void Allocator<T>::construct(T* p, T&& copy)
  {
    new (p) T(typ::forward<T>(copy));
  }

  /**
   * This method can be used to deconstruct the given object.
   * @param p pointer pointing to object to deconstruct
   */
  template<typename T>
  void Allocator<T>::destruct(T* p)
  {
    p->~T();
  }
}


#endif
