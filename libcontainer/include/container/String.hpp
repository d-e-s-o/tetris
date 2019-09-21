// String.hpp

/***************************************************************************
 *   Copyright (C) 2012-2014,2019 Daniel Mueller (deso@posteo.net)         *
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

#ifndef CTRSTRING_HPP
#define CTRSTRING_HPP

#include <util/String.hpp>

#include "container/Config.hpp"
#include "container/Array.hpp"
#include "container/Allocator.hpp"


namespace ctr
{
  template<typename CharT, typename AllocatorT>
  class BasicString;

  typedef BasicString<char_t,  Allocator<char_t>  > String;
  typedef BasicString<achar_t, Allocator<achar_t> > StringA;
  typedef BasicString<wchar_t, Allocator<wchar_t> > StringW;


  /**
   * This class wraps the supplied allocator class to always allocate space for one more
   * element than was actually requested. This functionality is required for the BasicString class
   * template to work.
   * @see BasicString
   */
  template<typename T, typename AllocatorT>
  class SlackAllocator: private AllocatorT
  {
  public:
    SlackAllocator(AllocatorT allocator);
    SlackAllocator(SlackAllocator&&) = default;
    SlackAllocator(SlackAllocator const&) = default;

    SlackAllocator& operator =(SlackAllocator&&) = default;
    SlackAllocator& operator =(SlackAllocator const&) = default;

    using AllocatorT::Rebind;

    T* allocate(size_t n, T const* hint = 0, T const* data = 0);

    using AllocatorT::deallocate;
    using AllocatorT::construct;
    using AllocatorT::destruct;

  private:
    AllocatorT allocator_;
  };


  /**
   * @note an important part of the BasicString class template is to support 'conversion' to a zero
   *       terminated C-style character array; to achieve this in an elegant way, we hook into the
   *       allocator class supplied and overwrite the allocate() method to always allocate one
   *       element more than actually requested; this way we make sure that the internal buffer can
   *       always store the terminating zero character, although in the actual logic of the class
   *       there need to be no special treatment for this case; the only thing to be done is to
   *       fill this slack character with a zero value whenever the toString() method is called
   */
  template<typename CharT, typename AllocatorT = Allocator<CharT> >
  class BasicString: private Array<CharT, SlackAllocator<CharT, AllocatorT> >
  {
  private:
    typedef Array<CharT, SlackAllocator<CharT, AllocatorT> > Base;

  public:
    using typename Base::Iterator;
    using typename Base::ConstIterator;

    explicit BasicString(AllocatorT allocator = AllocatorT());
    explicit BasicString(CharT character, AllocatorT allocator = AllocatorT());
    explicit BasicString(CharT const* string, AllocatorT allocator = AllocatorT());

    template<typename InputIteratorT>
    explicit BasicString(InputIteratorT begin, InputIteratorT end, AllocatorT allocator = AllocatorT());

    BasicString(BasicString&& other) = default;
    BasicString(BasicString const& other) = default;

    BasicString& operator =(BasicString&& other) = default;
    BasicString& operator =(BasicString const& other) = default;

    BasicString const& operator +=(BasicString const& other);

    using Base::operator [];
    using Base::replace;
    using Base::begin;
    using Base::end;
    using Base::size;

    CharT*       toString();
    CharT const* toString() const;
  };


  template<typename CharT, typename AllocatorT>
  BasicString<CharT, AllocatorT> operator +(BasicString<CharT, AllocatorT> const& lhs,
                                            BasicString<CharT, AllocatorT> const& rhs);

  template<typename CharT, typename AllocatorT>
  bool operator <(BasicString<CharT, AllocatorT> const& lhs,
                  BasicString<CharT, AllocatorT> const& rhs);

  template<typename CharT, typename AllocatorT>
  bool operator ==(BasicString<CharT, AllocatorT> const& lhs,
                   BasicString<CharT, AllocatorT> const& rhs);

  template<typename CharT, typename AllocatorT>
  bool operator !=(BasicString<CharT, AllocatorT> const& lhs,
                   BasicString<CharT, AllocatorT> const& rhs);

  template<typename CharT, typename AllocatorT>
  typename BasicString<CharT, AllocatorT>::Iterator begin(BasicString<CharT, AllocatorT>& string);

  template<typename CharT, typename AllocatorT>
  typename BasicString<CharT, AllocatorT>::Iterator end(BasicString<CharT, AllocatorT>& string);

  template<typename CharT, typename AllocatorT>
  typename BasicString<CharT, AllocatorT>::ConstIterator begin(BasicString<CharT, AllocatorT> const& string);

  template<typename CharT, typename AllocatorT>
  typename BasicString<CharT, AllocatorT>::ConstIterator end(BasicString<CharT, AllocatorT> const& string);
}


namespace ctr
{
  /**
   * @copydoc Allocator::Allocator
   */
  template<typename T, typename AllocatorT>
  SlackAllocator<T, AllocatorT>::SlackAllocator(AllocatorT allocator)
    : AllocatorT(),
      allocator_(allocator)
  {
  }

  /**
   * @copydoc Allocator::Allocate
   */
  template<typename T, typename AllocatorT>
  T* SlackAllocator<T, AllocatorT>::allocate(size_t n, T const* hint, T const* data)
  {
    // we want to always allocate one object more than actually requested
    return allocator_.allocate(n + 1, hint, data);
  }

  /**
   * @param allocator allocator object to use
   */
  template<typename CharT, typename AllocatorT>
  BasicString<CharT, AllocatorT>::BasicString(AllocatorT allocator)
    : Base(SlackAllocator<CharT, AllocatorT>(allocator))
  {
  }

  /**
   * @param character
   * @param allocator allocator object to use
   */
  template<typename CharT, typename AllocatorT>
  BasicString<CharT, AllocatorT>::BasicString(CharT character, AllocatorT allocator)
    : Base(&character, &character + 1, allocator)
  {
  }

  /**
   * @param string zero terminated C-style character array (non-null)
   * @param allocator allocator object to use
   */
  template<typename CharT, typename AllocatorT>
  BasicString<CharT, AllocatorT>::BasicString(CharT const* string, AllocatorT allocator)
    : Base(string, string + utl::length(string), allocator)
  {
  }

  /**
   * @param begin
   * @param end
   * @param allocator allocator object to use
   */
  template<typename CharT, typename AllocatorT>
  template<typename InputIteratorT>
  BasicString<CharT, AllocatorT>::BasicString(InputIteratorT begin, InputIteratorT end, AllocatorT allocator)
    : Base(begin, end, allocator)
  {
  }

  /**
   * @param other
   * @return
   */
  template<typename CharT, typename AllocatorT>
  BasicString<CharT, AllocatorT> const& BasicString<CharT, AllocatorT>::operator +=(BasicString const& other)
  {
    replace(end(), end(), other.begin(), other.end());
    return *this;
  }

  template<typename CharT, typename AllocatorT>
  CharT* BasicString<CharT, AllocatorT>::toString()
  {
    BasicString<CharT, AllocatorT> const* string = this;
    return const_cast<CharT*>(string->toString());
  }

  /**
   * @return pointer to zero terminated C-style character array
   */
  template<typename CharT, typename AllocatorT>
  CharT const* BasicString<CharT, AllocatorT>::toString() const
  {
    // terminate the actual string by zero; note that dereferencing the return value of end() is
    // only safe because the SlackAllocator made sure that upon each allocation request we actually
    // allocate one element more
    // @note there is one special corner case that needs attention here: in case we got created from
    //       an empty string nothing will be allocated at all (that makes sense from a logical point
    //       of view, because replace() is optimized for that case to do nothing), however if
    //       nothing got allocated we will run into trouble here, so we need to make sure to reserve
    //       at least one element
    // @todo I guess we are in undefined behavior here; it is not safe to cast away constness in
    //       every case; generally we would need to make the base class mutable or something like
    //       that -- find a safe way to actually make this work!
    auto s = const_cast<BasicString<CharT, AllocatorT>*>(this);
      s->Array<CharT, SlackAllocator<CharT, AllocatorT> >::reserve(1);
    *(s->Array<CharT, SlackAllocator<CharT, AllocatorT> >::begin() + size()) = 0;

    return begin();
  }

  /**
   * @param lhs first string
   * @param rhs second string
   * @return concatenation of both given strings
   */
  template<typename CharT, typename AllocatorT>
  BasicString<CharT, AllocatorT> operator +(BasicString<CharT, AllocatorT> const& lhs,
                                            BasicString<CharT, AllocatorT> const& rhs)
  {
    return BasicString<CharT, AllocatorT>(lhs) += rhs;
  }

  /**
   * @param lhs first string
   * @param rhs second string
   * @return true if the first string is "smaller" than the second, false if not
   * @note this function performes a comparison purely on the numerical values of the characters of
   *       the string; most importantly, no information about the locale is being used; it should
   *       mainly be used for establishing a consistent ordering between strings (e.g., to achieve
   *       better search times in a set), not for ordering of strings in a user-friendly and
   *       user-intended way
   */
  template<typename CharT, typename AllocatorT>
  bool operator <(BasicString<CharT, AllocatorT> const& lhs,
                  BasicString<CharT, AllocatorT> const& rhs)
  {
    // @note utl::compare is not used here because it expects a zero terminated string and we cannot
    //       guarantee that our string does not contain multiple zero bytes

    auto lhs_it  = lhs.begin();
    auto lhs_end = lhs.end();
    auto rhs_it  = rhs.begin();
    auto rhs_end = rhs.end();

    for ( ; lhs_it != lhs_end && rhs_it != rhs_end; ++lhs_it, ++rhs_it)
    {
      if (*lhs_it < *rhs_it)
        return true;

      if (*lhs_it > *rhs_it)
        return false;
    }
    return lhs.size() < rhs.size();
  }

  /**
   * @param lhs first string
   * @param rhs second string
   * @return true of both strings are equal, false if not
   */
  template<typename CharT, typename AllocatorT>
  bool operator ==(BasicString<CharT, AllocatorT> const& lhs,
                   BasicString<CharT, AllocatorT> const& rhs)
  {
    // @note utl::compare is not used here because it expects a zero terminated string and we cannot
    //       guarantee that our string does not contain multiple zero bytes

    if (lhs.size() != rhs.size())
      return false;

    auto lhs_it  = lhs.begin();
    auto lhs_end = lhs.end();
    auto rhs_it  = rhs.begin();

    // we bailed out before if the sizes did not match, so no need to check for end conditions on
    // both strings
    for ( ; lhs_it != lhs_end; ++lhs_it, ++rhs_it)
    {
      if (*lhs_it != *rhs_it)
        return false;
    }
    return true;
  }

  /**
   * @param lhs
   * @param rhs
   * @return true of both strings are not equal, false if they are
   */
  template<typename CharT, typename AllocatorT>
  bool operator !=(BasicString<CharT, AllocatorT> const& lhs,
                   BasicString<CharT, AllocatorT> const& rhs)
  {
    return !(lhs == rhs);
  }

  /**
   * @param string
   * @return
   */
  template<typename CharT, typename AllocatorT>
  typename BasicString<CharT, AllocatorT>::Iterator begin(BasicString<CharT, AllocatorT>& string)
  {
    return string.begin();
  }

  /**
   * @param string
   * @return
   */
  template<typename CharT, typename AllocatorT>
  typename BasicString<CharT, AllocatorT>::Iterator end(BasicString<CharT, AllocatorT>& string)
  {
    return string.end();
  }

  /**
   * @param string
   * @return
   */
  template<typename CharT, typename AllocatorT>
  typename BasicString<CharT, AllocatorT>::ConstIterator begin(BasicString<CharT, AllocatorT> const& string)
  {
    return string.begin();
  }

  /**
   * @param string
   * @return
   */
  template<typename CharT, typename AllocatorT>
  typename BasicString<CharT, AllocatorT>::ConstIterator end(BasicString<CharT, AllocatorT> const& string)
  {
    return string.end();
  }
}


#endif
