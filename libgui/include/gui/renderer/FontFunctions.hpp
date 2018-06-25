// FontFunctions.hpp

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

#ifndef GUIFONTFUNCTIONS_HPP
#define GUIFONTFUNCTIONS_HPP

#include "gui/Bounds.hpp"
#include "gui/String.hpp"
#include "gui/Alignment.hpp"


namespace gui
{
  class Font;


  PositionT getStringHPosition(Bounds const& bounds, Size const& size, HAlignment alignment);
  PositionT getStringVPosition(Bounds const& bounds, Size const& size, VAlignment alignment);

  Position getStringPosition(Font const& font,
                             Size const& size,
                             String const& string,
                             Alignment const& alignment);

  //Position getCaretPosition(Font const& font,
  //                          String const& string,
  //                          String::size_type index,
  //                          String const& caret);

  size_t getCaretIndex(Font const& font, String const& string, PositionT x);
}


#endif
