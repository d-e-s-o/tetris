// SimpleCaptionBarButton.cpp

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
#include "gui/widget/control/CaptionBarButton.hpp"
#include "gui/widget/control/theme/simple/SimpleThemeFunctions.hpp"
#include "gui/widget/control/theme/simple/SimpleCaptionBarButton.hpp"


namespace gui
{
  /**
   *
   */
  SimpleThemeBase::SimpleControlThemeBase<CaptionBarButton>::SimpleControlThemeBase(Theme& theme)
    : ControlTheme<CaptionBarButton>(theme)
  {
  }

  /**
   *
   */
  void SimpleThemeBase::SimpleControlThemeBase<CaptionBarButton>::renderWidget(CaptionBarButton const& widget, Size const& size) const
  {
    // @todo find out why this assertion fails
    //ASSERTOP(size, eq, widget.size());

    renderControl(utl::convert(getBounds(widget)), widget.isPressed());
  }

  /**
   *
   */
  SimpleTheme::SimpleControlTheme<CaptionBarButton>::SimpleControlTheme(SimpleTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<CaptionBarButton>, SimpleTheme>(theme)
  {
    press_color = Color(0xFF, 0xFF, 0xFF);
    bkgd_color  = Color(0xBE, 0xC3, 0xBA);
  }

  /**
   *
   */
  void SimpleTheme::SimpleControlTheme<CaptionBarButton>::renderControl(Rectangle const& rectangle, bool pressed) const
  {
    renderRectangle(getTheme().getRenderer(), rectangle, pressed ? press_color : bkgd_color);
  }

  /**
   *
   */
  SimpleTextureTheme::SimpleTextureControlTheme<CaptionBarButton>::SimpleTextureControlTheme(SimpleTextureTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<CaptionBarButton>, SimpleTextureTheme>(theme)
  {
    press_color = Color(0xFF, 0xFF, 0xFF);
    bkgd_color  = Color(0xFF, 0xFF, 0xFF);
  }

  /**
   *
   */
  void SimpleTextureTheme::SimpleTextureControlTheme<CaptionBarButton>::renderControl(Rectangle const& rectangle, bool pressed) const
  {
    if (pressed)
      renderRectangle(getTheme(), rectangle, getTheme().getPixelData().caption_bar_button_.widget_pressed_, press_color);
    else
      renderRectangle(getTheme(), rectangle, getTheme().getPixelData().caption_bar_button_.widget_, bkgd_color);
  }
}
