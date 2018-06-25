// StoneFactory.hpp

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

#ifndef TTRSSTONEFACTORY_HPP
#define TTRSSTONEFACTORY_HPP

#include <map>

#include "tetris/Color.hpp"
#include "tetris/renderer/Texture.hpp"
#include "tetris/game/Piece.hpp"
#include "tetris/game/Stone.hpp"
#include "tetris/game/AbstractStoneFactory.hpp"


namespace ttrs
{
  class Renderer;


  /**
   * This class can be used for creating new stones.
   * @note the factory keeps a pool of tetris pieces which are used by the created stones, due to
   *       that the factory needs to live at least as long as the last object accessing any of the
   *       stones or pieces
   * @note the factory uses a StoneTypeManager to get the "templates" for the stones to create, it
   *       does not own it, but keeps a reference to it - that means that this manager also have to
   *       live at least as long as the factory does
   */
  class StoneFactory: public AbstractStoneFactory<Stone>
  {
  public:
    StoneFactory(StoneTypeManager const& type_manager, Renderer& renderer, Texture* texture);

  protected:
    virtual Stone::Piece createPiece(size_t index) const;

  private:
    /**
     * @todo replace std::map and std::pair with ctr::Map and ctr::Tuple, respectively
     */
    typedef std::pair<Renderer const*, size_t> PieceKey;
    typedef std::map<PieceKey, Piece> PiecePool;

    Renderer* renderer_;
    Texture*  texture_;

    mutable PiecePool pool_;

    Color const& color(size_t index) const;
  };
}


#endif
