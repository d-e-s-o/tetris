// EventBase.hpp

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

#ifndef GUIEVENTBASE_HPP
#define GUIEVENTBASE_HPP

#include "gui/Config.hpp"


namespace gui
{
  class WidgetBase;
  class RootWidget;


  /**
   * This class is the base class for all events that are created by a "real"
   * window and are of some interest for the "virtual" gui or any of its
   * components (meaning the RootWidget or some of its children).
   * @see RootWidget
   */
  class LIBGUI_EXPORT EventBase
  {
  public:
    virtual ~EventBase() = 0;

    virtual void dispatchEvent(RootWidget& root_widget) const = 0;
    virtual void callHandler(WidgetBase& widget) const = 0;
  };
}


#endif
