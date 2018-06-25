// EditableText.hpp

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

#ifndef GUIEDITABLETEXT_HPP
#define GUIEDITABLETEXT_HPP

#include "gui/Config.hpp"
#include "gui/String.hpp"


namespace gui
{
  /**
   * This class represents an editable text. A caret can be moved to decide which character to
   * remove next or where to insert the next one.
   */
  class LIBGUI_EXPORT EditableText
  {
  public:
    typedef size_t Caret;

    static Caret const CARET_BEGIN;
    static Caret const CARET_END;

    EditableText();

    String const& getText() const;
    void setText(String const& text);

    Caret getCaret() const;
    void setCaret(Caret caret, bool with_select = false);

    Caret getSelection() const;

    void moveCaretLeft(bool with_select = false);
    void moveCaretRight(bool with_select = false);

    void insertCharacter(char_t character);
    void eraseLeftCharacter();
    void eraseRightCharacter();

  private:
    String text_;
    Caret  caret_;
    Caret  selection_;

    EditableText(EditableText const&);
    EditableText& operator =(EditableText const&);

    void eraseSelection();
  };
}


#endif
