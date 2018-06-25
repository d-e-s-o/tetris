// X11OpenGlWindowImpl.hpp

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

#ifndef WNDX11OPENGLWINDOWIMPL_HPP
#define WNDX11OPENGLWINDOWIMPL_HPP

#include "window/x11/X11WindowImplBase.hpp"
#include "window/WindowImpl.hpp"


namespace wnd
{
  class GraphicWindowBase;
  class OpenGlX11VisualCreator;


  /**
   * This class is used to create an OpenGl window on X11 implementations.
   */
  class X11OpenGlWindowImpl
    : public WindowImpl<GraphicWindowBase, X11WindowImplBase, OpenGlX11VisualCreator>
  {
  public:
    X11OpenGlWindowImpl(GraphicWindowBase& window, Bounds const& bounds, String const& title);
    virtual ~X11OpenGlWindowImpl();

    void render() const;

    bool isFullscreen() const;
    bool toggleFullscreen();

  private:
    typedef struct __GLXcontextRec* GLXContext;

    GLXContext context_;
    bool fullscreen_;

    X11OpenGlWindowImpl(X11OpenGlWindowImpl const&);
    X11OpenGlWindowImpl& operator =(X11OpenGlWindowImpl const&);

    OpenGlX11VisualCreator const& getVisualCreator() const;
  };
}


#endif
