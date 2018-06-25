// Limits.hpp

/***************************************************************************
 *   Copyright (C) 2009 Daniel Mueller                                     *
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

/**
 * This file defines the minimum and maximum values of various integral types.
 */

#ifndef TYPLIMITS_HPP
#define TYPLIMITS_HPP


#ifndef CHAR_BIT
#  define CHAR_BIT      8
#endif

#ifndef SCHAR_MIN
#  define SCHAR_MIN     (-128)
#endif

#ifndef SCHAR_MAX
#  define SCHAR_MAX     127
#endif

#ifndef UCHAR_MIN
#  define UCHAR_MIN     0
#endif

#ifndef UCHAR_MAX
#  define UCHAR_MAX     255
#endif

#ifdef __CHAR_UNSIGNED__
#  ifndef CHAR_MIN
#    define CHAR_MIN    0
#  endif

#  ifndef CHAR_MAX
#    define CHAR_MAX    UCHAR_MAX
#  endif
#else
#  ifndef CHAR_MIN
#    define CHAR_MIN    SCHAR_MIN
#  endif

#  ifndef CHAR_MAX
#    define CHAR_MAX    SCHAR_MAX
#  endif
#endif

#ifndef SHRT_MIN
#  define SHRT_MIN      (-32768)
#endif

#ifndef SHRT_MAX
#  define SHRT_MAX      32767
#endif

#ifndef USHRT_MIN
#  define USHRT_MIN     0
#endif

#ifndef USHRT_MAX
#  define USHRT_MAX     65535
#endif

#ifndef INT_MIN
#  define INT_MIN       (-INT_MAX - 1)
#endif

#ifndef INT_MAX
#  define INT_MAX       2147483647
#endif

#ifndef UINT_MIN
#  define UINT_MIN      0
#endif

#ifndef UINT_MAX
#  define UINT_MAX      4294967295u
#endif

#ifndef LONG_MIN
#  define LONG_MIN      (-LONG_MAX - 1l)
#endif

#if defined(HAS_64_BIT_INTEGRAL_TYPE)
#  ifndef LONG_MAX
#    define LONG_MAX    9223372036854775807l
#  endif
#else
#  ifndef LONG_MAX
#    define LONG_MAX    2147483647l
#  endif
#endif

#ifndef ULONG_MIN
#  define ULONG_MIN     0
#endif

#if defined(__WORDSIZE) and __WORDSIZE == 64
#  ifndef ULONG_MAX
#    define ULONG_MAX   18446744073709551615ul
#  endif
#else
#  ifndef ULONG_MAX
#    define ULONG_MAX   4294967295ul
#  endif
#endif

#define BITS_PER_BYTE 8


namespace typ
{
  template<typename T>
  struct Limits
  {
  };

  template<>
  struct Limits<unsigned char>
  {
    static unsigned char const min = UCHAR_MIN;
    static unsigned char const max = UCHAR_MAX;
  };

  template<>
  struct Limits<signed char>
  {
    static signed char const min = SCHAR_MIN;
    static signed char const max = SCHAR_MAX;
  };

  template<>
  struct Limits<char>
  {
    static char const min = CHAR_MIN;
    static char const max = CHAR_MAX;
  };

  template<>
  struct Limits<unsigned short>
  {
    static unsigned short const min = USHRT_MIN;
    static unsigned short const max = USHRT_MAX;
  };

  template<>
  struct Limits<signed short>
  {
    static signed short const min = SHRT_MIN;
    static signed short const max = SHRT_MAX;
  };

  template<>
  struct Limits<unsigned int>
  {
    static unsigned int const min = UINT_MIN;
    static unsigned int const max = UINT_MAX;
  };

  template<>
  struct Limits<signed int>
  {
    static signed int const min = INT_MIN;
    static signed int const max = INT_MAX;
  };

  template<>
  struct Limits<unsigned long>
  {
    static unsigned long const min = ULONG_MIN;
    static unsigned long const max = ULONG_MAX;
  };

  template<>
  struct Limits<signed long>
  {
    static signed long const min = LONG_MIN;
    static signed long const max = LONG_MAX;
  };
}


#endif
