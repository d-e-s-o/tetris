// Status.hpp

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

#ifndef TTRSSTATUS_HPP
#define TTRSSTATUS_HPP


namespace ttrs
{
  /**
   * This class defines the interface for objects that keep track of the current game status,
   * namely the level, points and cleared lines of the player. It will get passed directly to the
   * game which will call the appropiate methods if a change occurs.
   * It acts like a view (from the Model-View[-Control] model), though there may only be one.
   * @todo rename this to Score? Maybe rename Score to ScoreCalculator or something like that before
   */
  class Status
  {
  public:
    virtual void setLevel(int level) = 0;
    virtual void setPoints(int points) = 0;
    virtual void setLines(int lines) = 0;
  };
}


#endif
