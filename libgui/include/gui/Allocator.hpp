// Allocator.hpp

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

#ifndef GUIALLOCATOR_HPP
#define GUIALLOCATOR_HPP

/**
 * If you want the library to use a custom allocator for any memory allocation you can set this
 * define to include a header file that defines an allocator template that conforms to the
 * standard c++ allocator interface
 * Within the header file there must be a typedef like CustomAllocator<int> Allocator within
 * namespace gui (where CustomAllocator stands for your template).
 * @see look below an example definition for the default allocator
 * @todo use ctr::Allocator here
 */
#ifdef LIBGUI_CUSTOM_ALLOCATOR_INCLUDE
#  include LIBGUI_CUSTOM_ALLOCATOR_INCLUDE
#else
#  include <memory>

namespace gui
{
  typedef std::allocator<int> Allocator;
}

#endif


#endif
