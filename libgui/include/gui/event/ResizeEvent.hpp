// ResizeEvent.hpp

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

#ifndef GUIRESIZEEVENT_HPP
#define GUIRESIZEEVENT_HPP

#include "gui/Size.hpp"
#include "gui/event/RootWidgetEvent.hpp"


namespace gui
{
  /**
   * This class represents the notification a window sends if it is resized.
   */
  class LIBGUI_EXPORT ResizeEvent: public RootWidgetEvent
  {
  public:
    ResizeEvent(Size const& size);

    virtual void callHandler(WidgetBase& widget) const;

  private:
    Size size_;
  };
}


#endif
