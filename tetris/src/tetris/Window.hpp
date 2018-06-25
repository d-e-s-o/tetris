// Window.hpp

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

#ifndef TTRSWINDOW_HPP
#define TTRSWINDOW_HPP

#include <pointer/UniquePointer.hpp>

#ifdef USE_DIRECT3D
#  error "Direct3D is currently not supported"
#endif

#ifdef USE_DIRECT3D
#  ifndef NDEBUG
#    define D3D_DEBUG_INFO
#  endif
#  include <d3d9.h>
#  include <window/Direct3DWindow.hpp>
#  include <window/win32/Win32D3D9WindowImpl.hpp>
   typedef wnd::Direct3DWindow<wnd::Win32D3D9WindowImpl> WindowType;

#  include "D3D9Renderer.hpp"
   typedef D3D9Renderer RendererType;
#else
#  include <window/OpenGlWindow.hpp>
#  ifdef LIBWINDOW_WINDOWS
#    include <window/win32/Win32OpenGlWindowImpl.hpp>
     typedef wnd::Win32OpenGlWindowImpl WindowImpl;
#  else
#    include <window/x11/X11OpenGlWindowImpl.hpp>
     typedef wnd::X11OpenGlWindowImpl WindowImpl;

#    ifdef Status
#      undef Status
#    endif
#  endif
   typedef wnd::OpenGlWindow<WindowImpl> WindowType;

#  include "renderer/OpenGlRenderer.hpp"
#  include "renderer/OpenGlGuiRenderer.hpp"
   typedef ttrs::OpenGlRenderer RendererType;
#endif

#include <time/Timer.hpp>

#ifdef LIBWINDOW_WINDOWS
//#  include <time/win32/TickCount.hpp>
//  typedef tme::Timer<tme::TickCount, float, tme::PRECISION_S> Timer;

#  include <time/win32/QueryPerformance.hpp>
  typedef tme::Timer<tme::QueryPerformance, float, tme::PRECISION_S> Timer;

// using std::clock works fine as well, but only for Windows
//#  include <time/libc/Clock.hpp>
//  typedef tme::Timer<tme::Clock, float, tme::PRECISION_S> Timer;
#else
#  include <time/posix/TimeOfDay.hpp>
  typedef tme::Timer<tme::TimeOfDay, float, tme::PRECISION_S> Timer;
#endif

#include <gui/MemoryNamespace.hpp>
#include <gui/NamespaceManager.hpp>
#include <gui/ResourceManager.hpp>
#include <gui/renderer/Viewport.hpp>

#include "tetris/gui/Hud.hpp"
#include "tetris/gui/StatusHud.hpp"
#include "tetris/game/Game.hpp"


namespace ttrs
{
  class KeyboardCache;
  class Settings;


  /**
   *
   */
  class ResourceManager: public gui::ResourceManager
  {
  public:
    ResourceManager();

  private:
    gui::MemoryNamespace  memory_namespace_;
    gui::NamespaceManager namespace_manager_;
  };


  /**
   *
   */
  class DeferringRootWidgetViewport: public gui::Viewport
  {
  public:
    DeferringRootWidgetViewport(wnd::Dimensions const& size);

    virtual gui::Position offset() const;
    virtual gui::Size     size() const;

    void setRootWidget(gui::RootWidget const& root_widget);

  private:
    gui::RootWidget const* root_widget_;

    gui::Position offset_;
    gui::Size     size_;
  };


  /**
   * This is the class for the window the game uses. It is responsible for rendering the content
   * and handling events.
   */
  class Window: public WindowType
  {
  public:
    Window(Settings& settings);
    ~Window();

    virtual void initialize();
    virtual void render() const;

    virtual void update();

    virtual bool onResize(wnd::Dimensions const& size);

    virtual bool onMouseMove(wnd::Coordinates const& position);
    virtual bool onMouseDown(wnd::Coordinates const& position, wnd::MouseButton button);
    virtual bool onMouseUp(wnd::Coordinates const& position, wnd::MouseButton button);

    virtual bool onMouseWheelDown(int units);
    virtual bool onMouseWheelUp(int units);

    virtual bool onKeyDown(wnd::Key key, wnd::ModifierKey modifiers, bool repeated);
    virtual bool onKeyUp(wnd::Key key, wnd::ModifierKey modifiers, bool repeated);
    virtual bool onChar(char_t character);

    void newGame();
    void pauseGame();
    void resumeGame();
    void quitGame();

    bool isGamePaused() const;

  protected:
    virtual void initializeView() const;

  private:
    typedef ptr::UniquePointer<Game>          GamePointer;
    typedef ptr::UniquePointer<KeyboardCache> KeyboardCachePointer;

    ResourceManager             resource_manager_;
    DeferringRootWidgetViewport viewport_;

    /**
     * @todo OpenGlGuiRenderer is only needed when we actually create an OpenGlRenderer object
     */
    OpenGlGuiRenderer gui_renderer_;
    RendererType      renderer_;

    Settings* settings_;

    Timer timer_;

    Hud       hud_;
    StatusHud status_;

    GamePointer          game_;
    KeyboardCachePointer key_cache_;

    KeyboardCachePointer createKeyboardCache() const;
    GamePointer          createGame();

    void doAction(wnd::Key key);
    void togglePause();
    void toggleAutoPlay();
  };
}


#endif
