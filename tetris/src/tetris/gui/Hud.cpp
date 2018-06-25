// Hud.cpp

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

#include <util/Rectangle1Functions.hpp>

#include <gui/util/LexicalCast.hpp>
#include <gui/widget/control/theme/simple/SimpleTextureThemeFactory.hpp>

#include "tetris/Window.hpp"
#include "tetris/gui/Hud.hpp"


namespace ttrs
{
  /**
   * The constructor creates a new Hud object.
   * @param renderer
   * @param window
   * @param settings
   */
  Hud::Hud(gui::Renderer& renderer, Window& window, Settings& settings)
    : gui::RootWidget(
        renderer,
        gui::SimpleTextureThemeFactory(),
        gui::Bounds(0, 0, window.clientSize().x, window.clientSize().y)
      ),
      window_(&window),
      fps_(       gui::Bounds(size().x - 50,  size().y - 35,  50,  35)),
      level_(     gui::Bounds(size().x - 125, size().y - 100, 100, 35)),
      points_(    gui::Bounds(size().x - 125, size().y - 200, 100, 35)),
      lines_(     gui::Bounds(size().x - 125, size().y - 300, 100, 35)),
      new_game_(  gui::Bounds(size().x - 125, size().y - 350, 100, 35), *this, &Hud::onNewGameClick),
      pause_game_(gui::Bounds(size().x - 125, size().y - 400, 100, 35), *this, &Hud::onPauseGameClick),
      quite_game_(gui::Bounds(size().x - 125, size().y - 450, 100, 35), *this, &Hud::onQuitGameClick),
      settings_dialog_(gui::Bounds(size().x - 325, 25, 300, 200), settings)
  {
    fps_.hide();
    fps_.setVAnchors(gui::V_ANCHORS_TOP);
    fps_.setHAnchors(gui::H_ANCHORS_RIGHT);
    fps_.setHAlignment(gui::H_ALIGNMENT_CENTERED);

    level_.setVAnchors(gui::V_ANCHORS_TOP);
    level_.setHAnchors(gui::H_ANCHORS_RIGHT);

    points_.setVAnchors(gui::V_ANCHORS_TOP);
    points_.setHAnchors(gui::H_ANCHORS_RIGHT);

    lines_.setVAnchors(gui::V_ANCHORS_TOP);
    lines_.setHAnchors(gui::H_ANCHORS_RIGHT);

    new_game_.setText(gui::String(TEXT("New Game")));
    new_game_.setVAnchors(gui::V_ANCHORS_TOP);
    new_game_.setHAnchors(gui::H_ANCHORS_RIGHT);

    pause_game_.setText(gui::String(TEXT("Pause Game")));
    pause_game_.setVAnchors(gui::V_ANCHORS_TOP);
    pause_game_.setHAnchors(gui::H_ANCHORS_RIGHT);

    quite_game_.setText(gui::String(TEXT("Quit Game")));
    quite_game_.setVAnchors(gui::V_ANCHORS_TOP);
    quite_game_.setHAnchors(gui::H_ANCHORS_RIGHT);

    settings_dialog_.setVAnchors(gui::V_ANCHORS_BOTTOM);
    settings_dialog_.setHAnchors(gui::H_ANCHORS_RIGHT);
    settings_dialog_.hide();

    focus();
  }

  /**
   * @copydoc RootWidget::onKeyDown
   */
  void Hud::onKeyDown(gui::Key key, gui::ModifierKey modifier)
  {
    if (key == wnd::KEY_S)
      settings_dialog_.focus();
  }

  /**
   * This method updates all elements within the hud that needs cyclic updating.
   * @param time time elapsed since last rendering
   */
  void Hud::update(float time)
  {
    fps_.update(time);
  }

  /**
   * @param level level to display
   */
  void Hud::setLevel(int level)
  {
    level_.setText(gui::String(TEXT("Level: ")) + gui::lexicalCast<int, gui::String>(level));
  }

  /**
   * @param points points to display
   */
  void Hud::setPoints(int points)
  {
    points_.setText(gui::String(TEXT("Points: ")) + gui::lexicalCast<int, gui::String>(points));
  }

  /**
   * @param lines number of lines to display
   */
  void Hud::setLines(int lines)
  {
    lines_.setText(gui::String(TEXT("Lines: ")) + gui::lexicalCast<int, gui::String>(lines));
  }

  /**
   * Toggle the display of the current frame rate.
   */
  void Hud::toggleFps()
  {
    if (fps_.shown())
      fps_.hide();
    else
      fps_.show();
  }

  /**
   *
   */
  void Hud::onNewGameClick()
  {
    window_->newGame();
  }

  /**
   * @todo the HUD should actually also get informed whenever the game was paused by another event
   *       not available to the HUD
   */
  void Hud::onPauseGameClick()
  {
    if (window_->isGamePaused())
    {
      window_->resumeGame();
      pause_game_.setText(gui::String(TEXT("Pause Game")));
    }
    else
    {
      window_->pauseGame();
      pause_game_.setText(gui::String(TEXT("Resume Game")));
    }
  }

  /**
   *
   */
  void Hud::onQuitGameClick()
  {
    window_->quitGame();
  }
}
