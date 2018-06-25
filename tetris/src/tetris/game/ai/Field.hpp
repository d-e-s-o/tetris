// Field.hpp

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

#ifndef TTRSAIFIELD_HPP
#define TTRSAIFIELD_HPP

#include "tetris/game/AbstractField.hpp"
#include "tetris/game/ai/Stone.hpp"


namespace ttrs
{
  namespace ai
  {
    /**
     *
     */
    class Field: public AbstractField<bool>
    {
    public:
      Field(dimension_t width, dimension_t height);
    };
  }
}


namespace ttrs
{
  namespace ai
  {
    /**
     * @copydoc AbstractField::AbstractField
     */
    inline Field::Field(dimension_t width, dimension_t height)
      : AbstractField<bool>(width, height)
    {
    }
  }
}


#endif
