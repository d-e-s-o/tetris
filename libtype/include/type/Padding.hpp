// Padding.hpp

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
 * This file contains macros for disabling padding features for data types on various compilers.
 */

#ifndef TYPPADDING_HPP
#define TYPPADDING_HPP


#if defined(BEGIN_DISABLE_PADDING)
#  undef BEGIN_DISABLE_PADDING
#endif

#if defined(END_DISABLE_PADDING)
#  undef END_DISABLE_PADDING
#endif


/**
 * Usage:
 * BEGIN_DISABLE_PADDING
 * struct Foo
 * {
 *   short bar;
 * } // no semicolon (important)
 * END_DISABLE_PADDING
 */
// GCC/G++ and SunStudio
#if defined(__GNUC__) || defined(__GNUG__) || defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#  define BEGIN_DISABLE_PADDING
#  define END_DISABLE_PADDING   __attribute__((packed));
// Microsoft Visual Studio
#elif defined(_MSC_VER)
#  define BEGIN_DISABLE_PADDING   #pragma pack (push, 1)
#  define END_DISABLE_PADDING   ; #pragma pack (pop)
#endif


#endif
