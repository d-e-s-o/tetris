// EditableText.cpp

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

#include <algorithm>
#include <util/Assert.hpp>

#include "gui/widget/control/EditableText.hpp"


namespace gui
{
  /**
   * Constant representing first position in string
   */
  EditableText::Caret const EditableText::CARET_BEGIN = 0;

  /**
   * Constant representing last position in string
   */
  EditableText::Caret const EditableText::CARET_END = static_cast<Caret>(-1);


  /**
   * Create editable text object from given text. The caret will be set to the
   * last position in the text.
   * @param text string used as intern text
   */
  EditableText::EditableText()
    : text_(),
      caret_(0),
      selection_(0)
  {
  }

  /**
   * Retrieve the current text.
   * @return current version of the edited text
   */
  String const& EditableText::getText() const
  {
    return text_;
  }

  /**
   * Set the text to edit. The caret will be set to the end of the string.
   * @param text new text to edit
   */
  void EditableText::setText(String const& text)
  {
    text_ = text;
    setCaret(CARET_END);

    ASSERTOP(caret_, ge, 0);
    ASSERTOP(caret_, le, text_.size());
  }

  /**
   * Retrieve the current caret position relative to the begin.
   * @return current position of the caret in the text
   */
  EditableText::Caret EditableText::getCaret() const
  {
    ASSERTOP(caret_, ge, 0);
    ASSERTOP(caret_, le, text_.size());
    return caret_;
  }

  /**
   * Set the current caret position in the text:
   * - CARET_BEGIN sets the caret to the first character
   * - CARET_END sets the caret to the last character
   * @param position position value for the caret
   */
  void EditableText::setCaret(Caret caret, bool with_select)
  {
    if (caret <= 0 || caret == CARET_BEGIN)
      caret_ = 0;
    else if (caret >= text_.size() || caret == CARET_END)
      caret_ = text_.size();
    else
      caret_ = caret;

    if (!with_select)
      selection_ = caret_;

    ASSERTOP(caret_, ge, 0);
    ASSERTOP(caret_, le, text_.size());
  }

  /**
   *
   */
  EditableText::Caret EditableText::getSelection() const
  {
    return selection_;
  }

  /**
   *
   */
  void EditableText::moveCaretLeft(bool with_select)
  {
    ASSERTOP(caret_, ge, 0);
    ASSERTOP(caret_, le, text_.size());

    // move caret left with selection (like pressing shift + left)
    if (with_select)
    {
      if (caret_ > 0)
        --caret_;
    }
    // move caret left without selection (like pressing left)
    else
    {
      // if there is no selection currently
      if (caret_ == selection_)
      {
        if (caret_ > 0)
          --caret_;

        selection_ = caret_;
      }
      // if there is a selection, move caret to most left of selected area
      else
        caret_ = selection_ = std::min(caret_, selection_);
    }

    ASSERTOP(caret_, ge, 0);
    ASSERTOP(caret_, le, text_.size());
  }

  /**
   *
   */
  void EditableText::moveCaretRight(bool with_select)
  {
    ASSERTOP(caret_, ge, 0);
    ASSERTOP(caret_, le, text_.size());

    // move caret right with selection (like pressing shift + right)
    if (with_select)
    {
      if (caret_ < text_.size())
        ++caret_;
    }
    // move caret right without selection (like pressing right)
    else
    {
      // if there is no selection currently
      if (caret_ == selection_)
      {
        if (caret_ < text_.size())
          ++caret_;

        selection_ = caret_;
      }
      // if there is a selection, move caret to most right of selected area
      else
        caret_ = selection_ = std::max(caret_, selection_);
    }

    ASSERTOP(caret_, ge, 0);
    ASSERTOP(caret_, le, text_.size());
  }

  /**
   * This method inserts a new character into the text at the current caret position.
   * @param character character to insert into the string
   */
  void EditableText::insertCharacter(char_t character)
  {
    ASSERTOP(caret_, ge, 0);
    ASSERTOP(caret_, le, text_.size());

    // if there is a selection we replace it with the given character
    if (caret_ != selection_)
      eraseSelection();

    if (caret_ == text_.size())
    {
      append(text_, character);
      ++caret_;
    }
    else
      insert(text_, caret_++, character);

    selection_ = caret_;

    ASSERTOP(caret_, ge, 0);
    ASSERTOP(caret_, le, text_.size());
  }

  /**
   *
   */
  void EditableText::eraseLeftCharacter()
  {
    ASSERTOP(caret_, ge, 0);
    ASSERTOP(caret_, le, text_.size());

    if (caret_ == selection_)
    {
      if (caret_ > 0)
        remove(text_, --caret_, 1);

      selection_ = caret_;
    }
    else
      eraseSelection();

    ASSERTOP(caret_, ge, 0);
    ASSERTOP(caret_, le, text_.size());
  }

  /**
   *
   */
  void EditableText::eraseRightCharacter()
  {
    ASSERTOP(caret_, ge, 0);
    ASSERTOP(caret_, le, text_.size());

    if (caret_ == selection_)
    {
      if (caret_ < text_.size())
        remove(text_, caret_, 1);

      selection_ = caret_;
    }
    else
      eraseSelection();

    ASSERTOP(caret_, ge, 0);
    ASSERTOP(caret_, le, text_.size());
  }

  /**
   *
   */
  void EditableText::eraseSelection()
  {
    ASSERTOP(caret_, ne, selection_);

    size_t index = std::min(caret_, selection_);
    size_t count = std::max(caret_, selection_) - index;

    remove(text_, index, count);

    caret_ = selection_ = index;
  }
}
