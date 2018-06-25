// Config.hpp

/***************************************************************************
 *   Copyright (C) 2013-2014 Daniel Mueller                                *
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
 * This file provides defines identifying the compiler and target platform used.
 * @todo we likely want to provide different types of defines:
 *       compiler: GCC, GPP, CLANG, VISUALCPP, INTELCPP
 *       target machine word size: 16 bit, 32 bit, 64 bit, 128 bit
 *       target operating system: Linux, MS Windows, Solaris, ESX
 */

#ifndef TYPCONFIG_HPP
#define TYPCONFIG_HPP


#if defined(_MSC_VER)
#  define MS_VISUAL_CPP
#elif defined (__GNUC__)
#  define COMPILER_GCC
#else
#  error "Unknown compiler"
#endif


#if defined(__x86_64__)
#  define TARGET_64
#elif defined(__x86_32__)
#  define TARGET_32
#else
#  error "Unknown target"
#endif


#endif
