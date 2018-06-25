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

#ifndef GUIBUTTON_HPP
#define GUIBUTTON_HPP

#include "gui/String.hpp"
#include "gui/widget/Widget.hpp"
#include "gui/widget/control/ButtonLogic.hpp"


namespace gui
{
  class Font;


  /**
   * This class is used for objects that execute an action, if clicked on them. It may also have a
   * text which will be centralized on it.
   */
  class LIBGUI_EXPORT Button: public Widget
  {
  public:
    Button(Bounds const& bounds);

    virtual void onMouseDown(Position const& position, MouseButton button);
    virtual void onMouseUp(Position const& position, MouseButton button);
    virtual void onKeyDown(Key key, ModifierKey modifier);
    virtual void onKeyUp(Key key, ModifierKey modifier);

    virtual void onClick();

    bool isPressed() const;

    String const& getText() const;
    void setText(String const& string);

    Font const& getFont() const;

  protected:
    virtual void renderWidget(Size const& size) const;
    virtual void renderContent(Size const& size) const;

  private:
    ButtonLogic<Button> logic_;

    String text_;
  };
}


namespace gui
{
  /**
   * @return text to be displayed
   */
  inline String const& Button::getText() const
  {
    return text_;
  }

  /**
   * @param text new text to be displayed
   */
  inline void Button::setText(String const& text)
  {
    text_ = text;
  }

  /**
   * @return true if button is pressed, false if not
   */
  inline bool Button::isPressed() const
  {
    return logic_.isPressed();
  }
}


#endif
