// Window.cpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014,2019 Daniel Mueller (deso@posteo.net)    *
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
#include <image/codec/png/PngCodec.hpp>

#include <gui/event/MouseMoveEvent.hpp>
#include <gui/event/MouseDownEvent.hpp>
#include <gui/event/MouseUpEvent.hpp>
#include <gui/event/MouseWheelDownEvent.hpp>
#include <gui/event/MouseWheelUpEvent.hpp>
#include <gui/event/KeyDownEvent.hpp>
#include <gui/event/KeyUpEvent.hpp>
#include <gui/event/CharacterEvent.hpp>

#ifdef USE_DIRECT3D
#  include <gui/renderer/d3d9/D3D9Renderer.hpp>
#else
#  include "tetris/renderer/OpenGlGuiRenderer.hpp"
  typedef ttrs::OpenGlGuiRenderer InternalRendererType;
#endif

#include "tetris/KeyboardCache.hpp"
#include "tetris/Window.hpp"

#include "resource/Settings.hpp"
#include "resource/tetris_field_256x512.png.hpp"
#include "resource/tetris_piece_32x32.png.hpp"
#include "resource/tetris_ttf-bitstream-vera.ttf.hpp"
#include "resource/tetris_win_xp_silver_theme.png.hpp"


namespace ttrs
{
  /**
   * @param offset the initial viewport's offset
   * @param size the initial viewport's size
   * @note the given offset and size are used until a RootWidget was set that supplies the new
   *       offset and size values
   */
  DeferringRootWidgetViewport::DeferringRootWidgetViewport(wnd::Dimensions const& size)
    : root_widget_(0),
      offset_(),
      size_(size.x, size.y)
  {
  }

  /**
   * @copydoc gui::Viewport::offset
   */
  gui::Position DeferringRootWidgetViewport::offset() const
  {
    if (root_widget_ != 0)
      return root_widget_->position();

    return offset_;
  }

  /**
   * @copydoc gui::Viewport::size
   */
  gui::Size DeferringRootWidgetViewport::size() const
  {
    if (root_widget_ != 0)
      return root_widget_->size();

    return size_;
  }

  /**
   *
   */
  void DeferringRootWidgetViewport::setRootWidget(gui::RootWidget const& root_widget)
  {
    root_widget_ = &root_widget;
  }

  /**
   * The constructor creates a ready-to-use ResourceManager.
   */
  ResourceManager::ResourceManager()
    : gui::ResourceManager(namespace_manager_),
      memory_namespace_(),
      namespace_manager_()
  {
    registerCodec(img::PngCodec());

    memory_namespace_.insertEntry(gui::String("tetris_field_256x512.png"),
                                               tetris_field_256x512_png_data,
                                               tetris_field_256x512_png_size);

    memory_namespace_.insertEntry(gui::String("tetris_piece_32x32.png"),
                                               tetris_piece_32x32_png_data,
                                               tetris_piece_32x32_png_size);

    memory_namespace_.insertEntry(gui::String("tetris_wall_32x32.png"),
                                               tetris_piece_32x32_png_data,
                                               tetris_piece_32x32_png_size);

    memory_namespace_.insertEntry(gui::String("vera.ttf"),
                                               tetris_ttf_bitstream_vera_ttf_data,
                                               tetris_ttf_bitstream_vera_ttf_size);

    memory_namespace_.insertEntry(gui::String("win_xp_silver_theme.png"),
                                               tetris_win_xp_silver_theme_png_data,
                                               tetris_win_xp_silver_theme_png_size);

    namespace_manager_.registerNamespace(memory_namespace_, gui::String("mem"));
  }


  /**
   * The constructor creates a window for the tetris game.
   * @param bounds bounds (position and size) of the window
   */
  Window::Window(Settings& settings)
    : WindowType(wnd::Bounds(settings.getWindowX(), settings.getWindowY(),
                             settings.getWindowWidth(), settings.getWindowHeight()),
                             String(TEXT("Tetris"))),
      resource_manager_(),
      viewport_(clientSize()),
      gui_renderer_(viewport_, resource_manager_),
      renderer_(gui_renderer_),
      settings_(&settings),
      timer_(),
      hud_(gui_renderer_, *this, settings),
      status_(hud_),
      game_(createGame()),
      key_cache_(createKeyboardCache())
  {
    viewport_.setRootWidget(hud_);

    initialize();
    newGame();
  }

  Window::~Window()
  {
  }

  /**
   * This method intializes the window by setting up all necessary states for rendering and
   * starting the timer.
   */
  void Window::initialize()
  {
    renderer_.setupStates();
    timer_.start();
  }

  /**
   * This method renders the game and the hud.
   */
  void Window::render() const
  {
    // the "renderer_" is used only for the game objects, the hud has its own
    renderer_.onPreRender();
    game_->render();
    renderer_.onPostRender();

    hud_.render();

    WindowType::render();
  }

  /**
   * This method updates the game and the hud, enabling time based movement.
   */
  void Window::update()
  {
    float time = timer_.getTimeAndRestart();

    if (key_cache_ != 0)
    {
      key_cache_->update(time);

      wnd::Key key = wnd::KEY_MIN;

      while (key_cache_->needsAction(key))
        doAction(key);
    }

    game_->update(time);
    hud_.update(time);
  }

  /**
   * @copydoc GraphicWindow::onResize
   */
  bool Window::onResize(wnd::Dimensions const& size)
  {
    hud_.resize(gui::Size(clientSize()));
    return WindowType::onResize(size);
  }

  /**
   * @copydoc GraphicWindow::onMouseMove
   */
  bool Window::onMouseMove(wnd::Coordinates const& position)
  {
    hud_.handleEvent(gui::MouseMoveEvent(gui::Position(position)));
    return true;
  }

  /**
   * @copydoc GraphicWindow::onMouseDown
   */
  bool Window::onMouseDown(wnd::Coordinates const& position, wnd::MouseButton button)
  {
    hud_.handleEvent(gui::MouseDownEvent(gui::Position(position), button));
    return true;
  }

  /**
   * @copydoc GraphicWindow::onMouseUp
   */
  bool Window::onMouseUp(wnd::Coordinates const& position, wnd::MouseButton button)
  {
    hud_.handleEvent(gui::MouseUpEvent(gui::Position(position), button));
    return true;
  }

  /**
   * @copydoc GraphicWindow::onMouseWheelDown
   */
  bool Window::onMouseWheelDown(int units)
  {
    hud_.handleEvent(gui::MouseWheelDownEvent(units));
    return true;
  }

  /**
   * @copydoc GraphicWindow::onMouseWheelUp
   */
  bool Window::onMouseWheelUp(int units)
  {
    hud_.handleEvent(gui::MouseWheelUpEvent(units));
    return true;
  }

  /**
   * This method performs the necessary actions based on the type of key pressed.
   * @copydoc GraphicWindow::onKeyDown
   */
  bool Window::onKeyDown(wnd::Key key, wnd::ModifierKey modifiers, bool repeated)
  {
    hud_.handleEvent(gui::KeyDownEvent(key, modifiers));

    // we only care for initial key events, repeated ones are generated by the keyboard-cache with
    // custom repeat delay and repeat rate
    if (key_cache_ != 0)
    {
      if (!repeated && key_cache_->onKeyDown(key))
        doAction(key);
    }
    else
      doAction(key);

    return true;
  }

  /**
   * @copydoc GraphicWindow::onKeyUp
   */
  bool Window::onKeyUp(wnd::Key key, wnd::ModifierKey modifiers, bool repeated)
  {
    hud_.handleEvent(gui::KeyUpEvent(key, modifiers));

    if (key_cache_ != 0)
    {
      if (!repeated)
        key_cache_->onKeyUp(key);
    }
    return true;
  }

  /**
   * @copydoc GraphicWindow::onChar
   */
  bool Window::onChar(char_t character)
  {
    hud_.handleEvent(gui::CharacterEvent(character));
    return true;
  }

  /**
   * This method sets up the view so the whole game can be seen. It is called whenever the game
   * is resized and during initialization.
   */
  void Window::initializeView() const
  {
    wnd::Dimensions size = clientSize();
    renderer_.setupView(size.x, size.y, game_->width(), game_->height());
  }

  /**
   * @return newly created KeyboardCache object or null if the settings object does not require a
   *         KeyboardCache to be used
   */
  Window::KeyboardCachePointer Window::createKeyboardCache() const
  {
    if (!settings_->getKeyboardNative())
    {
      return KeyboardCachePointer(new KeyboardCache(settings_->getKeyboardRepeatDelay(),
                                                    settings_->getKeyboardRepeatInterval()));
    }
    return KeyboardCachePointer(0);
  }

  /**
   * @return newly created game
   */
  Window::GamePointer Window::createGame()
  {
    return GamePointer(new Game(renderer_, *settings_, status_));
  }

  /**
   * This method starts a new game.
   */
  void Window::newGame()
  {
    game_ = createGame();
    initializeView();
  }

  /**
   * This method pauses the game.
   */
  void Window::pauseGame()
  {
    game_->pause(true);
  }

  /**
   * This method resumes a previously paused game.
   */
  void Window::resumeGame()
  {
    game_->pause(false);
  }

  /**
   * This method quits the whole game by closing the window.
   */
  void Window::quitGame()
  {
    close();
  }

  /**
   * @return true if the game is paused, false if it is not
   */
  bool Window::isGamePaused() const
  {
    return game_->paused();
  }

  /**
   * This method executes the action that belongs to the given key.
   * @param key key to execute action bound to it
   */
  void Window::doAction(wnd::Key key)
  {
    ASSERTOP(key, gt, wnd::KEY_MIN);
    ASSERTOP(key, lt, wnd::KEY_MAX);

    // @todo it's not good to invoke the game methods directly here I would say; we would need a
    //       mapping Key->Action and then send the Action to the game; that would also work very
    //       well with the ActionList we get from the AI
    // @todo we need to be able to customize the keyboard bindings
    switch(key)
    {
    case wnd::KEY_SPACE:
      game_->onMoveFastDown();
      break;

    case wnd::KEY_K:
      game_->onMoveDown();
      break;

    case wnd::KEY_H:
      game_->onMoveLeft();
      break;

    case wnd::KEY_L:
      game_->onMoveRight();
      break;

    case wnd::KEY_1:
      game_->onRotateLeft();
      break;

    case wnd::KEY_2:
      game_->onRotateRight();
      break;

    case wnd::KEY_RETURN:
      newGame();
      break;

    case wnd::KEY_F1:
      toggleFullscreen();
      break;

    case wnd::KEY_F2:
      toggleAutoPlay();
      break;

    case wnd::KEY_F3:
      togglePause();
      break;

    case wnd::KEY_F:
      hud_.toggleFps();
      break;

    case wnd::KEY_Q:
      close();
      break;

    default:
      break;
    }
  }

  /**
   * This method can be used to pause/unpause the game.
   */
  void Window::togglePause()
  {
    game_->pause(!game_->paused());
  }

  /**
   *
   */
  void Window::toggleAutoPlay()
  {
    game_->play(!game_->plays());
    settings_->setAutoPlay(game_->plays());
  }
}
