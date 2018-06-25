// Piece.hpp

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

#ifndef TTRSPIECE_HPP
#define TTRSPIECE_HPP

#include "tetris/Color.hpp"
#include "tetris/renderer/Texture.hpp"


namespace ttrs
{
  class Renderer;


  /**
   * Objects of this class represent parts of a tetris stone with width and height of one unit.
   * @note pieces can be copied freely, however the StoneFactory should manage that for you
   * @see StoneFactory
   * @todo try factoring out Renderer and Texture as well
   */
  class Piece
  {
  public:
    Piece(Renderer& renderer, Texture* texture, Color const& color);

    // use compiler generated copy constructor and assignment operator

    void render(int x, int y) const;
    void render(int x, int y, Color const& overlay) const;

  private:
    Renderer* renderer_;
    Texture*  texture_;

    Color color_;
  };
}


#endif
