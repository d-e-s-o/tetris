// GameField.cpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#include <stdexcept>
#include <util/Assert.hpp>

#include "tetris/ColorFunctions.hpp"
#include "tetris/renderer/Renderer.hpp"
#include "tetris/game/ai/Action.hpp"
#include "tetris/game/ai/StoneDropper.hpp"
#include "tetris/game/FieldFunctions.hpp"
#include "tetris/game/GameField.hpp"


namespace ttrs
{
  namespace
  {
    float const CLEAR_TIME = 0.2f;
  }


  /**
   * This class represents the auto player.
   */
  class AI
  {
  public:
    void update(ai::Field const& field, ai::StoneList const& stones);
    void play(Stone& stone, bool moveDown);

  private:
    ai::StoneDropper dropper_;
    ai::ActionList actions_;
  };


  /**
   * This constant defines the thickness of the walls of the field.
   */
  dimension_t const GameField::WALL_WIDTH = 1;


  /**
   * @param field the field we are working on
   * @param stones list of the upcoming stones
   */
  void AI::update(ai::Field const& field, ai::StoneList const& stones)
  {
    actions_ = dropper_.search(field, stones);
  }

  /**
   * @param stone stone to move
   * @param moveDown true if an auto move down did just happen
   */
  void AI::play(Stone& stone, bool movedDown)
  {
    if (movedDown)
    {
      if (actions_.size() > 0 && actions_[0] == ai::Action::MOVE_DOWN)
        ctr::remove(actions_, 0, 1);
    }

    while (actions_.size() > 0)
    {
      ai::Action action = actions_[0];

      if (action != ai::Action::MERGE &&
          action != ai::Action::MOVE_DOWN)
      {
        ctr::remove(actions_, 0, 1);

        if (action != ai::Action::NONE)
        {
          perform(action, stone);
          continue;
        }
      }
      break;
    }
  }


  /**
   * @param renderer
   * @param wall
   * @param back
   * @param x x position of the field (including walls)
   * @param y y position of the field (including walls)
   * @param w width of the field in pieces (excluding walls)
   * @param h height of the field in pieces (excluding walls)
   * @param data_manager
   */
  GameField::GameField(Renderer& renderer, Texture* wall, Texture* back,
                       coordinate_t x, coordinate_t y,
                       dimension_t w, dimension_t h,
                       FieldDataManager& data_manager)
    : x_(x),
      y_(y),
      clearing_(false),
      clear_time_(0.0f),
      movement_(0.0f),
      data_manager_(&data_manager),
      stone_(data_manager_->popStone()),
      piece_field_(w, h),
      ai_(nullptr),
      renderer_(&renderer),
      back_(back),
      wall_(wall)
  {
    /**
     * @todo remove usage of std::runtime_error
     */
    if (w < 1 || h < 1)
      throw std::runtime_error("Invalid field size");

    resetStone();
  }

  /**
   *
   */
  GameField::~GameField()
  {
  }

  /**
   * This method renders the tetris field by rendering the dropped pieces, the walls and the
   * background.
   */
  void GameField::render() const
  {
    if (!clearing_)
    {
      Point point = renderer_->setOrigin(Point(innerX(), innerY()));
      stone_.render();
      renderer_->setOrigin(point);
    }

    renderPieces();
    renderWalls();
    renderBack();
  }

  /**
   * @param time time passed since last call to update
   * @param movement movement calculated from passed time and current level
   */
  void GameField::update(float time, float movement)
  {
    if (clearing_)
    {
      clear_time_ -= time;

      if (clear_time_ <= 0.0f)
      {
        clearing_ = false;
        data_manager_->addLines(clearLines(piece_field_, stone_));
        newStone();
      }
    }

    if (clearing_)
      return;

    if (plays())
      ai_->play(stone_, false);

    movement_ += movement;

    // if the movement hits one unit then the stone should be moved down; and movement is decreased
    // by one (it should not be reset to zero as this would be wrong because we would omit the slack
    // time)
    while (movement_ >= 1.0f)
    {
      bool moved = moveDown();

      if (plays())
        ai_->play(stone_, moved);

      movement_ -= 1.0f;
    }
  }

  /**
   * This method can be used to move the currently active stone down until it can no longer be
   * moved.
   */
  void GameField::dropStone()
  {
    if (clearing_ || plays())
      return;

    // move the stone down as long as no collision is detected
    while(moveDown())
    {
    }
    movement_ = 0.0f;
  }

  /**
   * This method can be used to move the currently active stone down by one unit.
   */
  void GameField::moveStoneDown()
  {
    if (clearing_ || plays())
      return;

    moveDown();
    movement_ = 0.0f;
  }

  /**
   * This method can be used to move the currently active stone left by one unit.
   */
  void GameField::moveStoneLeft()
  {
    if (clearing_ || plays())
      return;

    moveSideways(true);
  }

  /**
   * This method can be used to move the currently active stone right by one unit.
   */
  void GameField::moveStoneRight()
  {
    if (clearing_ || plays())
      return;

    moveSideways(false);
  }

  /**
   * This method can be used to rotate the currently active stone to the left, i.e.,
   * counter-clockwise.
   */
  void GameField::rotateStoneLeft()
  {
    if (clearing_ || plays())
      return;

    rotate(true);
  }

  /**
   * This method can be used to rotate the currently active stone to the right, i.e., clockwise.
   */
  void GameField::rotateStoneRight()
  {
    if (clearing_ || plays())
      return;

    rotate(false);
  }

  /**
   * @return true if the AI is enabled and playing, false otherwise
   */
  bool GameField::plays() const
  {
    return ai_ != nullptr;
  }

  /**
   * @param play true to enable the auto playing AI, false otherwise
   */
  void GameField::play(bool play)
  {
    if (play)
    {
      if (ai_ == nullptr)
      {
        ai_ = AIPtr(new AI());
        updateActions();
      }
    }
    else
    {
      if (ai_ != nullptr)
        ai_ = AIPtr(nullptr);
    }
  }

  /**
   * This method creates a new stone and places it at the initial position.
   */
  void GameField::newStone()
  {
    ASSERT(!clearing_);

    stone_ = data_manager_->popStone();

    resetStone();

    if (plays())
      updateActions();
  }

  /**
   * This method puts the active stone to the default position on the field centered on the
   * highest point. If there is already another stone located the game is over.
   */
  void GameField::resetStone()
  {
    ASSERT(!clearing_);

    moveToInitialPosition(stone_);

    // if the new stone hits another as he is moved to the position the game is over
    if (stone_.collidesWith(piece_field_))
      data_manager_->endGame();
  }

  /**
   * @param stone stone to move
   */
  void GameField::moveToInitialPosition(Stone& stone) const
  {
    coordinate_t x = piece_field_.width() / 2 - stone.width() / 2;
    coordinate_t y = piece_field_.height()    - stone.height();

    stone.moveTo(x, y);
  }

  /**
   * This method updates the next actions to execute in case the AI is enabled.
   */
  void GameField::updateActions()
  {
    ai::StoneList stones(2);
    ctr::append(stones, stone_.convert());

    Stone stone = data_manager_->allStones()[0];
    moveToInitialPosition(stone);
    ctr::append(stones, stone.convert());

    ai_->update(piece_field_.convert(), stones);
  }

  /**
   * This method moves the active stone down (one unit). It also checks for collision and only
   * actually do something if there is none.
   * @return true if the stone was moved down, false if not
   */
  bool GameField::moveDown()
  {
    ASSERT(!clearing_);

    stone_.moveDown();

    // @todo collision check is actually performed twice, once here and one for the merge -- fix
    //       this!
    if (stone_.collidesWith(piece_field_))
    {
      // if it collided then move it up
      stone_.moveBy(0, 1);

      if (merge(stone_))
      {
        clear_time_ = CLEAR_TIME;
        clearing_   = true;
      }
      else
        newStone();

      return false;
    }
    return true;
  }

  /**
   * This method moves the active stone to the left or the right. It will also check for collision
   * and only actually do something if there is none.
   * @param left true to move the stone left, false to move it right
   * @return true if the stone was moved, false if not
   */
  bool GameField::moveSideways(bool left)
  {
    ASSERT(!clearing_);

    stone_.moveBy(left ? -1 : 1, 0);

    if (stone_.collidesWith(piece_field_))
    {
      stone_.moveBy(left ? 1 : -1, 0);
      return false;
    }
    return true;
  }

  /**
   * This method rotates the active stone left or right. The rotation will work only, if it does
   * collide with another stone/piece after rotation.
   * @param left true to rotate the stone left, false for right
   * @return true if the stone was rotated, false if not
   */
  bool GameField::rotate(bool left)
  {
    ASSERT(!clearing_);

    left ? stone_.rotateLeft() : stone_.rotateRight();

    if (stone_.collidesWith(piece_field_))
    {
      left ? stone_.rotateRight() : stone_.rotateLeft();
      return false;
    }
    return true;
  }

  /**
   * This method merges the pieces of the given stone with the field.
   * @param[in] stone the stone to merge with the field
   * @return true if the merged stone created new complete lines, false otherwise
   */
  bool GameField::merge(Stone const& stone)
  {
    ASSERT(!clearing_);

    stone.mergeWith(piece_field_);
    return linesComplete(piece_field_, stone);
  }

  /**
   * This method renders all dropped pieces.
   */
  inline void GameField::renderPieces() const
  {
    Point point = renderer_->setOrigin(Point(innerX(), innerY()));
    piece_field_.render(clearing_, clear_time_ / CLEAR_TIME);
    renderer_->setOrigin(point);
  }

  /**
   * This method renders the walls of the field.
   */
  inline void GameField::renderWalls() const
  {
    Rectangle left;
    left.x1_ = x_;
    left.y1_ = y_;
    left.x2_ = innerX();
    left.y2_ = innerY() + piece_field_.height();

    Rectangle bottom;
    bottom.x1_ = innerX();
    bottom.y1_ = y_;
    bottom.x2_ = innerX() + piece_field_.width();
    bottom.y2_ = innerY();

    Rectangle right;
    right.x1_ = innerX() + piece_field_.width();
    right.y1_ = y_;
    right.x2_ = x_ + width();
    right.y2_ = y_ + height();

    // @todo make the color somehow configurable
    Texture const* texture = renderer_->setTexture(wall_);
    Color          color   = renderer_->setColor(orange());

    renderer_->renderRectangle(left,   TextureRectangle(left));
    renderer_->renderRectangle(bottom, TextureRectangle(bottom));
    renderer_->renderRectangle(right,  TextureRectangle(right));

    renderer_->setColor(color);
    renderer_->setTexture(texture);
  }

  /**
   * This method renders the background of the field and draws vertical lines.
   */
  inline void GameField::renderBack() const
  {
    Point point = renderer_->setOrigin(Point(innerX(), innerY()));

    // draw the raster in the background (vertical lines)
    Color dark;
    dark.setRed(Color::max());
    dark.setGreen(Color::max());
    dark.setBlue(Color::max());
    dark.setAlpha(Color::max() / 5);

    Texture const* texture = renderer_->setTexture(0);
    Color          color   = renderer_->setColor(dark);

    for (coordinate_t i = 1; i < piece_field_.width(); ++i)
      renderer_->renderLine(Point(i, 0), Point(i, piece_field_.height()));

    renderer_->setColor(color);
    renderer_->setTexture(texture);

    // @todo make the color somehow configurable
    texture = renderer_->setTexture(back_);
    color   = renderer_->setColor(white());

    renderer_->renderRectangle(Rectangle(0, 0, piece_field_.width(), piece_field_.height()),
                               TextureRectangle(0.0f, 0.0f, 1.0f, 1.0f));

    renderer_->setColor(color);
    renderer_->setTexture(texture);
    renderer_->setOrigin(point);
  }
}
