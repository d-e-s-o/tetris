// CheckBox.hpp

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

#ifndef GUICHECKBOX_HPP
#define GUICHECKBOX_HPP

#include "gui/String.hpp"
#include "gui/widget/Widget.hpp"
#include "gui/widget/control/CheckBoxLogic.hpp"


namespace gui
{
  class Font;


  /**
   * This class represents a check box. That is a control that has two click states and
   * changes between them after a full mouse press-release-combo.
   */
  class LIBGUI_EXPORT CheckBox: public Widget
  {
  public:
    CheckBox(Bounds const& bounds);

    virtual void onMouseDown(Position const& position, MouseButton button);
    virtual void onMouseUp(Position const& position, MouseButton button);
    virtual void onKeyDown(Key key, ModifierKey modifier);
    virtual void onKeyUp(Key key, ModifierKey modifier);

    virtual void onClick();

    bool isChecked() const;
    void setChecked(bool checked);

    bool isPressed() const;

    String const& getText() const;
    void setText(String const& string);

    Font const& getFont() const;

    SizeT getRectangleSpace() const;
    SizeT textSpace() const;

  protected:
    virtual void renderWidget(Size const& size) const;
    virtual void renderContent(Size const& size) const;

  private:
    CheckBoxLogic<CheckBox> logic_;

    String text_;
    bool   checked_;
  };
}


namespace gui
{
  /**
   * @copydoc CheckBoxLogic::isChecked
   */
  inline bool CheckBox::isChecked() const
  {
    return checked_;
  }

  /**
   * @copydoc CheckBoxLogic::setChecked
   */
  inline void CheckBox::setChecked(bool checked)
  {
    if (checked != checked_)
    {
      checked_ = checked;
      onClick();
    }
  }

  /**
   * @copydoc CheckBoxLogic::isPressed
   */
  inline bool CheckBox::isPressed() const
  {
    return logic_.isPressed();
  }

  /**
   * @return text to be displayed
   */
  inline String const& CheckBox::getText() const
  {
    return text_;
  }

  /**
   * @param text new text to be displayed
   */
  inline void CheckBox::setText(String const& text)
  {
    text_ = text;
  }
}


#endif
