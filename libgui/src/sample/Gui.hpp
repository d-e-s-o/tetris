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

#ifndef SAMPLEGUI_HPP
#define SAMPLEGUI_HPP

#include <gui/widget/RootWidget.hpp>
#include <gui/widget/control/StaticText.hpp>
#include <gui/widget/control/Button.hpp>
#include <gui/widget/control/CheckBox.hpp>
#include <gui/widget/control/EditBox.hpp>
#include <gui/widget/control/Slider.hpp>
#include <gui/widget/control/ProgressBar.hpp>
#include <gui/widget/control/Picture.hpp>
#include <gui/widget/control/GroupBox.hpp>
#include <gui/widget/control/Dialog.hpp>

#include "StatusText.hpp"


namespace sample
{
  class Gui;


  /**
   *
   */
  class Slider: public gui::Slider
  {
  public:
    Slider(gui::Bounds const& bounds, Gui& gui);

    virtual void onChange();

  private:
    Gui* gui_;
  };

  /**
   *
   */
  class CheckBox: public gui::CheckBox
  {
  public:
    CheckBox(gui::Bounds const& bounds, Gui& gui);

    virtual void onClick();

  private:
    Gui* gui_;
  };

  /**
   *
   */
  class Button: public gui::Button
  {
  public:
    Button(gui::Bounds const& bounds, Gui& gui);

    virtual void onClick();

  private:
    Gui* gui_;
  };

  /**
   *
   */
  class Gui: public gui::RootWidget
  {
  public:
    Gui(gui::Renderer& renderer,
        gui::ThemeFactory const& theme_factory,
        gui::Bounds const& bounds);

    virtual void onKeyDown(wnd::Key key, wnd::ModifierKey modifier);

    void onSliderChange();
    void onCheckBoxClick();
    void onButtonClick();

    void setFps(int fps);

  private:
    gui::Dialog dialog_1_;
    gui::Dialog dialog_2_;
    gui::Dialog dialog_2_1_;

    gui::StaticText  text_1_;
         Button      button_1_;
         CheckBox    check_box_1_;
    gui::EditBox     edit_box_1_;
         Slider      slider_1_;
    gui::ProgressBar progress_bar_1_;
    gui::Picture     picture_1_;

    gui::GroupBox group_box_1_;
    gui::EditBox edit_box_1_1_;
    gui::EditBox edit_box_1_2_;
    gui::EditBox edit_box_1_3_;
    gui::EditBox edit_box_1_4_;

    gui::GroupBox group_box_1_5_;
    gui::EditBox edit_box_1_5_1_;
    gui::EditBox edit_box_1_5_2_;
    gui::EditBox edit_box_1_5_3_;
    gui::EditBox edit_box_1_5_4_;

    StatusText status_;
  };
}


namespace sample
{
  /**
   *
   */
  inline void Gui::setFps(int fps)
  {
    status_.setFps(fps);
  }
}


#endif
