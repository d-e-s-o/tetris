// SimpleStaticText.cpp

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

#include "gui/widget/control/StaticText.hpp"
#include "gui/widget/control/theme/simple/SimpleThemeFunctions.hpp"
#include "gui/widget/control/theme/simple/SimpleStaticText.hpp"


namespace gui
{
  /**
   *
   */
  SimpleThemeBase::SimpleControlThemeBase<StaticText>::SimpleControlThemeBase(Theme& theme)
    : ControlTheme<StaticText>(theme)
  {
    font_data = getDefaultFontData();
    font      = createFont(theme, font_data);

    text_space = 2;
  }

  /**
   *
   */
  void SimpleThemeBase::SimpleControlThemeBase<StaticText>::renderWidget(StaticText const& widget, Size const& size) const
  {
    ASSERT(size == widget.size());

    renderControl(getRectangle(Point(), size));
  }

  /**
   *
   */
  void SimpleThemeBase::SimpleControlThemeBase<StaticText>::renderContent(StaticText const& widget, Size const& size) const
  {
    ASSERT(size == utl::getSize(widget.clientArea()));

    renderMarginString(getTheme().getRenderer(),
                       *font,
                       widget.getText(),
                       font_data.font_color,
                       size,
                       Alignment(widget.getHAlignment(), widget.getVAlignment()),
                       Margin(text_space, text_space, text_space, text_space));
  }

  /**
   *
   */
  SimpleTheme::SimpleControlTheme<StaticText>::SimpleControlTheme(SimpleTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<StaticText>, SimpleTheme>(theme)
  {
    bkgd_color = Color(0x68, 0x6A, 0x65);
  }

  /**
   *
   */
  void SimpleTheme::SimpleControlTheme<StaticText>::renderControl(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme().getRenderer(), rectangle, bkgd_color);
  }

  /**
   *
   */
  SimpleTextureTheme::SimpleTextureControlTheme<StaticText>::SimpleTextureControlTheme(SimpleTextureTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<StaticText>, SimpleTextureTheme>(theme)
  {
    bkgd_color = Color(0xFF, 0xFF, 0xFF);
  }

  /**
   *
   */
  void SimpleTextureTheme::SimpleTextureControlTheme<StaticText>::renderControl(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme(), rectangle, getTheme().getPixelData().static_text_.widget_, bkgd_color);
  }
}
