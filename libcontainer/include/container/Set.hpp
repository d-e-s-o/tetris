// Set.hpp

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

#ifndef CTRSET_HPP
#define CTRSET_HPP

#include "container/Config.hpp"
#include "container/Allocator.hpp"
#include "container/SplayTree.hpp"
#include "container/Functional.hpp"


namespace ctr
{
  /**
   * This class implements a set.
   * @note we cannot use private inheritance here, as at least the SplayTree does not provide const
   *       versions of the findXXX() methods, but we want the Set to provide these
   * @todo use a Red-Black-Tree here when available
   * @todo remove mutablility of tree_ when SplayTree has const-Find-methods (will it ever?)
   */
  template<typename T,
           typename CompareT   = Less<T>,
           typename AllocatorT = Allocator<T> >
  class Set
  {
  private:
    typedef SplayTree<T, CompareT, AllocatorT> Tree;

  public:
    typedef typename Tree::ConstIterator ConstIterator;

    explicit Set(AllocatorT const& allocator = AllocatorT());

    Set(Set&& other) = default;
    Set(Set const& other) = default;

    Set& operator =(Set&& other) = default;
    Set& operator =(Set const& other) = default;

    bool insert(T const& value);
    bool remove(T const& value);

    ConstIterator find(T const& value) const;
    ConstIterator findLowerBound(T const& value) const;
    ConstIterator findLowerEqual(T const& value) const;

    ConstIterator begin() const;
    ConstIterator end() const;

    size_t size() const;

  private:
    mutable Tree tree_;
  };
}


namespace ctr
{
  /**
   * @copydoc SplayTree::SplayTree
   */
  template<typename T, typename CompareT, typename AllocatorT>
  Set<T, CompareT, AllocatorT>::Set(AllocatorT const& allocator)
    : tree_(allocator)
  {
  }

  /**
   * @copydoc SplayTree::insert
   */
  template<typename T, typename CompareT, typename AllocatorT>
  bool Set<T, CompareT, AllocatorT>::insert(T const& value)
  {
    return tree_.insert(value);
  }

  /**
   * @copydoc SplayTree::remove
   */
  template<typename T, typename CompareT, typename AllocatorT>
  bool Set<T, CompareT, AllocatorT>::remove(T const& value)
  {
    return tree_.remove(value);
  }

  /**
   * @copydoc SplayTree::find
   */
  template<typename T, typename CompareT, typename AllocatorT>
  typename Set<T, CompareT, AllocatorT>::ConstIterator
  Set<T, CompareT, AllocatorT>::find(T const& value) const
  {
    return tree_.find(value);
  }

  /**
   * @copydoc SplayTree::findLowerBound
   */
  template<typename T, typename CompareT, typename AllocatorT>
  typename Set<T, CompareT, AllocatorT>::ConstIterator
  Set<T, CompareT, AllocatorT>::findLowerBound(T const& value) const
  {
    return tree_.findLowerBound(value);
  }

  /**
   * @copydoc SplayTree::findLowerEqual
   */
  template<typename T, typename CompareT, typename AllocatorT>
  typename Set<T, CompareT, AllocatorT>::ConstIterator
  Set<T, CompareT, AllocatorT>::findLowerEqual(T const& value) const
  {
    return tree_.findLowerEqual(value);
  }

  /**
   * @copydoc SplayTree::begin
   */
  template<typename T, typename CompareT, typename AllocatorT>
  typename Set<T, CompareT, AllocatorT>::ConstIterator
  Set<T, CompareT, AllocatorT>::begin() const
  {
    return tree_.begin();
  }

  /**
   * @copydoc SplayTree::end
   */
  template<typename T, typename CompareT, typename AllocatorT>
  typename Set<T, CompareT, AllocatorT>::ConstIterator
  Set<T, CompareT, AllocatorT>::end() const
  {
    return tree_.end();
  }

  /**
   * @copydoc SplayTree::size
   */
  template<typename T, typename CompareT, typename AllocatorT>
  size_t Set<T, CompareT, AllocatorT>::size() const
  {
    return tree_.size();
  }
}


#endif
