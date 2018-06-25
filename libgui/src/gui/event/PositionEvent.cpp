// PositionEvent.cpp

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

#include "gui/widget/RootWidget.hpp"
#include "gui/event/PositionEvent.hpp"


namespace gui
{
  /**
   * @note it is important that the event is dispatched only once, otherwise we will get problems
   *       here (we could however solve this by adding another position member with pixel
   *       coordinates)
   */
  void PositionEvent::dispatchEvent(RootWidget& root_widget) const
  {
    root_widget.handlePositionEvent(*this);
  }

  /**
   * @param widget widget to calculate relative position of event from
   * @return position position of event relative to the widget
   */
  Position PositionEvent::relativePosition(WidgetBase const& widget) const
  {
    return position_ - widget.absolutePosition();
  }
}
