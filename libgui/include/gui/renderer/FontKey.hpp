// FontKey.hpp

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

#ifndef GUIFONTKEY_HPP
#define GUIFONTKEY_HPP

#include "gui/Config.hpp"
#include "gui/String.hpp"
#include "gui/Size.hpp"


namespace gui
{
  struct LIBGUI_EXPORT FontKey
  {
    String name;
    SizeT  size;

    FontKey();
    FontKey(String const& name, SizeT size);
  };

  //bool operator <(Color const& lhs, Color const& rhs);
  bool operator <(FontKey const& lhs, FontKey const& rhs);
}


namespace gui
{
  inline FontKey::FontKey()
    : name(TEXT("")),
      size(0)
  {
  }

  inline FontKey::FontKey(String const& name, SizeT size)
    : name(name),
      size(size)
  {
  }

  inline bool operator <(FontKey const& lhs, FontKey const& rhs)
  {
    return (lhs.name <  rhs.name) ||
           (lhs.name == rhs.name && lhs.size < rhs.size);
  }
}


#endif
