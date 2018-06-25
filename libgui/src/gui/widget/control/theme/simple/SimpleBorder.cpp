// SimpleBorder.cpp

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

#include "gui/widget/control/Border.hpp"
#include "gui/widget/control/theme/simple/SimpleThemeFunctions.hpp"
#include "gui/widget/control/theme/simple/SimpleBorder.hpp"


namespace gui
{
  /**
   *
   */
  SimpleThemeBase::SimpleControlThemeBase<Border>::SimpleControlThemeBase(Theme& theme)
    : ControlTheme<Border>(theme)
  {
    width       = 1;
    inner_space = 1;
    outer_space = 1;
  }

  /**
   *
   */
  void SimpleThemeBase::SimpleControlThemeBase<Border>::renderWidget(Border const& widget, Size const& size) const
  {
    // @todo find out why this assertion fails
    //ASSERTOP(size, eq, widget.size());

    SizeT x1 = outer_space;
    SizeT y1 = outer_space;
    SizeT x2 = size.x - outer_space;
    SizeT y2 = size.y - (widget.hasNoTopBorder() ? outer_space : 0);

    // @note the order is important since the SimpleTexture theme has a texture that covers the
    //       left and right edges of the border and belongs to the bottom and top parts these must
    //       be rendered after the left and right border
    renderLeftBorder(  Rectangle(x1,         y1,         x1 + width, y2));
    renderRightBorder( Rectangle(x2 - width, y1,         x2,         y2));
    renderBottomBorder(Rectangle(x1,         y1,         x2,         y1 + width));

    if (!widget.hasNoTopBorder())
      renderTopBorder( Rectangle(x1,         y2 - width, x2,         y2));
  }

  /**
   *
   */
  SimpleTheme::SimpleControlTheme<Border>::SimpleControlTheme(SimpleTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<Border>, SimpleTheme>(theme)
  {
    bkgd_color  = Color(0x00, 0x00, 0x00);
  }

  /**
   *
   */
  void SimpleTheme::SimpleControlTheme<Border>::renderControl(Rectangle const& rectangle) const
  {
  }

  /**
   *
   */
  void SimpleTheme::SimpleControlTheme<Border>::renderRightBorder(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme().getRenderer(), rectangle, bkgd_color);
  }

  /**
   *
   */
  void SimpleTheme::SimpleControlTheme<Border>::renderTopBorder(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme().getRenderer(), rectangle, bkgd_color);
  }

  /**
   *
   */
  void SimpleTheme::SimpleControlTheme<Border>::renderLeftBorder(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme().getRenderer(), rectangle, bkgd_color);
  }

  /**
   *
   */
  void SimpleTheme::SimpleControlTheme<Border>::renderBottomBorder(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme().getRenderer(), rectangle, bkgd_color);
  }

  /**
   *
   */
  SimpleTextureTheme::SimpleTextureControlTheme<Border>::SimpleTextureControlTheme(SimpleTextureTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<Border>, SimpleTextureTheme>(theme)
  {
    width       = 4;
    inner_space = 0;
    outer_space = 0;

    bkgd_color  = Color(0xFF, 0xFF, 0xFF);
  }

  /**
   *
   */
  void SimpleTextureTheme::SimpleTextureControlTheme<Border>::renderControl(Rectangle const& rectangle) const
  {
  }

  /**
   *
   */
  void SimpleTextureTheme::SimpleTextureControlTheme<Border>::renderRightBorder(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme(), rectangle, getTheme().getPixelData().border_.right_, bkgd_color);
  }

  /**
   *
   */
  void SimpleTextureTheme::SimpleTextureControlTheme<Border>::renderTopBorder(Rectangle const& rectangle) const
  {
    Margin margin;
    margin.left  = getTheme().getPixelData().border_.margin_left_right_;
    margin.right = margin.left;

    renderRectangle(getTheme(), rectangle, getTheme().getPixelData().border_.top_, bkgd_color, margin);
  }

  /**
   *
   */
  void SimpleTextureTheme::SimpleTextureControlTheme<Border>::renderLeftBorder(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme(), rectangle, getTheme().getPixelData().border_.left_, bkgd_color);
  }

  /**
   *
   */
  void SimpleTextureTheme::SimpleTextureControlTheme<Border>::renderBottomBorder(Rectangle const& rectangle) const
  {
    Margin margin;
    margin.left  = getTheme().getPixelData().border_.margin_left_right_;
    margin.right = margin.left;

    renderRectangle(getTheme(), rectangle, getTheme().getPixelData().border_.bottom_, bkgd_color, margin);
  }
}
