// AbstractField.hpp

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

#ifndef TTRSABSTRACTFIELD_HPP
#define TTRSABSTRACTFIELD_HPP

#include <util/Assert.hpp>
#include <util/Algorithm.hpp>
#include <container/Array.hpp>

#include "tetris/game/Coordinate.hpp"
#include "tetris/game/Dimension.hpp"


namespace ttrs
{
  /**
   * This type defines the basic interface of all Tetris fields. A field in that sense is a
   * rectangular area of Tetris pieces.
   * @param PieceT a default initializable type representing a Tetris piece in this field
   */
  template<typename PieceT>
  class AbstractField
  {
  private:
    template<typename PieceU, typename FieldT>
    class ProxyImpl
    {
    public:
      ProxyImpl(FieldT& field, coordinate_t x);

      PieceU& operator[](coordinate_t y);

    private:
      FieldT&      field_;
      coordinate_t x_;
    };

  public:
    typedef ProxyImpl<PieceT,       AbstractField>       Proxy;
    typedef ProxyImpl<PieceT const, AbstractField const> ConstProxy;

    AbstractField(dimension_t width, dimension_t height);
    virtual ~AbstractField();

    bool lineComplete(coordinate_t line) const;
    void clearLine(coordinate_t line);

    Proxy      operator[](coordinate_t x);
    ConstProxy operator[](coordinate_t x) const;

    dimension_t width() const;
    dimension_t height() const;

  private:
    typedef ctr::Array<PieceT> Pieces;

  protected:
    typedef typename Pieces::ConstIterator ConstIterator;

    ConstIterator begin() const;
    ConstIterator end() const;

  private:
    dimension_t width_;
    dimension_t height_;

    Pieces pieces_;

    PieceT&       at(coordinate_t x, coordinate_t y);
    PieceT const& at(coordinate_t x, coordinate_t y) const;
  };
}


namespace ttrs
{
  /**
   * @param field field this proxy class works on
   * @param x x coordinate of interest
   */
  template<typename PieceT>
  template<typename PieceU, typename FieldT>
  AbstractField<PieceT>::ProxyImpl<PieceU, FieldT>::ProxyImpl(FieldT& field, coordinate_t x)
    : field_(field),
      x_(x)
  {
  }

  /**
   * @param y y coordinate of interest
   * @return piece at the position formed by the x (supplied during construction) and y coordinate
   *         (supplied right here)
   */
  template<typename PieceT>
  template<typename PieceU, typename FieldT>
  PieceU& AbstractField<PieceT>::ProxyImpl<PieceU, FieldT>::operator[](coordinate_t y)
  {
    return field_.at(x_, y);
  }

  /**
   * @param width width of the field
   * @param height height of the field
   */
  template<typename PieceT>
  AbstractField<PieceT>::AbstractField(dimension_t width, dimension_t height)
    : width_(width),
      height_(height),
      pieces_(width * height)
  {
    pieces_.grow(width * height, PieceT());
  }

  /**
   * The destructor is virtual to provide correct behavior when deleting objects of derived classes.
   */
  template<typename PieceT>
  AbstractField<PieceT>::~AbstractField()
  {
  }

  /**
   * @param line y value of line to clear
   * @return true if the given line is complete, false if not
   */
  template<typename PieceT>
  bool AbstractField<PieceT>::lineComplete(coordinate_t line) const
  {
    ASSERTOP(line, ge, 0);
    ASSERTOP(line, lt, height());

    auto line_begin = pieces_.begin() + width() * line;
    auto line_end   = pieces_.begin() + width() * (line + 1);

    // if we can find a an empty piece the line is not complete
    return utl::find(line_begin, line_end, PieceT()) == line_end;
  }

  /**
   * @param line y value of line to clear
   */
  template<typename PieceT>
  void AbstractField<PieceT>::clearLine(coordinate_t line)
  {
    ASSERTOP(line, ge, 0);
    ASSERTOP(line, lt, height());

    auto line_begin = pieces_.begin() + width() * line;
    auto line_end   = pieces_.begin() + width() * (line + 1);
    auto end        = pieces_.begin() + width() * height();

    auto move = [](PieceT& piece)
    {
      auto copy = piece;
      piece = PieceT();
      return copy;
    };

    // we move every piece one line down
    utl::transform(line_end, end, line_begin, move);
  }

  /**
   * @param x
   */
  template<typename PieceT>
  typename AbstractField<PieceT>::Proxy
  AbstractField<PieceT>::operator[](coordinate_t x)
  {
    return Proxy(*this, x);
  }

  /**
   * @param x
   */
  template<typename PieceT>
  typename AbstractField<PieceT>::ConstProxy
  AbstractField<PieceT>::operator[](coordinate_t x) const
  {
    return ConstProxy(*this, x);
  }

  /**
   * @return width of the field
   */
  template<typename PieceT>
  dimension_t AbstractField<PieceT>::width() const
  {
    return width_;
  }

  /**
   * @return height of the field
   */
  template<typename PieceT>
  dimension_t AbstractField<PieceT>::height() const
  {
    return height_;
  }

  /**
   * @return
   */
  template<typename PieceT>
  typename AbstractField<PieceT>::ConstIterator AbstractField<PieceT>::begin() const
  {
    return pieces_.begin();
  }

  /**
   * @return
   */
  template<typename PieceT>
  typename AbstractField<PieceT>::ConstIterator AbstractField<PieceT>::end() const
  {
    return pieces_.end();
  }

  /**
   * @param x
   * @param y
   * @return
   */
  template<typename PieceT>
  PieceT& AbstractField<PieceT>::at(coordinate_t x, coordinate_t y)
  {
    return const_cast<PieceT&>(static_cast<AbstractField const*>(this)->at(x, y));
  }

  /**
   * @param x
   * @param y
   * @return
   */
  template<typename PieceT>
  PieceT const& AbstractField<PieceT>::at(coordinate_t x, coordinate_t y) const
  {
    ASSERTOP(x, ge, 0);
    ASSERTOP(x, lt, width_);
    ASSERTOP(y, ge, 0);
    ASSERTOP(y, lt, height_);

    return pieces_[y * width_ + x];
  }
}


#endif
