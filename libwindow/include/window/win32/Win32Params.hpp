// Win32Params.hpp

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

#ifndef WNDWIN32PARAMS_HPP
#define WNDWIN32PARAMS_HPP

#include "window/include/Windows.hpp"


namespace wnd
{
  /**
   * This structure is used to pass window creation styles to the implementation.
   */
  struct Win32Params
  {
    DWORD style_;
    DWORD style_ex_;

    explicit Win32Params(DWORD style = 0, DWORD style_ex = 0);
  };
}


namespace wnd
{
  /**
   * @param style style of the window
   * @param style_ex extended style of the window
   */
  inline Win32Params::Win32Params(DWORD style, DWORD style_ex)
    : style_(style),
      style_ex_(style_ex)
  {
  }
}


#endif
