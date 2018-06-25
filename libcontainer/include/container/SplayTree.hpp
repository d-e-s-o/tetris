// SplayTree.hpp

/***************************************************************************
 *   Copyright (C) 2010-2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#ifndef CTRSPLAYTREE_HPP
#define CTRSPLAYTREE_HPP

#include <util/Assert.hpp>

#include "container/Config.hpp"
#include "container/Allocator.hpp"
#include "container/BinaryTree.hpp"
#include "container/Functional.hpp"


namespace ctr
{
  /**
   * This class template represents a Splay-Tree.
   * @todo think about making Find and FindLowerBound const
   */
  template<typename T,
           typename CompareT   = Less<T>,
           typename AllocatorT = Allocator<T> >
  class SplayTree: private BinaryTree<T, CompareT, AllocatorT>
  {
  public:
    typedef typename BinaryTree<T, CompareT, AllocatorT>::ConstIterator ConstIterator;

    explicit SplayTree(AllocatorT const& allocator = AllocatorT());

    SplayTree(SplayTree&& other) = default;
    SplayTree(SplayTree const& other) = default;

    SplayTree& operator =(SplayTree&& other) = default;
    SplayTree& operator =(SplayTree const& other) = default;

    using BinaryTree<T, CompareT, AllocatorT>::clear;
    using BinaryTree<T, CompareT, AllocatorT>::begin;
    using BinaryTree<T, CompareT, AllocatorT>::end;
    using BinaryTree<T, CompareT, AllocatorT>::size;
    using BinaryTree<T, CompareT, AllocatorT>::depth;

    bool insert(T const& value);
    bool remove(T const& value);

    ConstIterator find(T const& value);
    ConstIterator findLowerBound(T const& value);
    ConstIterator findLowerEqual(T const& value);

  private:
    typedef typename BinaryTree<T, CompareT, AllocatorT>::Node Node;

    void splay(Node* node);
  };
}


namespace ctr
{
  /**
   * The constructor creates a new (empty) Splay-tree.
   */
  template<typename T, typename CompareT, typename AllocatorT>
  SplayTree<T, CompareT, AllocatorT>::SplayTree(AllocatorT const& allocator)
    : BinaryTree<T, CompareT, AllocatorT>(allocator)
  {
  }

  /**
   * @copydoc BinaryTree::Insert
   */
  template<typename T, typename CompareT, typename AllocatorT>
  bool SplayTree<T, CompareT, AllocatorT>::insert(T const& value)
  {
    Node* node = this->insertImpl(value);

    if (node != nullptr)
      splay(node);

    return node != nullptr;
  }

  /**
   * @copydoc BinaryTree::Remove
   * @todo there is this small code duplication here with regard to BinaryTree::Remove - fix this!
   */
  template<typename T, typename CompareT, typename AllocatorT>
  bool SplayTree<T, CompareT, AllocatorT>::remove(T const& value)
  {
    // the return value is a bit tricky:
    //   RemoveImpl gives us the follower or parent of the node that was removed, however this may
    //   be 0 in case the last element was removed; in order to catch this case we check whether the
    //   tree actually contained some element before and after suspected removal is empty
    bool  empty = size() == 0;
    Node* node  = this->removeImpl(value);

    if (node != nullptr)
      splay(node);

    return (node != nullptr) || (!empty && size() == 0);
  }

  /**
   * @copydoc BinaryTree::Find
   */
  template<typename T, typename CompareT, typename AllocatorT>
  typename SplayTree<T, CompareT, AllocatorT>::ConstIterator
  SplayTree<T, CompareT, AllocatorT>::find(T const& value)
  {
    Node* node = this->findEqualImpl(value);

    if (node != nullptr)
      splay(node);

    return ConstIterator(*this, node);
  }

  /**
   * @copydoc BinaryTree::FindLowerBound
   */
  template<typename T, typename CompareT, typename AllocatorT>
  typename SplayTree<T, CompareT, AllocatorT>::ConstIterator
  SplayTree<T, CompareT, AllocatorT>::findLowerBound(T const& value)
  {
    Node* node = this->findLowerBoundImpl(value);

    if (node != nullptr)
      splay(node);

    return ConstIterator(*this, node);
  }

  /**
   * @copydoc BinaryTree::FindLowerEqual
   */
  template<typename T, typename CompareT, typename AllocatorT>
  typename SplayTree<T, CompareT, AllocatorT>::ConstIterator
  SplayTree<T, CompareT, AllocatorT>::findLowerEqual(T const& value)
  {
    Node* node = this->findLowerEqualImpl(value);

    if (node != nullptr)
      splay(node);

    return ConstIterator(*this, node);
  }

  /**
   * This method is the main method this tree uses for implementing various other methods. It
   * rotates the given node until it reaches the root of the tree - thereby somehow balancing the
   * tree.
   * @note in every source I found the splay operation has several cases, taking into consideration
   *       the node, its parent and grandparent and their relations (mounted left etc.) and acts
   *       differently on each constellation - however I do not see the point...all we want to do is
   *       rotate the node upwards until it eventually reaches the root, and that is exactly what
   *       we do here
   */
  template<typename T, typename CompareT, typename AllocatorT>
  void SplayTree<T, CompareT, AllocatorT>::splay(Node* node)
  {
    ASSERTOP(node, ne, nullptr);

    while (node != BinaryTree<T, CompareT, AllocatorT>::getRootNode())
      this->rotate(node);
  }
}


#endif
