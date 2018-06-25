// SimpleCaptionBar.cpp

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
#include <util/RectangleFunctions.hpp>

#include "gui/widget/WidgetFunctions.hpp"
#include "gui/widget/control/CaptionBar.hpp"
#include "gui/widget/control/theme/simple/SimpleThemeFunctions.hpp"
#include "gui/widget/control/theme/simple/SimpleCaptionBar.hpp"


namespace gui
{
  /**
   *
   */
  SimpleThemeBase::SimpleControlThemeBase<CaptionBar>::SimpleControlThemeBase(Theme& theme)
    : ControlTheme<CaptionBar>(theme)
  {
    font_data = getDefaultFontData();
    font      = createFont(theme, font_data);

    height       = 25;
    text_space   = 5;
    button_space = 3;
  }

  /**
   *
   */
  void SimpleThemeBase::SimpleControlThemeBase<CaptionBar>::renderWidget(CaptionBar const& widget, Size const& size) const
  {
    // @todo find out why this assertion fails
    //ASSERTOP(size, eq, widget.size());

    renderControl(utl::convert(getBounds(widget)));

    int left   = widget.position().x + text_space;
    int bottom = widget.position().y + text_space;

    renderMarginString(getTheme().getRenderer(),
                       *font,
                       widget.getCaption(),
                       font_data.font_color,
                       size,
                       Alignment(H_ALIGNMENT_LEFT, V_ALIGNMENT_CENTERED),
                       Margin(left, text_space, bottom, text_space));
  }

  /**
   *
   */
  SimpleTheme::SimpleControlTheme<CaptionBar>::SimpleControlTheme(SimpleTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<CaptionBar>, SimpleTheme>(theme)
  {
    bkgd_color = Color(0x5A, 0x6A, 0x50);
  }

  /**
   *
   */
  void SimpleTheme::SimpleControlTheme<CaptionBar>::renderControl(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme().getRenderer(), rectangle, bkgd_color);
  }

  /**
   *
   */
  SimpleTextureTheme::SimpleTextureControlTheme<CaptionBar>::SimpleTextureControlTheme(SimpleTextureTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<CaptionBar>, SimpleTextureTheme>(theme)
  {
    bkgd_color = Color(0xFF, 0xFF, 0xFF);
  }

  /**
   *
   */
  void SimpleTextureTheme::SimpleTextureControlTheme<CaptionBar>::renderControl(Rectangle const& rectangle) const
  {
    Margin margin;
    margin.left  = getTheme().getPixelData().caption_bar_.left_margin_;
    margin.right = getTheme().getPixelData().caption_bar_.right_margin_;

    renderRectangle(getTheme(), rectangle, getTheme().getPixelData().caption_bar_.widget_, bkgd_color, margin);
  }
}
