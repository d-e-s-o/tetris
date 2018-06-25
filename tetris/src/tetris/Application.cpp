// Application.cpp

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
#include "tetris/Options.hpp"
#include "tetris/Window.hpp"
#include "tetris/Application.hpp"


namespace ttrs
{
  namespace
  {
    Settings* initializeSettings(Options const& options)
    {
      if (options.config().available)
      {
        if (options.config().argument.size() != 0)
          return new IniSettings(String(options.config().argument));
        else
          return new IniSettings(String("tetris.cfg"));
      }
      else
        return new VolatileSettings();

      return 0;
    }
  }

  /**
   * @param options
   */
  Application::Application(Options const& options)
    : settings_(initializeSettings(options)),
      window_(new Window(*settings_))
  {
  }

  Application::~Application()
  {
  }

  /**
   * This method makes the window handle incoming events and rendering the game. If a quit message
   * is recieved it will exit.
   * @return 0 on success, false otherwise
   */
  int Application::run()
  {
    ASSERTOP(window_.pointer(), ne, nullptr);

    while (window_->handleEvents())
    {
      window_->render();
      window_->update();
    }
    return 0;
  }
}
