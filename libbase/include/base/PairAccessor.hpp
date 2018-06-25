// PairAccessor.hpp

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

#ifndef BASEPAIRACCESSOR_HPP
#define BASEPAIRACCESSOR_HPP


namespace base
{
  template<typename IteratorT, bool First>
  struct PairAccessor;


  /**
   * This class can be used in the IteratorWrapper to access the first value of a pair.
   * @see IteratorWrapper
   */
  template<typename IteratorT>
  struct PairAccessorFirst: PairAccessor<IteratorT, true>
  {
  };

  /**
   * This class can be used in the IteratorWrapper to access the second value of a pair.
   * @see IteratorWrapper
   */
  template<typename IteratorT>
  struct PairAccessorSecond: PairAccessor<IteratorT, false>
  {
  };
}


namespace base
{
  template<typename PairT, bool First>
  struct PairTraits;

  template<typename PairT>
  struct PairTraits<PairT&, true>
  {
    typedef typename PairT::first_type value_type;
  };

  template<typename PairT>
  struct PairTraits<PairT const&, true>
  {
    typedef typename PairT::first_type const value_type;
  };

  template<typename PairT>
  struct PairTraits<PairT&, false>
  {
    typedef typename PairT::second_type value_type;
  };

  template<typename PairT>
  struct PairTraits<PairT const&, false>
  {
    typedef typename PairT::second_type const value_type;
  };

  template<typename IteratorT>
  struct PairAccessor<IteratorT, true>
  {
    typedef typename PairTraits<typename IteratorT::reference, true>::value_type value_type;

    typedef value_type& reference;
    typedef value_type* pointer;

    reference getReference(IteratorT const& it) const
    {
      return it->first;
    }

    pointer getPointer(IteratorT const& it) const
    {
      return &it->first;
    }
  };

  template<typename IteratorT>
  struct PairAccessor<IteratorT, false>
  {
    typedef typename PairTraits<typename IteratorT::reference, false>::value_type value_type;

    typedef value_type& reference;
    typedef value_type* pointer;

    reference getReference(IteratorT const& it) const
    {
      return it->second;
    }

    pointer getPointer(IteratorT const& it) const
    {
      return &it->second;
    }
  };
}


#endif
