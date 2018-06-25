// GameField.hpp

/***************************************************************************
 *   Copyright (C) 2006-2014 Daniel Mueller (deso@posteo.net)              *
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

#ifndef TTRSGAMEFIELD_HPP
#define TTRSGAMEFIELD_HPP

#include <pointer/UniquePointer.hpp>

#include "tetris/game/Coordinate.hpp"
#include "tetris/game/Dimension.hpp"
#include "tetris/game/Stone.hpp"
#include "tetris/game/StoneFactory.hpp"
#include "tetris/game/PieceField.hpp"
#include "tetris/renderer/Texture.hpp"


namespace ttrs
{
  class Renderer;
  class Piece;
  class AI;


  /**
   * This class is used for communication between GameField, Game, and Stones. It provides all the
   * function required by the GameField but provided by the Stones and the Game.
   * @todo replace this class by something more generic like a messaging bus
   */
  class FieldDataManager
  {
  public:
    /**
     * This method is called to retrieve the next stone to control.
     * @return a new stone
     */
    virtual Stone popStone() = 0;

    /**
     * @return
     */
    virtual StoneFactory::StoneList allStones() = 0;

    /**
     * This method is called when one or more lines were cleared.
     * @param lines number of cleared lines
     */
    virtual void addLines(int lines) = 0;

    /**
     * This method will be called when the game has ended.
     */
    virtual void endGame() = 0;
  };


  /**
   * This class represents the tetris field with all dropped pieces including the walls.
   */
  class GameField
  {
  public:
    GameField(Renderer& renderer, Texture* wall, Texture* back,
              coordinate_t x, coordinate_t y,
              dimension_t w, dimension_t h,
              FieldDataManager& data_manager);
    ~GameField();

    void render() const;
    void update(float time, float movement);

    void dropStone();
    void moveStoneDown();
    void moveStoneLeft();
    void moveStoneRight();
    void rotateStoneLeft();
    void rotateStoneRight();

    dimension_t width() const;
    dimension_t height() const;

    bool plays() const;
    void play(bool play);

    static int calculateFieldWidth(int inner_width);
    static int calculateFieldHeight(int inner_height);

  private:
    typedef ptr::UniquePointer<AI> AIPtr;

    static int const WALL_WIDTH;

    coordinate_t x_;
    coordinate_t y_;

    bool  clearing_;
    float clear_time_;
    float movement_;

    FieldDataManager* data_manager_;

    Stone      stone_;
    PieceField piece_field_;

    AIPtr ai_;

    Renderer* renderer_;
    Texture*  back_;
    Texture*  wall_;

    GameField(GameField const&) = delete;
    GameField& operator =(GameField const&) = delete;

    coordinate_t innerX() const;
    coordinate_t innerY() const;

    void newStone();
    void resetStone();

    void moveToInitialPosition(Stone& stone) const;

    void updateActions();

    bool moveDown();
    bool moveSideways(bool left);
    bool rotate(bool left);

    bool merge(Stone const& stone);

    void renderPieces() const;
    void renderWalls() const;
    void renderBack() const;
  };
}


namespace ttrs
{
  /**
   * @return width of the field in pieces
   */
  inline dimension_t GameField::width() const
  {
    return piece_field_.width() + 2 * WALL_WIDTH;
  }

  /**
   * @return height of the field in pieces
   */
  inline dimension_t GameField::height() const
  {
    return piece_field_.height() + WALL_WIDTH;
  }

  /**
   * @return x coordinate of the inner field, that is the field without the walls
   */
  inline coordinate_t GameField::innerX() const
  {
    return x_ + WALL_WIDTH;
  }

  /**
   * @return y coordinate of the inner field, that is the field without the walls
   */
  inline coordinate_t GameField::innerY() const
  {
    return y_ + WALL_WIDTH;
  }

  /**
   *
   */
  inline dimension_t GameField::calculateFieldWidth(int inner_width)
  {
    return inner_width + 2 * WALL_WIDTH;
  }

  /**
   *
   */
  inline dimension_t GameField::calculateFieldHeight(int inner_height)
  {
    return inner_height + WALL_WIDTH;
  }
}


#endif
