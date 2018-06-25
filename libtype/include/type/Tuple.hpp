// Tuple.hpp

/***************************************************************************
 *   Copyright (C) 2010-2014 Daniel Mueller                                *
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

#ifndef TYPTUPLE_HPP
#define TYPTUPLE_HPP

#include "type/Config.hpp"
#include "type/Types.hpp"


namespace typ
{
  /**
   * This forward declaration acts as a workaround for only partially implemented variadic templates
   * in gcc 4.6.
   * @todo remove me some time!
   */
  template<size_t Dummy, typename ...TypeListT>
  struct TupleImpl;


  /**
   * This specialization terminates the inheritance recursion.
   */
  template<size_t Dummy>
  struct TupleImpl<Dummy>
  {
  };

  template<size_t I, typename TupleImplT>
  struct GetImpl: GetImpl<I - 1, typename TupleImplT::Base>
  {
  };

  template<typename TupleImplT>
  struct GetImpl<0, TupleImplT>
  {
    typedef TupleImplT Impl;
  };


  /**
   * This template provides storage for values of the given list of types as well as access to them.
   * The implementation is based on inheritance.
   */
  template<size_t Dummy, typename TypeT, typename ...TypeListT>
  struct TupleImpl<Dummy, TypeT, TypeListT...>: TupleImpl<0, TypeListT...>
  {
    typedef TupleImpl<0, TypeT, TypeListT...> This;
    typedef TupleImpl<0, TypeListT...>        Base;
    typedef TypeT                             Type;

    TypeT value_;

    TupleImpl(TypeT const& value, TypeListT const&... values)
      : Base(values...),
        value_(value)
    {
    }

    template<size_t I>
    typename GetImpl<I, This>::Impl::Type& get()
    {
      return static_cast<typename GetImpl<I, This>::Impl*>(this)->value_;
    }

    template<size_t I>
    typename GetImpl<I, This>::Impl::Type const& get() const
    {
      return static_cast<typename GetImpl<I, This>::Impl const*>(this)->value_;
    }
  };


  /**
   * @todo implement comparison operators (== and <) for tuples
   */
  template<typename ...TypeListT>
  struct Tuple: TupleImpl<0, TypeListT...>
  {
    typedef TupleImpl<0, TypeListT...> Impl;

    Tuple(TypeListT const&... values)
      : Impl(values...)
    {
    }

    using Impl::get;
  };


  //template<typename T, typename U>
  //bool operator ==(Tuple<T, U> lhs, Tuple<T, U> rhs);

  //template<typename T, typename U>
  //bool operator !=(Tuple<T, U> lhs, Tuple<T, U> rhs);

  template<size_t Index, typename ...TypeListT>
  typename GetImpl<Index, TupleImpl<0, TypeListT...>>::Impl::Type&
  get(Tuple<TypeListT...>& tuple);

  template<size_t Index, typename ...TypeListT>
  typename GetImpl<Index, TupleImpl<0, TypeListT...>>::Impl::Type const&
  get(Tuple<TypeListT...> const& tuple);

  template<typename ...TypeListT>
  Tuple<TypeListT...> makeTuple(TypeListT const&... values);
}


namespace typ
{
  //template<typename T, typename U>
  //bool operator ==(Tuple<T, U> lhs, Tuple<T, U> rhs)
  //{
  //  return (lhs.first == rhs.first) && (lhs.second == rhs.second);
  //}

  //template<typename T, typename U>
  //bool operator !=(Tuple<T, U> lhs, Tuple<T, U> rhs)
  //{
  //  return !(lhs == rhs);
  //}

  /**
   * @param tuple some tuple
   * @return element of given tuple at given index
   */
  template<size_t Index, typename ...TypeListT>
  typename GetImpl<Index, TupleImpl<0, TypeListT...>>::Impl::Type&
  get(Tuple<TypeListT...>& tuple)
  {
    return tuple.template get<Index>();
  }

  /**
   * @param tuple some tuple
   * @return element of given tuple at given index
   */
  template<size_t Index, typename ...TypeListT>
  typename GetImpl<Index, TupleImpl<0, TypeListT...>>::Impl::Type const&
  get(Tuple<TypeListT...> const& tuple)
  {
    return tuple.template get<Index>();
  }

  /**
   * @param values list of values from which to create Tuple
   * @return tuple created from the given list of values
   */
  template<typename ...TypeListT>
  Tuple<TypeListT...> makeTuple(TypeListT const&... values)
  {
    return Tuple<TypeListT...>(values...);
  }
}


#endif
