// Stone1.hpp

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

#ifndef TESTSTONE1_HPP
#define TESTSTONE1_HPP

#include <tetris/game/AbstractStone.hpp>


namespace test
{
  /**
   * A stone for our testing purposes here is nothing more than a collection of booleans, there is
   * no special piece type.
   */
  class Stone1: public ttrs::AbstractStone<bool>
  {
  public:
    Stone1(Pieces const& pieces);
  };
}


namespace test
{
  /**
   * @copydoc AbstractStone::AbstractStone
   */
  inline Stone1::Stone1(Pieces const& pieces)
    : ttrs::AbstractStone<bool>(pieces)
  {
  }
}


#endif
