// StoneFactory.hpp

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

#ifndef TESTSTONEFACTORY_HPP
#define TESTSTONEFACTORY_HPP

#include <tetris/game/Coordinate.hpp>
#include <tetris/game/StoneTypeManager.hpp>
#include <tetris/game/AbstractStoneFactory.hpp>


namespace test
{
  static size_t const STONE_1_SINGLE   = 0;
  static size_t const STONE_2_LINE     = 1;
  static size_t const STONE_2_DIAGONAL = 2;
  static size_t const STONE_4_BLOCK    = 3;
  static size_t const STONE_4_LINE     = 4;
  static size_t const STONE_4_TRIANGLE = 5;


  /**
   * Our stone type manager that has a fixed set of available stone types.
   */
  class StoneTypeManager: public ttrs::StoneTypeManager
  {
  public:
    StoneTypeManager();
  };


  /**
   *
   */
  template<typename StoneT>
  class StoneFactory: public ttrs::AbstractStoneFactory<StoneT>
  {
  public:
    StoneFactory(StoneTypeManager const& type_manager);

    StoneT createAndMoveStone(size_t index, ttrs::coordinate_t x, ttrs::coordinate_t y) const;

  protected:
    virtual typename StoneT::Piece createPiece(size_t index) const;
  };
}


namespace test
{
  template<typename StoneT>
  StoneFactory<StoneT>::StoneFactory(StoneTypeManager const& type_manager)
    : ttrs::AbstractStoneFactory<StoneT>(type_manager)
  {
  }

  /**
   * @copydoc AbstractStoneFactory::createPiece
   */
  template<typename StoneT>
  typename StoneT::Piece StoneFactory<StoneT>::createPiece(size_t index) const
  {
    // a piece in our sense here is nothing more than a boolean, so there is no need for a fancy
    // construction of any kind
    return true;
  }

  /**
   * @param factory
   * @param index
   * @param x
   * @param y
   * @return
   */
  template<typename StoneT>
  StoneT StoneFactory<StoneT>::createAndMoveStone(size_t index, ttrs::coordinate_t x, ttrs::coordinate_t y) const
  {
    StoneT stone = this->createStone(index);
    stone.moveTo(x, y);
    return stone;
  }
}


#endif
