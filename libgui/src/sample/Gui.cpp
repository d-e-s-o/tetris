/***************************************************************************
 *   Copyright (C) 2006-2012,2019 Daniel Mueller (deso@posteo.net)         *
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

#include <iostream>
#include <gui/renderer/Renderer.hpp>

#include "Gui.hpp"


namespace sample
{
  /**
   *
   */
  Slider::Slider(gui::Bounds const& bounds, Gui& gui)
    : gui::Slider(bounds),
      gui_(&gui)
  {
  }

  /**
   *
   */
  void Slider::onChange()
  {
    gui_->onSliderChange();
  }

  /**
   *
   */
  CheckBox::CheckBox(gui::Bounds const& bounds, Gui& gui)
    : gui::CheckBox(bounds),
      gui_(&gui)
  {
  }

  /**
   *
   */
  void CheckBox::onClick()
  {
    gui_->onCheckBoxClick();
  }

  /**
   *
   */
  Button::Button(gui::Bounds const& bounds, Gui& gui)
    : gui::Button(bounds),
      gui_(&gui)
  {
  }

  /**
   *
   */
  void Button::onClick()
  {
    gui_->onButtonClick();
  }

  /**
   *
   */
  Gui::Gui(gui::Renderer& renderer,
           gui::ThemeFactory const& theme_factory,
           gui::Bounds const& bounds)
    : gui::RootWidget(renderer, theme_factory, bounds),
      dialog_1_(      gui::Bounds(170, 260, 350, 200)),
      dialog_2_(      gui::Bounds(400, 10,  350, 300)),
      dialog_2_1_(    gui::Bounds(10,  10,  230, 200)),
      text_1_(        gui::Bounds(10,  475, 400, 75)),
      button_1_(      gui::Bounds(20,  400, 120, 30), *this),
      check_box_1_(   gui::Bounds(20,  350, 120, 30), *this),
      edit_box_1_(    gui::Bounds(20,  300, 120, 30)),
      slider_1_(      gui::Bounds(20,  250, 120, 30), *this),
      progress_bar_1_(gui::Bounds(20,  200, 120, 30)),
      picture_1_(     gui::Bounds(10,  10,  200, 150)),
      status_(        gui::Bounds(575, 400, 200, 150)),
      group_box_1_(   gui::Bounds(10,  10,  300, 100)),
      edit_box_1_1_(  gui::Bounds(10,  70,  40,  20)),
      edit_box_1_2_(  gui::Bounds(80,  70,  40,  20)),
      edit_box_1_3_(  gui::Bounds(10,  30,  40,  20)),
      edit_box_1_4_(  gui::Bounds(80,  30,  40,  20)),
      group_box_1_5_( gui::Bounds(150, 10,  140, 80)),
      edit_box_1_5_1_(gui::Bounds(10,  50,  40,  20)),
      edit_box_1_5_2_(gui::Bounds(80,  50,  40,  20)),
      edit_box_1_5_3_(gui::Bounds(10,  10,  40,  20)),
      edit_box_1_5_4_(gui::Bounds(80,  10,  40,  20))
  {
    text_1_.setText(gui::String(TEXT("Press 1-6 to move this text!")));
    text_1_.setHAnchors(gui::H_ANCHORS_LEFT);
    text_1_.setVAnchors(gui::V_ANCHORS_TOP);

    button_1_.setText(gui::String(TEXT("Enable Dialogs")));
    check_box_1_.setText(gui::String(TEXT("Show Status")));
    check_box_1_.setChecked(true);
    edit_box_1_.setText(gui::String(TEXT("Enter text here")));
    progress_bar_1_.setProgress(45);

    try
    {
      // load an image and set it to be displayed by the picture control
      gui::Texture* picture = getRenderer().createTexture(gui::String(TEXT("mem://win_xp_silver_theme.png")));
      picture_1_.setPicture(picture);
      picture_1_.setParent(&dialog_2_1_);
    }
    catch (...)
    {
      std::cerr << TEXT("Warning: could not create texture from file") << std::endl;
    }

    status_.setHAnchors(gui::H_ANCHORS_RIGHT);
    status_.setVAnchors(gui::V_ANCHORS_TOP);

    dialog_1_.setCaption(gui::String(TEXT("First Dialog")));

    dialog_2_.setCaption(gui::String(TEXT("Second Dialog")));
    dialog_2_.setHAnchors(gui::H_ANCHORS_RIGHT | gui::H_ANCHORS_LEFT);
    dialog_2_.setVAnchors(gui::V_ANCHORS_BOTTOM | gui::V_ANCHORS_TOP);

    dialog_2_1_.setParent(&dialog_2_);
    dialog_2_1_.setCaption(gui::String(TEXT("Child Dialog")));

    edit_box_1_1_.setParent(&group_box_1_);
    edit_box_1_1_.setText(gui::String(TEXT("try")));
    edit_box_1_2_.setParent(&group_box_1_);
    edit_box_1_2_.setText(gui::String(TEXT("using")));
    edit_box_1_3_.setParent(&group_box_1_);
    edit_box_1_3_.setText(gui::String(TEXT("the")));
    edit_box_1_4_.setParent(&group_box_1_);
    edit_box_1_4_.setText(gui::String(TEXT("tab")));

    group_box_1_5_.setParent(&group_box_1_);
    edit_box_1_5_1_.setParent(&group_box_1_5_);
    edit_box_1_5_1_.setText(gui::String(TEXT("key")));
    edit_box_1_5_2_.setParent(&group_box_1_5_);
    edit_box_1_5_2_.setText(gui::String(TEXT(":)")));
    edit_box_1_5_3_.setParent(&group_box_1_5_);
    edit_box_1_5_4_.setParent(&group_box_1_5_);
  }

  /**
   *
   */
  void Gui::onKeyDown(wnd::Key key, wnd::ModifierKey modifier)
  {
    switch(key)
    {
    //case wnd::KEY_B:
    //  if (focusedWidget() != 0)
    //    focusedWidget()->moveToBottom();
    //  break;

    //case wnd::KEY_T:
    //  if (focusedWidget() != 0)
    //    focusedWidget()->moveToTop();
    //  break;

    case wnd::KEY_1:
      text_1_.setHAlignment(gui::H_ALIGNMENT_LEFT);
      break;

    case wnd::KEY_2:
      text_1_.setHAlignment(gui::H_ALIGNMENT_CENTERED);
      break;

    case wnd::KEY_3:
      text_1_.setHAlignment(gui::H_ALIGNMENT_RIGHT);
      break;

    case wnd::KEY_4:
      text_1_.setVAlignment(gui::V_ALIGNMENT_BOTTOM);
      break;

    case wnd::KEY_5:
      text_1_.setVAlignment(gui::V_ALIGNMENT_CENTERED);
      break;

    case wnd::KEY_6:
      text_1_.setVAlignment(gui::V_ALIGNMENT_TOP);
      break;

    default:
      break;
    }

    RootWidget::onKeyDown(key, modifier);
  }

  /**
   *
   */
  void Gui::onSliderChange()
  {
    progress_bar_1_.setProgress(slider_1_.getValue());
  }

  /**
   *
   */
  void Gui::onCheckBoxClick()
  {
    if (check_box_1_.isChecked())
      status_.show();
    else
      status_.hide();
  }

  /**
   *
   */
  void Gui::onButtonClick()
  {
    dialog_1_.show();
    dialog_2_.show();
    dialog_2_1_.show();
  }
}
