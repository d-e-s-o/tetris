// Algorithm.hpp

/***************************************************************************
 *   Copyright (C) 2010-2014 Daniel Mueller (deso@posteo.net)              *
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

#ifndef UTLALGORITHM_HPP
#define UTLALGORITHM_HPP

#include <type/Move.hpp>
#include <type/Traits.hpp>

#include "util/Config.hpp"


namespace utl
{
  template<typename Iterator1T, typename Iterator2T>
  bool includes(Iterator1T begin, Iterator1T end, Iterator2T it);

  //template<typename IteratorT>
  //difference_t difference(IteratorT first, IteratorT second);

  template<typename InputIteratorT, typename OutputIteratorT>
  OutputIteratorT move(InputIteratorT begin, InputIteratorT end, OutputIteratorT destination);

  template<typename InputIteratorT, typename OutputIteratorT>
  OutputIteratorT copy(InputIteratorT begin, InputIteratorT end, OutputIteratorT destination);

  template<typename InputIteratorT, typename OutputIteratorT, typename CopyT>
  OutputIteratorT copy(InputIteratorT begin, InputIteratorT end, OutputIteratorT destination, CopyT copy);

  template<typename IteratorT, typename T>
  void fill(IteratorT begin, IteratorT end, T const& value);

  template<typename IteratorT, typename T>
  IteratorT find(IteratorT begin, IteratorT end, T const& value);

  template<typename IteratorT, typename T>
  IteratorT findNot(IteratorT begin, IteratorT end, T const& value);

  template<typename IteratorT, typename T, typename FunctorT>
  IteratorT findIf(IteratorT begin, IteratorT end, FunctorT const& functor);

  template<typename IteratorT, typename T>
  IteratorT findBinary(IteratorT begin, IteratorT end, T const& value);

  template<typename IteratorT, typename TransformT>
  IteratorT transform(IteratorT begin, IteratorT end, TransformT const& transformer);
}


namespace utl
{
  /**
   * @param it iterator to check if it is in the range [begin, end]
   * @param begin begin of range to check for inclusion of it
   * @param end end of range to check for inclusion of it
   * @note although in general 'end' refers to the first invalid element of a range, 'it' could
   *       still be equal to 'end' and would in this case be treated as part of the range
   * @todo this function works for pointers and for iterator types that are comparable, but will
   *       fail for all other types -- fix this!
   */
  template<typename IteratorT>
  constexpr bool includesImpl(IteratorT begin, IteratorT end, IteratorT it)
  {
    return begin <= it && it <= end;
  }

  /**
   *
   */
  template<typename Iterator1T, typename Iterator2T>
  constexpr bool includesImpl(Iterator1T begin, Iterator1T end, Iterator2T it)
  {
    return false;
  }

  namespace impl
  {
    /**
     * @param t some value
     * @return the given value
     * @todo move into libtype or a more publicly accessible header once required somewhere else
     */
    template<typename T>
    constexpr T const& makeLvalue(T&& t)
    {
      return t;
    }
  }

  /**
   * @note the assumption is that two distinct types of iterators can never point to the same
   *       underlying data structure; however, one must take into consideration that types can be
   *       distinct just because of their constness
   */
  template<typename Iterator1T, typename Iterator2T>
  bool includes(Iterator1T begin, Iterator1T end, Iterator2T it)
  {
    typedef typename typ::RemoveReference<
            typename typ::RemoveRvalueReference< decltype(*begin)>::Type>::Type T1;
    typedef typename typ::RemoveReference<
            typename typ::RemoveRvalueReference< decltype(*it)>::Type>::Type T2;

    // Note that we need to use operator * and operator & on the iterator to
    // correctly handle overloaded versions of them. To make this work we need
    // to convert the value return from operator * to an L-value.
    T1 const* new_begin = &impl::makeLvalue(*begin);
    T1 const* new_end   = &impl::makeLvalue(*end);
    T2 const* new_it    = &impl::makeLvalue(*it);
    return includesImpl(new_begin, new_end, new_it);
  }

  /**
   * @todo we could pass references to iterators to this function, then Copy (the optimized
   *       version) could make better use of it
   */
  template<typename InputIteratorT, typename OutputIteratorT, typename CopyT>
  inline OutputIteratorT simpleCopy(InputIteratorT begin, InputIteratorT end,
                                    OutputIteratorT destination, CopyT copy)
  {
    // if destination is not in [begin, end) (the ranges do not overlap [general case]), simply copy
    // element by element in forward order, otherwise we copy backwards
    // @todo copying backwards is probably a really bad thing with regard to performance, as modern
    //       processors will be optimized for forward access and probably do some prefetching --
    //       find a better way!
    if (!includes(begin, end, destination))
    {
      // copy element by element
      while (begin != end)
        copy(begin++, destination++);

      return destination;
    }
    else
    {
      InputIteratorT  rbegin  = end - 1;
      InputIteratorT  rend    = begin - 1;
      OutputIteratorT rout    = destination + ((end - 1) - begin);
      OutputIteratorT out_end = rout + 1;

      while (rbegin != rend)
        copy(rbegin--, rout--);

      return out_end;
    }
  }

  template<typename InputIteratorT, typename OutputIteratorT>
  inline OutputIteratorT simpleCopy(InputIteratorT begin, InputIteratorT end,
                                    OutputIteratorT destination)
  {
    auto assign = [](InputIteratorT in, OutputIteratorT out) { *out = *in; };
    return simpleCopy(begin, end, destination, assign);
  }

  /**
   * @param begin iterator to begin of input region
   * @param end iterator to end of input region (pointing right after last element)
   * @param destination iterator to begin of output region
   * @return iterator pointing right after last element copied to output region
   */
  template<typename InputIteratorT, typename OutputIteratorT>
  inline OutputIteratorT move(InputIteratorT begin, InputIteratorT end, OutputIteratorT destination)
  {
    auto assign = [](InputIteratorT in, OutputIteratorT out) { *out = typ::move(*in); };
    return simpleCopy(begin, end, destination, assign);
  }

  /**
   * @todo it would make sense to make Copy return an iterator just past the last element copied,
   *       however this is not as trivial as it might seem at first glance
   */
  template<typename InputIteratorT, typename OutputIteratorT>
  inline OutputIteratorT copy(InputIteratorT begin, InputIteratorT end, OutputIteratorT destination)
  {
    return simpleCopy(begin, end, destination);
  }

  /**
   *
   */
  template<typename InputIteratorT, typename OutputIteratorT, typename CopyT>
  inline OutputIteratorT copy(InputIteratorT begin, InputIteratorT end,
                              OutputIteratorT destination, CopyT copy)
  {
    return simpleCopy(begin, end, destination, copy);
  }

  /**
   * This is the specialized version of copy for pointers to unsigned char. IteratorT is optimized for
   * better performance and can be always used for POD like types.
   */
  template<>
  inline byte_t* copy(byte_t const* begin, byte_t const* end, byte_t* destination)
  {
    // number of bytes to copy in "one rush"
    int const BLOCK_SIZE = 16 * sizeof(ulong_t);

    // only use the optimized version for large memory blocks greater or equal 2 * "BLOCK_SIZE"
    // because if less than 2 * "BLOCK_SIZE" we could get "tmp_end" less than "tmp_begin" below
    // which would be bad (but it does not make sense to use the optimized version in that case
    // anyway)
    // also destination must not be in [begin - BLOCKSIZE, begin + BLOCKIZE], because we would run
    // into problems with overlapping ranges
    // @todo use difference() function here
    if (end - begin >= 2 * BLOCK_SIZE &&
      !(begin - BLOCK_SIZE <= destination && destination <= begin + BLOCK_SIZE))
    {
      // @todo Null should be declared somewhere globally
      byte_t const* Null = 0;

      int const mod1 = (begin - Null) % BLOCK_SIZE;
      int const mod2 = (end   - Null) % BLOCK_SIZE;

      // first copy until we are "BLOCK_SIZE" aligned
      // e.g., if "begin" is 1025 then we are not 4 byte aligned (1024 would be)
      //       we add (4 - (1025 % 4)) = 4 - 1 = 3 bytes to "begin" and are 4 byte aligned
      //       so 1025 + 3 = 1028
      if (mod1 != 0)
      {
        byte_t const* tmp_end = begin + (BLOCK_SIZE - mod1);

        while (begin != tmp_end)
          *destination++ = *begin++;
      }

      // next copy the main part while staying "BLOCK_SIZE" aligned
      // note that tmp_end2 needs to point right after the last valid entry
      // e.g. if "end" is 1027 then we are not 4 byte aligned
      //      we subtract 1027 % 4 = 3 bytes from "end" to get a 4 byte aligned address
      ulong_t const* tmp_begin = reinterpret_cast<ulong_t const*>(begin);
      ulong_t const* tmp_end   = reinterpret_cast<ulong_t const*>(end - mod2);
      ulong_t*       tmp_dest  = reinterpret_cast<ulong_t*>      (destination);

      while (tmp_begin != tmp_end)
      {
        // "BLOCK_SIZE" is 16 * sizeof(ulong_t) so we need to copy 16 ulong_ts in "one rush"
        *tmp_dest++ = *tmp_begin++;
        *tmp_dest++ = *tmp_begin++;
        *tmp_dest++ = *tmp_begin++;
        *tmp_dest++ = *tmp_begin++;

        *tmp_dest++ = *tmp_begin++;
        *tmp_dest++ = *tmp_begin++;
        *tmp_dest++ = *tmp_begin++;
        *tmp_dest++ = *tmp_begin++;

        *tmp_dest++ = *tmp_begin++;
        *tmp_dest++ = *tmp_begin++;
        *tmp_dest++ = *tmp_begin++;
        *tmp_dest++ = *tmp_begin++;

        *tmp_dest++ = *tmp_begin++;
        *tmp_dest++ = *tmp_begin++;
        *tmp_dest++ = *tmp_begin++;
        *tmp_dest++ = *tmp_begin++;
      }

      // next copy the last part that is not "BLOCK_SIZE" aligned
      if (mod2 != 0)
      {
        begin       = reinterpret_cast<byte_t const*>(tmp_begin);
        destination = reinterpret_cast<byte_t*>      (tmp_dest);

        while (begin != end)
          *destination++ = *begin++;
      }
      return destination;
    }
    else
      return simpleCopy(begin, end, destination);
  }

  /**
   * This function fills the values in range [begin, end) with the given value.
   */
  template<typename IteratorT, typename T>
  void fill(IteratorT begin, IteratorT end, T const& value)
  {
    while (begin != end)
      *begin++ = value;
  }

  /**
   * This function finds the first occurrence of the given value in the range [begin, end).
   */
  template<typename IteratorT, typename T>
  IteratorT find(IteratorT begin, IteratorT end, T const& value)
  {
    while (begin != end && *begin != value)
      ++begin;

    return begin;
  }

  /**
   * This function finds the first value in the range [begin, end) that does not equal the given
   * one.
   */
  template<typename IteratorT, typename T>
  IteratorT findNot(IteratorT begin, IteratorT end, T const& value)
  {
    while (begin != end && *begin == value)
      ++begin;

    return begin;
  }

  /**
   * @param begin
   * @param end
   * @param value
   * @todo think about renaming this function to 'searchBinary' -- the behavior is different than
   *       for 'findX' functions in that we also return a valid iterator in most cases where no
   *       matching element is actually found
   */
  template<typename IteratorT, typename T>
  IteratorT findBinary(IteratorT begin, IteratorT end, T const& value)
  {
    while (end - begin > 0)
    {
      IteratorT it = begin + (end - 1 - begin) / 2;

      if (value < *it)
        end = it;
      else if (value > *it)
        begin = it + 1;
      else
        return it;
    }
    return begin;
  }

  /**
   * @param in_begin
   * @param in_end
   * @param out_begin
   * @param transformer
   * @return
   */
  template<typename IteratorT, typename TransformT>
  IteratorT transform(IteratorT in_begin, IteratorT in_end, IteratorT out_begin, TransformT const& transformer)
  {
    while (in_begin != in_end)
    {
      *out_begin = transformer(*in_begin);

      ++in_begin;
      ++out_begin;
    }
    return out_begin;
  }
}


#endif
