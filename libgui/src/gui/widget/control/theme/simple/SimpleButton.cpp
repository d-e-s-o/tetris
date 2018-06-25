// SimpleButton.cpp

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
#include <util/Rectangle2Functions.hpp>

#include "gui/widget/control/Button.hpp"
#include "gui/widget/control/theme/simple/SimpleThemeFunctions.hpp"
#include "gui/widget/control/theme/simple/SimpleButton.hpp"


namespace gui
{
  /**
   *
   */
  SimpleThemeBase::SimpleControlThemeBase<Button>::SimpleControlThemeBase(Theme& theme)
    : ControlTheme<Button>(theme)
  {
    font_data = getDefaultFontData();
    font      = createFont(theme, font_data);

    text_space = 2;
  }

  /**
   *
   */
  void SimpleThemeBase::SimpleControlThemeBase<Button>::renderWidget(Button const& widget, Size const& size) const
  {
    ASSERT(size == widget.size());

    renderControl(getRectangle(Point(), size), widget.isPressed());
  }

  /**
   *
   */
  void SimpleThemeBase::SimpleControlThemeBase<Button>::renderContent(Button const& widget, Size const& size) const
  {
    ASSERT(size == utl::getSize(widget.clientArea()));

    renderMarginString(getTheme().getRenderer(),
                       *font,
                       widget.getText(),
                       font_data.font_color,
                       size,
                       Alignment(H_ALIGNMENT_CENTERED, V_ALIGNMENT_CENTERED),
                       Margin(text_space, text_space, text_space, text_space));
  }

  /**
   *
   */
  SimpleTheme::SimpleControlTheme<Button>::SimpleControlTheme(SimpleTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<Button>, SimpleTheme>(theme)
  {
    press_color = Color(0x7D, 0x80, 0x78);
    bkgd_color  = Color(0x49, 0x4E, 0x49);
  }

  /**
   *
   */
  void SimpleTheme::SimpleControlTheme<Button>::renderControl(Rectangle const& rectangle, bool pressed) const
  {
    renderRectangle(getTheme().getRenderer(), rectangle, pressed ? press_color : bkgd_color);
  }

  /**
   *
   */
  SimpleTextureTheme::SimpleTextureControlTheme<Button>::SimpleTextureControlTheme(SimpleTextureTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<Button>, SimpleTextureTheme>(theme)
  {
    press_color = Color(0xFF, 0xFF, 0xFF);
    bkgd_color  = Color(0xFF, 0xFF, 0xFF);
  }

  /**
   *
   */
  void SimpleTextureTheme::SimpleTextureControlTheme<Button>::renderControl(Rectangle const& rectangle, bool pressed) const
  {
    Margin margin;
    margin.left  = getTheme().getPixelData().button_.left_margin_;
    margin.right = getTheme().getPixelData().button_.right_margin_;

    if (pressed)
      renderRectangle(getTheme(), rectangle, getTheme().getPixelData().button_.widget_pressed_, press_color, margin);
    else
      renderRectangle(getTheme(), rectangle, getTheme().getPixelData().button_.widget_, bkgd_color, margin);
  }
}
