// Margin.hpp

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

#ifndef GUIMARGIN_HPP
#define GUIMARGIN_HPP

#include "Config.hpp"


namespace gui
{
  /**
   *
   */
  struct LIBGUI_EXPORT Margin
  {
    int left;
    int right;
    int bottom;
    int top;

    Margin();
    Margin(int left, int right, int bottom, int top);
  };
}


namespace gui
{
  /**
   * The default constructor creates a margin object and initializes all members with 0.
   */
  inline Margin::Margin()
    : left(0),
      right(0),
      bottom(0),
      top(0)
  {
  }

  /**
   *
   */
  inline Margin::Margin(int left, int right, int bottom, int top)
    : left(left),
      right(right),
      bottom(bottom),
      top(top)
  {
  }
}


#endif
