// Button.cpp

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
#include "gui/widget/control/Button.hpp"


namespace gui
{
  /**
   * @copydoc Widget::Widget
   */
  Button::Button(Bounds const& bounds)
    : Widget(bounds),
      logic_(*this),
      text_()
  {
    setAlwaysOnBottom(true);
  }

  /**
   * @copydoc Widget::onMouseDown
   */
  void Button::onMouseDown(Position const& position, MouseButton button)
  {
    logic_.onMouseDown(position, button);
  }

  /**
   * @copydoc Widget::onMouseUp
   */
  void Button::onMouseUp(Position const& position, MouseButton button)
  {
    logic_.onMouseUp(position, button);
  }

  /**
   * @copydoc Widget::onKeyDown
   */
  void Button::onKeyDown(Key key, ModifierKey modifier)
  {
    logic_.onKeyDown(key, modifier);
  }

  /**
   * @copydoc Widget::onKeyUp
   */
  void Button::onKeyUp(Key key, ModifierKey modifier)
  {
    logic_.onKeyUp(key, modifier);
  }

  /**
   * This method is called whenever the button was clicked. A "click" in that case means pressing
   * and releasing the appropriate key or pressing and releasing the mouse over the widget.
   */
  void Button::onClick()
  {
  }

  /**
   * @return font used for rendering text on this control
   */
  Font const& Button::getFont() const
  {
    ASSERTOP(rootWidget(), ne, nullptr);

    return *rootWidget()->getTheme().getControlTheme<Button>().font;
  }

  /**
   * @copydoc Widget::renderWidget
   */
  void Button::renderWidget(Size const& size) const
  {
    ASSERTOP(rootWidget(), ne, nullptr);

    rootWidget()->getTheme().getControlTheme<Button>().renderWidget(*this, size);
  }

  /**
   * @copydoc Widget::renderContent
   */
  void Button::renderContent(Size const& size) const
  {
    ASSERTOP(rootWidget(), ne, nullptr);

    rootWidget()->getTheme().getControlTheme<Button>().renderContent(*this, size);
  }
}
