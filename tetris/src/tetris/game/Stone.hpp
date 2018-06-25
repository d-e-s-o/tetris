// Stone.hpp

/***************************************************************************
 *   Copyright (C) 2006-2013 Daniel Mueller (deso@posteo.net)              *
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

#ifndef TTRSSTONE_HPP
#define TTRSSTONE_HPP

#include "tetris/game/AbstractStone.hpp"


namespace ttrs
{
  namespace ai
  {
    class Stone;
  }

  class Piece;


  /**
   * This class represents stones in a tetris game. An object of this class consists of various
   * pieces and coordinates them.
   * @note objects of this class are free copyable
   * @todo find out why we cannot make the tetris pieces have relative positions
   */
  class Stone: public AbstractStone<ttrs::Piece const*>
  {
  public:
    Stone(Pieces const& pieces);

    // use compiler generated copy constructor and assignment operator

    void render() const;

    ai::Stone convert() const;
  };
}


#endif
