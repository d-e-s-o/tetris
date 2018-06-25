// Array.hpp

/***************************************************************************
 *   Copyright (C) 2009,2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#ifndef CTRARRAY_HPP
#define CTRARRAY_HPP

#include <util/Assert.hpp>
#include <util/Algorithm.hpp>

#include "container/Config.hpp"
#include "container/Allocator.hpp"
#include "container/MoveIterator.hpp"


namespace ctr
{
  /**
   * This class represents a resizable array.
   * @todo we need exception support for cases where the allocator fails to allocate data
   * @todo add constructor accepting fixed size array
   */
  template<typename T, typename AllocatorT = Allocator<T> >
  class Array
  {
  public:
    typedef T        Element;
    typedef T*       Iterator;
    typedef T const* ConstIterator;

    explicit Array(AllocatorT allocator = Allocator<T>());
    explicit Array(size_t capacity, AllocatorT allocator = Allocator<T>());

    template<typename InputIteratorT>
    explicit Array(InputIteratorT begin, InputIteratorT end, AllocatorT allocator = Allocator<T>());

    Array(Array&& other);
    Array(Array const& other);

    ~Array();

    Array const& operator =(Array&& other);
    Array const& operator =(Array const& other);

    T&       operator [](size_t index);
    T const& operator [](size_t index) const;

    template<typename OutputIteratorT, typename InputIteratorT>
    OutputIteratorT replace(OutputIteratorT out_begin, OutputIteratorT out_end,
                            InputIteratorT  in_begin,  InputIteratorT  in_end);

    Iterator begin();
    Iterator end();

    ConstIterator begin() const;
    ConstIterator end() const;

    size_t size() const;

    void grow(size_t size, T const& value);
    void shrink(size_t size);

    size_t capacity() const;
    void reserve(size_t capacity);

  private:
    T*     data_;
    size_t size_;
    size_t capacity_;

    AllocatorT allocator_;

    template<typename InputIteratorT, typename OutputIteratorT>
    void move(InputIteratorT begin, InputIteratorT end, OutputIteratorT destination);

    template<typename InputIteratorT, typename OutputIteratorT>
    void moveChecked(InputIteratorT begin, InputIteratorT end, OutputIteratorT destination);

    void construct(Iterator begin, Iterator end, T const& value);
    void destruct(Iterator begin, Iterator end);

    void free();

    void autoReserve(size_t capacity);
  };


  template<typename T, typename AllocatorT>
  typename Array<T, AllocatorT>::Iterator begin(Array<T, AllocatorT>& array);

  template<typename T, typename AllocatorT>
  typename Array<T, AllocatorT>::Iterator end(Array<T, AllocatorT>& array);

  template<typename T, typename AllocatorT>
  typename Array<T, AllocatorT>::ConstIterator begin(Array<T, AllocatorT> const& array);

  template<typename T, typename AllocatorT>
  typename Array<T, AllocatorT>::ConstIterator end(Array<T, AllocatorT> const& array);
}


namespace ctr
{
  /**
   * The constructor creates an empty array.
   * @param allocator allocator to use
   */
  template<typename T, typename AllocatorT>
  Array<T, AllocatorT>::Array(AllocatorT allocator)
    : data_(nullptr),
      size_(0),
      capacity_(0),
      allocator_(allocator)
  {
  }

  /**
   * @param capacity capacity to reserve initially
   * @param allocator allocator to use
   */
  template<typename T, typename AllocatorT>
  Array<T, AllocatorT>::Array(size_t capacity, AllocatorT allocator)
    : data_(nullptr),
      size_(0),
      capacity_(0),
      allocator_(allocator)
  {
    reserve(capacity);
  }

  /**
   * @param begin
   * @param end
   * @param allocator allocator to use
   */
  template<typename T, typename AllocatorT>
  template<typename InputIteratorT>
  Array<T, AllocatorT>::Array(InputIteratorT begin, InputIteratorT end, AllocatorT allocator)
    : data_(nullptr),
      size_(0),
      capacity_(0),
      allocator_(allocator)
  {
    replace(this->begin(), this->end(), begin, end);
  }

  /**
   * The move constructor creates a new array based on a given one.
   * @param other array to move
   */
  template<typename T, typename AllocatorT>
  Array<T, AllocatorT>::Array(Array&& other)
    : data_(other.data_),
      size_(other.size_),
      capacity_(other.capacity_),
      allocator_(other.allocator_)
  {
    other.data_     = nullptr;
    other.size_     = 0;
    other.capacity_ = 0;
  }

  /**
   * The copy constructor creates a new array as copy from a given one.
   * @param other array to copy
   */
  template<typename T, typename AllocatorT>
  Array<T, AllocatorT>::Array(Array const& other)
    : data_(nullptr),
      size_(0),
      capacity_(0),
      allocator_(other.allocator_)
  {
    replace(begin(), end(), other.begin(), other.end());
  }

  /**
   * The destructor free's all allocated data.
   */
  template<typename T, typename AllocatorT>
  Array<T, AllocatorT>::~Array()
  {
    free();
  }

  /**
   * @param other array to move to the current one
   * @return modified version of the array after assignment
   */
  template<typename T, typename AllocatorT>
  Array<T, AllocatorT> const& Array<T, AllocatorT>::operator =(Array&& other)
  {
    ASSERTOP(this, ne, &other);

    free();

    data_      = other.data_;
    size_      = other.size_;
    capacity_  = other.capacity_;
    allocator_ = other.allocator_;

    other.data_     = nullptr;
    other.size_     = 0;
    other.capacity_ = 0;
    return *this;
  }

  /**
   * @param other array to assign to the current one
   * @return modified version of the array after assignment
   */
  template<typename T, typename AllocatorT>
  Array<T, AllocatorT> const& Array<T, AllocatorT>::operator =(Array const& other)
  {
    if (this != &other)
      replace(begin(), end(), other.begin(), other.end());

    return *this;
  }

  /**
   * @param index index of the element to retrieve
   * @return element at the given index
   * @note no boundary checking is performed here
   */
  template<typename T, typename AllocatorT>
  T& Array<T, AllocatorT>::operator [](size_t index)
  {
    ASSERTOP(index, ge, 0);
    ASSERTOP(index, lt, size_);
    return data_[index];
  }

  /**
   * @param index index of the element to retrieve
   * @return element at the given index
   * @note no boundary checking is performed here
   */
  template<typename T, typename AllocatorT>
  T const& Array<T, AllocatorT>::operator [](size_t index) const
  {
    ASSERTOP(index, ge, 0);
    ASSERTOP(index, lt, size_);
    return data_[index];
  }

  /**
   * @param out_begin iterator pointing to begin of region to overwrite within the array
   * @param out_end iterator pointing to end of region to overwrite within the array
   * @param in_begin iterator pointing to begin of region to copy in
   * @param in_end iterator pointing to end of region to copy in
   * @return iterator pointing behind last element that was copied in into the array
   * @note a replace() method in this style is pretty much _the_ method that insertions, removals,
   *       and much more into an array can be implemented with
   * @todo use distance() or difference() function for calculating distance between iterators
   */
  template<typename T, typename AllocatorT>
  template<typename OutputIteratorT, typename InputIteratorT>
  OutputIteratorT Array<T, AllocatorT>::replace(OutputIteratorT out_begin, OutputIteratorT out_end,
                                                InputIteratorT  in_begin,  InputIteratorT  in_end)
  {
    /**
     * There are three cases to consider here:
     * 1) if the in and out range are equal in size
     *    then
     *      simply copy the in range over the out range
     * 2) if the in range is smaller than the out range
     *    then
     *      copy the in range to the begin of the out range and
     *      copy the remaining part of the out range right behind the newly copied part
     * 3) if the in range is larger than the out range
     *    then
     *      ensure that our array is large enough to hold all values of the replace operation
     *      copy the left over part of the out range to the end of the array
     *      copy the in range at the begin of the out range
     */
    ASSERT(begin() <= out_begin && out_begin <= end());
    ASSERT(begin() <= out_end   && out_end   <= end());
    ASSERT(out_begin <= out_end);
    ASSERT(in_begin  <= in_end);

    size_t out_size = out_end - out_begin;
    size_t in_size  = in_end  - in_begin;

    // case 1)
    if (out_size == in_size)
    {
      utl::copy(in_begin, in_end, out_begin);
      return out_end;
    }

    size_t new_size = size_ - out_size + in_size;

    // case 2)
    if (out_size > in_size)
    {
      // the last step in this case is concerned strictly only with moving internal data (no user
      // input), so it is safe to move
      auto move_out_begin = makeMoveIterator(out_end);
      auto move_out_end   = makeMoveIterator(end());

      utl::copy(in_begin, in_end, out_begin);
      utl::copy(move_out_begin, move_out_end, out_begin + in_size);

      shrink(new_size);
      return out_end;
    }
    // case 3)
    else // if (out_size < in_size)
    {
      size_t old_size = size_;

      // in case the capacity is not enough we need to reallocate the array, which invalidates all
      // the iterators; thus we need to store their offsets (with regard to the 'old' array first)
      // in order to make them point to the same relative position in the new array
      // @todo strictly speaking this case could be optimized by simply creating a new array of the
      //       desired size and then copying the ranges as desired
      if (capacity_ < new_size)
      {
        size_t out_begin_offset = out_begin - begin();
        size_t out_end_offset   = out_end   - begin();

        // we need to check if the input range also lies within 'this' array, if so, these iterators
        // will also be invalidated (and thus require the same treatment)
        if (utl::includes(begin(), end(), in_begin) || utl::includes(begin(), end(), in_end))
        {
          // the input and output iterators might have different types at compile time which might
          // lead to errors when we just subtract one from the other (although in that case we never
          // hit that path due to the check above); but if we actually go into this path we are sure
          // they are of same type; we use this nifty subtraction stuff to avoid weird casting
          // @todo this path is effectively untested -- no unit test exercises it!
          OutputIteratorT const OutNull = 0;
          InputIteratorT  const InNull  = 0;
          ASSERTOP(sizeof(*OutNull), eq, sizeof(*InNull));

          size_t in_begin_offset = (in_begin - InNull) - (begin() - OutNull);
          size_t in_end_offset   = (in_end   - InNull) - (begin() - OutNull);

          autoReserve(new_size);

          in_begin = InNull + (begin() - OutNull) + in_begin_offset;
          in_end   = InNull + (begin() - OutNull) + in_end_offset;
        }
        else
          autoReserve(new_size);

        out_begin = begin() + out_begin_offset;
        out_end   = begin() + out_end_offset;
      }

      auto move_out_begin = makeMoveIterator(out_end);
      auto move_out_end   = makeMoveIterator(begin() + old_size);

      moveChecked(move_out_begin, move_out_end, out_begin + in_size);
      moveChecked(in_begin, in_end, out_begin);

      size_ = new_size;
      return out_end;
    }
  }

  /**
   * @return iterator pointing to the first element of the array
   */
  template<typename T, typename AllocatorT>
  typename Array<T, AllocatorT>::Iterator Array<T, AllocatorT>::begin()
  {
    return data_;
  }

  /**
   * @return iterator pointing right behind the last element of the array
   */
  template<typename T, typename AllocatorT>
  typename Array<T, AllocatorT>::Iterator Array<T, AllocatorT>::end()
  {
    return data_ + size_;
  }

  /**
   * @return iterator pointing to the first element of the array
   */
  template<typename T, typename AllocatorT>
  typename Array<T, AllocatorT>::ConstIterator Array<T, AllocatorT>::begin() const
  {
    return data_;
  }

  /**
   * @return iterator pointing right behind the last element of the array
   */
  template<typename T, typename AllocatorT>
  typename Array<T, AllocatorT>::ConstIterator Array<T, AllocatorT>::end() const
  {
    return data_ + size_;
  }

  /**
   * @return size of the array
   */
  template<typename T, typename AllocatorT>
  size_t Array<T, AllocatorT>::size() const
  {
    return size_;
  }

  /**
   * @param size new size the array should have
   * @param value value used for initialization of the new elements
   */
  template<typename T, typename AllocatorT>
  void Array<T, AllocatorT>::grow(size_t size, T const& value)
  {
    if (size <= size_)
      return;

    if (size > capacity_)
      autoReserve(size);

    // some new objects appeared that have to be constructed first
    construct(data_ + size_, data_ + size, value);

    size_ = size;
  }

  /**
   * @param size new size the array should have
   */
  template<typename T, typename AllocatorT>
  void Array<T, AllocatorT>::shrink(size_t size)
  {
    if (size >= size_)
      return;

    // some objects are no longer inside the array and have to be destroyed correctly
    destruct(data_ + size, data_ + size_);

    size_ = size;
  }

  /**
   * @return capacity (maximal size) of the array
   */
  template<typename T, typename AllocatorT>
  size_t Array<T, AllocatorT>::capacity() const
  {
    return capacity_;
  }

  /**
   * This method can be used to reserve space for increasing the size of the array without the
   * need to actually allocate and copy something.
   * @param capacity final capacity to reserve
   * @return true if reserving the given capacity was successful, false if not
   * @note the capacity may only increase; passing a value that is less than the current capacity
   *       will result in nothing being done
   */
  template<typename T, typename AllocatorT>
  void Array<T, AllocatorT>::reserve(size_t capacity)
  {
    if (capacity <= capacity_)
      return;

    T* data = allocator_.allocate(capacity);
    ASSERTOP(data, ne, nullptr);

    // we only copy internal data, so moving is safe and more efficient
    move(makeMoveIterator(begin()), makeMoveIterator(end()), data);
    free();

    data_     = data;
    capacity_ = capacity;
  }

  /**
   *
   */
  template<typename T, typename AllocatorT>
  void Array<T, AllocatorT>::construct(Iterator begin, Iterator end, T const& value)
  {
    ASSERTOP(begin, le, end);

    for (Iterator it = begin; it != end; it++)
      allocator_.construct(it, value);
  }

  /**
   *
   */
  template<typename T, typename AllocatorT>
  void Array<T, AllocatorT>::destruct(Iterator begin, Iterator end)
  {
    ASSERTOP(begin, le, end);

    // @todo strictly speaking the order of destruction should be reversed -- does this matter? is
    //       this specified somewhere?
    for (Iterator it = begin; it != end; it++)
      allocator_.destruct(it);
  }

  /**
   * This helper method destroys and frees any allocated data.
   */
  template<typename T, typename AllocatorT>
  void Array<T, AllocatorT>::free()
  {
    ASSERT(data_ != nullptr && size_ >= 0 && capacity_ >  0 && capacity_ >= size_ ||
           data_ == nullptr && size_ == 0 && capacity_ == 0);

    destruct(begin(), end());
    allocator_.deallocate(data_);
  }

  /**
   * This method is the one used internally whenever one of the Array's operations requests new
   * memory allocated. It will take care to allocate some additional memory in the hope to reduce
   * futher allocations in the near future.
   * @param capacity
   * @todo to make things more predictable we should make the algorithm used for calculating the
   *       actualy amount to reserve somehow configurable/overwritable by the user
   */
  template<typename T, typename AllocatorT>
  void Array<T, AllocatorT>::autoReserve(size_t capacity)
  {
    // allocate twice the requested amount
    reserve(2 * capacity);
  }

  /**
   * This method can be used to copy data to an uninitialized area within the array, i.e., a place
   * that has been allocated using the allocator but no object has been created there yet.
   * @param begin begin of range to copy to 'destination'
   * @param end end of range to copy to 'destination'
   * @param destination iterator to begin of destination range
   * @note the name is a bit misleading as there is no actual move performed but an inplace
   *       construction from a copy instead of an assignment as would be the case by ordinary copy
   */
  template<typename T, typename AllocatorT>
  template<typename InputIteratorT, typename OutputIteratorT>
  void Array<T, AllocatorT>::move(InputIteratorT  begin,
                                  InputIteratorT  end,
                                  OutputIteratorT destination)
  {
    auto functor = [this](InputIteratorT in, OutputIteratorT out) {
      allocator_.construct(out, *in);
    };
    utl::copy(begin, end, destination, functor);
  }

  /**
   * @param begin
   * @param end
   * @param destination
   */
  template<typename T, typename AllocatorT>
  template<typename InputIteratorT, typename OutputIteratorT>
  void Array<T, AllocatorT>::moveChecked(InputIteratorT  begin,
                                         InputIteratorT  end,
                                         OutputIteratorT destination)
  {
    using utl::copy;

    ASSERTOP(destination, ge, data_);
    ASSERTOP(destination, le, data_ + capacity_);

    size_t offset = destination - this->begin();
    size_t size   = end - begin;

    ASSERTOP(offset + (end - begin), le, capacity_);

    if (offset >= size_)
    {
      // if the destination range is entirely in uninitialized area simply perform the move
      move(begin, end, destination);
    }
    else if (offset + size <= size_)
    {
      // if we do not even touch an uninitialized area one copy is sufficient
      copy(begin, end, destination);
    }
    else
    {
      // if part of the destination range is already initialized we have to do a copy to that range,
      // the remaining part can be moved
      size_t split = (size_ - 1) - offset;

      // first move the part at the end then copy the part at the front, the order is important in
      // case we have overlappings
      move(begin + split, end, destination + split);
      copy(begin, begin + split, destination);
    }
  }

  /**
   * @param array
   * @return
   */
  template<typename T, typename AllocatorT>
  typename Array<T, AllocatorT>::Iterator begin(Array<T, AllocatorT>& array)
  {
    return array.begin();
  }

  /**
   * @param array
   * @return
   */
  template<typename T, typename AllocatorT>
  typename Array<T, AllocatorT>::Iterator end(Array<T, AllocatorT>& array)
  {
    return array.end();
  }

  /**
   * @param array
   * @return
   */
  template<typename T, typename AllocatorT>
  typename Array<T, AllocatorT>::ConstIterator begin(Array<T, AllocatorT> const& array)
  {
    return array.begin();
  }

  /**
   * @param array
   * @return
   */
  template<typename T, typename AllocatorT>
  typename Array<T, AllocatorT>::ConstIterator end(Array<T, AllocatorT> const& array)
  {
    return array.end();
  }
}


#endif
