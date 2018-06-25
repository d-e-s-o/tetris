// Stones.cpp

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

#include <container/QueueFunctions.hpp>

#include "tetris/game/StoneFactory.hpp"
#include "tetris/game/Stones.hpp"


namespace ttrs
{
  /**
   * The space between each stone in pieces.
   */
  coordinate_t const Stones::SPACE = 1;


  /**
   * The constructor creates a new object for preview stones. It will also add the given number
   * of stones to the list.
   * @param factory factory used for creating new stones
   * @param x x coordinate of upper left corner of the highest stone
   * @param y y coordinate of upper left corner of the highest stone
   * @param stones number of stones to create among each other
   */
  Stones::Stones(StoneFactory const& factory, coordinate_t x, coordinate_t y, int stones)
    : x_(x),
      y_(y),
      stones_(),
      factory_(&factory)
  {
    addNewStones(stones);
  }

  /**
   * This method renders all the stones in the list.
   */
  void Stones::render() const
  {
    for (auto it = stones_.begin(); it != stones_.end(); ++it)
      it->render();
  }

  /**
   * This method removes the first stone from the list and returns it. It will also append a new
   * one so that the stone count stays the same.
   * @return stone removed from top of the list
   */
  Stone Stones::pop()
  {
    addNewStones(1);

    Stone result = ctr::popFront(stones_);

    if (stones_.size() > 0)
    {
      // move all stones as much pieces up as the new first one needs to be equal to y_
      coordinate_t y_delta = y_ - (stones_[0].y() + stones_[0].height());

      for (auto it = stones_.begin(); it != stones_.end(); ++it)
        it->moveBy(0, y_delta);
    }
    return result;
  }

  /**
   * @return list of all stones to be popped next
   */
  StoneFactory::StoneList const& Stones::list() const
  {
    return stones_;
  }

  /**
   * @return width of the stones
   */
  dimension_t Stones::width() const
  {
    dimension_t w = 0;

    for (auto stone : stones_)
    {
      // @todo use max() function here when made publicly available
      if (stone.width() > w)
        w = stone.width();
    }
    return w;
  }

  /**
   * @return height of the stones
   */
  dimension_t Stones::height() const
  {
    dimension_t h = 0;

    for (auto stone : stones_)
    {
      // @todo use max() function here when made publicly available
      if (stone.height() > h)
        h = stone.height();
    }
    return static_cast<dimension_t>(stones_.size() * h * (SPACE - 1));
  }

  /**
   * This method adds (appends) the given number of stones to the list.
   * @param count number of stones to add
   */
  void Stones::addNewStones(int count)
  {
    coordinate_t y = stones_.size() > 0 ? stones_[stones_.size() - 1].y() - SPACE : y_;

    for ( ; count > 0; --count)
    {
      addNewStone(y);

      y = stones_[stones_.size() - 1].y() - SPACE;
    }
  }

  /**
   * This method adds a new stone to the list of stones.
   * @param top y value where the stone has to be created (upper left corner)
   */
  void Stones::addNewStone(int top)
  {
    Stone stone = factory_->createStone();
    stone.moveTo(x_, top - stone.height());

    ctr::pushBack(stones_, stone);
  }
}
