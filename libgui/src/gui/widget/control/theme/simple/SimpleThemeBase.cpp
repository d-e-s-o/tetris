// SimpleThemeBase.cpp

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

#include "gui/widget/control/theme/simple/SimpleThemeBase.hpp"


namespace gui
{
  /**
   * @copydoc Theme::actionButton
   */
  wnd::MouseButton SimpleThemeBase::actionButton() const
  {
    return wnd::MOUSE_BUTTON_LEFT;
  }

  /**
   * @copydoc Theme::menuButton
   */
  wnd::MouseButton SimpleThemeBase::menuButton() const
  {
    return wnd::MOUSE_BUTTON_RIGHT;
  }

  /**
   * @copydoc Theme::actionKey
   */
  wnd::Key SimpleThemeBase::actionKey() const
  {
    return wnd::KEY_SPACE;
  }

  /**
   * @copydoc Theme::leftKey
   */
  wnd::Key SimpleThemeBase::leftKey() const
  {
    return wnd::KEY_LEFT;
  }

  /**
   * @copydoc Theme::rightKey
   */
  wnd::Key SimpleThemeBase::rightKey() const
  {
    return wnd::KEY_RIGHT;
  }
}
