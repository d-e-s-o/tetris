// StaticText.hpp

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

#ifndef GUISTATICTEXT_HPP
#define GUISTATICTEXT_HPP

#include <util/Assert.hpp>

#include "gui/Alignment.hpp"
#include "gui/String.hpp"
#include "gui/widget/Widget.hpp"


namespace gui
{
  class Font;


  /**
   * This class represents a static text control. The displayed text can be aligned to the
   * different sides.
   */
  class LIBGUI_EXPORT StaticText: public Widget
  {
  public:
    StaticText(Bounds const& bounds);

    String const& getText() const;
    void setText(String const& string);

    HAlignment getHAlignment() const;
    void setHAlignment(HAlignment alignment);

    VAlignment getVAlignment() const;
    void setVAlignment(VAlignment alignment);

    Font const& getFont() const;

    SizeT textSpace() const;

  protected:
    virtual void renderWidget(Size const& size) const;
    virtual void renderContent(Size const& size) const;

  private:
    String text_;
    HAlignment h_alignment_;
    VAlignment v_alignment_;
  };
}


namespace gui
{
  /**
   * @return text to be displayed
   */
  inline String const& StaticText::getText() const
  {
    return text_;
  }

  /**
   * @param text new text to be displayed
   */
  inline void StaticText::setText(String const& text)
  {
    text_ = text;
  }

  /**
   * @return horizontal alignment the text has
   */
  inline HAlignment StaticText::getHAlignment() const
  {
    return h_alignment_;
  }

  /**
   * @param alignment new horizontal alignment the text should have
   */
  inline void StaticText::setHAlignment(HAlignment alignment)
  {
    ASSERTOP(alignment, gt, H_ALIGNMENT_MIN);
    ASSERTOP(alignment, lt, H_ALIGNMENT_MAX);

    h_alignment_ = alignment;
  }

  /**
   * @return vertical alignment the text has
   */
  inline VAlignment StaticText::getVAlignment() const
  {
    return v_alignment_;
  }

  /**
   * @param alignment new vertical alignment the text should have
   */
  inline void StaticText::setVAlignment(VAlignment alignment)
  {
    ASSERTOP(alignment, gt, V_ALIGNMENT_MIN);
    ASSERTOP(alignment, lt, V_ALIGNMENT_MAX);

    v_alignment_ = alignment;
  }
}


#endif
