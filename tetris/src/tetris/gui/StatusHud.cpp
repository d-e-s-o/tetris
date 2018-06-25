// StatusHud.cpp

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

#include "tetris/gui/Hud.hpp"
#include "tetris/gui/StatusHud.hpp"


namespace ttrs
{
  /**
   * @param hud
   */
  StatusHud::StatusHud(Hud& hud)
    : hud_(&hud)
  {
  }

  /**
   * @copydoc Status::setLevel
   */
  void StatusHud::setLevel(int level)
  {
    hud_->setLevel(level);
  }

  /**
   * @copydoc Status::setPoints
   */
  void StatusHud::setPoints(int points)
  {
    hud_->setPoints(points);
  }

  /**
   * @copydoc Status::setLines
   */
  void StatusHud::setLines(int lines)
  {
    hud_->setLines(lines);
  }
}
