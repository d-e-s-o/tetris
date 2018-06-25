// StoneTypeManager.hpp

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

#ifndef TTRSSTONETYPEMANAGER_HPP
#define TTRSSTONETYPEMANAGER_HPP

#include <container/Array.hpp>
#include <container/ArrayFunctions.hpp>

#include "tetris/game/Coordinates.hpp"


namespace ttrs
{
  /**
   * This class can be used to create StoneType objects. This objects are like templates for tetris
   * stones. They contain the positions of the different pieces relative to the lower left edge of
   * the stone.
   */
  class StoneTypeManager
  {
  public:
    typedef ctr::Array<Coordinates> StoneType;
    typedef ctr::Array<StoneType>   StoneTypes;

    StoneTypeManager(bool register_default_stones = false);

    // use default copy and move constructor and copy and move assignment operator

    template<size_t N, size_t P>
    void registerTemplates(coordinate_t const (&templates)[N][P][2]);

    StoneType const& type(size_t index) const;
    size_t count() const;

  private:
    StoneTypes stone_types_;
  };
}


namespace ttrs
{
  /**
   * This method can be used to register new stone templates.
   * @param templates
   * @todo describe what a stone template looks like
   */
  template<size_t N, size_t P>
  void StoneTypeManager::registerTemplates(coordinate_t const (&templates)[N][P][2])
  {
    size_t stones = N;
    size_t pieces = P;

    for (size_t stone = 0; stone < stones; stone++)
    {
      StoneType stone_type;

      for (size_t piece = 0; piece < pieces; piece++)
      {
        coordinate_t x = templates[stone][piece][0];
        coordinate_t y = templates[stone][piece][1];

        ctr::append(stone_type, Coordinates(x, y));
      }

      ctr::append(stone_types_, stone_type);
    }
  }
}


#endif
