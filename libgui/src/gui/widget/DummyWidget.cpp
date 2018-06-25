// DummyWidget.cpp

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

#include "gui/widget/DummyWidget.hpp"


namespace gui
{
  void DummyWidget::onGainFocus()
  {
  }

  void DummyWidget::onLooseFocus()
  {
  }

  void DummyWidget::onShow()
  {
  }

  void DummyWidget::onHide()
  {
  }

  void DummyWidget::onMouseDown(Position const& position, MouseButton button)
  {
  }

  void DummyWidget::onMouseUp(Position const& position, MouseButton button)
  {
  }

  void DummyWidget::onMouseMove(Position const& position)
  {
  }

  void DummyWidget::onMouseWheelDown(unsigned int units)
  {
  }

  void DummyWidget::onMouseWheelUp(unsigned int units)
  {
  }

  void DummyWidget::onKeyDown(Key key, ModifierKey modifier)
  {
  }

  void DummyWidget::onKeyUp(Key key, ModifierKey modifier)
  {
  }

  void DummyWidget::onChar(char_t character)
  {
  }

  void DummyWidget::onCanResize(Size const& size, bool& can_resize)
  {
  }

  void DummyWidget::onResize(Size const& size)
  {
  }

  void DummyWidget::onMove(Position const& position)
  {
  }

  RootWidget* DummyWidget::rootWidget() const
  {
    return 0;
  }

  Widget* DummyWidget::focusedWidget() const
  {
    return 0;
  }

  Bounds DummyWidget::clientArea() const
  {
    return Bounds();
  }

  Position DummyWidget::absolutePosition() const
  {
    return Position();
  }

  Position DummyWidget::position() const
  {
    return Position();
  }

  void DummyWidget::move(Position const& position)
  {
  }

  Size DummyWidget::size() const
  {
    return Size();
  }

  void DummyWidget::resize(Size const& size)
  {
  }

  void DummyWidget::render(Size const& size) const
  {
  }

  void DummyWidget::handleFocusEvent(FocusEvent const& event)
  {
  }

  void DummyWidget::handlePositionEvent(PositionEvent const& event)
  {
  }

  void DummyWidget::handleBroadcastEvent(BroadcastEvent const& event)
  {
  }

  void DummyWidget::handleWidgetEvent(WidgetEvent const& event)
  {
  }
}
