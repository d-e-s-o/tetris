// SettingsDialog.cpp

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

#include <gui/util/LexicalCast.hpp>

#include "resource/Settings.hpp"
#include "tetris/gui/SettingsDialog.hpp"


namespace ttrs
{
  namespace
  {
    gui::SizeT const SPACE = 8;

    gui::SizeT const LABEL_WIDTH  = 100;
    gui::SizeT const LABEL_HEIGHT = 20;

    gui::SizeT const BUTTON_WIDTH  = 50;
    gui::SizeT const BUTTON_HEIGHT = 20;

    gui::SizeT const EDIT_WIDTH  = 50;
    gui::SizeT const EDIT_HEIGHT = 20;
  }


  /**
   *
   */
  ModalDialog::ModalDialog(gui::Bounds const& bounds)
    : Dialog(bounds),
      result_(false),
      cancel_(gui::Bounds(clientArea().w - BUTTON_WIDTH - SPACE,
                          SPACE,
                          BUTTON_WIDTH,
                          BUTTON_HEIGHT),
              *this),
      ok_(gui::Bounds(cancel_.position().x - BUTTON_WIDTH - SPACE,
                      SPACE,
                      BUTTON_WIDTH,
                      BUTTON_HEIGHT),
          *this)
  {
    cancel_.setParent(this);
    cancel_.setText(gui::String(TEXT("Cancel")));
    cancel_.setHAnchors(gui::H_ANCHORS_RIGHT);
    cancel_.setVAnchors(gui::V_ANCHORS_BOTTOM);

    ok_.setParent(this);
    ok_.setText(gui::String(TEXT("OK")));
    ok_.setHAnchors(gui::H_ANCHORS_RIGHT);
    ok_.setVAnchors(gui::V_ANCHORS_BOTTOM);
  }

  /**
   * @copydoc Dialog::onShow
   */
  void ModalDialog::onShow()
  {
    setModalResult(false);
    updateData(false);
  }

  /**
   * @copydoc Dialog::onHide
   */
  void ModalDialog::onHide()
  {
    if (getModalResult())
      updateData(true);
  }

  /**
   *
   */
  bool ModalDialog::getModalResult() const
  {
    return result_;
  }

  /**
   *
   */
  void ModalDialog::setModalResult(bool result)
  {
    result_ = result;
  }

  /**
   *
   */
  ModalDialog::DialogButton::DialogButton(gui::Bounds const& bounds, ModalDialog& dialog)
    : Button(bounds),
      dialog_(&dialog)
  {
  }

  /**
   *
   */
  ModalDialog& ModalDialog::DialogButton::getDialog()
  {
    return *dialog_;
  }

  /**
   *
   */
  ModalDialog::OkButton::OkButton(gui::Bounds const& bounds, ModalDialog& dialog)
    : DialogButton(bounds, dialog)
  {
  }

  /**
   *
   */
  void ModalDialog::OkButton::onClick()
  {
    getDialog().setModalResult(true);
    getDialog().hide();
  }

  /**
   *
   */
  ModalDialog::CancelButton::CancelButton(gui::Bounds const& bounds, ModalDialog& dialog)
    : DialogButton(bounds, dialog)
  {
  }

  /**
   *
   */
  void ModalDialog::CancelButton::onClick()
  {
    getDialog().setModalResult(false);
    getDialog().hide();
  }

  /**
   *
   */
  SettingsDialog::SettingsDialog(gui::Bounds const& bounds, Settings& settings)
    : ModalDialog(bounds),
      settings_(&settings),
      level_text_(gui::Bounds(SPACE,
                              clientArea().y + clientArea().h - LABEL_HEIGHT - SPACE,
                              LABEL_WIDTH,
                              LABEL_HEIGHT)),
      level_box_(gui::Bounds(level_text_.position().x + level_text_.size().x + SPACE,
                             level_text_.position().y,
                             EDIT_WIDTH,
                             EDIT_HEIGHT)),
      lines_text_(gui::Bounds(level_text_.position().x,
                              level_text_.position().y - LABEL_HEIGHT - SPACE,
                              LABEL_WIDTH,
                              LABEL_HEIGHT)),
      lines_box_(gui::Bounds(level_box_.position().x,
                             level_box_.position().y - EDIT_HEIGHT - SPACE,
                             EDIT_WIDTH,
                             EDIT_HEIGHT)),
      width_text_(gui::Bounds(lines_text_.position().x,
                              lines_text_.position().y - LABEL_HEIGHT - SPACE,
                              LABEL_WIDTH,
                              LABEL_HEIGHT)),
      width_box_(gui::Bounds(lines_box_.position().x,
                             lines_box_.position().y - EDIT_HEIGHT - SPACE,
                             EDIT_WIDTH,
                             EDIT_HEIGHT)),
      height_text_(gui::Bounds(width_text_.position().x,
                               width_text_.position().y - LABEL_HEIGHT - SPACE,
                               LABEL_WIDTH,
                               LABEL_HEIGHT)),
      height_box_(gui::Bounds(width_box_.position().x,
                              width_box_.position().y - EDIT_HEIGHT - SPACE,
                              EDIT_WIDTH,
                              EDIT_HEIGHT)),
      preview_text_(gui::Bounds(height_text_.position().x,
                                height_text_.position().y - LABEL_HEIGHT - SPACE,
                                LABEL_WIDTH,
                                LABEL_HEIGHT)),
      preview_box_(gui::Bounds(height_box_.position().x,
                               height_box_.position().y - EDIT_HEIGHT - SPACE,
                               EDIT_WIDTH,
                               EDIT_HEIGHT))
  {
    setCaption(gui::String(TEXT("Settings")));

    level_text_.setParent(this);
    level_text_.setText(gui::String(TEXT("start level:")));
    level_text_.setHAlignment(gui::H_ALIGNMENT_LEFT);

    level_box_.setParent(this);

    lines_text_.setParent(this);
    lines_text_.setText(gui::String(TEXT("lines for level:")));
    lines_text_.setHAlignment(gui::H_ALIGNMENT_LEFT);

    lines_box_.setParent(this);

    width_text_.setParent(this);
    width_text_.setText(gui::String(TEXT("field width:")));
    width_text_.setHAlignment(gui::H_ALIGNMENT_LEFT);

    width_box_.setParent(this);

    height_text_.setParent(this);
    height_text_.setText(gui::String(TEXT("field height:")));
    height_text_.setHAlignment(gui::H_ALIGNMENT_LEFT);

    height_box_.setParent(this);

    preview_text_.setParent(this);
    preview_text_.setText(gui::String(TEXT("preview stones:")));
    preview_text_.setHAlignment(gui::H_ALIGNMENT_LEFT);

    preview_box_.setParent(this);

    updateData(false);
  }

  /**
   * @todo even if a conversion fails (exception) we should try to read in the other settings
   */
  void SettingsDialog::updateData(bool save)
  {
    if (settings_ != 0)
    {
      try
      {
        if (save)
        {
          settings_->setStartLevel(gui::lexicalCast<gui::String, int>(level_box_.getText()));
          settings_->setLinesForLevel(gui::lexicalCast<gui::String, int>(lines_box_.getText()));
          settings_->setFieldWidth(gui::lexicalCast<gui::String, int>(width_box_.getText()));
          settings_->setFieldHeight(gui::lexicalCast<gui::String, int>(height_box_.getText()));
          settings_->setPreviewStoneCount(gui::lexicalCast<gui::String, int>(preview_box_.getText()));
        }
        else
        {
          level_box_.setText(gui::lexicalCast<int, gui::String>(settings_->getStartLevel()));
          lines_box_.setText(gui::lexicalCast<int, gui::String>(settings_->getLinesForLevel()));
          width_box_.setText(gui::lexicalCast<int, gui::String>(settings_->getFieldWidth()));
          height_box_.setText(gui::lexicalCast<int, gui::String>(settings_->getFieldHeight()));
          preview_box_.setText(gui::lexicalCast<int, gui::String>(settings_->getPreviewStoneCount()));
        }
      }
      catch (...)
      {
      }
    }
  }
}
