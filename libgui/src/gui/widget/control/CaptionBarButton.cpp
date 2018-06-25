// CaptionBarButton.cpp

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

#include "gui/event/PositionEvent.hpp"
#include "gui/widget/RootWidget.hpp"
#include "gui/widget/control/theme/Theme.hpp"
#include "gui/widget/control/CaptionBar.hpp"
#include "gui/widget/control/CaptionBarButton.hpp"


namespace gui
{
  /**
   * Create a new button for the given caption bar. As this class is a Decorator it also belongs
   * to a widget, which has to be given.
   * @param caption_bar CaptionBar the button belongs to (is used to position the button)
   * @param widget widget the Decorator belongs to
   */
  CaptionBarButton::CaptionBarButton(CaptionBar& caption_bar, Widget& widget)
    : Decorator(widget),
      logic_(*this),
      caption_bar_(&caption_bar)
  {
    ASSERTOP(caption_bar_, ne, nullptr);
  }

  /**
   * @copydoc Decorator::onMouseDown
   */
  void CaptionBarButton::onMouseDown(Position const& position, MouseButton button)
  {
    logic_.onMouseDown(position, button);
  }

  /**
   * @copydoc Decorator::onMouseUp
   */
  void CaptionBarButton::onMouseUp(Position const& position, MouseButton button)
  {
    logic_.onMouseUp(position, button);
  }

  /**
   * This method gets called if the button was clicked. It takes care for closing the caption bar
   * (which will close the dialog it belongs to).
   */
  void CaptionBarButton::onClick()
  {
    ASSERTOP(caption_bar_, ne, nullptr);
    caption_bar_->onClose();
  }

  /**
   * @copydoc Decorator::position
   */
  Position CaptionBarButton::position() const
  {
    ASSERTOP(caption_bar_, ne, nullptr);

    Position position = caption_bar_->position();

    PositionT x = position.x + caption_bar_->size().x - size().x;
    PositionT y = position.y;
    SizeT space = caption_bar_->buttonSpace();

    return Position(x - space, y + space);
  }

  /**
   * @copydoc Decorator::size
   */
  Size CaptionBarButton::size() const
  {
    ASSERTOP(caption_bar_, ne, nullptr);

    SizeT height = caption_bar_->height();
    SizeT space  = caption_bar_->buttonSpace();

    return Size(height - 2 * space, height - 2 * space);
  }

  /**
   * @copydoc Decorator::renderWidget
   */
  void CaptionBarButton::renderWidget(Size const& size) const
  {
    ASSERTOP(rootWidget(), ne, nullptr);

    rootWidget()->getTheme().getControlTheme<CaptionBarButton>().renderWidget(*this, size);
  }

  /**
   * @copydoc Decorator::handlePositionEvent
   */
  void CaptionBarButton::handlePositionEvent(PositionEvent const& event)
  {
    if (logic_.isCaptured() || isPositionInButton(event.position()))
      event.callHandler(*this);
    else
      Decorator::handlePositionEvent(event);
  }

  /**
   * @return true if the position is within the button, false otherwise
   */
  bool CaptionBarButton::isPositionInButton(Position const& position) const
  {
    Bounds bounds = getAbsoluteBounds(*this);
    return contains(bounds, position);
  }
}
