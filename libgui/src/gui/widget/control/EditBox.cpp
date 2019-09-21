// EditBox.cpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014,2019 Daniel Mueller (deso@posteo.net)    *
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

#include "gui/renderer/FontFunctions.hpp"
#include "gui/widget/RootWidget.hpp"
#include "gui/widget/control/theme/Theme.hpp"
#include "gui/widget/control/EditBox.hpp"


namespace gui
{
  /**
   * @copydoc Widget::Widget
   */
  EditBox::EditBox(Bounds const& bounds)
    : Widget(bounds),
      logic_(*this),
      text_()
  {
    setAlwaysOnBottom(true);
  }

  /**
   * @copydoc Widget::onMouseDown
   */
  void EditBox::onMouseDown(Position const& position, MouseButton button)
  {
    logic_.onMouseDown(position, button);
  }

  /**
   * @copydoc Widget::onMouseUp
   */
  void EditBox::onMouseUp(Position const& position, MouseButton button)
  {
    logic_.onMouseUp(position, button);
  }

  /**
   * @copydoc Widget::onMouseMove
   */
  void EditBox::onMouseMove(Position const& position)
  {
    logic_.onMouseMove(position);
  }

  /**
   * @copydoc Widget::onKeyDown
   * @todo think about moving this stuff into the logic
   * @todo think about removing the hard coded keys and putting this stuff into theme (like
   *       Theme::getActionKey() etc.)
   */
  void EditBox::onKeyDown(Key key, ModifierKey modifier)
  {
    bool select = wnd::checkForModifier(modifier, wnd::MOD_KEY_LSHIFT) ||
                  wnd::checkForModifier(modifier, wnd::MOD_KEY_RSHIFT);

    switch(key)
    {
    case wnd::KEY_BACKSPACE:
      text_.eraseLeftCharacter();
      break;

    case wnd::KEY_DELETE:
      text_.eraseRightCharacter();
      break;

    case wnd::KEY_LEFT:
      text_.moveCaretLeft(select);
      break;

    case wnd::KEY_RIGHT:
      text_.moveCaretRight(select);
      break;

    case wnd::KEY_HOME:
      text_.setCaret(text_.CARET_BEGIN, select);
      break;

    case wnd::KEY_END:
      text_.setCaret(text_.CARET_END, select);
      break;

    default:
      break;
    }
  }

  /**
   * @copydoc Widget::onChar
   */
  void EditBox::onChar(char_t character)
  {
    text_.insertCharacter(character);
  }

  /**
   * @copydoc Widget::renderWidget
   */
  void EditBox::renderWidget(Size const& size) const
  {
    ASSERTOP(rootWidget(), ne, nullptr);

    rootWidget()->getTheme().getControlTheme<EditBox>().renderWidget(*this, size);
  }

  /**
   * @copydoc Widget::renderContent
   */
  void EditBox::renderContent(Size const& size) const
  {
    ASSERTOP(rootWidget(), ne, nullptr);

    rootWidget()->getTheme().getControlTheme<EditBox>().renderContent(*this, size);
  }
}
