// SimpleProgressBar.cpp

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
#include <util/Rectangle1Functions.hpp>
#include <util/Rectangle2Functions.hpp>

#include "gui/util/LexicalCast.hpp"
#include "gui/widget/control/ProgressBar.hpp"
#include "gui/widget/control/theme/simple/SimpleThemeFunctions.hpp"
#include "gui/widget/control/theme/simple/SimpleProgressBar.hpp"


namespace gui
{
  /**
   *
   */
  SimpleThemeBase::SimpleControlThemeBase<ProgressBar>::SimpleControlThemeBase(Theme& theme)
    : ControlTheme<ProgressBar>(theme)
  {
    font_data = getDefaultFontData();
    font      = createFont(theme, font_data);

    bar_space = 3;
  }

  /**
   *
   */
  void SimpleThemeBase::SimpleControlThemeBase<ProgressBar>::renderWidget(ProgressBar const& widget, Size const& size) const
  {
    ASSERT(size == widget.size());

    renderControl(getRectangle(Point(), size));
  }

  /**
   *
   */
  void SimpleThemeBase::SimpleControlThemeBase<ProgressBar>::renderContent(ProgressBar const& widget, Size const& size) const
  {
    ASSERT(size == utl::getSize(widget.clientArea()));

    SizeT offset = calculateValueOffset(size.x - 2 * bar_space,
                                        widget.getMinValue(),
                                        widget.getMaxValue(),
                                        widget.getProgress());

    Rectangle rectangle;
    rectangle.x1_ = bar_space;
    rectangle.y1_ = bar_space;
    rectangle.x2_ = rectangle.x1_ + offset;
    rectangle.y2_ = size.y - bar_space;

    renderBar(rectangle);

    renderMarginString(getTheme().getRenderer(),
                       *font,
                       lexicalCast<int, String>(widget.getProgress()) + String(TEXT("%")),
                       font_data.font_color,
                       size,
                       Alignment(H_ALIGNMENT_CENTERED, V_ALIGNMENT_CENTERED),
                       Margin(bar_space, bar_space, bar_space, bar_space));
  }

  /**
   *
   */
  SimpleTheme::SimpleControlTheme<ProgressBar>::SimpleControlTheme(SimpleTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<ProgressBar>, SimpleTheme>(theme)
  {
    bar_color  = Color(0x7D, 0x80, 0x78);
    bkgd_color = Color(0x49, 0x4E, 0x49);
  }

  /**
   *
   */
  void SimpleTheme::SimpleControlTheme<ProgressBar>::renderControl(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme().getRenderer(), rectangle, bkgd_color);
  }

  /**
   *
   */
  void SimpleTheme::SimpleControlTheme<ProgressBar>::renderBar(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme().getRenderer(), rectangle, bar_color);
  }

  /**
   *
   */
  SimpleTextureTheme::SimpleTextureControlTheme<ProgressBar>::SimpleTextureControlTheme(SimpleTextureTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<ProgressBar>, SimpleTextureTheme>(theme)
  {
    bar_color  = Color(0xFF, 0xFF, 0xFF);
    bkgd_color = Color(0xFF, 0xFF, 0xFF);
  }

  /**
   *
   */
  void SimpleTextureTheme::SimpleTextureControlTheme<ProgressBar>::renderControl(Rectangle const& rectangle) const
  {
    Margin margin;
    margin.left  = getTheme().getPixelData().progress_bar_.left_margin_;
    margin.right = getTheme().getPixelData().progress_bar_.right_margin_;

    renderRectangle(getTheme(), rectangle, getTheme().getPixelData().progress_bar_.widget_, bkgd_color, margin);
  }

  /**
   *
   */
  void SimpleTextureTheme::SimpleTextureControlTheme<ProgressBar>::renderBar(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme(), rectangle, getTheme().getPixelData().progress_bar_.bar_, bar_color);
  }
}
