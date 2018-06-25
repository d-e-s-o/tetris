// MoveIterator.hpp

/***************************************************************************
 *   Copyright (C) 2014 Daniel Mueller (deso@posteo.net)                   *
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

#ifndef CTRMOVEITERATOR_HPP
#define CTRMOVEITERATOR_HPP

#include <type/Move.hpp>
#include <type/Traits.hpp>

#include "container/Config.hpp"


namespace ctr
{
  /**
   * This class implements can be used to wrap existing iterators to provide move instead of copy
   * semantics.
   */
  template<typename IteratorT, typename T>
  class MoveIterator
  {
  public:
    MoveIterator(IteratorT const& iterator);
    MoveIterator(MoveIterator&& other) = default;
    MoveIterator(MoveIterator const& other) = default;

    MoveIterator& operator =(MoveIterator&& other) = default;
    MoveIterator& operator =(MoveIterator const& other) = default;

    MoveIterator& operator +=(int value);
    MoveIterator& operator -=(int value);

    MoveIterator& operator ++();
    MoveIterator  operator ++(int);

    MoveIterator& operator --();
    MoveIterator  operator --(int);

    T&& operator *() const;
    T*  operator ->() const;

    IteratorT const& iterator() const;

  private:
    IteratorT iterator_;
  };


  template<typename IteratorT, typename T>
  bool operator ==(MoveIterator<IteratorT, T> const& first, MoveIterator<IteratorT, T> const& second);

  template<typename IteratorT, typename T>
  bool operator !=(MoveIterator<IteratorT, T> const& first, MoveIterator<IteratorT, T> const& second);

  template<typename IteratorT, typename T>
  bool operator <=(MoveIterator<IteratorT, T> const& first, MoveIterator<IteratorT, T> const& second);

  template<typename IteratorT, typename T>
  bool operator >=(MoveIterator<IteratorT, T> const& first, MoveIterator<IteratorT, T> const& second);

  template<typename IteratorT, typename T>
  bool operator <(MoveIterator<IteratorT, T> const& first, MoveIterator<IteratorT, T> const& second);

  template<typename IteratorT, typename T>
  bool operator >(MoveIterator<IteratorT, T> const& first, MoveIterator<IteratorT, T> const& second);

  template<typename IteratorT, typename T>
  MoveIterator<IteratorT, T> operator +(MoveIterator<IteratorT, T> const& instance, int value);

  template<typename IteratorT, typename T>
  MoveIterator<IteratorT, T> operator -(MoveIterator<IteratorT, T> const& instance, int value);

  template<typename IteratorT, typename T>
  int operator -(MoveIterator<IteratorT, T> const& first, MoveIterator<IteratorT, T> const& second);

  /**
   * @return invalid object, must not be used -- only the return type is of relevance
   */
  template<typename IteratorT>
  typename typ::RemoveReference<decltype(*(*static_cast<IteratorT*>(nullptr)))>::Type iteratorType()
  {
    return *static_cast<IteratorT*>(nullptr);
  }

  template<typename IteratorT, typename T = decltype(iteratorType<IteratorT>())>
  MoveIterator<IteratorT, T> makeMoveIterator(IteratorT const& iterator);
}


namespace ctr
{
  /**
   * @param iterator some iterator to wrap in a move iterator
   */
  template<typename IteratorT, typename T>
  inline MoveIterator<IteratorT, T>::MoveIterator(IteratorT const& iterator)
    : iterator_(iterator)
  {
  }

  /**
   * @param value value to add to the iterator
   * @return this move iterator object after addition
   */
  template<typename IteratorT, typename T>
  inline MoveIterator<IteratorT, T>& MoveIterator<IteratorT, T>::operator +=(int value)
  {
    iterator_ += value;
    return *this;
  }

  /**
   * @param value value to subtract from the iterator
   * @return this move iterator object after subtraction
   */
  template<typename IteratorT, typename T>
  inline MoveIterator<IteratorT, T>& MoveIterator<IteratorT, T>::operator -=(int value)
  {
    iterator_ -= value;
    return *this;
  }

  /**
   * @return this move iterator object after increment
   */
  template<typename IteratorT, typename T>
  inline MoveIterator<IteratorT, T>& MoveIterator<IteratorT, T>::operator ++()
  {
    ++iterator_;
    return *this;
  }

  /**
   * @param dummy dummy value to overload post increment
   * @return move iterator object before increment
   */
  template<typename IteratorT, typename T>
  inline MoveIterator<IteratorT, T> MoveIterator<IteratorT, T>::operator ++(int dummy)
  {
    return makeMoveIterator(iterator_++);
  }

  /**
   * @return this move iterator object after decrement
   */
  template<typename IteratorT, typename T>
  inline MoveIterator<IteratorT, T>& MoveIterator<IteratorT, T>::operator --()
  {
    --iterator_;
    return *this;
  }

  /**
   * @param dummy dummy value to overload post increment
   * @return move iterator object before decrement
   */
  template<typename IteratorT, typename T>
  inline MoveIterator<IteratorT, T> MoveIterator<IteratorT, T>::operator --(int dummy)
  {
    return makeMoveIterator(iterator_--);
  }

  /**
   * @return result of iterator dereference
   */
  template<typename IteratorT, typename T>
  inline T&& MoveIterator<IteratorT, T>::operator *() const
  {
    return typ::move(*iterator_);
  }

  /**
   * @return XXX
   */
  template<typename IteratorT, typename T>
  inline T* MoveIterator<IteratorT, T>::operator ->() const
  {
    return operator ->(iterator_);
  }

  /**
   * @return internally used wrapped iterator object
   */
  template<typename IteratorT, typename T>
  inline IteratorT const& MoveIterator<IteratorT, T>::iterator() const
  {
    return iterator_;
  }

  /**
   * @param first an iterator
   * @param second an iterator
   * @return true if both iterators are equal, false if they are not
   */
  template<typename IteratorT, typename T>
  inline bool operator ==(MoveIterator<IteratorT, T> const& first, MoveIterator<IteratorT, T> const& second)
  {
    return first.iterator() == second.iterator();
  }

  /**
   * @param first an iterator
   * @param second an iterator
   * @return true if both iterators are not equal, false if they are
   */
  template<typename IteratorT, typename T>
  inline bool operator !=(MoveIterator<IteratorT, T> const& first, MoveIterator<IteratorT, T> const& second)
  {
    return first.iterator() != second.iterator();
  }

  /**
   * @param first an iterator
   * @param second an iterator
   * @return true if the first iterator is less or equal than the second, false if not
   */
  template<typename IteratorT, typename T>
  inline bool operator <=(MoveIterator<IteratorT, T> const& first, MoveIterator<IteratorT, T> const& second)
  {
    return first.iterator() <= second.iterator();
  }

  /**
   * @param first an iterator
   * @param second an iterator
   * @return true if the first iterator is greater or equal than the second, false if not
   */
  template<typename IteratorT, typename T>
  inline bool operator >=(MoveIterator<IteratorT, T> const& first, MoveIterator<IteratorT, T> const& second)
  {
    return first.iterator() >= second.iterator();
  }

  /**
   * @param first an iterator
   * @param second an iterator
   * @return true if the first iterator is less than the second, false if not
   */
  template<typename IteratorT, typename T>
  inline bool operator <(MoveIterator<IteratorT, T> const& first, MoveIterator<IteratorT, T> const& second)
  {
    return first.iterator() < second.iterator();
  }

  /**
   * @param first an iterator
   * @param second an iterator
   * @return true if the first iterator is greater than the second, false if not
   */
  template<typename IteratorT, typename T>
  inline bool operator >(MoveIterator<IteratorT, T> const& first, MoveIterator<IteratorT, T> const& second)
  {
    return first.iterator() > second.iterator();
  }

  /**
   * @param instance an iterator
   * @param value a value by which to increment the iterator
   * @return move iterator object after increment
   */
  template<typename IteratorT, typename T>
  inline MoveIterator<IteratorT, T> operator +(MoveIterator<IteratorT, T> const& instance, int value)
  {
    auto other = instance;
    other += value;
    return other;
  }

  /**
   * @param instance an iterator
   * @param value a value by which to decrement the iterator
   * @return move iterator object after decrement
   */
  template<typename IteratorT, typename T>
  inline MoveIterator<IteratorT, T> operator -(MoveIterator<IteratorT, T> const& instance, int value)
  {
    auto other = instance;
    other -= value;
    return other;
  }

  /**
   * @param first an iterator
   * @param second an iterator
   * @return difference between the two iterators
   */
  template<typename IteratorT, typename T>
  inline int operator -(MoveIterator<IteratorT, T> const& first, MoveIterator<IteratorT, T> const& second)
  {
    return first.iterator() - second.iterator();
  }

  /**
   * @param iterator some iterator from which to create a move iterator
   * @return newly created move iterator based on the given iterator
   */
  template<typename IteratorT, typename T>
  inline MoveIterator<IteratorT, T> makeMoveIterator(IteratorT const& iterator)
  {
    return MoveIterator<IteratorT, T>(iterator);
  }
}


#endif
