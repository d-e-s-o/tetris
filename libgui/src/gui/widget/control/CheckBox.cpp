// CheckBox.cpp

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

#include "gui/widget/RootWidget.hpp"
#include "gui/widget/control/theme/Theme.hpp"
#include "gui/widget/control/CheckBox.hpp"


namespace gui
{
  /**
   * @copydoc Widget::Widget
   */
  CheckBox::CheckBox(Bounds const& bounds)
    : Widget(bounds),
      logic_(*this),
      text_(),
      checked_(false)
  {
    setAlwaysOnBottom(true);
  }

  /**
   * @copydoc Widget::onMouseDown
   */
  void CheckBox::onMouseDown(Position const& position, MouseButton button)
  {
    logic_.onMouseDown(position, button);
  }

  /**
   * @copydoc Widget::onMouseUp
   */
  void CheckBox::onMouseUp(Position const& position, MouseButton button)
  {
    logic_.onMouseUp(position, button);
  }

  /**
   * @copydoc Widget::onKeyDown
   */
  void CheckBox::onKeyDown(Key key, ModifierKey modifier)
  {
    logic_.onKeyDown(key, modifier);
  }

  /**
   * @copydoc Widget::onKeyUp
   */
  void CheckBox::onKeyUp(Key key, ModifierKey modifier)
  {
    logic_.onKeyUp(key, modifier);
  }

  /**
   * This method is called whenever the CheckBox is clicked. A "click" in that case is any state
   * change, caused by either action key press and release, mouse down and release or simple
   * calling SetChecked with a different value than the current one.
   */
  void CheckBox::onClick()
  {
  }

  /**
   * @return font used for rendering text on this control
   */
  Font const& CheckBox::getFont() const
  {
    return *rootWidget()->getTheme().getControlTheme<CheckBox>().font;
  }

  /**
   * @return space between the rectangle that signals the state and the left, top and bottom edges
   */
  SizeT CheckBox::getRectangleSpace() const
  {
    return rootWidget()->getTheme().getControlTheme<CheckBox>().rectangle_space;
  }

  /**
   * @return space between the text being displayed and the right edge of the rectangle signaling
   *         the check state
   */
  SizeT CheckBox::textSpace() const
  {
    return rootWidget()->getTheme().getControlTheme<CheckBox>().text_space;
  }

  /**
   * @copydoc Widget::renderWidget
   */
  void CheckBox::renderWidget(Size const& size) const
  {
    ASSERTOP(rootWidget(), ne, nullptr);

    rootWidget()->getTheme().getControlTheme<CheckBox>().renderWidget(*this, size);
  }

  /**
   * @copydoc Widget::renderContent
   */
  void CheckBox::renderContent(Size const& size) const
  {
    ASSERTOP(rootWidget(), ne, nullptr);

    rootWidget()->getTheme().getControlTheme<CheckBox>().renderContent(*this, size);
  }
}
