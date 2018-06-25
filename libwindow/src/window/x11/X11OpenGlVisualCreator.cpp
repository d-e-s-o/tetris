// OpenGlX11VisualCreator.cpp

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

#include <X11/Xutil.h>
#include <GL/glx.h>

#include "X11OpenGlVisualCreator.hpp"


namespace wnd
{
  namespace
  {
    int attributes[] = {GLX_RGBA, GLX_DEPTH_SIZE, 16, GLX_DOUBLEBUFFER, None};
  }


  /**
   * @copydoc X11VisualCreatorBase::~X11VisualCreatorBase
   */
  OpenGlX11VisualCreator::~OpenGlX11VisualCreator()
  {
    XFree(visual_info_);
  }

  Visual* OpenGlX11VisualCreator::operator ()(Display* display, int screen, int& depth) const
  {
    visual_info_ = glXChooseVisual(display, screen, attributes);

    if (visual_info_ != 0)
    {
      depth = visual_info_->depth;
      return visual_info_->visual;
    }
    return 0;
  }
}
