// SimpleCheckBox.cpp

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

#include "gui/widget/control/CheckBox.hpp"
#include "gui/widget/control/theme/simple/SimpleThemeFunctions.hpp"
#include "gui/widget/control/theme/simple/SimpleCheckBox.hpp"


namespace gui
{
  /**
   *
   */
  SimpleThemeBase::SimpleControlThemeBase<CheckBox>::SimpleControlThemeBase(Theme& theme)
    : ControlTheme<CheckBox>(theme)
  {
    font_data = getDefaultFontData();
    font      = createFont(theme, font_data);

    rectangle_space = 3;
    text_space      = 2;
  }

  /**
   *
   */
  void SimpleThemeBase::SimpleControlThemeBase<CheckBox>::renderWidget(CheckBox const& widget, Size const& size) const
  {
    ASSERT(size == widget.size());

    renderControl(getRectangle(Point(), size));
  }

  /**
   *
   */
  void SimpleThemeBase::SimpleControlThemeBase<CheckBox>::renderContent(CheckBox const& widget, Size const& size) const
  {
    ASSERT(size == utl::getSize(widget.clientArea()));

    Rectangle rectangle = Rectangle(rectangle_space,
                                    rectangle_space,
                                    size.y - rectangle_space,
                                    size.y - rectangle_space);

    renderBox(rectangle, widget.isChecked());

    PositionT left = size.y - rectangle_space + text_space;

    renderMarginString(getTheme().getRenderer(),
                       *font,
                       widget.getText(),
                       font_data.font_color,
                       size,
                       Alignment(H_ALIGNMENT_LEFT, V_ALIGNMENT_CENTERED),
                       Margin(left, text_space, text_space, text_space));
  }

  /**
   *
   */
  SimpleTheme::SimpleControlTheme<CheckBox>::SimpleControlTheme(SimpleTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<CheckBox>, SimpleTheme>(theme)
  {
    no_check_color = Color(0xFF, 0xFF, 0xFF);
    check_color    = Color(0x00, 0x00, 0x00);
    bkgd_color     = Color(0x49, 0x4E, 0x49);
  }

  /**
   *
   */
  void SimpleTheme::SimpleControlTheme<CheckBox>::renderControl(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme().getRenderer(), rectangle, bkgd_color);
  }

  /**
   *
   */
  void SimpleTheme::SimpleControlTheme<CheckBox>::renderBox(Rectangle const& rectangle, bool checked) const
  {
    renderRectangle(getTheme().getRenderer(), rectangle, no_check_color);

    if (checked)
    {
      Rectangle rectangle1 = rectangle;

      rectangle1.x1_ += rectangle_space;
      rectangle1.y1_ += rectangle_space;
      rectangle1.x2_ -= rectangle_space;
      rectangle1.y2_ -= rectangle_space;

      renderRectangle(getTheme().getRenderer(), rectangle1, check_color);
    }
  }

  /**
   *
   */
  SimpleTextureTheme::SimpleTextureControlTheme<CheckBox>::SimpleTextureControlTheme(SimpleTextureTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<CheckBox>, SimpleTextureTheme>(theme)
  {
    no_check_color = Color(0xFF, 0xFF, 0xFF);
    check_color    = Color(0xFF, 0xFF, 0xFF);
    bkgd_color     = Color(0xFF, 0xFF, 0xFF);
  }

  /**
   *
   */
  void SimpleTextureTheme::SimpleTextureControlTheme<CheckBox>::renderControl(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme(), rectangle, getTheme().getPixelData().check_box_.widget_, bkgd_color);
  }

  /**
   *
   */
  void SimpleTextureTheme::SimpleTextureControlTheme<CheckBox>::renderBox(Rectangle const& rectangle, bool checked) const
  {
    if (checked)
      renderRectangle(getTheme(), rectangle, getTheme().getPixelData().check_box_.box_checked_, check_color);
    else
      renderRectangle(getTheme(), rectangle, getTheme().getPixelData().check_box_.box_, no_check_color);
  }
}
