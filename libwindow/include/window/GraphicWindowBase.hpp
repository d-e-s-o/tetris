// GraphicWindowBase.hpp

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

#ifndef WNDOPENGLWINDOWBASE_HPP
#define WNDOPENGLWINDOWBASE_HPP

#include "window/WindowInterface.hpp"


namespace wnd
{
  /**
   * This class is the base class for every OpenGl window.
   */
  class LIBWINDOW_EXPORT GraphicWindowBase: public WindowInterface
  {
  public:
    /**
     * This method sets up the OpenGl scene. Overwrite it and put all you
     * initializing stuff into it, then call it in the constructor.
     */
    virtual void initialize() = 0;

    /**
     * This method renders the OpenGl scene to the screen. It should be
     * overwritten with the actual rendering code and at the end the base method
     * should be called (to put the scene to screen).
     */
    virtual void render() const = 0;

    /**
     * @return true if window is in fullscreen mode
     */
    virtual bool isFullscreen() const = 0;

    /**
     * This method toggles between fullscreen and windowed mode.
     * @return true if changing the mode was successful, false if not
     */
    virtual bool toggleFullscreen() = 0;

  protected:
    /**
     * This method sets up the view for the OpenGl window. It is called by
     * default in Initialize (which should be called when the window is set up)
     * and by default in OnResize because if the windows size changes the view
     * needs to be adjusted.
     */
    virtual void initializeView() const = 0;
  };
}


#endif
