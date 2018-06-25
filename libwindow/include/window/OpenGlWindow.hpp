// OpenGlWindow.hpp

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

#ifndef WNDOPENGLWINDOW_HPP
#define WNDOPENGLWINDOW_HPP

#include "window/include/OpenGl.hpp"
#include "window/Bounds.hpp"
#include "window/GraphicWindow.hpp"


namespace wnd
{
  /**
   * This class represents a window with OpenGl rendering context.
   * @todo add some parameter to specfiy color depth
   */
  template<typename ImplT>
  class OpenGlWindow: public GraphicWindow<ImplT>
  {
  public:
    OpenGlWindow(Bounds const& bounds, String const& title = String(TEXT("")));

    virtual void initialize();

  protected:
    virtual void initializeView() const;
  };
}


namespace wnd
{
  /**
   * @param bounds position and size of the window
   * @param title title of the window (in the caption bar)
   */
  template<typename ImplT>
  OpenGlWindow<ImplT>::OpenGlWindow(Bounds const& bounds, String const& title)
    : GraphicWindow<ImplT>(bounds, title)
  {
  }

  /**
   * @copydoc GraphicWindowBase::initialize
   */
  template<typename ImplT>
  void OpenGlWindow<ImplT>::initialize()
  {
    initializeView();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  }

  /**
   * @copydoc GraphicWindowBase::initializeView
   */
  template<typename ImplT>
  void OpenGlWindow<ImplT>::initializeView() const
  {
    Dimensions const& size = this->clientSize();

    glPushAttrib(GL_TRANSFORM_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, size.x, size.y);
    gluPerspective(45.0f, 1.0f * size.x / size.y, 0.1f, 10.0f);
    glPopAttrib();
  }
}


#endif
