// StoneFactory.cpp

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

#include <type/Util.hpp>

#include "tetris/ColorFunctions.hpp"
#include "tetris/game/Stone.hpp"
#include "tetris/game/StoneFactory.hpp"


namespace ttrs
{
  /**
   * The constructor creates a new stone factory object.
   */
  StoneFactory::StoneFactory(StoneTypeManager const& type_manager, Renderer& renderer, Texture* texture)
    : AbstractStoneFactory<Stone>(type_manager),
      renderer_(&renderer),
      texture_(texture)
  {
  }

  /**
   * This method checks whether a piece associated with the two given values already exists in the
   * pool and returns it, if it does not exist it will be created.
   * @return piece associated with the given data
   */
  Stone::Piece StoneFactory::createPiece(size_t index) const
  {
    auto key = PieceKey(renderer_, index);
    auto it  = pool_.find(key);

    if (it != pool_.end())
      return &it->second;
    else
    {
      // @todo get rid of this std:: stuff!
      // @note for this to be replaced by ctr::Map we need it to be able to handle non default
      //       constructible objects -- as of now these are not supported and thus we cannot replace
      //       this
      auto result = pool_.insert(std::make_pair(key, Piece(*renderer_, texture_, color(index))));

      return &result.first->second;
    }
  }

  /**
   * @param value integer that is used to find a color
   * @return a color
   */
  Color const& StoneFactory::color(size_t index) const
  {
    static Color const colors[] =
    {
      red(),
      green(),
      yellow(),
      violet(),
      blue(),
      cyan(),
      gray()
    };
    return colors[index % typ::arraySize(colors)];
  }

  /**
   * @return true if the left pair is less the right one
   * @todo find out why std::map does not require this definition!
   */
  //inline bool operator <(std::pair<Renderer*, Color> const& lhs, std::pair<Renderer*, Color> const& rhs)
  //{
  //  return lhs.first <  rhs.first ||
  //         lhs.first == rhs.first && lhs.second < rhs.second;
  //}
}
