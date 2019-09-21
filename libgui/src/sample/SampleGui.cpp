/***************************************************************************
 *   Copyright (C) 2006-2012,2019 Daniel Mueller (deso@posteo.net)         *
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

// use this define to use Direct3D instead of OpenGl
//#define SAMPLE_DIRECT3D


#include <iostream>

// only MS Windows supports Direct3D
#ifndef LIBWINDOW_WINDOWS
#  ifdef SAMPLE_DIRECT3D
#    undef SAMPLE_DIRECT3D
#  endif
#endif

#ifdef SAMPLE_DIRECT3D
#  ifndef NDEBUG
#    define D3D_DEBUG_INFO
#  endif
#  include <d3d9.h>
#  include <window/Direct3DWindow.hpp>
#  include <window/win32/Win32D3D9WindowImpl.hpp>
#  include <gui/renderer/d3d9/D3D9Renderer.hpp>
   typedef gui::D3D9Renderer Renderer;
   typedef wnd::Direct3DWindow<wnd::Win32D3D9WindowImpl> WindowBase;
#else
#  include <window/OpenGlWindow.hpp>
#  ifdef LIBWINDOW_WINDOWS
#    include <window/win32/Win32OpenGlWindowImpl.hpp>
     typedef wnd::Win32OpenGlWindowImpl WindowImpl;
#  else
#    include <window/x11/X11OpenGlWindowImpl.hpp>
     typedef wnd::X11OpenGlWindowImpl WindowImpl;
#  endif
#  include <gui/renderer/opengl/OpenGlRenderer.hpp>
   typedef gui::OpenGlRenderer Renderer;
   typedef wnd::OpenGlWindow<WindowImpl> WindowBase;
#endif

#include <time/Timer.hpp>

#ifdef LIBWINDOW_WINDOWS
#  include <time/win32/TickCount.hpp>
  typedef tme::Timer<tme::TickCount, float, tme::PRECISION_S> Timer;
#else
#  include <time/posix/TimeOfDay.hpp>
  typedef tme::Timer<tme::TimeOfDay, float, tme::PRECISION_S> Timer;
#endif

#ifdef GetMessage
#  undef GetMessage
#endif

#include <util/Rectangle1Functions.hpp>

#include <image/codec/png/PngCodec.hpp>
#include <image/Error.hpp>
#include <font/Error.hpp>

#include <gui/Error.hpp>
#include <gui/MemoryNamespace.hpp>
#include <gui/ResourceManager.hpp>
#include <gui/renderer/RootWidgetViewport.hpp>
#include <gui/event/MouseMoveEvent.hpp>
#include <gui/event/MouseDownEvent.hpp>
#include <gui/event/MouseUpEvent.hpp>
#include <gui/event/MouseWheelDownEvent.hpp>
#include <gui/event/MouseWheelUpEvent.hpp>
#include <gui/event/KeyDownEvent.hpp>
#include <gui/event/KeyUpEvent.hpp>
#include <gui/event/CharacterEvent.hpp>
//#include <gui/widget/control/theme/simple/SimpleThemeFactory.hpp>
#include <gui/widget/control/theme/simple/SimpleTextureThemeFactory.hpp>

#include <sample/resource/ttf-bitstream-vera.ttf.hpp>
#include <sample/resource/win_xp_silver_theme.png.hpp>

#include "Gui.hpp"


namespace sample
{
  /**
   * This class represents the window containing the gui (the root widget and with it all
   * children).
   */
  class GuiWindow: public WindowBase
  {
  public:
    GuiWindow(wnd::Bounds const& bounds, gui::ResourceManager const& resource_manager);

    virtual void initialize();
    virtual void render() const;

    virtual void update();

    virtual bool onResize(wnd::Dimensions const& size);

    virtual bool onMouseMove(wnd::Coordinates const& coordinates);
    virtual bool onMouseDown(wnd::Coordinates const& coordinates, wnd::MouseButton button);
    virtual bool onMouseUp(wnd::Coordinates const& coordinates, wnd::MouseButton button);

    virtual bool onMouseWheelDown(int units);
    virtual bool onMouseWheelUp(int units);

    virtual bool onKeyDown(wnd::Key key, wnd::ModifierKey modifiers, bool repeated);
    virtual bool onKeyUp(wnd::Key key, wnd::ModifierKey modifiers, bool repeated);
    virtual bool onChar(char_t character);

  private:
    gui::RootWidgetViewport viewport_;
    Renderer renderer_;

    Gui   gui_;
    Timer timer_;

    int fps_;

    void updateFps();
  };
}


namespace sample
{
  /**
   * The window constructor creates the window and the gui and sets up some basic settings.
   * @todo passing in gui_ to viewport_'s constructor is wrong, it is not yet created (!)
   */
  GuiWindow::GuiWindow(wnd::Bounds const& bounds, gui::ResourceManager const& resource_manager)
    : WindowBase(bounds, gui::String(TEXT("SampleGui"))),
      viewport_(gui_),
      renderer_(viewport_, resource_manager),
      gui_(renderer_, gui::SimpleTextureThemeFactory(), utl::getRectangle(gui::Position(), gui::Size(clientSize()))),
      timer_(),
      fps_(0)
  {
    initialize();

    timer_.start();
  }

  /**
   * We do some one-time initializations in here.
   */
  void GuiWindow::initialize()
  {
    WindowBase::initialize();

#ifndef SAMPLE_DIRECT3D
    glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
#endif
  }

  /**
   * This method is called to render the scene to the screen.
   */
  void GuiWindow::render() const
  {
#ifdef SAMPLE_DIRECT3D
    Direct3DDevice& device = getD3DDevice();

    device.Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(127, 127, 255), 1.0f, 0);
    device.BeginScene();
#else
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif

    gui_.render();

#ifdef SAMPLE_DIRECT3D
    device.DndScene();
#endif

    WindowBase::render();
  }

  /**
   * This method is called every frame; it is used for updating all time related stuff, in this
   * case the frames per second.
   */
  void GuiWindow::update()
  {
    updateFps();
  }

  /**
   * @copydoc GraphicWindow::onResize
   */
  bool GuiWindow::onResize(wnd::Dimensions const& size)
  {
    // as the gui should fill the whole window we resize it every time the "real" window is
    // resized
    gui_.resize(gui::Size(clientSize().x, clientSize().y));
    return WindowBase::onResize(size);
  }

  /**
   * @copydoc GraphicWindow::onMouseMove
   */
  bool GuiWindow::onMouseMove(wnd::Coordinates const& position)
  {
    gui_.handleEvent(gui::MouseMoveEvent(gui::Position(position)));
    return true;
  }

  /**
   * @copydoc GraphicWindow::onMouseDown
   */
  bool GuiWindow::onMouseDown(wnd::Coordinates const& position, wnd::MouseButton button)
  {
    gui_.handleEvent(gui::MouseDownEvent(gui::Position(position), button));
    return true;
  }

  /**
   * @copydoc GraphicWindow::onMouseUp
   */
  bool GuiWindow::onMouseUp(wnd::Coordinates const& position, wnd::MouseButton button)
  {
    gui_.handleEvent(gui::MouseUpEvent(gui::Position(position), button));
    return true;
  }

  /**
   * @copydoc GraphicWindow::onMouseWheelDown
   */
  bool GuiWindow::onMouseWheelDown(int units)
  {
    gui_.handleEvent(gui::MouseWheelDownEvent(units));
    return true;
  }

  /**
   * @copydoc GraphicWindow::onMouseWheelUp
   */
  bool GuiWindow::onMouseWheelUp(int units)
  {
    gui_.handleEvent(gui::MouseWheelUpEvent(units));
    return true;
  }

  /**
   * @copydoc GraphicWindow::onKeyDown
   */
  bool GuiWindow::onKeyDown(wnd::Key key, wnd::ModifierKey modifiers, bool repeated)
  {
    switch(key)
    {
    case wnd::KEY_F1:
      toggleFullscreen();
      return true;

    case wnd::KEY_H:
      if (wnd::checkForModifier(modifiers, wnd::MOD_KEY_LCTRL) ||
          wnd::checkForModifier(modifiers, wnd::MOD_KEY_RCTRL))
      {
        if (gui_.shown())
          gui_.hide();
        else
          gui_.show();
      }
      break;

    default:
      break;
    }

    gui_.handleEvent(gui::KeyDownEvent(key, modifiers));
    return true;
  }

  /**
   * @copydoc GraphicWindow::onKeyUp
   */
  bool GuiWindow::onKeyUp(wnd::Key key, wnd::ModifierKey modifiers, bool repeated)
  {
    gui_.handleEvent(gui::KeyUpEvent(key, modifiers));
    return true;
  }

  /**
   * @copydoc GraphicWindow::onChar
   */
  bool GuiWindow::onChar(char_t character)
  {
    gui_.handleEvent(gui::CharacterEvent(character));
    return true;
  }

  /**
   * This method is called every frame; it calls the frames and prints out the frames per second.
   */
  void GuiWindow::updateFps()
  {
    ++fps_;

    if (timer_.getTime() >= 1.0f)
    {
      gui_.setFps(fps_);

      std::cout << fps_ << std::endl;

      fps_ = 0;
      timer_.start();
    }
  }
}


int main(int argc, char* argv[])
{
  try
  {
    gui::MemoryNamespace memory_namespace;
    memory_namespace.insertEntry(gui::String("vera.ttf"),
                                              ttf_bitstream_vera_ttf_data,
                                              ttf_bitstream_vera_ttf_size);

    memory_namespace.insertEntry(gui::String("win_xp_silver_theme.png"),
                                              win_xp_silver_theme_png_data,
                                              win_xp_silver_theme_png_size);

    gui::NamespaceManager namespace_manager;
    namespace_manager.registerNamespace(memory_namespace, gui::String("mem"));

    gui::ResourceManager resource_manager(namespace_manager);
    resource_manager.registerCodec(img::PngCodec());

    sample::GuiWindow window(wnd::Bounds(100, 100, 800, 600), resource_manager);

    while (window.handleEvents())
    {
      window.render();
      window.update();
    }
  }
  catch(gui::Error const& error)
  {
    std::cerr << "Error: " << error.message() << '\n'
              << "Cause: " << error.cause()   << std::endl;
  }
  catch(img::Error const& error)
  {
    std::cerr << "Error: " << error.message() << '\n'
              << "Cause: " << error.cause()   << std::endl;
  }
  catch(fnt::Error const& error)
  {
    std::cerr << "Error: " << error.message() << '\n'
              << "Cause: " << error.cause()   << std::endl;
  }
  catch(...)
  {
    std::cerr << "An unexpected error occurred" << std::endl;
  }
  return 0;
}
