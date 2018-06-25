// Game.cpp

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

#include <util/Assert.hpp>

#include "resource/Settings.hpp"
#include "tetris/Status.hpp"
#include "tetris/game/Resource.hpp"
#include "tetris/game/Game.hpp"
#include "tetris/renderer/Renderer.hpp"


namespace ttrs
{
  /**
   * Space between the left screen side and the field.
   */
  int const Game::LEFT_SPACE = 1;

  /**
   * Space between the bottom of the screen and the field.
   */
  int const Game::BOTTOM_SPACE = 1;

  /**
   * Space between the right side of the screen and the preview stones.
   */
  int const Game::RIGHT_SPACE = 1;

  /**
   * Space between the upper screen side and the field.
   */
  int const Game::TOP_SPACE = 1;

  /**
   * Space between the right side of the field and the preview stones.
   */
  int const Game::PREVIEW_STONE_SPACE = 1;


  /**
   * @param game
   * @param stones
   */
  GameProxy::GameProxy(Game& game, Stones& stones)
    : game_(&game),
      stones_(&stones)
  {
  }

  /**
   * @copydoc FieldDataManager::popStone
   */
  Stone GameProxy::popStone()
  {
    return stones_->pop();
  }

  /**
   * @copydoc FieldDataManager::allStones
   */
  StoneFactory::StoneList GameProxy::allStones()
  {
    return stones_->list();
  }

  /**
   * @copydoc FieldDataManager::addLines
   */
  void GameProxy::addLines(int lines)
  {
    game_->addLines(lines);
  }

  /**
   * @copydoc FieldDataManager::endGame
   */
  void GameProxy::endGame()
  {
    game_->endGame();
  }

  /**
   * The constructor creates all components of the game
   * at the correct places and starts a new game.
   * @param renderer
   * @param settings
   * @param status
   */
  Game::Game(Renderer& renderer, Settings& settings, Status& status)
    : type_manager_(true),
      factory_(type_manager_, renderer, renderer.createTexture(TETRIS_PIECE_TEXTURE)),
      stones_(factory_,
              LEFT_SPACE + GameField::calculateFieldWidth(settings.getFieldWidth()) + PREVIEW_STONE_SPACE,
              BOTTOM_SPACE + GameField::calculateFieldHeight(settings.getFieldHeight()),
              settings.getPreviewStoneCount()),
      score_(settings.getStartLevel(), settings.getLinesForLevel()),
      game_proxy_(*this, stones_),
      game_field_(renderer,
                  renderer.createTexture(TETRIS_FIELD_WALL_TEXTURE),
                  renderer.createTexture(TETRIS_FIELD_BACK_TEXTURE),
                  LEFT_SPACE,
                  BOTTOM_SPACE,
                  settings.getFieldWidth(),
                  settings.getFieldHeight(),
                  game_proxy_),
      status_(&status),
      paused_(false),
      over_(false)
  {
    if (settings.getAutoPlay())
      game_field_.play(true);

    updateStatus();
  }

  /**
   * This method renders the active stone, the preview stones and the field.
   */
  void Game::render() const
  {
    game_field_.render();
    stones_.render();
  }

  /**
   * @param time time elapsed since last update
   */
  void Game::update(float time)
  {
    if (isRunning())
    {
      // increase the movement by the movement speed given by the level relative to the time
      float speed = 1.0f + 0.2f * score_.level();

      game_field_.update(time, speed * time);
    }
  }

  /**
   * Call this method if the 'move fast down' event has occured - this will move the active stone
   * down until it collides with either another stone/piece or the bottom.
   */
  void Game::onMoveFastDown()
  {
    if (!isRunning())
      return;

    game_field_.dropStone();
  }

  /**
   * Call this method if the 'move down' event has occured - this will move the active stone one
   * unit down.
   */
  void Game::onMoveDown()
  {
    if (!isRunning())
      return;

    game_field_.moveStoneDown();
  }

  /**
   * Call this method if the 'move left' event has occured - this will move the active stone one
   * unit to the left.
   */
  void Game::onMoveLeft()
  {
    if (!isRunning())
      return;

    game_field_.moveStoneLeft();
  }

  /**
   * Call this method if the 'move right' event has occured - this will move the active stone one
   * unit to the right.
   */
  void Game::onMoveRight()
  {
    if (!isRunning())
      return;

    game_field_.moveStoneRight();
  }

  /**
   * Call this method if the 'rotate left' event has occured - this will rotate the active stone
   * to the left.
   */
  void Game::onRotateLeft()
  {
    if (!isRunning())
      return;

    game_field_.rotateStoneLeft();
  }

  /**
   * Call this method if the 'rotate right' event has occured - this will rotate the active stone
   * to the right.
   */
  void Game::onRotateRight()
  {
    if (!isRunning())
      return;

    game_field_.rotateStoneRight();
  }

  /**
   * @return width of the game (everything that represents it)
   */
  dimension_t Game::width() const
  {
    return LEFT_SPACE + game_field_.width() + stones_.width() + RIGHT_SPACE;
  }

  /**
   * @return height of the game (everything that represents it)
   */
  dimension_t Game::height() const
  {
    return BOTTOM_SPACE + std::max(game_field_.height(), stones_.height()) + TOP_SPACE;
  }

  /**
   * @return true if the game is currently paused, false if not
   */
  bool Game::paused() const
  {
    return paused_;
  }

  /**
   * This method pauses/unpauses the game.
   */
  void Game::pause(bool pause)
  {
    paused_ = pause;
  }

  /**
   * @return
   */
  bool Game::plays() const
  {
    return game_field_.plays();
  }

  /**
   *
   */
  void Game::play(bool play)
  {
    game_field_.play(play);
  }

  /**
   * This method stops the game and set game over.
   */
  void Game::endGame()
  {
    over_ = true;
  }

  /**
   * @return true if the game is still running (not paused and not over yet), false otherwise
   */
  bool Game::isRunning() const
  {
    return !paused_ && !over_;
  }

  /**
   * Call this method to add the given number of lines to the current count. This will do the
   * necessary point calculations and increase the level if needed. After that the status gets
   * updated.
   */
  void Game::addLines(int lines)
  {
    ASSERTOP(lines, gt, 0);

    score_.add(lines);
    updateStatus();
  }

  /**
   * This method updates the status object with the data from the game.
   */
  void Game::updateStatus()
  {
    status_->setLevel(score_.level());
    status_->setPoints(score_.points());
    status_->setLines(score_.lines());
  }
}
