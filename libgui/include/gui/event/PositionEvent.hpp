// PositionEvent.hpp

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

#ifndef GUIPOSITIONEVENT_HPP
#define GUIPOSITIONEVENT_HPP

#include "gui/Position.hpp"
#include "gui/event/EventBase.hpp"


namespace gui
{
  /**
   * This class is the base class for events that need to be handled by a widget
   * at a given position.
   * @see PositionEvent::callHandler
   * @todo think about renaming to MouseEvent (we assume it is used for mouse events anyway!)
   */
  class LIBGUI_EXPORT PositionEvent: public EventBase
  {
  public:
    PositionEvent(Position const& position);

    virtual void dispatchEvent(RootWidget& root_widget) const;

    Position const& position() const;

  protected:
    Position relativePosition(WidgetBase const& widget) const;

  private:
    mutable Position position_;
  };
}


namespace gui
{
  inline PositionEvent::PositionEvent(Position const& position)
    : position_(position)
  {
  }

  /**
   *
   */
  inline Position const& PositionEvent::position() const
  {
    return position_;
  }
}


#endif
