// BinaryHeap.hpp

/***************************************************************************
 *   Copyright (C) 2013-2014 Daniel Mueller (deso@posteo.net)              *
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

#ifndef CTRBINARYHEAP_HPP
#define CTRBINARYHEAP_HPP

#include <util/Util.hpp>
#include <util/Assert.hpp>

#include "container/Config.hpp"
#include "container/Allocator.hpp"
#include "container/Functional.hpp"
#include "container/Array.hpp"


namespace ctr
{
  /**
   * @todo make the underlying container configurable
   * @note for the ease of index computation this this binary heap implementation relies on the
   *       first element of the heap being the second (i.e., the one with index 1) in the
   *       underlying array
   * @param T
   * @param CompareT
   * @param AllocatorT
   */
  template<typename T,
           typename CompareT = Less<T>,
           typename AllocatorT = Allocator<T> >
  class BinaryHeap: private Array<T, AllocatorT>
  {
  public:
    explicit BinaryHeap(AllocatorT allocator = Allocator<T>());

    BinaryHeap(BinaryHeap&& other) = default;
    BinaryHeap(BinaryHeap const& other) = default;

    BinaryHeap& operator =(BinaryHeap&& other) = default;
    BinaryHeap& operator =(BinaryHeap const& other) = default;

    T const& top() const;

    void insert(T const& value);
    T remove();

    size_t size() const;

  private:
    CompareT compare_;

    void cascadeUp(size_t index);
    void cascadeDown(size_t index);

    size_t parentIndex(size_t index) const;
    size_t leftChildIndex(size_t index) const;
    size_t rightChildIndex(size_t index) const;

    bool less(size_t lhs, size_t rhs) const;
    void swap(size_t lhs, size_t rhs);
  };
}


namespace ctr
{
  /**
   * @param allocator
   */
  template<typename T, typename CompareT, typename AllocatorT>
  BinaryHeap<T, CompareT, AllocatorT>::BinaryHeap(AllocatorT allocator)
    : Array<T, AllocatorT>(1, allocator),
      compare_()
  {
    // @todo this can cause problems with not default constructible items
    this->grow(1, T());
  }

  /**
   * @return front element of the queue
   */
  template<typename T, typename CompareT, typename AllocatorT>
  T const& BinaryHeap<T, CompareT, AllocatorT>::top() const
  {
    ASSERTOP(size(), gt, 0);
    return (*this)[1];
  }

  /**
   *
   */
  template<typename T, typename CompareT, typename AllocatorT>
  void BinaryHeap<T, CompareT, AllocatorT>::insert(T const& value)
  {
    size_t size = Array<T, AllocatorT>::size();
    this->grow(size + 1, value);
    cascadeUp(size);
  }

  /**
   * @return
   */
  template<typename T, typename CompareT, typename AllocatorT>
  T BinaryHeap<T, CompareT, AllocatorT>::remove()
  {
    T value  = top();
    (*this)[1] = (*this)[size()];
    this->shrink(size());

    cascadeDown(1);
    return value;
  }

  /**
   * @return
   */
  template<typename T, typename CompareT, typename AllocatorT>
  size_t BinaryHeap<T, CompareT, AllocatorT>::size() const
  {
    ASSERTOP((Array<T, AllocatorT>::size()), gt, 0);
    return Array<T, AllocatorT>::size() - 1;
  }

  /**
   * @param index
   */
  template<typename T, typename CompareT, typename AllocatorT>
  void BinaryHeap<T, CompareT, AllocatorT>::cascadeUp(size_t index)
  {
    while (index > 1)
    {
      size_t parent = parentIndex(index);

      if (less(index, parent))
      {
        swap(index, parent);
        index = parent;
      }
      else
        break;
    }
  }

  /**
   * @param index
   */
  template<typename T, typename CompareT, typename AllocatorT>
  void BinaryHeap<T, CompareT, AllocatorT>::cascadeDown(size_t index)
  {
    size_t size = this->size();

    while (true)
    {
      size_t left_child  = leftChildIndex(index);
      size_t right_child = rightChildIndex(index);
      size_t min_child;

      if (right_child <= size)
      {
        // if the right child index is valid then the left child index is valid as well
        min_child = less(left_child, right_child)
                  ? left_child : right_child;
      }
      else if (left_child <= size)
        min_child = left_child;
      else
        break;

      if (!less(index, min_child))
      {
        swap(min_child, index);
        index = min_child;
      }
      else
        break;
    }
  }

  /**
   * @param index
   * @return
   */
  template<typename T, typename CompareT, typename AllocatorT>
  size_t BinaryHeap<T, CompareT, AllocatorT>::parentIndex(size_t index) const
  {
    return index / 2;
  }

  /**
   * @param index
   * @return
   */
  template<typename T, typename CompareT, typename AllocatorT>
  size_t BinaryHeap<T, CompareT, AllocatorT>::leftChildIndex(size_t index) const
  {
    return index * 2;
  }

  /**
   * @param index
   * @return
   */
  template<typename T, typename CompareT, typename AllocatorT>
  size_t BinaryHeap<T, CompareT, AllocatorT>::rightChildIndex(size_t index) const
  {
    return index * 2 + 1;
  }

  /**
   * @param lhs index of first object
   * @param rhs index of second object
   * @return true if the object at index 'lhs' is less than the one at 'rhs', false otherwise
   */
  template<typename T, typename CompareT, typename AllocatorT>
  bool BinaryHeap<T, CompareT, AllocatorT>::less(size_t lhs, size_t rhs) const
  {
    ASSERTOP(lhs, ge, 0);
    ASSERTOP(lhs, le, size());
    ASSERTOP(rhs, ge, 0);
    ASSERTOP(rhs, le, size());

    return compare_((*this)[lhs], (*this)[rhs]);
  }

  /**
   * @param lhs index of first object to swap with second
   * @param rhs index of second object to swap with first
   */
  template<typename T, typename CompareT, typename AllocatorT>
  void BinaryHeap<T, CompareT, AllocatorT>::swap(size_t lhs, size_t rhs)
  {
    ASSERTOP(lhs, ge, 0);
    ASSERTOP(lhs, le, size());
    ASSERTOP(rhs, ge, 0);
    ASSERTOP(rhs, le, size());

    utl::swap((*this)[lhs], (*this)[rhs]);
  }
}


#endif
