// Game.hpp

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

#ifndef TTRSGAME_HPP
#define TTRSGAME_HPP

#include "tetris/game/Dimension.hpp"
#include "tetris/game/StoneFactory.hpp"
#include "tetris/game/GameField.hpp"
#include "tetris/game/Stones.hpp"
#include "tetris/game/Score.hpp"


namespace ttrs
{
  class Renderer;
  class Settings;
  class Status;
  class Game;


  /**
   * This class is used for communication between GameField, Game, and Stones.
   * @todo replace this class by something more generic like a messaging bus
   * @see FieldDataManager
   */
  class GameProxy: public FieldDataManager
  {
  public:
    GameProxy(Game& game, Stones& stones);

    virtual Stone popStone();
    virtual StoneFactory::StoneList allStones();

    virtual void addLines(int lines);
    virtual void endGame();

  private:
    Game*   game_;
    Stones* stones_;
  };


  /**
   * This represents the tetris game. It contains the field, the list of preview stones and the
   * currently active stone (the one which is controlled by the user) and is responsible for all
   * the logic involved into their interactions.
   */
  class Game
  {
  public:
    Game(Renderer& renderer, Settings& settings, Status& status);

    void render() const;
    void update(float time);

    void onMoveFastDown();
    void onMoveDown();
    void onMoveLeft();
    void onMoveRight();
    void onRotateLeft();
    void onRotateRight();

    dimension_t width() const;
    dimension_t height() const;

    bool paused() const;
    void pause(bool pause);

    bool plays() const;
    void play(bool play);

  private:
    friend class GameProxy;

    static int const LEFT_SPACE;
    static int const BOTTOM_SPACE;
    static int const RIGHT_SPACE;
    static int const TOP_SPACE;
    static int const PREVIEW_STONE_SPACE;

    StoneTypeManager type_manager_;
    StoneFactory     factory_;
    Stones           stones_;
    Score            score_;

    GameProxy game_proxy_;
    GameField game_field_;

    Status* status_;

    bool paused_;
    bool over_;

    Game(Game const&) = delete;
    Game& operator =(Game const&) = delete;

    void endGame();

    bool isRunning() const;

    void addLines(int lines);
    void updateStatus();
  };
}


#endif
