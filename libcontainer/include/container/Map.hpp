// Map.hpp

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

#ifndef CTRMAP_HPP
#define CTRMAP_HPP

#include "container/Config.hpp"
#include "container/Pair.hpp"
#include "container/SplayTree.hpp"
#include "container/Allocator.hpp"
#include "container/Functional.hpp"


namespace ctr
{
  /**
   * This class implements a map, granting access to values by supplying a key.
   * @note we cannot use private inheritance here, as at least the SplayTree does not provide const
   *       versions of the findXXX() methods, but we want the Map to provide these
   * @todo use a Red-Black-Tree here when available
   * @todo remove mutablility of tree_ when SplayTree has const-Find-methods (will it ever?)
   * @todo we really need to find a way to workaround the must for default constructability of
   *       ValueT objects -- this is an unbearable requirement!
   * @todo use typ::Tuple here!
   */
  template<typename KeyT,
           typename ValueT,
           typename CompareT   = Less<KeyT>,
           typename AllocatorT = Allocator<KeyT> >
  class Map
  {
  public:
    typedef Pair<KeyT, ValueT> Entry;

  private:
    class EntryCompare
    {
    public:
      EntryCompare() = default;
      EntryCompare(EntryCompare&&) = default;
      EntryCompare(EntryCompare const&) = default;

      EntryCompare& operator =(EntryCompare&&) = default;
      EntryCompare& operator =(EntryCompare const&) = default;

      bool operator ()(Entry const& lhs, Entry const& rhs) const;

    private:
      CompareT compare_;
    };

    typedef SplayTree<Entry, EntryCompare, AllocatorT> Tree;

  public:
    typedef typename Tree::ConstIterator ConstIterator;

    explicit Map(AllocatorT const& allocator = AllocatorT());

    Map(Map&&) = default;
    Map(Map const&) = default;

    Map& operator =(Map&&) = default;
    Map& operator =(Map const&) = default;

    bool insert(Entry const& entry);
    bool remove(KeyT const& key);

    ConstIterator find(KeyT const& key) const;
    ConstIterator findLowerBound(KeyT const& key) const;
    ConstIterator findLowerEqual(KeyT const& key) const;

    ConstIterator begin() const;
    ConstIterator end() const;

    size_t size() const;

  private:
    mutable Tree tree_;
  };
}


namespace ctr
{
  template<typename KeyT, typename ValueT, typename CompareT, typename AllocatorT>
  bool Map<KeyT, ValueT, CompareT, AllocatorT>::EntryCompare::operator ()(Entry const& lhs,
                                                                          Entry const& rhs) const
  {
    return compare_(lhs.first, rhs.first);
  }

  template<typename KeyT, typename ValueT, typename CompareT, typename AllocatorT>
  Map<KeyT, ValueT, CompareT, AllocatorT>::Map(AllocatorT const& allocator)
    : tree_(allocator)
  {
  }

  /**
   * @param entry entry to store in the tree
   * @return true if the given entry was inserted into the map, false if it was already there
   */
  template<typename KeyT, typename ValueT, typename CompareT, typename AllocatorT>
  bool Map<KeyT, ValueT, CompareT, AllocatorT>::insert(Entry const& entry)
  {
    return tree_.insert(entry);
  }

  /**
   * @param key key identifying the element to remove
   * @return true if an element with the given key was found and removed, false otherwise
   */
  template<typename KeyT, typename ValueT, typename CompareT, typename AllocatorT>
  bool Map<KeyT, ValueT, CompareT, AllocatorT>::remove(KeyT const& key)
  {
    return tree_.remove(Entry(key, ValueT()));
  }

  template<typename KeyT, typename ValueT, typename CompareT, typename AllocatorT>
  typename Map<KeyT, ValueT, CompareT, AllocatorT>::ConstIterator
  Map<KeyT, ValueT, CompareT, AllocatorT>::find(KeyT const& key) const
  {
    return tree_.find(Entry(key, ValueT()));
  }

  template<typename KeyT, typename ValueT, typename CompareT, typename AllocatorT>
  typename Map<KeyT, ValueT, CompareT, AllocatorT>::ConstIterator
  Map<KeyT, ValueT, CompareT, AllocatorT>::findLowerBound(KeyT const& key) const
  {
    return tree_.findLowerBound(Entry(key, ValueT()));
  }

  template<typename KeyT, typename ValueT, typename CompareT, typename AllocatorT>
  typename Map<KeyT, ValueT, CompareT, AllocatorT>::ConstIterator
  Map<KeyT, ValueT, CompareT, AllocatorT>::findLowerEqual(KeyT const& key) const
  {
    return tree_.findLowerEqual(Entry(key, ValueT()));
  }

  template<typename KeyT, typename ValueT, typename CompareT, typename AllocatorT>
  typename Map<KeyT, ValueT, CompareT, AllocatorT>::ConstIterator
  Map<KeyT, ValueT, CompareT, AllocatorT>::begin() const
  {
    return tree_.begin();
  }

  template<typename KeyT, typename ValueT, typename CompareT, typename AllocatorT>
  typename Map<KeyT, ValueT, CompareT, AllocatorT>::ConstIterator
  Map<KeyT, ValueT, CompareT, AllocatorT>::end() const
  {
    return tree_.end();
  }

  template<typename KeyT, typename ValueT, typename CompareT, typename AllocatorT>
  size_t Map<KeyT, ValueT, CompareT, AllocatorT>::size() const
  {
    return tree_.size();
  }
}


#endif
