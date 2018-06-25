// AbstractStoneFactory.hpp

/***************************************************************************
 *   Copyright (C) 2013-2014 Daniel Mueller (deso@posteo.net)              *
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

#ifndef TTRSABSTRACTSTONEFACTORY_HPP
#define TTRSABSTRACTSTONEFACTORY_HPP

#include <cstdlib>

#include <util/Assert.hpp>
#include <container/Array.hpp>
#include <container/Pair.hpp>

#include "tetris/game/StoneTypeManager.hpp"


namespace ttrs
{
  /**
   * @todo I cannot think of a valid reason for the splitting between a factory and a type manager
   *       -- think about merging them
   * @todo think about accepting some randomizer object here (implementing some randomizer
   *       interface) for creating stones at random
   */
  template<typename StoneT>
  class AbstractStoneFactory
  {
  public:
    typedef ctr::Array<StoneT> StoneList;

    AbstractStoneFactory(StoneTypeManager const& type_manager);
    virtual ~AbstractStoneFactory();

    // use default copy and move constructor and copy and move assignment operator

    virtual StoneT createStone() const;
    virtual StoneT createStone(size_t index) const;

    virtual StoneList createAllStones() const;

  protected:
    virtual typename StoneT::Piece createPiece(size_t index) const = 0;

  private:
    StoneTypeManager const* type_manager_;

    StoneT createStoneFromType(StoneTypeManager::StoneType const& type, size_t index) const;
  };


  void randomize();
}


namespace ttrs
{
  /**
   * The constructor creates a new stone factory object.
   * @param type_manager
   */
  template<typename StoneT>
  AbstractStoneFactory<StoneT>::AbstractStoneFactory(StoneTypeManager const& type_manager)
    : type_manager_(&type_manager)
  {
    randomize();
  }

  /**
   * The destructor is virtual to provide correct behavior when deleting objects of derived classes.
   */
  template<typename StoneT>
  AbstractStoneFactory<StoneT>::~AbstractStoneFactory()
  {
  }

  /**
   * This method creates a new Stone with the given data.
   * @return new created stone
   */
  template<typename StoneT>
  StoneT AbstractStoneFactory<StoneT>::createStone() const
  {
    ASSERTOP(type_manager_->count(), gt, 0);

    size_t index = std::rand() % type_manager_->count();
    ASSERTOP(index, ge, 0);
    ASSERTOP(index, lt, type_manager_->count());

    return createStoneFromType(type_manager_->type(index), index);
  }

  /**
   * This method creates a new Stone with the given data.
   * @return new created stone
   */
  template<typename StoneT>
  StoneT AbstractStoneFactory<StoneT>::createStone(size_t index) const
  {
    ASSERTOP(type_manager_->count(), gt, 0);
    ASSERTOP(index, ge, 0);
    ASSERTOP(index, lt, type_manager_->count());

    return createStoneFromType(type_manager_->type(index), index);
  }

  /**
   * @return list of all stones creatable by this factory
   */
  template<typename StoneT>
  typename AbstractStoneFactory<StoneT>::StoneList
  AbstractStoneFactory<StoneT>::createAllStones() const
  {
    StoneList stones;

    for (size_t i = 0; i < type_manager_->count(); i++)
      ctr::append(stones, createStoneFromType(type_manager_->type(i), i));

    return stones;
  }

  /**
   * @param type stone type to create stone from
   * @param index index of stone type
   * @return stone created from the given stone type
   */
  template<typename StoneT>
  StoneT AbstractStoneFactory<StoneT>::createStoneFromType(StoneTypeManager::StoneType const& type, size_t index) const
  {
    typename StoneT::Pieces pieces(type.size());

    for (auto it = type.begin(); it != type.end(); ++it)
    {
      auto point = *it;
      auto piece = createPiece(index);

      ctr::append(pieces, ctr::makePair(point, piece));
    }
    return StoneT(pieces);
  }
}


#endif
