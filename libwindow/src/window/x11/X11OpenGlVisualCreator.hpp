// OpenGlX11VisualCreator.hpp

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

#ifndef WNDOPENGLX11VISUALCREATOR_HPP
#define WNDOPENGLX11VISUALCREATOR_HPP

#include "X11VisualCreatorBase.hpp"


namespace wnd
{
  /**
   * @todo this is really bad, we return a pointer to a visual which is free'd in the destructor,
   *       fix this somehow
   */
  class OpenGlX11VisualCreator: public X11VisualCreatorBase
  {
  public:
    OpenGlX11VisualCreator();
    virtual ~OpenGlX11VisualCreator();

    virtual Visual* operator ()(Display* display, int screen, int& depth) const;

    XVisualInfo* getVisualInfo() const;

  private:
    mutable XVisualInfo* visual_info_;
  };
}

namespace wnd
{
  /**
   *
   */
  inline OpenGlX11VisualCreator::OpenGlX11VisualCreator()
    : visual_info_(0)
  {
  }

  /**
   *
   */
  inline XVisualInfo* OpenGlX11VisualCreator::getVisualInfo() const
  {
    return visual_info_;
  }
}


#endif
