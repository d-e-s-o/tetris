// ReleaseEvent.hpp

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

#ifndef GUIRELEASEEVENT_HPP
#define GUIRELEASEEVENT_HPP

#include "gui/event/WidgetEvent.hpp"


namespace gui
{
  template<typename T>
  class ReleaseEvent: public WidgetEvent<ReleaseEvent<T>, T>
  {
  public:
    releaseEvent(T& widget);

    virtual bool callHandler(WidgetInterface& widget) const;
  };
}


namespace gui
{
  template<typename T>
  ReleaseEvent<T>::releaseEvent(T& widget)
    : widgetEvent(*this, widget)
  {
  }

  /**
   * @todo think about removing the check for equality, it might be nonsense
   */
  template<typename T>
  bool ReleaseEvent<T>::callHandler(WidgetInterface& widget) const
  {
    T& stored = getWidget();

    if (&widget == &stored)
      return stored.onRelease();

    return false;
  }
}


#endif
