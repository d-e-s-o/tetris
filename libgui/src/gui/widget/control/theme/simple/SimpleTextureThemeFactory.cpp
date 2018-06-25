// SimpleTextureThemeFactory.cpp

/***************************************************************************
 *   Copyright (C) 2006-2012 Daniel Mueller (deso@posteo.net)              *
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

#include "gui/renderer/Renderer.hpp"
#include "gui/widget/RootWidget.hpp"
#include "gui/widget/control/theme/simple/SimpleTextureTheme.hpp"
#include "gui/widget/control/theme/simple/SimpleTextureThemeFactory.hpp"


namespace gui
{
  namespace
  {
    SimpleTextureThemeData getXpThemePixels()
    {
      SimpleTextureThemeData xp;

      xp.static_text_.widget_ = Pixels(0, 0, 0, 0);

      xp.button_.widget_         = Pixels(1,  1, 1  + 50, 1 + 21);
      xp.button_.widget_pressed_ = Pixels(52, 1, 52 + 50, 1 + 21);
      xp.button_.left_margin_    = 4;
      xp.button_.right_margin_   = 4;

      xp.check_box_.widget_      = Pixels(0, 0, 0, 0);
      xp.check_box_.box_         = Pixels(29, 23, 29 + 13, 23 + 13);
      xp.check_box_.box_checked_ = Pixels(43, 23, 43 + 13, 23 + 13);

      xp.edit_box_.widget_        = Pixels(219, 1, 219 + 36, 1 + 17);
      xp.edit_box_.left_margin_   = 2;
      xp.edit_box_.bottom_margin_ = 2;
      xp.edit_box_.right_margin_  = 2;
      xp.edit_box_.top_margin_    = 2;

      xp.slider_.widget_ = Pixels(0, 0, 0, 0);
      xp.slider_.line_   = Pixels(1, 37, 1 + 55, 37 + 4);
      xp.slider_.slider_ = Pixels(1, 42, 1 + 11, 42 + 23);

      xp.progress_bar_.widget_       = Pixels(103, 1, 103 + 50, 1 + 21);
      xp.progress_bar_.bar_          = Pixels(154, 1, 154 + 64, 1 + 17);
      xp.progress_bar_.left_margin_  = 4;
      xp.progress_bar_.right_margin_ = 5;

      xp.picture_.widget_        = Pixels(0, 0, 0, 0);
      xp.picture_.picture_empty_ = Pixels(0, 0, 0, 0);

      xp.dialog_.widget_ = Pixels(0, 0, 0, 0);

      xp.caption_bar_.widget_       = Pixels(161, 19, 161 + 94, 19 + 30);
      xp.caption_bar_.left_margin_  = 8;
      xp.caption_bar_.right_margin_ = 8;

      xp.caption_bar_button_.widget_         = Pixels(117, 23, 117 + 21, 23 + 21);
      xp.caption_bar_button_.widget_pressed_ = Pixels(139, 23, 139 + 21, 23 + 21);

      xp.border_.bottom_            = Pixels(161, 50, 161 + 94, 50 + 4);
      xp.border_.right_             = Pixels(156, 46, 156 + 4,  46 + 18);
      xp.border_.top_               = Pixels(0, 0, 0, 0);
      xp.border_.left_              = Pixels(151, 46, 151 + 4,  46 + 18);
      xp.border_.margin_left_right_ = 4;

      return xp;
    }
  }


  /**
   *
   */
  Theme* SimpleTextureThemeFactory::createTheme(RootWidget& root_widget) const
  {
    Renderer& renderer = root_widget.getRenderer();
    Texture* texture   = renderer.createTexture(String(TEXT("mem://win_xp_silver_theme.png")));

    return texture != 0 ? new SimpleTextureTheme(renderer, *texture, getXpThemePixels()) : 0;
  }
}
