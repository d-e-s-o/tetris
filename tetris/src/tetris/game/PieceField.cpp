// PieceField.cpp

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

#include "tetris/game/ai/Field.hpp"
#include "tetris/game/Piece.hpp"
#include "tetris/game/PieceField.hpp"


namespace ttrs
{
  /**
   * @param w width of the field
   * @param h height of the field
   */
  PieceField::PieceField(dimension_t w, dimension_t h)
    : AbstractField<Piece const*>(w, h)
  {
  }

  /**
   * @param alpha_factor
   */
  void PieceField::render(bool clearing, float alpha_factor) const
  {
    coordinate_t x = 0;
    coordinate_t y = 0;

    bool complete = false;

    for (auto it = begin(); it != end(); ++it)
    {
      if (clearing && x == 0)
        complete = lineComplete(y);

      if (*it != 0)
      {
        if (!complete)
          (*it)->render(x, y);
        else
        {
          Color::ChannelType alpha = Color::max() - (Color::max() * alpha_factor);
          (*it)->render(x, y, Color(Color::min(), Color::min(), Color::min(), alpha));
        }
      }

      if (++x >= width())
      {
        ++y;
        x = 0;
      }
    }
  }

  /**
   * @return
   */
  ai::Field PieceField::convert() const
  {
    ai::Field field(width(), height());

    for (coordinate_t x = 0; x < width(); x++)
    {
      for (coordinate_t y = 0; y < height(); y++)
        field[x][y] = (*this)[x][y] != nullptr;
    }
    return field;
  }
}
