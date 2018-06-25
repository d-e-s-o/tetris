// CaptionBar.cpp

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


namespace gui
{
  CaptionBarArea::CaptionBarArea(CaptionBar const& caption_bar, Widget& widget)
    : Decorator(widget),
      caption_bar_(&caption_bar)
  {
  }

  /**
   * @copydoc Decorator::shrinkClientArea
   */
  void CaptionBarArea::shrinkClientArea(Bounds& bounds) const
  {
    bounds.h -= caption_bar_->height();
  }

  /**
   * @copydoc Decorator::Decorator
   */
  CaptionBar::CaptionBar(Widget& widget)
    : Decorator(widget),
      button_(*this, widget),
      area_(*this, widget),
      logic_(*this, widget)
  {
    button_.insertAfter(*this);
    area_.insertAfter(button_);
  }

  /**
   * @copydoc Decorator::onMouseDown
   */
  void CaptionBar::onMouseDown(Position const& position, MouseButton button)
  {
    logic_.onMouseDown(position, button);
  }

  /**
   * @copydoc Decorator::onMouseUp
   */
  void CaptionBar::onMouseUp(Position const& position, MouseButton button)
  {
    logic_.onMouseUp(position, button);
  }

  /**
   * @copydoc Decorator::onMouseMove
   */
  void CaptionBar::onMouseMove(Position const& position)
  {
    logic_.onMouseMove(position);
  }

  /**
   *
   */
  void CaptionBar::onClose()
  {
    getWidget().hide();
  }

  /**
   * @copydoc Decorator::position
   */
  Position CaptionBar::position() const
  {
    return Position(0, Decorator::size().y - height());
  }

  /**
   * @copydoc Decorator::size
   */
  Size CaptionBar::size() const
  {
    return Size(Decorator::size().x, height());
  }

  /**
   * @return font used for rendering text on this control
   */
  Font const& CaptionBar::getFont() const
  {
    return *rootWidget()->getTheme().getControlTheme<CaptionBar>().font;
  }

  /**
   * @return height of the caption bar
   */
  SizeT CaptionBar::height() const
  {
    return rootWidget()->getTheme().getControlTheme<CaptionBar>().height;
  }

  /**
   * @return space between the displayed text and the left edge of the client area
   */
  SizeT CaptionBar::textSpace() const
  {
    return rootWidget()->getTheme().getControlTheme<CaptionBar>().text_space;
  }

  /**
   * @return space between the button and the edges
   */
  SizeT CaptionBar::buttonSpace() const
  {
    return rootWidget()->getTheme().getControlTheme<CaptionBar>().button_space;
  }

  /**
   * @copydoc Decorator::renderWidget
   */
  void CaptionBar::renderWidget(Size const& size) const
  {
    ASSERTOP(rootWidget(), ne, nullptr);

    rootWidget()->getTheme().getControlTheme<CaptionBar>().renderWidget(*this, size);
  }

  /**
   * This method is overwritten to only let events get passed to the underlying decorator/widget
   * that happened to occur while the mouse was not captured by it.
   */
  void CaptionBar::handlePositionEvent(PositionEvent const& event)
  {
    if (logic_.isCaptured() || isPositionInCaptionBar(event.position()))
      event.callHandler(*this);
    else
      Decorator::handlePositionEvent(event);
  }

  /**
   * @copydoc Decorator::getFirst
   */
  Decorator& CaptionBar::getFirst()
  {
    return *this;
  }

  /**
   * @copydoc Decorator::getLast
   */
  Decorator& CaptionBar::getLast()
  {
    return area_;
  }

  /**
   * @copydoc Decorator::isChild
   */
  bool CaptionBar::isChild(Decorator const& decorator) const
  {
    return (&decorator == &button_) || (&decorator == &area_);
  }

  /**
   * @return true if the position is not only within the bounds of the widget but also in the
   *         caption bar itself, false otherwise
   */
  bool CaptionBar::isPositionInCaptionBar(Position const& position) const
  {
    Bounds bounds = getAbsoluteBounds(*this);

    if (contains(bounds, position))
    {
      area_.shrinkClientArea(bounds);
      return !contains(bounds, position);
    }
    return false;
  }
}
