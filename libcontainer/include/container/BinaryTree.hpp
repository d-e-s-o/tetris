// BinaryTree.hpp

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

#ifndef CTRBINARYTREE_HPP
#define CTRBINARYTREE_HPP

#include <util/Assert.hpp>

#include "container/Config.hpp"
#include "container/Allocator.hpp"
#include "container/Functional.hpp"


namespace ctr
{
  /**
   * This class represents a binary tree.
   * @param T
   * @param CompareT
   * @param AllocatorT
   * @todo think about adding support for merging two trees
   * @todo none of the code below is exception safe - think about changing this
   * @todo the insert() and remove() methods should also return an iterator, instead of a boolean
   *       value
   * @todo we also need overloads for (at least) remove that take an iterator as argument
   * @todo I guess we should also introduce another type as return type for GetSize and GetDepth
   * @todo find(), findLowerBound() should be const (and with that the Impl stuff)
   * @todo we could also use a findUpperBound() method (which would be kind of straight forward to
   *       implement I guess)
   * @todo find and findLowerBound() should also allow passing in a different compare object only
   *       used for this find-call
   * @note I thought about implementing the tree by having some real root-node that is always
   *       present and has no value (or no defined one), the left subtree would then be the actual
   *       binary tree - this would remove all the special "if node == root_" or "if parent ==
   *       nullptr" cases, as the root of the binary tree would not be handled special in any way;
   *       this however turns out to be really difficult to achieve:
   *       - one way I could come up with is making the Node class somehow polymorph and make it
   *         return a pointer to the data in the GetValue method, but that would have implications
   *         on performance
   *       - another way would be to always have a value but don't touch it, this would cause
   *         problems if there is not default constructor for this type or if there are other
   *         constraints (like there can only be a limited number of objects or so) - this is just
   *         unacceptable
   *       - one could also do some really nasty casting stuff to assign a value to the node and
   *         never touch it (such that there is no need for polymorphism), that could work but it is
   *         not nice and may even be undefined behavior
   *       -> in the end the way it is done here is probably not bad, especially as I could break
   *          down the special case handling to one method; also in the case of iterators having
   *          this special root node could introduce other problems to check for (predecessor of
   *          first actual node)
   */
  template<typename T,
           typename CompareT   = Less<T>,
           typename AllocatorT = Allocator<T> >
  class BinaryTree
  {
  protected:
    class Node;

  public:
    /**
     * @todo it would be nice to have some more or less generic iterator class that we would just
     *       need to specialize/parametrize here to get the intended functionality (I believe I have
     *       written something like that before... [?])
     * @note it is not (easily?) possible to make operator ==() and operator !=() free-standing
     *       functions:
     *       - using
     *         template<typename T> operator ==(typename BinaryTree<T>::ConstIterator, ...)
     *         will not work as the template parameter T will not be deducible
     *       - alternatives:
     *         - define ConstIterator outside of BinaryTree
     *         - make an inline friend definition of operator ==(ConstIterator, ConstIterator)
     */
    class ConstIterator
    {
    public:
      ConstIterator(BinaryTree const& tree, Node* node);
      ConstIterator(ConstIterator&&) = default;
      ConstIterator(ConstIterator const&) = default;

      ConstIterator& operator =(ConstIterator&&) = default;
      ConstIterator& operator =(ConstIterator const&) = default;

      bool operator ==(ConstIterator const& other) const;
      bool operator !=(ConstIterator const& other) const;

      ConstIterator& operator ++();
      ConstIterator  operator ++(int);

      ConstIterator& operator --();
      ConstIterator  operator --(int);

      T const& operator *() const;
      T const* operator ->() const;

    private:
      BinaryTree const* tree_;
      Node*             node_;
    };

    explicit BinaryTree(AllocatorT const& allocator = AllocatorT());

    BinaryTree(BinaryTree&& other);
    BinaryTree(BinaryTree const& other);

    ~BinaryTree();

    BinaryTree& operator =(BinaryTree&& other);
    BinaryTree& operator =(BinaryTree const& other);

    bool insert(T const& value);
    bool remove(T const& value);

    void clear();

    ConstIterator find(T const& value);
    ConstIterator findLowerBound(T const& value);
    ConstIterator findLowerEqual(T const& value);

    ConstIterator begin() const;
    ConstIterator end() const;

    size_t size() const;
    size_t depth() const;

  protected:
    Node* insertImpl(T const& value);
    Node* removeImpl(T const& value);
    Node* removeNodeImpl(Node* node);

    Node* findImpl(T const& value);
    Node* findEqualImpl(T const& value);
    Node* findLowerBoundImpl(T const& value);
    Node* findLowerEqualImpl(T const& value);

    void rotate(Node* node);

    Node const* getRootNode() const;

    class Node
    {
    public:
      Node(T const& value);
      Node(Node&&) = default;
      Node(Node const&) = default;

      Node& operator =(Node&&) = default;
      Node& operator =(Node const&) = default;

      Node* getParent() const;
      void setParent(Node* node);

      Node* getLeft() const;
      void setLeft(Node* node);

      Node* getRight() const;
      void setRight(Node* node);

      T const& getValue() const;

    private:
      Node* parent_;
      Node* left_;
      Node* right_;

      T value_;
    };

  private:
    typedef typename AllocatorT::template Rebind<Node>::Other NodeAllocator;

    NodeAllocator allocator_;
    CompareT      compare_;
    Node*         root_;

    bool less(T const& lhs, T const& rhs) const;
    bool greater(T const& lhs, T const& rhs) const;
    bool equal(T const& lhs, T const& rhs) const;

    Node* createNode(Node const& other);
    void destroyNode(Node* node);

    void exchangeNode(Node* node1, Node* node2);
    void safeSetNode(Node* parent, Node* child, bool left);

    Node* getRightmostNode(Node* node) const;
    Node* getLeftmostNode(Node* node) const;
    Node* getPreviousNode(Node* node) const;
    Node* getNextNode(Node* node) const;

    Node* copy(Node* tree);
    void destroy(Node* tree);

    size_t sizeImpl(Node* node) const;
    size_t depthImpl(Node* node) const;

    bool isValidTree() const;
    bool isValidTree(Node* parent, Node* tree) const;
    bool isRelated(Node* parent, Node* child) const;
  };
}


namespace ctr
{
  template<typename T, typename CompareT, typename AllocatorT>
  BinaryTree<T, CompareT, AllocatorT>::ConstIterator::ConstIterator(BinaryTree const& tree,
                                                                    Node* node)
    : tree_(&tree),
      node_(node)
  {
  }

  template<typename T, typename CompareT, typename AllocatorT>
  bool
  BinaryTree<T, CompareT, AllocatorT>::ConstIterator::operator ==(ConstIterator const& other) const
  {
    ASSERTOP(tree_, eq, other.tree_);
    return node_ == other.node_;
  }

  template<typename T, typename CompareT, typename AllocatorT>
  bool
  BinaryTree<T, CompareT, AllocatorT>::ConstIterator::operator !=(ConstIterator const& other) const
  {
    return !operator ==(other);
  }

  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::ConstIterator&
  BinaryTree<T, CompareT, AllocatorT>::ConstIterator::operator ++()
  {
    ASSERTOP(node_, ne, nullptr);
    node_ = tree_->getNextNode(node_);
    return *this;
  }

  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::ConstIterator
  BinaryTree<T, CompareT, AllocatorT>::ConstIterator::operator ++(int)
  {
    ConstIterator it = *this;
    operator ++();
    return it;
  }

  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::ConstIterator&
  BinaryTree<T, CompareT, AllocatorT>::ConstIterator::operator --()
  {
    ASSERTOP(node_, ne, nullptr);
    node_ = tree_->getPreviousNode(node_);
    return *this;
  }

  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::ConstIterator
  BinaryTree<T, CompareT, AllocatorT>::ConstIterator::operator --(int)
  {
    ConstIterator it = *this;
    operator --();
    return it;
  }

  template<typename T, typename CompareT, typename AllocatorT>
  T const& BinaryTree<T, CompareT, AllocatorT>::ConstIterator::operator *() const
  {
    return node_->getValue();
  }

  template<typename T, typename CompareT, typename AllocatorT>
  T const* BinaryTree<T, CompareT, AllocatorT>::ConstIterator::operator ->() const
  {
    return &node_->getValue();
  }

  /**
   * The constructor creates a new (empty) binary tree.
   */
  template<typename T, typename CompareT, typename AllocatorT>
  BinaryTree<T, CompareT, AllocatorT>::BinaryTree(AllocatorT const& allocator)
    : allocator_(allocator),
      compare_(),
      root_(nullptr)
  {
  }

  /**
   * The move constructor moves the given tree into the newly created one.
   * @param other tree to move from
   */
  template<typename T, typename CompareT, typename AllocatorT>
  BinaryTree<T, CompareT, AllocatorT>::BinaryTree(BinaryTree&& other)
    : allocator_(other.allocator_),
      compare_(other.compare_),
      root_(other.root_)
  {
    other.root_ = nullptr;
  }

  /**
   * The copy constructor creates a new tree as copy of an existing one.
   * @param other tree to copy
   */
  template<typename T, typename CompareT, typename AllocatorT>
  BinaryTree<T, CompareT, AllocatorT>::BinaryTree(BinaryTree const& other)
    : allocator_(other.allocator_),
      compare_(other.compare_),
      root_(copy(other.root_))
  {
  }

  /**
   * The destructor free's the given binary tree and all its nodes.
   */
  template<typename T, typename CompareT, typename AllocatorT>
  BinaryTree<T, CompareT, AllocatorT>::~BinaryTree()
  {
    destroy(root_);
  }

  /**
   * @param other tree to copy
   * @return this tree
   */
  template<typename T, typename CompareT, typename AllocatorT>
  BinaryTree<T, CompareT, AllocatorT>&
  BinaryTree<T, CompareT, AllocatorT>::operator =(BinaryTree&& other)
  {
    if (&other != this)
    {
      allocator_ = other.allocator_;
      compare_   = other.compare_;
      root_      = other.root_;

      other.root_ = nullptr;
    }
    return *this;
  }

  /**
   * The assignment operator assigns the current tree a copy of the given one.
   * @param other tree to copy
   * @return this tree
   */
  template<typename T, typename CompareT, typename AllocatorT>
  BinaryTree<T, CompareT, AllocatorT>&
  BinaryTree<T, CompareT, AllocatorT>::operator =(BinaryTree const& other)
  {
    if (&other != this)
    {
      destroy(root_);

      allocator_ = other.allocator_;
      compare_   = other.compare_;
      root_      = copy(other.root_);
    }
    return *this;
  }

  /**
   * @param value value to store in the tree
   * @return true if inserting the given value was successful, false if not
   */
  template<typename T, typename CompareT, typename AllocatorT>
  bool BinaryTree<T, CompareT, AllocatorT>::insert(T const& value)
  {
    ASSERT(isValidTree());
    return insertImpl(value) != nullptr;
  }

  /**
   * @param value value identifying the node to remove
   * @return true if the given value was found and the associated node could be removed, false
   *         otherwise
   */
  template<typename T, typename CompareT, typename AllocatorT>
  bool BinaryTree<T, CompareT, AllocatorT>::remove(T const& value)
  {
    ASSERT(isValidTree());

    // the return value is a bit tricky:
    //   removeImpl gives us the follower or parent of the node that was removed, however this may
    //   be null in case the last element was removed; in order to catch this case we check whether
    //   the tree actually contained some element before and after suspected removal is empty
    bool empty = size() == 0;

    return (removeImpl(value) != nullptr) || (!empty && size() == 0);
  }

  template<typename T, typename CompareT, typename AllocatorT>
  void BinaryTree<T, CompareT, AllocatorT>::clear()
  {
    destroy(root_);
    root_ = nullptr;
  }

  /**
   * @param value value to find
   * @return iterator pointing to the given value or end() if no node with that value was found
   */
  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::ConstIterator
  BinaryTree<T, CompareT, AllocatorT>::find(T const& value)
  {
    ASSERT(isValidTree());
    return ConstIterator(*this, findEqualImpl(value));
  }

  /**
   * @param value value to find lower bound element for
   * @return iterator to element whose value is closest to the given value but not greater, or end()
   *         if none was found
   */
  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::ConstIterator
  BinaryTree<T, CompareT, AllocatorT>::findLowerBound(T const& value)
  {
    return ConstIterator(*this, findLowerBoundImpl(value));
  }

  /**
   * @param value value to find first less or equal element for
   * @return iterator to first element less or equal to the given value, or end() if none was found
   */
  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::ConstIterator
  BinaryTree<T, CompareT, AllocatorT>::findLowerEqual(T const& value)
  {
    return ConstIterator(*this, findLowerEqualImpl(value));
  }

  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::ConstIterator
  BinaryTree<T, CompareT, AllocatorT>::begin() const
  {
    if (root_ != nullptr)
      return ConstIterator(*this, getLeftmostNode(root_));

    return end();
  }

  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::ConstIterator
  BinaryTree<T, CompareT, AllocatorT>::end() const
  {
    return ConstIterator(*this, nullptr);
  }

  /**
   * @return size of the tree (number of nodes)
   */
  template<typename T, typename CompareT, typename AllocatorT>
  size_t BinaryTree<T, CompareT, AllocatorT>::size() const
  {
    return sizeImpl(root_);
  }

  template<typename T, typename CompareT, typename AllocatorT>
  size_t BinaryTree<T, CompareT, AllocatorT>::depth() const
  {
    return depthImpl(root_);
  }

  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::Node const*
  BinaryTree<T, CompareT, AllocatorT>::getRootNode() const
  {
    return root_;
  }

  template<typename T, typename CompareT, typename AllocatorT>
  bool BinaryTree<T, CompareT, AllocatorT>::less(T const& lhs, T const& rhs) const
  {
    return compare_(lhs, rhs);
  }

  template<typename T, typename CompareT, typename AllocatorT>
  bool BinaryTree<T, CompareT, AllocatorT>::greater(T const& lhs, T const& rhs) const
  {
    return less(rhs, lhs);
  }

  template<typename T, typename CompareT, typename AllocatorT>
  bool BinaryTree<T, CompareT, AllocatorT>::equal(T const& lhs, T const& rhs) const
  {
    return !less(lhs, rhs) && !greater(lhs, rhs);
  }

  /**
   * @param value value to store in the tree
   * @return new node inserted or null if an error occurred (creating node failed or an equal node
   *         is already in the tree)
   */
  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::Node*
  BinaryTree<T, CompareT, AllocatorT>::insertImpl(T const& value)
  {
    if (root_ != nullptr)
    {
      Node* found = findImpl(value);
      ASSERTOP(found, ne, nullptr);

      if (!equal(value, found->getValue()))
      {
        Node* node = createNode(Node(value));
        ASSERT((less(value,    found->getValue()) && found->getLeft()  == nullptr) ||
               (greater(value, found->getValue()) && found->getRight() == nullptr));

        safeSetNode(found, node, less(value, found->getValue()));
        return node;
      }
      else
        return nullptr;
    }
    else
    {
      root_ = createNode(Node(value));
      return root_;
    }
  }

  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::Node*
  BinaryTree<T, CompareT, AllocatorT>::removeImpl(T const& value)
  {
    Node* node = findEqualImpl(value);

    if (node != nullptr)
      return removeNodeImpl(node);

    return nullptr;
  }

  /**
   * @param node node to remove
   * @return a follower node if there is any or the parent node otherwise
   */
  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::Node*
  BinaryTree<T, CompareT, AllocatorT>::removeNodeImpl(Node* node)
  {
    ASSERTOP(node, ne, nullptr);

    Node* left     = node->getLeft();
    Node* right    = node->getRight();
    Node* parent   = node->getParent();
    Node* follower = nullptr;

    // to remove a node there are several cases to consider:
    //   1) the node has no child (case two here), then just remove it
    //   2) it has one child (cases three and four here), then just move this child up
    //   3) it has two children (case one), then we exchange the node to be removed with its
    //      value wise immediate (with respect to the tree) predecessor (meaning the right most
    //      node of the left subtree) [note: in a symmetric fashion we could also use the
    //      successor]; after the exchange we can be sure the node to be removed only has (at
    //      most) one child (that is, because we exchanged it with a node with at most one
    //      child [it cannot have more than one child because otherwise it would not be the
    //      rightmost]) - this is exactly one of the first two cases mentioned above
    if (left != nullptr && right != nullptr)
    {
      exchangeNode(node, getRightmostNode(left));

      return removeNodeImpl(node);
    }
    else if (left == nullptr && right == nullptr)
    {
      follower = nullptr;
    }
    else if (left == nullptr)
    {
      follower = right;
    }
    else if (right == nullptr)
    {
      follower = left;
    }

    safeSetNode(parent, follower, parent != nullptr && parent->getLeft() == node);
    destroyNode(node);

    return follower != nullptr ? follower : parent;
  }

  /**
   * This method searches for a node with the given value. If it is not found it returns the node
   * where the search stopped (which is also the node where a node with the given value would be
   * mounted).
   * @param value value identifying the node
   * @return either the node that has the given value (if the returned node's value equals the given
   *         value) or the node where the search stopped (if the returned node's value is not equal
   *         the given value) - this is the place where a node with that value would be mounted at
   */
  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::Node*
  BinaryTree<T, CompareT, AllocatorT>::findImpl(T const& value)
  {
    Node* node = root_;
    Node* prev = nullptr;

    while (node != nullptr)
    {
      prev = node;

      if (greater(node->getValue(), value))
        node = node->getLeft();
      else if (less(node->getValue(), value))
        node = node->getRight();
      else
        return node;
    }
    return prev;
  }

  /**
   * @param value value identifying the node
   * @return node that has the given value or null if such a node does not exist in the tree
   */
  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::Node*
  BinaryTree<T, CompareT, AllocatorT>::findEqualImpl(T const& value)
  {
    Node* node = findImpl(value);

    if (node != nullptr)
    {
      if (equal(node->getValue(), value))
        return node;
    }
    return nullptr;
  }

  /**
   *
   */
  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::Node*
  BinaryTree<T, CompareT, AllocatorT>::findLowerBoundImpl(T const& value)
  {
    Node* node = findImpl(value);

    /**
     * @todo I guess a simple node->getPrevious would do the trick here
     */
    while (node != nullptr && greater(node->getValue(), value))
      node = node->getParent();

    return node;
  }

  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::Node*
  BinaryTree<T, CompareT, AllocatorT>::findLowerEqualImpl(T const& value)
  {
    Node* node = root_;

    while (node != nullptr && greater(node->getValue(), value))
      node = node->getLeft();

    return node;
  }

  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::Node*
  BinaryTree<T, CompareT, AllocatorT>::createNode(Node const& other)
  {
    Node* node = allocator_.allocate(1, 0, &other);
    allocator_.construct(node, other);

    return node;
  }

  template<typename T, typename CompareT, typename AllocatorT>
  void BinaryTree<T, CompareT, AllocatorT>::destroyNode(Node* node)
  {
    allocator_.destruct(node);
    allocator_.deallocate(node);
  }

  /**
   * This method can be used to exchange two nodes by swapping all the children and the parent
   * with each other.
   * @param node1 first node to exchange with second one given, must not be null
   * @param node2 second node to exchange with first one given, must not be null
   * @note at the moment the only place this method is used is in removeNodeImpl; the call there
   *       guarantees, that node1 is _always_ a direct or indirect parent of node2 (and _never_ vice
   *       versa), we use this assumption here to get rid of 3 conditions that would otherwise be
   *       needed (see below, first 3 SafeSetNode calls) - if this method is to be used in a more
   *       general fashion we need to add those conditions!
   */
  template<typename T, typename CompareT, typename AllocatorT>
  void BinaryTree<T, CompareT, AllocatorT>::exchangeNode(Node* node1, Node* node2)
  {
    ASSERTOP(node1, ne, nullptr);
    ASSERTOP(node2, ne, nullptr);
    ASSERTOP(node1, ne, node2);
    ASSERT(isRelated(node1, node2));

    // at first we need to store the current constellation in variables, because it changes over time
    // below but we need to access the values as they were when we started
    Node* parent1 = node1->getParent();
    Node* left1   = node1->getLeft();
    Node* right1  = node1->getRight();
    Node* parent2 = node2->getParent();
    Node* left2   = node2->getLeft();
    Node* right2  = node2->getRight();

    // we also need to remember whether each of the nodes is the left or right child of its parent,
    // for node1 and node2 resp. (because later we need to mount them that way)
    bool is_left1 = parent1 != nullptr ? parent1->getLeft() == node1 : true /* does not matter */;
    bool is_left2 = parent2 != nullptr ? parent2->getLeft() == node2 : true /* does not matter */;

    // under the assumption that node1 is always a direct or indirect parent of node2 we do not need
    // conditions like below to check for equality for the next 3 SafeSetNode calls
    safeSetNode(node1,   left2,  true);
    safeSetNode(node1,   right2, false);
    safeSetNode(parent1, node2,  is_left1);

    if (left1 != node2)
      safeSetNode(node2, left1, true);
    else
      safeSetNode(node2, node1, true);

    if (right1 != node2)
      safeSetNode(node2, right1, false);
    else
      safeSetNode(node2, node1, false);

    if (parent2 != node1)
      safeSetNode(parent2, node1, is_left2);
    else
      safeSetNode(node2, node1, is_left2);

    ASSERT(root_ == nullptr || root_->getParent() == nullptr);
  }

  /**
   * @param parent parent to mount the given node at
   * @param node node to mount at the given parent
   * @param left true to mount it as left child, false to mount it as right one
   */
  template<typename T, typename CompareT, typename AllocatorT>
  void BinaryTree<T, CompareT, AllocatorT>::safeSetNode(Node* parent, Node* child, bool left)
  {
    ASSERT((parent == nullptr && child == nullptr) || parent != child);

    if (child != nullptr)
      child->setParent(parent);

    if (parent != nullptr)
    {
      if (left)
        parent->setLeft(child);
      else
        parent->setRight(child);
    }
    else
      root_ = child;
  }

  /**
   * @note node whose rightmost leaf is to be found
   * @return rightmost leaf of the given node
   */
  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::Node*
  BinaryTree<T, CompareT, AllocatorT>::getRightmostNode(Node* node) const
  {
    ASSERTOP(node, ne, nullptr);

    while (node->getRight() != nullptr)
      node = node->getRight();

    return node;
  }

  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::Node*
  BinaryTree<T, CompareT, AllocatorT>::getLeftmostNode(Node* node) const
  {
    ASSERTOP(node, ne, nullptr);

    while (node->getLeft() != nullptr)
      node = node->getLeft();

    return node;
  }

  /**
   * @param node node whose previous node to get
   * @return node preceding the given one (the first one that is "less") or null if none was found
   */
  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::Node*
  BinaryTree<T, CompareT, AllocatorT>::getPreviousNode(Node* node) const
  {
    if (node->getLeft() != nullptr)
      return getRightmost(node->getLeft());

    T value = node->getValue();
    node    = node->getParent();

    while (node != nullptr && greater(node->getValue(), value))
      node = node->getParent();

    return node;
  }

  /**
   * @param node node whose next node to get
   * @return node following the given one (the first one that is "greater") or null if none was
   *         found
   */
  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::Node*
  BinaryTree<T, CompareT, AllocatorT>::getNextNode(Node* node) const
  {
    if (node->getRight() != nullptr)
      return getLeftmostNode(node->getRight());

    T value = node->getValue();
    node    = node->getParent();

    while (node != nullptr && less(node->getValue(), value))
      node = node->getParent();

    return node;
  }

  /**
   * @param node node to rotate
   * @note rotation always rotates a given node upwards, meaning its depth in the tree will
   *       decrease with every rotation until it reaches the root of the tree; depending on the
   *       side the node is mounted at its parent node we do a left rotation (mounted on right
   *       side of parent) or a right rotation (mounted on left side of parent)
   */
  template<typename T, typename CompareT, typename AllocatorT>
  void BinaryTree<T, CompareT, AllocatorT>::rotate(Node* node)
  {
    ASSERTOP(node, ne, nullptr);
    ASSERTOP(node->getParent(), ne, nullptr);
    ASSERT(node == node->getParent()->getLeft() || node == node->getParent()->getRight());

    Node* root   = node->getParent();
    Node* parent = root->getParent();

    // this is the actual rotation
    if (node == root->getRight())
    {
      Node* left = node->getLeft();

      if (left != nullptr)
        left->setParent(root);

      root->setRight(left);
      node->setLeft(root);
      root->setParent(node);
    }
    else
    {
      Node* right = node->getRight();

      if (right != nullptr)
        right->setParent(root);

      root->setLeft(right);
      node->setRight(root);
      root->setParent(node);
    }

    // we need to register the new node at the parent correctly
    safeSetNode(parent, node, parent != nullptr && parent->getLeft() == root);
  }

  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::Node*
  BinaryTree<T, CompareT, AllocatorT>::copy(Node* tree)
  {
    if (tree != nullptr)
    {
      Node* node  = createNode(*tree);
      Node* left  = copy(tree->getLeft());
      Node* right = copy(tree->getRight());

      node->setParent(nullptr);
      node->setLeft(left);
      node->setRight(right);

      if (left != nullptr)
        left->setParent(node);

      if (right != nullptr)
        right->setParent(node);

      return node;
    }
    return nullptr;
  }

  /**
   * This helper method destroys (free's) all nodes below the given node and node itself (in that
   * order).
   * @param tree tree to be free'd, including the child-nodes
   */
  template<typename T, typename CompareT, typename AllocatorT>
  void BinaryTree<T, CompareT, AllocatorT>::destroy(Node* tree)
  {
    if (tree != nullptr)
    {
      destroy(tree->getLeft());
      destroy(tree->getRight());

      destroyNode(tree);
    }
  }

  template<typename T, typename CompareT, typename AllocatorT>
  size_t BinaryTree<T, CompareT, AllocatorT>::sizeImpl(Node* node) const
  {
    if (node != nullptr)
      return 1 + sizeImpl(node->getLeft()) + sizeImpl(node->getRight());

    return 0;
  }

  template<typename T, typename CompareT, typename AllocatorT>
  size_t BinaryTree<T, CompareT, AllocatorT>::depthImpl(Node* node) const
  {
    if (node != nullptr)
    {
      size_t l = depthImpl(node->getLeft());
      size_t r = depthImpl(node->getRight());

      /**
       * @todo use shd::Max here if available
       */
      return 1 + (l > r ? l : r);
    }
    return nullptr;
  }

  /**
   * @return true if this tree is a valid binary search tree with correctly linked nodes
   * @note this method is used only for sanity checks!
   */
  template<typename T, typename CompareT, typename AllocatorT>
  bool BinaryTree<T, CompareT, AllocatorT>::isValidTree() const
  {
    return isValidTree(nullptr, root_);
  }

  /**
   * @param parent some parent node
   * @param tree left or right sub-tree of the given parent node
   * @return true if the given tree is a valid binary search tree with correctly linked nodes
   * @note this method is used only for sanity checks!
   */
  template<typename T, typename CompareT, typename AllocatorT>
  bool BinaryTree<T, CompareT, AllocatorT>::isValidTree(Node* parent, Node* tree) const
  {
    if (tree != nullptr)
    {
      // check for valid parent relation
      if (parent == tree->getParent())
      {
        if (parent != nullptr)
        {
          bool left  = false;
          bool right = false;

          if (tree == parent->getLeft())
          {
            left = true;

            if (!less(tree->getValue(), parent->getValue()))
              return false;
          }

          if (tree == parent->getRight())
          {
            right = true;

            if (!greater(tree->getValue(), parent->getValue()))
              return false;
          }

          if (!((left && !right) || (!left && right)))
            return false;
        }
        return isValidTree(tree, tree->getLeft()) &&
               isValidTree(tree, tree->getRight());
      }
      return false;
    }
    return true;
  }

  /**
   * @param parent some node to check whether it is direct or indirect parent of the given child
   * @param child some node to check whether it is direct or indirect child of the given parent
   * @return true if the given parent node is really a direct or indirect parent of the given child
   *         node, false otherwise
   * @note this method is used only for sanity checks!
   */
  template<typename T, typename CompareT, typename AllocatorT>
  bool BinaryTree<T, CompareT, AllocatorT>::isRelated(Node* parent, Node* child) const
  {
    ASSERT(parent != nullptr && child != nullptr);

    while (child != nullptr)
    {
      if (child == parent)
        return true;

      child = child->getParent();
    }
    return false;
  }

  template<typename T, typename CompareT, typename AllocatorT>
  BinaryTree<T, CompareT, AllocatorT>::Node::Node(T const& value)
    : parent_(nullptr),
      left_(nullptr),
      right_(nullptr),
      value_(value)
  {
  }

  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::Node*
  BinaryTree<T, CompareT, AllocatorT>::Node::getParent() const
  {
    return parent_;
  }

  template<typename T, typename CompareT, typename AllocatorT>
  void BinaryTree<T, CompareT, AllocatorT>::Node::setParent(Node* node)
  {
    ASSERTOP(node, ne, this);
    parent_ = node;
  }

  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::Node*
  BinaryTree<T, CompareT, AllocatorT>::Node::getLeft() const
  {
    return left_;
  }

  template<typename T, typename CompareT, typename AllocatorT>
  void BinaryTree<T, CompareT, AllocatorT>::Node::setLeft(Node* node)
  {
    ASSERTOP(node, ne, this);
    left_ = node;
  }

  template<typename T, typename CompareT, typename AllocatorT>
  typename BinaryTree<T, CompareT, AllocatorT>::Node*
  BinaryTree<T, CompareT, AllocatorT>::Node::getRight() const
  {
    return right_;
  }

  template<typename T, typename CompareT, typename AllocatorT>
  void BinaryTree<T, CompareT, AllocatorT>::Node::setRight(Node* node)
  {
    ASSERTOP(node, ne, this);
    right_ = node;
  }

  template<typename T, typename CompareT, typename AllocatorT>
  T const& BinaryTree<T, CompareT, AllocatorT>::Node::getValue() const
  {
    return value_;
  }
}


#endif
