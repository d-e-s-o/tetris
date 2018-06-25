// Border.cpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#include <util/Assert.hpp>
#include <util/Rectangle1Functions.hpp>

#include "gui/event/PositionEvent.hpp"
#include "gui/widget/RootWidget.hpp"
#include "gui/widget/control/theme/Theme.hpp"
#include "gui/widget/control/Border.hpp"


namespace gui
{
  /**
   * @copydoc Decorator::Decorator
   */
  Border::Border(Widget& widget, bool no_top_border)
    : Decorator(widget),
      no_top_border_(no_top_border)
  {
  }

  /**
   * @return width of the border
   */
  SizeT Border::width() const
  {
    return rootWidget()->getTheme().getControlTheme<Border>().width;
  }

  /**
   * @return space between the edges of the widget and the actually rendered border
   */
  SizeT Border::innerSpace() const
  {
    return rootWidget()->getTheme().getControlTheme<Border>().inner_space;
  }

  /**
   * @return space between the actually rendered border and the client area of the Decorator
   */
  SizeT Border::outerSpace() const
  {
    return rootWidget()->getTheme().getControlTheme<Border>().outer_space;
  }

  /**
   * @copydoc Decorator::renderWidget
   */
  void Border::renderWidget(Size const& size) const
  {
    ASSERTOP(rootWidget(), ne, nullptr);

    rootWidget()->getTheme().getControlTheme<Border>().renderWidget(*this, size);
  }

  /**
   * We do not want any Position events that occurred directly on the Border to get passed on.
   * Therefore this method is overwritten and checks for that.
   */
  void Border::handlePositionEvent(PositionEvent const& event)
  {
    if (isPositionInBorder(event.position()))
      event.callHandler(*this);
    else
      Decorator::handlePositionEvent(event);
  }

  /**
   * @copydoc Decorator::shrinkClientArea
   */
  void Border::shrinkClientArea(Bounds& bounds) const
  {
    SizeT w = outerSpace() + width() + innerSpace();

    bounds.x += w;
    bounds.y += w;

    bounds.w -= 2 * w;
    bounds.h -= no_top_border_ ? w : 2 * w;
  }

  /**
   * @param position absolute position to check whether it is within the bounds of the border
   * @return true if the position is within the border, false otherwise
   */
  bool Border::isPositionInBorder(Position const& position) const
  {
    Bounds bounds = utl::getRectangle(absolutePosition(), size());

    if (contains(bounds, position))
    {
      shrinkClientArea(bounds);
      return !contains(bounds, position);
    }
    return false;
  }
}
