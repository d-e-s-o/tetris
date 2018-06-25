// AbstractStone.hpp

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

#ifndef TTRSABSTRACTSTONE_HPP
#define TTRSABSTRACTSTONE_HPP

#include <util/Assert.hpp>
#include <util/Point.hpp>
#include <util/Rectangle2.hpp>
#include <container/Array.hpp>
#include <container/Pair.hpp>

#include "tetris/game/Coordinates.hpp"
#include "tetris/game/Dimension.hpp"

namespace ttrs
{
  typedef utl::Point<float>    Center;
  typedef utl::Rectangle2<int> Bounds;


  /**
   * This type defines the basic interface of all Tetris stones. A stone in that sense is an entity
   * consisting of various smaller pieces at various positions that are moved and rotated as a
   * group.
   */
  template<typename PieceT>
  class AbstractStone
  {
  public:
    typedef PieceT                        Piece;
    typedef ctr::Pair<Coordinates, Piece> PiecePair;
    typedef ctr::Array<PiecePair>         Pieces;

    AbstractStone(Pieces const& pieces);
    virtual ~AbstractStone() = 0;

    virtual void moveBy(coordinate_t x, coordinate_t y);

    void moveTo(coordinate_t x, coordinate_t y);
    void moveDown();
    void moveLeft();
    void moveRight();

    virtual void rotateLeft();
    virtual void rotateRight();

    template<typename FieldT>
    bool collidesWith(FieldT const& field) const;

    template<typename FieldT>
    bool mergeWith(FieldT& field) const;

    coordinate_t x() const;
    coordinate_t y() const;

    dimension_t width() const;
    dimension_t height() const;

  protected:
    typedef typename Pieces::ConstIterator ConstIterator;

    ConstIterator begin() const;
    ConstIterator end() const;

    size_t count() const;

  private:
    Pieces pieces_;

    Bounds bounds() const;

    template<bool Left>
    void rotate();
  };


  Coordinates rotatePoint(Coordinates const& coordinates, Center const& center, bool left);
}


namespace ttrs
{
  /**
   * @param pieces
   */
  template<typename PieceT>
  AbstractStone<PieceT>::AbstractStone(Pieces const& pieces)
    : pieces_(pieces)
  {
    ASSERTOP(pieces_.size(), gt, 0);
  }

  /**
   *
   */
  template<typename PieceT>
  AbstractStone<PieceT>::~AbstractStone()
  {
  }

  /**
   * Move this stone by the given amount in x and y direction.
   * @param x
   * @param y
   */
  template<typename PieceT>
  void AbstractStone<PieceT>::moveBy(coordinate_t x, coordinate_t y)
  {
    for (auto it = pieces_.begin(); it != pieces_.end(); ++it)
    {
      it->first.x += x;
      it->first.y += y;
    }
  }

  /**
   * Move this stone to the given coordinates.
   * @param x
   * @param y
   */
  template<typename PieceT>
  void AbstractStone<PieceT>::moveTo(coordinate_t x, coordinate_t y)
  {
    moveBy(x - this->x(), y - this->y());
  }

  /**
   * Move this stone down by one unit.
   */
  template<typename PieceT>
  void AbstractStone<PieceT>::moveDown()
  {
    moveTo(x(), y() - 1);
  }

  /**
   * Move this stone left by one unit.
   */
  template<typename PieceT>
  void AbstractStone<PieceT>::moveLeft()
  {
    moveTo(x() - 1, y());
  }

  /**
   * Move this stone right by one unit.
   */
  template<typename PieceT>
  void AbstractStone<PieceT>::moveRight()
  {
    moveTo(x() + 1, y());
  }

  /**
   * Rotate this stone left by 90 degrees.
   */
  template<typename PieceT>
  void AbstractStone<PieceT>::rotateLeft()
  {
    rotate<true>();
  }

  /**
   * Rotate this stone right by 90 degrees.
   */
  template<typename PieceT>
  void AbstractStone<PieceT>::rotateRight()
  {
    rotate<false>();
  }

  /**
   * @param field field to check for collision with this stone
   * @return true if this stone collides with the given field
   * @note per definition a stone that is not within the given field collides with it
   */
  template<typename PieceT>
  template<typename FieldT>
  bool AbstractStone<PieceT>::collidesWith(FieldT const& field) const
  {
    for (auto it = pieces_.begin(); it != pieces_.end(); ++it)
    {
      coordinate_t x = it->first.x;
      coordinate_t y = it->first.y;

      if (!(0 <= x && x < field.width() && 0 <= y && y < field.height()))
        return true;

      if (field[x][y] != PieceT())
        return true;
    }
    return false;
  }

  /**
   * Merge this stone into the given field.
   * @param field field to merge this stone into
   * @return true if the merge did succeed, i.e., all pieces were located inside the given field and
   *         none of the positions was already occupied, false otherwise
   * @todo omit the collision check here
   */
  template<typename PieceT>
  template<typename FieldT>
  bool AbstractStone<PieceT>::mergeWith(FieldT& field) const
  {
    if (collidesWith(field))
      return false;

    for (auto it = pieces_.begin(); it != pieces_.end(); ++it)
    {
      coordinate_t x = it->first.x;
      coordinate_t y = it->first.y;

      ASSERTOP(x, ge, 0);
      ASSERTOP(x, lt, field.width());
      ASSERTOP(y, ge, 0);
      ASSERTOP(y, lt, field.height());
      ASSERTOP(field[x][y], eq, PieceT());

      field[x][y] = it->second;
    }
    return true;
  }

  /**
   * @return x coordinate of this stone
   */
  template<typename PieceT>
  coordinate_t AbstractStone<PieceT>::x() const
  {
    return bounds().x1_;
  }

  /**
   * @return y coordinate of this stone
   */
  template<typename PieceT>
  coordinate_t AbstractStone<PieceT>::y() const
  {
    return bounds().y1_;
  }

  /**
   * @return width of this stone
   */
  template<typename PieceT>
  dimension_t AbstractStone<PieceT>::width() const
  {
    Bounds const& b = bounds();
    return b.x2_ - b.x1_ + 1;
  }

  /**
   * @return height of this stone
   */
  template<typename PieceT>
  dimension_t AbstractStone<PieceT>::height() const
  {
    Bounds const& b = bounds();
    return b.y2_ - b.y1_ + 1;
  }

  /**
   * @return iterator pointing to first piece of the stone
   */
  template<typename PieceT>
  typename AbstractStone<PieceT>::ConstIterator AbstractStone<PieceT>::begin() const
  {
    return pieces_.begin();
  }

  /**
   * @return iterator pointing right behind the last valid piece of the stone
   */
  template<typename PieceT>
  typename AbstractStone<PieceT>::ConstIterator AbstractStone<PieceT>::end() const
  {
    return pieces_.end();
  }

  /**
   * @return number of pieces this stone is made of
   */
  template<typename PieceT>
  size_t AbstractStone<PieceT>::count() const
  {
    return pieces_.size();
  }

  /**
   * @return
   */
  template<typename PieceT>
  Bounds AbstractStone<PieceT>::bounds() const
  {
    ASSERTOP(pieces_.size(), gt, 0);

    Bounds bounds;
    bool   first = true;

    for (auto it = pieces_.begin(); it != pieces_.end(); ++it)
    {
      if (!first)
      {
        if (it->first.x < bounds.x1_)
          bounds.x1_ = it->first.x;

        if (it->first.x > bounds.x2_)
          bounds.x2_ = it->first.x;

        if (it->first.y < bounds.y1_)
          bounds.y1_ = it->first.y;

        if (it->first.y > bounds.y2_)
          bounds.y2_ = it->first.y;
      }
      else
      {
        bounds.x1_ = it->first.x;
        bounds.x2_ = it->first.x;
        bounds.y1_ = it->first.y;
        bounds.y2_ = it->first.y;
        first = false;
      }
    }
    return bounds;
  }

  template<typename PieceT>
  template<bool Left>
  void AbstractStone<PieceT>::rotate()
  {
    // do not ask me why center has such strange values...
    // and especially why they are different for left/right...
    // I DONT KNOW IT - I WENT CRAZY TRYING TO FIND IT OUT ;D;D
    float center_x;
    float center_y;

    dimension_t w = width();
    dimension_t h = height();

    if (Left)
    {
      center_x = 0.5f * w;
      center_y = 0.5f * h + (h % 2 == 0 ? 0.0f : 0.5f);
    }
    else
    {
      center_x = 0.5f * w + (w % 2 == 0 ? 0.5f : 0.0f);
      center_y = 0.5f * h;
    }

    // @todo for now we need to add a constant value here before we rotate -- this is necessary
    //       because the rotation code is somewhat broken for values close to zero -- fix this!
    Center center(x() + center_x + 10, y() + center_y + 10);

    for (auto it = pieces_.begin(); it != pieces_.end(); ++it)
    {
      it->first.x += 10;
      it->first.y += 10;

      it->first = rotatePoint(it->first, center, Left);

      it->first.x -= 10;
      it->first.y -= 10;
    }
  }
}


#endif
