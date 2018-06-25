// IteratorWrapper.hpp

/***************************************************************************
 *   Copyright (C) 2006-2012 Daniel Mueller (deso@posteo.net)              *
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

#ifndef BASEITERATORWRAPPER_HPP
#define BASEITERATORWRAPPER_HPP

#include <iterator>


namespace base
{
  /**
   * This class wraps an (STL-like) iterator, but is able to grant "native" access to a special
   * member of a structured type.
   * @todo this class does not conform to the requirements of a random access or bidirectional
   *       iterator - implement this if needed
   */
  template<typename IteratorT, template<typename> class AccessorT>
  class IteratorWrapper
  {
  public:
    typedef typename AccessorT<IteratorT>::reference  reference;
    typedef typename AccessorT<IteratorT>::pointer    pointer;
    typedef typename AccessorT<IteratorT>::value_type value_type;

    typedef typename IteratorT::difference_type   difference_type;
    typedef typename IteratorT::iterator_category iterator_category;

    explicit IteratorWrapper();
    explicit IteratorWrapper(IteratorT const& iterator);

    IteratorWrapper& operator ++();
    IteratorWrapper& operator --();

    reference operator *();
    pointer   operator ->();

    IteratorT const& getIterator() const;

  private:
    IteratorT            iterator_;
    AccessorT<IteratorT> accessor_;
  };


  template<typename IteratorT, template<typename> class AccessorT>
  bool operator ==(IteratorWrapper<IteratorT, AccessorT> const& lhs,
                   IteratorWrapper<IteratorT, AccessorT> const& rhs);

  template<typename IteratorT, template<typename> class AccessorT>
  bool operator !=(IteratorWrapper<IteratorT, AccessorT> const& lhs,
                   IteratorWrapper<IteratorT, AccessorT> const& rhs);

  template<typename IteratorT, template<typename> class AccessorT>
  bool operator <(IteratorWrapper<IteratorT, AccessorT> const& lhs,
                   IteratorWrapper<IteratorT, AccessorT> const& rhs);

  template<typename IteratorT, template<typename> class AccessorT>
  typename std::iterator_traits<IteratorT>::difference_type
       operator -(IteratorWrapper<IteratorT, AccessorT> const& lhs,
                   IteratorWrapper<IteratorT, AccessorT> const& rhs);
}


namespace base
{
  template<typename IteratorT, template<typename> class AccessorT>
  inline IteratorWrapper<IteratorT, AccessorT>::IteratorWrapper()
    : iterator_(),
      accessor_()
  {
  }

  template<typename IteratorT, template<typename> class AccessorT>
  inline IteratorWrapper<IteratorT, AccessorT>::IteratorWrapper(IteratorT const& iterator)
    : iterator_(iterator),
      accessor_()
  {
  }

  template<typename IteratorT, template<typename> class AccessorT>
  inline IteratorWrapper<IteratorT, AccessorT>& IteratorWrapper<IteratorT, AccessorT>::operator ++()
  {
    ++iterator_;
    return *this;
  }

  template<typename IteratorT, template<typename> class AccessorT>
  inline IteratorWrapper<IteratorT, AccessorT>& IteratorWrapper<IteratorT, AccessorT>::operator --()
  {
    --iterator_;
    return *this;
  }

  template<typename IteratorT, template<typename> class AccessorT>
  inline typename IteratorWrapper<IteratorT, AccessorT>::reference IteratorWrapper<IteratorT, AccessorT>::operator *()
  {
    return accessor_.getReference(iterator_);
  }

  template<typename IteratorT, template<typename> class AccessorT>
  inline typename IteratorWrapper<IteratorT, AccessorT>::pointer IteratorWrapper<IteratorT, AccessorT>::operator ->()
  {
    return accessor_.getPointer(iterator_);
  }

  template<typename IteratorT, template<typename> class AccessorT>
  inline IteratorT const& IteratorWrapper<IteratorT, AccessorT>::getIterator() const
  {
    return iterator_;
  }

  template<typename IteratorT, template<typename> class AccessorT>
  inline bool operator ==(IteratorWrapper<IteratorT, AccessorT> const& lhs,
                          IteratorWrapper<IteratorT, AccessorT> const& rhs)
  {
    return lhs.getIterator() == rhs.getIterator();
  }

  template<typename IteratorT, template<typename> class AccessorT>
  inline bool operator !=(IteratorWrapper<IteratorT, AccessorT> const& lhs,
                          IteratorWrapper<IteratorT, AccessorT> const& rhs)
  {
    return lhs.getIterator() != rhs.getIterator();
  }

  template<typename IteratorT, template<typename> class AccessorT>
  inline bool operator <(IteratorWrapper<IteratorT, AccessorT> const& lhs,
                          IteratorWrapper<IteratorT, AccessorT> const& rhs)
  {
    return lhs.getIterator() < rhs.getIterator();
  }

  template<typename IteratorT, template<typename> class AccessorT>
  inline typename std::iterator_traits<IteratorT>::difference_type
       operator -(IteratorWrapper<IteratorT, AccessorT> const& lhs,
                   IteratorWrapper<IteratorT, AccessorT> const& rhs)
  {
    return lhs.getIterator() - rhs.getIterator();
  };
}


#endif
