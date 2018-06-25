// EditBox.hpp

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

#ifndef GUIEDITBOX_HPP
#define GUIEDITBOX_HPP

#include "gui/widget/Widget.hpp"
#include "gui/widget/control/EditBoxLogic.hpp"
#include "gui/widget/control/EditableText.hpp"


namespace gui
{
  /**
   * This widget represents an EditBox. It can be used for entering text via keyboard. A caret
   * marks where the next character will be inserted.
   * @todo maybe we could add something like OnChange here too
   */
  class LIBGUI_EXPORT EditBox: public Widget
  {
  public:
    typedef EditableText::Caret Caret;

    EditBox(Bounds const& bounds);

    virtual void onMouseDown(Position const& position, MouseButton button);
    virtual void onMouseUp(Position const& position, MouseButton button);
    virtual void onMouseMove(Position const& position);
    virtual void onKeyDown(Key key, ModifierKey modifier);
    virtual void onChar(char_t character);

    String const& getText() const;
    void setText(String const& string);

    Caret getCaret() const;
    void setCaret(Caret caret, bool with_select = false);

    Caret getSelection() const;

  protected:
    virtual void renderWidget(Size const& size) const;
    virtual void renderContent(Size const& size) const;

  private:
    EditBoxLogic<EditBox> logic_;
    EditableText          text_;
  };
}


namespace gui
{
  /**
   * @return text to be displayed
   */
  inline String const& EditBox::getText() const
  {
    return text_.getText();
  }

  /**
   * @param text new text to be displayed
   */
  inline void EditBox::setText(String const& text)
  {
    text_.setText(text);
  }

  /**
   * @return current position the caret has
   */
  inline EditBox::Caret EditBox::getCaret() const
  {
    return text_.getCaret();
  }

  /**
   * @param caret new caret position to set
   */
  inline void EditBox::setCaret(Caret caret, bool with_select)
  {
    text_.setCaret(caret, with_select);
  }

  /**
   *
   */
  inline EditBox::Caret EditBox::getSelection() const
  {
    return text_.getSelection();
  }
}


#endif
