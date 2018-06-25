// Stone.hpp

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

#ifndef TTRSAISTONE_HPP
#define TTRSAISTONE_HPP

#include "tetris/game/AbstractStone.hpp"
#include "tetris/game/ai/Orientation.hpp"


namespace ttrs
{
  namespace ai
  {
    /**
     * @todo think about incorporating Action here as well
     */
    class Stone: public AbstractStone<bool>
    {
    public:
      Stone(Pieces const& pieces);

      virtual void rotateLeft();
      virtual void rotateRight();

      Orientation orientation() const;

    private:
      Orientation orientation_;
    };
  }
}


namespace ttrs
{
  namespace ai
  {
    /**
     * @copydoc AbstractStone::AbstractStone
     */
    inline Stone::Stone(Pieces const& pieces)
      : AbstractStone<bool>(pieces),
        orientation_(Orientation::ROTATED_0)
    {
    }

    /**
     * @copydoc AbstractStone::rotateLeft
     */
    inline void Stone::rotateLeft()
    {
      orientation_ = ai::rotateLeft(orientation_);
      AbstractStone<bool>::rotateLeft();
    }

    /**
     * @copydoc AbstractStone::rotateRight
     */
    inline void Stone::rotateRight()
    {
      orientation_ = ai::rotateRight(orientation_);
      AbstractStone<bool>::rotateRight();
    }

    /**
     * @return current orientation of the stone
     */
    inline Orientation Stone::orientation() const
    {
      return orientation_;
    }
  }
}


#endif
