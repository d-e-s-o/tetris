// Types.hpp

/***************************************************************************
 *   Copyright (C) 2009-2012 Daniel Mueller                                *
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

#ifndef TYPTYPES_HPP
#define TYPTYPES_HPP

#include "type/Config.hpp"


typedef unsigned char  byte_t;
typedef unsigned char  uchar_t;
typedef signed   char  schar_t;

typedef unsigned short ushort_t;
typedef signed   short sshort_t;

typedef unsigned int   uint_t;
typedef signed   int   sint_t;

typedef unsigned long  ulong_t;
typedef signed   long  slong_t;

typedef unsigned char  uint8_t;
typedef signed   char  sint8_t;

typedef unsigned short uint16_t;
typedef signed   short sint16_t;

typedef unsigned int   uint32_t;
typedef signed   int   sint32_t;

// The standard defines nullptr_t to reside in the namespace std. Since we try to avoid using any
// functionality from the standard library, we introduce our own typedef.
typedef decltype(nullptr) nullptr_t;

template<bool Condition, typename ThenT, typename ElseT>
struct If
{
};

template<typename ThenT, typename ElseT>
struct If<true, ThenT, ElseT>
{
  typedef ThenT Value;
};

template<typename ThenT, typename ElseT>
struct If<false, ThenT, ElseT>
{
  typedef ElseT Value;
};


typedef If<sizeof(unsigned long) == 8, unsigned long, unsigned long long>::Value uint64_t;
typedef If<sizeof(unsigned long) == 8,          long,          long long>::Value sint64_t;
typedef If<sizeof(void*) == 4, uint32_t, uint64_t>::Value uword_t;
typedef If<sizeof(void*) == 4, sint32_t, sint64_t>::Value sword_t;


template<typename T>
constexpr T typeFunction(T t) { return t; }

/**
 * size_t should represent the type that the sizeof operator returns; this typedef expands
 * to precisely that
 */
typedef decltype(typeFunction(sizeof(char))) size_t;


#if defined(UNICODE) || defined(_UNICODE)
  typedef wchar_t char_t;
#  if !defined(TEXT)
#    define TEXT(s) L##s
#  endif
#else
  typedef char char_t;
#  if !defined(TEXT)
#    define TEXT(s) s
#  endif
#endif

typedef char achar_t;


static_assert(sizeof(byte_t)   == 1, "byte_t: wrong typedef");
static_assert(sizeof(uint8_t)  == 1, "uint8_t: wrong typedef");
static_assert(sizeof(sint8_t)  == 1, "sint8_t: wrong typedef");
static_assert(sizeof(uint16_t) == 2, "uint16_t: wrong typedef");
static_assert(sizeof(sint16_t) == 2, "sint16_t: wrong typedef");
static_assert(sizeof(uint32_t) == 4, "uint32_t: wrong typedef");
static_assert(sizeof(sint32_t) == 4, "sint32_t: wrong typedef");
static_assert(sizeof(uint64_t) == 8, "uint64_t: wrong typedef");
static_assert(sizeof(sint64_t) == 8, "sint64_t: wrong typedef");

static_assert(sizeof(size_t) == sizeof(unsigned int) ||
              sizeof(size_t) == sizeof(unsigned long), "size_t: wrong typedef");


#endif
