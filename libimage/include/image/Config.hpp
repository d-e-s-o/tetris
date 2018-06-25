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

#ifndef IMGCONFIG_HPP
#define IMGCONFIG_HPP

#include <type/Types.hpp>


#if defined(WIN32) || defined(__WIN32__) || defined(_WIN32)
#  ifdef LIBIMAGE_BUILD_DLL
#    define LIBIMAGE_EXPORT __declspec(dllexport)
#  elif  LIBIMAGE_USE_DLL
#    define LIBIMAGE_EXPORT __declspec(dllimport)
#  else
#    define LIBIMAGE_EXPORT
#  endif
#else
#  define LIBIMAGE_EXPORT
#endif


#endif
