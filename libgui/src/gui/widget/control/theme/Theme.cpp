// Theme.cpp

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

#include "gui/widget/control/theme/Theme.hpp"


namespace gui
{
  /**
   * The destructor is virtual to allow inheritance.
   */
  Theme::ControlThemeBase::~ControlThemeBase()
  {
  }

  /**
   * The destructor is virtual to allow inheritance. It will destroy all control themes created
   * during construction.
   */
  Theme::~Theme()
  {
    destroy();
  }

  /**
   * This method destroys all control themes.
   */
  void Theme::destroy()
  {
    destroyControlTheme(border_theme_);
    destroyControlTheme(caption_bar_button_theme_);
    destroyControlTheme(caption_bar_theme_);
    destroyControlTheme(dialog_theme_);
    destroyControlTheme(group_box_theme_);
    destroyControlTheme(picture_theme_);
    destroyControlTheme(progress_bar_theme_);
    destroyControlTheme(slider_theme_);
    destroyControlTheme(edit_box_theme_);
    destroyControlTheme(check_box_theme_);
    destroyControlTheme(button_theme_);
    destroyControlTheme(static_text_theme_);
  }

  template<>
  Theme::ControlTheme<StaticText> const& Theme::getControlTheme() const
  {
    ASSERTOP(static_text_theme_, ne, nullptr);

    return *static_text_theme_;
  }

  template<>
  Theme::ControlTheme<Button> const& Theme::getControlTheme() const
  {
    ASSERTOP(button_theme_, ne, nullptr);

    return *button_theme_;
  }

  template<>
  Theme::ControlTheme<CheckBox> const& Theme::getControlTheme() const
  {
    ASSERTOP(check_box_theme_, ne, nullptr);

    return *check_box_theme_;
  }

  template<>
  Theme::ControlTheme<EditBox> const& Theme::getControlTheme() const
  {
    ASSERTOP(edit_box_theme_, ne, nullptr);

    return *edit_box_theme_;
  }

  template<>
  Theme::ControlTheme<Slider> const& Theme::getControlTheme() const
  {
    ASSERTOP(slider_theme_, ne, nullptr);

    return *slider_theme_;
  }

  template<>
  Theme::ControlTheme<ProgressBar> const& Theme::getControlTheme() const
  {
    ASSERTOP(progress_bar_theme_, ne, nullptr);

    return *progress_bar_theme_;
  }

  template<>
  Theme::ControlTheme<Picture> const& Theme::getControlTheme() const
  {
    ASSERTOP(picture_theme_, ne, nullptr);

    return *picture_theme_;
  }

  template<>
  Theme::ControlTheme<GroupBox> const& Theme::getControlTheme() const
  {
    ASSERTOP(group_box_theme_, ne, nullptr);

    return *group_box_theme_;
  }

  template<>
  Theme::ControlTheme<Dialog> const& Theme::getControlTheme() const
  {
    ASSERTOP(dialog_theme_, ne, nullptr);

    return *dialog_theme_;
  }

  template<>
  Theme::ControlTheme<CaptionBar> const& Theme::getControlTheme() const
  {
    ASSERTOP(caption_bar_theme_, ne, nullptr);

    return *caption_bar_theme_;
  }

  template<>
  Theme::ControlTheme<CaptionBarButton> const& Theme::getControlTheme() const
  {
    ASSERTOP(caption_bar_button_theme_, ne, nullptr);

    return *caption_bar_button_theme_;
  }

  template<>
  Theme::ControlTheme<Border> const& Theme::getControlTheme() const
  {
    ASSERTOP(border_theme_, ne, nullptr);

    return *border_theme_;
  }

  Theme::ControlTheme<StaticText>::ControlTheme(Theme& theme)
    : ControlThemeBase()
  {
  }

  Theme::ControlTheme<Button>::ControlTheme(Theme& theme)
    : ControlThemeBase()
  {
  }

  Theme::ControlTheme<CheckBox>::ControlTheme(Theme& theme)
    : ControlThemeBase()
  {
  }

  Theme::ControlTheme<EditBox>::ControlTheme(Theme& theme)
    : ControlThemeBase()
  {
  }

  Theme::ControlTheme<Slider>::ControlTheme(Theme& theme)
    : ControlThemeBase()
  {
  }

  Theme::ControlTheme<ProgressBar>::ControlTheme(Theme& theme)
    : ControlThemeBase()
  {
  }

  Theme::ControlTheme<Picture>::ControlTheme(Theme& theme)
    : ControlThemeBase()
  {
  }

  Theme::ControlTheme<GroupBox>::ControlTheme(Theme& theme)
    : ControlThemeBase()
  {
  }


  Theme::ControlTheme<Dialog>::ControlTheme(Theme& theme)
    : ControlThemeBase()
  {
  }

  Theme::ControlTheme<CaptionBar>::ControlTheme(Theme& theme)
    : ControlThemeBase()
  {
  }

  Theme::ControlTheme<CaptionBarButton>::ControlTheme(Theme& theme)
    : ControlThemeBase()
  {
  }

  Theme::ControlTheme<Border>::ControlTheme(Theme& theme)
    : ControlThemeBase()
  {
  }
}
