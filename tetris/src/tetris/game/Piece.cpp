// Piece.cpp

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

#include "tetris/renderer/Renderer.hpp"
#include "tetris/game/Piece.hpp"


namespace ttrs
{
  /**
   * The constructor creates a new piece object with the given color.
   * @param color color of the piece
   */
  Piece::Piece(Renderer& renderer, Texture* texture, Color const& color)
    : renderer_(&renderer),
      texture_(texture),
      color_(color)
  {
  }

  /**
   * @param x x coordinate to render the piece at
   * @param y y coordinate to render the piece at
   */
  void Piece::render(int x, int y) const
  {
    render(x, y, Color(0x00, 0x00, 0x00, 0x00));
  }

  /**
   *
   */
  void Piece::render(int x, int y, Color const& overlay) const
  {
    Texture const* texture = renderer_->setTexture(texture_);
    Color          color   = renderer_->setColor(color_ - overlay);

    renderer_->renderRectangle(Rectangle(x, y, x + 1, y + 1),
                               TextureRectangle(0.0f, 0.0f, 1.0f, 1.0f));

    renderer_->setColor(color);
    renderer_->setTexture(texture);
  }
}
