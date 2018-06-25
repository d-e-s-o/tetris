// SimpleSlider.cpp

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

#include "gui/widget/control/Slider.hpp"
#include "gui/widget/control/theme/simple/SimpleThemeFunctions.hpp"
#include "gui/widget/control/theme/simple/SimpleSlider.hpp"


namespace gui
{
  /**
   *
   */
  SimpleThemeBase::SimpleControlThemeBase<Slider>::SimpleControlThemeBase(Theme& theme)
    : ControlTheme<Slider>(theme)
  {
    line_space   = 8;
    line_height  = 2;
    slider_space = 3;
    slider_width = 10;
  }


  /**
   *
   */
  void SimpleThemeBase::SimpleControlThemeBase<Slider>::renderWidget(Slider const& widget, Size const& size) const
  {
    ASSERT(size == widget.size());

    renderControl(getRectangle(Point(), size));
  }

  /**
   *
   */
  void SimpleThemeBase::SimpleControlThemeBase<Slider>::renderContent(Slider const& widget, Size const& size) const
  {
    ASSERT(size == utl::getSize(widget.clientArea()));

    Rectangle rectangle1;
    rectangle1.x1_ = line_space;
    rectangle1.y1_ = size.y / 2 - line_height / 2;
    rectangle1.x2_ = size.x - line_space;
    rectangle1.y2_ = rectangle1.y1_ + line_height;

    renderLine(rectangle1);


    SizeT offset = calculateValueOffset(size.x - 2 * line_space,
                                        widget.getMinValue(),
                                        widget.getMaxValue(),
                                        widget.getValue());
    Rectangle rectangle2;
    rectangle2.x1_ = line_space - slider_width / 2 + offset;
    rectangle2.y1_ = slider_space;
    rectangle2.x2_ = rectangle2.x1_ + slider_width;
    rectangle2.y2_ = size.y - slider_space;

    renderSlider(rectangle2);
  }

  /**
   *
   */
  SimpleTheme::SimpleControlTheme<Slider>::SimpleControlTheme(SimpleTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<Slider>, SimpleTheme>(theme)
  {
    slider_color = Color(0x7D, 0x80, 0x78);
    line_color   = Color(0x00, 0x00, 0x00);
    bkgd_color   = Color(0x49, 0x4E, 0x49);
  }

  /**
   *
   */
  void SimpleTheme::SimpleControlTheme<Slider>::renderControl(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme().getRenderer(), rectangle, bkgd_color);
  }

  /**
   *
   */
  void SimpleTheme::SimpleControlTheme<Slider>::renderLine(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme().getRenderer(), rectangle, line_color);
  }

  /**
   *
   */
  void SimpleTheme::SimpleControlTheme<Slider>::renderSlider(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme().getRenderer(), rectangle, slider_color);
  }

  /**
   *
   */
  SimpleTextureTheme::SimpleTextureControlTheme<Slider>::SimpleTextureControlTheme(SimpleTextureTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<Slider>, SimpleTextureTheme>(theme)
  {
    line_height  = 4;
    slider_width = 11;

    slider_color = Color(0xFF, 0xFF, 0xFF);
    line_color   = Color(0xFF, 0xFF, 0xFF);
    bkgd_color   = Color(0xFF, 0xFF, 0xFF);
  }

  /**
   *
   */
  void SimpleTextureTheme::SimpleTextureControlTheme<Slider>::renderControl(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme(), rectangle, getTheme().getPixelData().slider_.widget_, bkgd_color);
  }

  /**
   *
   */
  void SimpleTextureTheme::SimpleTextureControlTheme<Slider>::renderLine(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme(), rectangle, getTheme().getPixelData().slider_.line_, line_color);
  }

  /**
   *
   */
  void SimpleTextureTheme::SimpleTextureControlTheme<Slider>::renderSlider(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme(), rectangle, getTheme().getPixelData().slider_.slider_, slider_color);
  }
}
