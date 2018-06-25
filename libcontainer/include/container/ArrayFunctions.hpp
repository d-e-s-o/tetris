// ArrayFunctions.hpp

/***************************************************************************
 *   Copyright (C) 2012-2014 Daniel Mueller (deso@posteo.net)              *
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

#ifndef CTRARRAYFUNCTIONS_HPP
#define CTRARRAYFUNCTIONS_HPP

#include "container/Config.hpp"
#include "container/MoveIterator.hpp"


namespace ctr
{
  template<typename ArrayT, typename T>
  typename ArrayT::Iterator append(ArrayT& array, T const& value);

  template<typename ArrayT, typename InputIteratorT>
  typename ArrayT::Iterator append(ArrayT& array, InputIteratorT in_begin, InputIteratorT in_end);

  template<typename ArrayT, typename T>
  typename ArrayT::Iterator insert(ArrayT& array, size_t index, T const& value);

  template<typename ArrayT, typename InputIteratorT>
  typename ArrayT::Iterator insert(ArrayT& array, size_t index, InputIteratorT in_begin, InputIteratorT in_end);

  template<typename ArrayT>
  typename ArrayT::Iterator remove(ArrayT& array, size_t index, size_t count);

  template<typename ArrayT, typename IteratorT>
  typename ArrayT::Iterator remove(ArrayT& array, IteratorT iterator);

  template<typename ArrayT, typename T>
  void resize(ArrayT& array, size_t size, T const& value);
}


namespace ctr
{
  /**
   * @param array some array
   * @param value value to append to the given array
   * @return iterator pointing behind the newly appended element
   */
  template<typename ArrayT, typename T>
  typename ArrayT::Iterator append(ArrayT& array, T&& value)
  {
    auto begin = makeMoveIterator(&value);
    auto end   = makeMoveIterator(&value + 1);
    return array.replace(array.end(), array.end(), begin, end);
  }

  /**
   * @param array some array
   * @param value value to append to the given array
   * @return iterator pointing behind the newly appended element
   */
  template<typename ArrayT, typename T>
  typename ArrayT::Iterator append(ArrayT& array, T const& value)
  {
    return array.replace(array.end(), array.end(), &value, &value + 1);
  }

  /**
   * @param array some array
   * @param begin iterator pointing to first element of a range to append
   * @param end iterator pointing after last element of a range to append
   * @return iterator pointing behind the last appended element
   */
  template<typename ArrayT, typename InputIteratorT>
  typename ArrayT::Iterator append(ArrayT& array, InputIteratorT begin, InputIteratorT end)
  {
    return array.replace(array.end(), array.end(), begin, end);
  }

  /**
   * @param array some array
   * @param index index where to insert the new element
   * @param value some value to insert into the given array at the given index
   * @return iterator pointing behind the newly inserted element
   */
  template<typename ArrayT, typename T>
  typename ArrayT::Iterator insert(ArrayT& array, size_t index, T&& value)
  {
    auto begin = makeMoveIterator(&value);
    auto end   = makeMoveIterator(&value + 1);
    return array.replace(array.begin() + index, array.begin() + index, begin, end);
  }

  /**
   * @param array some array
   * @param index index where to insert the new element
   * @param value some value to insert into the given array at the given index
   * @return iterator pointing behind the newly inserted element
   */
  template<typename ArrayT, typename T>
  typename ArrayT::Iterator insert(ArrayT& array, size_t index, T const& value)
  {
    return array.replace(array.begin() + index, array.begin() + index, &value, &value + 1);
  }

  /**
   * @param array some array
   * @param index index at which to insert the given range
   * @param begin iterator pointing to first element of a range to insert
   * @param end iterator pointing after last element of a range to insert
   * @return iterator pointing behind the last inserted element
   */
  template<typename ArrayT, typename InputIteratorT>
  typename ArrayT::Iterator insert(ArrayT& array, size_t index, InputIteratorT begin, InputIteratorT end)
  {
    return array.replace(array.begin() + index, array.begin() + index, begin, end);
  }

  /**
   * @param array some array
   * @param index starting index from where to remove
   * @param count number of elements to remove
   * @return iterator pointing behind the last removed element
   */
  template<typename ArrayT>
  typename ArrayT::Iterator remove(ArrayT& array, size_t index, size_t count)
  {
    auto begin = array.begin() + index;
    auto end   = array.begin() + index + count;
    return array.replace(begin, end, array.end(), array.end());
  }

  /**
   * @param array some array
   * @param iterator iterator pointing to the element to remove
   * @return iterator pointing behind the removed element
   */
  template<typename ArrayT, typename IteratorT>
  typename ArrayT::Iterator remove(ArrayT& array, IteratorT iterator)
  {
    auto end = iterator != array.end() ? iterator + 1 : iterator;
    return array.replace(iterator, end, array.end(), array.end());
  }

  /**
   * @param array some array
   * @param size new size of the array
   * @param value value with which to initialize newly allocated elements
   */
  template<typename ArrayT, typename T>
  void resize(ArrayT& array, size_t size, T const& value)
  {
    if (size > array.size())
      array.grow(size, value);
    else
      array.shrink(size);
  }
}


#endif
