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

#ifndef GUICONFIG_HPP
#define GUICONFIG_HPP


/**
 * This file defines several symbols the library uses or offers for use:
 * - LIBGUI_WINDOWS will be defined if the library is compiled for MS Windows
 *   - if you are compiling the DLL you have to define LIBGUI_BUILD_DLL
 *   - if you are using the DLL define LIBGUI_USE_DLL
 * - LIBGUI_LINUX will be defined for Linux
 * - LIBGUI_UNKNOWN will be defined for other systems
 */

#include <type/Types.hpp>


#if defined(WIN32) || defined(__WIN32__) || defined(_WIN32)
#  define LIBGUI_WINDOWS
#  ifdef LIBGUI_BUILD_DLL
#    define LIBGUI_EXPORT __declspec(dllexport)
#  elif LIBGUI_USE_DLL
#    define LIBGUI_EXPORT __declspec(dllimport)
#  else
#    define LIBGUI_EXPORT
#  endif
#elif defined(linux) || defined(__linux) || defined(__linux__)
#  define LIBGUI_LINUX
#  define LIBGUI_EXPORT
#else
#  define LIBGUI_UNKNOWN
#  define LIBGUI_EXPORT
#endif


#endif
