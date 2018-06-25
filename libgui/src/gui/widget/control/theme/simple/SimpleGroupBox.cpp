// SimpleGroupBox.cpp

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

#include "gui/widget/control/GroupBox.hpp"
#include "gui/widget/control/theme/simple/SimpleThemeFunctions.hpp"
#include "gui/widget/control/theme/simple/SimpleGroupBox.hpp"


namespace gui
{
  /**
   *
   */
  SimpleThemeBase::SimpleControlThemeBase<GroupBox>::SimpleControlThemeBase(Theme& theme)
    : ControlTheme<GroupBox>(theme)
  {
    font_data = getDefaultFontData();
    font      = createFont(theme, font_data);
  }

  /**
   *
   */
  void SimpleThemeBase::SimpleControlThemeBase<GroupBox>::renderWidget(GroupBox const& widget, Size const& size) const
  {
    ASSERT(size == widget.size());

    renderControl(getRectangle(Point(), size));
  }

  /**
   *
   */
  void SimpleThemeBase::SimpleControlThemeBase<GroupBox>::renderContent(GroupBox const& widget, Size const& size) const
  {
    ASSERT(size == utl::getSize(widget.clientArea()));
  }

  /**
   *
   */
  SimpleTheme::SimpleControlTheme<GroupBox>::SimpleControlTheme(SimpleTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<GroupBox>, SimpleTheme>(theme)
  {
    bkgd_color = Color(0x99, 0x5E, 0x00);
  }

  /**
   *
   */
  void SimpleTheme::SimpleControlTheme<GroupBox>::renderControl(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme().getRenderer(), rectangle, bkgd_color);
  }

  /**
   *
   */
  SimpleTextureTheme::SimpleTextureControlTheme<GroupBox>::SimpleTextureControlTheme(SimpleTextureTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<GroupBox>, SimpleTextureTheme>(theme)
  {
    bkgd_color = Color(0xFF, 0xFF, 0xFF);
  }

  /**
   *
   */
  void SimpleTextureTheme::SimpleTextureControlTheme<GroupBox>::renderControl(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme(), rectangle, getTheme().getPixelData().group_box_.widget_, bkgd_color);
  }
}
