// GroupBox.hpp

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

#ifndef GUIGROUPBOX_HPP
#define GUIGROUPBOX_HPP

#include "gui/String.hpp"
#include "gui/widget/Decorator.hpp"
#include "gui/widget/Container.hpp"


namespace gui
{
  class Font;


  class LIBGUI_EXPORT GroupBoxBorder: public Decorator
  {
  public:
    GroupBoxBorder(Widget& widget);

    String const& getText() const;
    void setText(String const& string);

  private:
    String text_;
  };


  /**
   *
   */
  class LIBGUI_EXPORT GroupBox: public Container
  {
  public:
    GroupBox(Bounds const& bounds);

    String const& getText() const;
    void setText(String const& string);

    Font const& getFont() const;

  protected:
    virtual void renderWidget(Size const& size) const;
    virtual void renderContent(Size const& size) const;

  private:
    GroupBoxBorder border_;
  };
}


namespace gui
{
  /**
   * @return text to be displayed
   */
  inline String const& GroupBoxBorder::getText() const
  {
    return text_;
  }

  /**
   * @param text new text to be displayed
   */
  inline void GroupBoxBorder::setText(String const& text)
  {
    text_ = text;
  }

  /**
   * @return text to be displayed
   */
  inline String const& GroupBox::getText() const
  {
    return border_.getText();
  }

  /**
   * @param text new text to be displayed
   */
  inline void GroupBox::setText(String const& text)
  {
    border_.setText(text);
  }
}


#endif
