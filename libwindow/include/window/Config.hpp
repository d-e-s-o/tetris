// Config.hpp

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

#ifndef WNDCONFIG_HPP
#define WNDCONFIG_HPP

#include <type/Types.hpp>


#if defined(WIN32) || defined(__WIN32__) || defined(_WIN32)
#  define LIBWINDOW_WINDOWS
#  ifdef LIBWINDOW_BUILD_DLL
#    define LIBWINDOW_EXPORT __declspec(dllexport)
#  elif  LIBWINDOW_USE_DLL
#    define LIBWINDOW_EXPORT __declspec(dllimport)
#  else
#    define LIBWINDOW_EXPORT
#  endif
#elif defined(linux) || defined(__linux) || defined(__linux__)
#  define LIBWINDOW_LINUX
#  define LIBWINDOW_EXPORT
#else
#  define LIBWINDOW_UNKNOWN
#  define LIBWINDOW_EXPORT
#endif


#endif
