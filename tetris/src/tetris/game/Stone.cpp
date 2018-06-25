// Stone.cpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#include <container/ArrayFunctions.hpp>

#include "tetris/game/ai/Stone.hpp"
#include "tetris/game/Piece.hpp"
#include "tetris/game/Stone.hpp"


namespace ttrs
{
  /**
   * The constructor creates a new stone at the given coordinates.
   * @param pieces pieces of the stone
   */
  Stone::Stone(Pieces const& pieces)
    : AbstractStone<ttrs::Piece const*>(pieces)
  {
  }

  /**
   * This method renders all pieces the stone has.
   */
  void Stone::render() const
  {
    for (auto it = begin(); it != end(); ++it)
      it->second->render(it->first.x, it->first.y);
  }

  /**
   * @return
   */
  ai::Stone Stone::convert() const
  {
    ai::Stone::Pieces pieces(count());

    for (auto it = begin(); it != end(); ++it)
      ctr::append(pieces, ctr::makePair(it->first, true));

    return ai::Stone(pieces);
  }
}
