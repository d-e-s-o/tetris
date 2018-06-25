// Traits.hpp

/***************************************************************************
 *   Copyright (C) 2012 Daniel Mueller                                     *
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

#ifndef TYPTRAITS_HPP
#define TYPTRAITS_HPP

/**
 * @todo add unit tests for these templates
 */


namespace typ
{
  /**
   * @param Type1T first type
   * @param Type2T second type
   * @value Value true if both types are equal, false if not
   */
  template<typename Type1T, typename Type2T>
  struct Equal
  {
    static bool const Value = false;
  };

  /**
   * @param TypeT
   * @value Type type of input type with removed const modifier
   */
  template<typename TypeT>
  struct RemoveConst
  {
    typedef TypeT Type;
  };

  /**
   *
   */
  template<typename TypeT>
  struct RemovePointer
  {
    typedef TypeT Type;
  };

  /**
   *
   */
  template<typename TypeT>
  struct RemoveReference
  {
    typedef TypeT Type;
  };

  /**
   *
   */
  template<typename TypeT>
  struct RemoveRvalueReference
  {
    typedef TypeT Type;
  };

  template<typename TypeT>
  struct IsBuiltInImpl
  {
    static bool const Value = false;
  };

  /**
   *
   */
  template<typename TypeT>
  struct IsBuiltIn
  {
    static bool const Value = IsBuiltInImpl<typename RemoveConst<typename RemoveReference<TypeT>::Type>::Type>::Value;
  };

  /**
   *
   */
  template<typename TypeT>
  struct MakeConst
  {
    typedef TypeT const Type;
  };

  /**
   * Convert a signed data type into an unsigned one.
   */
  template<typename TypeT>
  struct MakeUnsigned
  {
    typedef TypeT const Type;
  };
}


namespace typ
{
  template<typename Type1T>
  struct Equal<Type1T, Type1T>
  {
    static bool const Value = true;
  };

  template<typename TypeT>
  struct RemoveConst<TypeT const>
  {
    typedef TypeT Type;
  };

  template<typename TypeT>
  struct RemovePointer<TypeT*>
  {
    typedef TypeT Type;
  };

  template<typename TypeT>
  struct RemoveReference<TypeT&>
  {
    typedef TypeT Type;
  };

  template<typename TypeT>
  struct RemoveRvalueReference<TypeT&&>
  {
    typedef TypeT Type;
  };

  template<typename TypeT>
  struct IsBuiltInImpl<TypeT*>
  {
    static bool const Value = true;
  };

  template<>
  struct IsBuiltInImpl<char>
  {
    static bool const Value = true;
  };

  template<>
  struct IsBuiltInImpl<wchar_t>
  {
    static bool const Value = true;
  };

  template<>
  struct IsBuiltInImpl<signed char>
  {
    static bool const Value = true;
  };

  template<>
  struct IsBuiltInImpl<unsigned char>
  {
    static bool const Value = true;
  };

  template<>
  struct IsBuiltInImpl<short>
  {
    static bool const Value = true;
  };

  template<>
  struct IsBuiltInImpl<unsigned short>
  {
    static bool const Value = true;
  };

  template<>
  struct IsBuiltInImpl<int>
  {
    static bool const Value = true;
  };

  template<>
  struct IsBuiltInImpl<unsigned int>
  {
    static bool const Value = true;
  };

  template<>
  struct IsBuiltInImpl<long>
  {
    static bool const Value = true;
  };

  template<>
  struct IsBuiltInImpl<unsigned long>
  {
    static bool const Value = true;
  };

  template<>
  struct IsBuiltInImpl<float>
  {
    static bool const Value = true;
  };

  template<>
  struct IsBuiltInImpl<double>
  {
    static bool const Value = true;
  };

  template<typename TypeT>
  struct MakeConst<TypeT&>
  {
    typedef TypeT const& Type;
  };

  template<>
  struct MakeUnsigned<char>
  {
    typedef unsigned char Type;
  };

  template<>
  struct MakeUnsigned<signed char>
  {
    typedef unsigned char Type;
  };

  template<>
  struct MakeUnsigned<signed short>
  {
    typedef unsigned short Type;
  };

  template<>
  struct MakeUnsigned<signed int>
  {
    typedef unsigned int Type;
  };

  template<>
  struct MakeUnsigned<signed long>
  {
    typedef unsigned long Type;
  };

  template<>
  struct MakeUnsigned<signed long long>
  {
    typedef unsigned long long Type;
  };
}


#endif
