// WidgetFunctions.hpp

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

#ifndef GUIWIDGETFUNCTIONS_HPP
#define GUIWIDGETFUNCTIONS_HPP

#include <util/Rectangle1Functions.hpp>

#include "gui/widget/WidgetBase.hpp"


namespace gui
{
  Bounds getBounds(WidgetBase const& widget);
  Bounds getAbsoluteBounds(WidgetBase const& widget);

  void move(WidgetBase& widget, Position const& amount);
}


namespace gui
{
  /**
   *
   */
  inline Bounds getBounds(WidgetBase const& widget)
  {
    return utl::getRectangle<PositionT, SizeT>(widget.position(), widget.size());
  }

  /**
   * @param widget widget to get bounds from
   * @return bounds of the widget with absolute position
   */
  inline Bounds getAbsoluteBounds(WidgetBase const& widget)
  {
    return utl::getRectangle<PositionT, SizeT>(widget.absolutePosition(), widget.size());
  }

  /**
   * Move the widget by given amount on x- and y-axis (in pixels)
   * @param amount amount to move
   */
  inline void move(WidgetBase& widget, Position const& amount)
  {
    widget.move(widget.position() + amount);
  }
}


#endif
