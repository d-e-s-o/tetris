// X11WindowImpl.cpp

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

#include "window/WindowBase.hpp"

#include "window/x11/X11VisualCreator.hpp"
#include "window/x11/X11WindowImpl.hpp"


namespace wnd
{
  /**
   * @param window
   * @param bounds
   * @param title
   */
  X11WindowImpl::X11WindowImpl(WindowBase& window, Bounds const& bounds, String const& title)
    : WindowImpl<WindowBase,
                 X11WindowImplBase,
                 X11VisualCreator>(window, bounds, title, X11VisualCreator())
  {
  }

  /**
   *
   */
  X11WindowImpl::~X11WindowImpl()
  {
  }

  /**
   *
   */
  bool X11WindowImpl::onDraw()
  {
    return owner().onDraw();
  }

  /**
   *
   */
  void X11WindowImpl::dispatchEvent(XEvent const& event)
  {
    // if a part of the window needs to be redrawn
    switch (event.type)
    {
    case Expose:
      onDraw();
      return;
    }
    X11WindowImplBase::dispatchEvent(event);
  }
}
