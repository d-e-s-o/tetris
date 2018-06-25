// QueueFunctions.hpp

/***************************************************************************
 *   Copyright (C) 2013 Daniel Mueller (deso@posteo.net)                   *
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

#ifndef CTRQUEUEFUNCTIONS_HPP
#define CTRQUEUEFUNCTIONS_HPP

#include "container/Config.hpp"
#include "container/ArrayFunctions.hpp"


namespace ctr
{
  template<typename ArrayT, typename T>
  typename ArrayT::Iterator pushFront(ArrayT& array, T const& value);

  template<typename ArrayT, typename T>
  typename ArrayT::Iterator pushBack(ArrayT& array, T const& value);

  template<typename ArrayT>
  typename ArrayT::Element popFront(ArrayT& array);

  template<typename ArrayT>
  typename ArrayT::Element popBack(ArrayT& array);
}


namespace ctr
{
  /**
   * @param array some array
   * @param value some value to insert at the front of the given array
   * @return iterator pointing behind the newly inserted element
   */
  template<typename ArrayT, typename T>
  typename ArrayT::Iterator pushFront(ArrayT& array, T const& value)
  {
    return insert(array, 0, value);
  }

  /**
   * @param array some array
   * @param value some value to append to the given array
   * @return iterator pointing behind the appended element
   */
  template<typename ArrayT, typename T>
  typename ArrayT::Iterator pushBack(ArrayT& array, T const& value)
  {
    return append(array, value);
  }

  /**
   * @param array some array
   * @return element that was popped from the front of the array
   */
  template<typename ArrayT>
  typename ArrayT::Element popFront(ArrayT& array)
  {
    auto value = array[0];
    remove(array, 0, 1);
    return value;
  }

  /**
   * @param array some array
   * @return element that was popped from the back of the array
   */
  template<typename ArrayT>
  typename ArrayT::Element popBack(ArrayT& array)
  {
    auto value = array[array.size() - 1];
    array.shrink(array.size() - 1);
    return value;
  }
}


#endif
