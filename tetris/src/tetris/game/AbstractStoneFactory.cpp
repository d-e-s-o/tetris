// AbstractStoneFactory.cpp

/***************************************************************************
 *   Copyright (C) 2013 Daniel Mueller (deso@posteo.net)                   *
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

#include <ctime>

#include "tetris/game/AbstractStoneFactory.hpp"


namespace ttrs
{
  namespace
  {
    /**
     * This class initializes the standard random number generator by calling std::srand with the
     * current time.
     */
    struct Randomizer
    {
      Randomizer()
      {
        std::srand(static_cast<unsigned int>(std::time(0)));
      }
    };
  }


  void randomize()
  {
    // initialize the random number generator
    static Randomizer randomizer;
  }
}
