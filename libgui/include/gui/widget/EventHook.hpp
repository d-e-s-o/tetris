// EventHook.hpp

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

#ifndef GUIEVENTHOOK_HPP
#define GUIEVENTHOOK_HPP


namespace gui
{
  /*
   * Enumeration for the different hook types in RootWidget
   */
  enum EventHook
  {
    EVENT_HOOK_MIN,
    EVENT_HOOK_FOCUS,
    EVENT_HOOK_POSITION,
    EVENT_HOOK_ALL,
    EVENT_HOOK_MAX
  };
}


#endif
