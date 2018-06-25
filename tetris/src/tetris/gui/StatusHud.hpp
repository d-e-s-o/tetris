// StatusHud.hpp

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

#ifndef TTRSSTATUSHUD_HPP
#define TTRSSTATUSHUD_HPP

#include "tetris/Status.hpp"


namespace ttrs
{
  class Hud;


  /**
   * This class implements the StatusInterface for the HUD that is used by the game.
   * @note we could also inherit Hud directly from Status, this would make this class obsolete,
   *       however I dont like multi-inheritance and so this is the way to go
   * @see Status
   */
  class StatusHud: public Status
  {
  public:
    StatusHud(Hud& hud);

    virtual void setLevel(int level);
    virtual void setPoints(int points);
    virtual void setLines(int lines);

  private:
    Hud* hud_;
  };
}


#endif
