// SettingsDialog.hpp

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

#ifndef TTRSSETTINGSDIALOG_HPP
#define TTRSSETTINGSDIALOG_HPP

#include <gui/widget/control/StaticText.hpp>
#include <gui/widget/control/EditBox.hpp>
#include <gui/widget/control/Button.hpp>
#include <gui/widget/control/Dialog.hpp>


namespace ttrs
{
  class Settings;


  /**
   *
   */
  class ModalDialog: public gui::Dialog
  {
  public:
    ModalDialog(gui::Bounds const& bounds);

    virtual void onShow();
    virtual void onHide();

    bool getModalResult() const;
    void setModalResult(bool result);

  protected:
    virtual void updateData(bool save) = 0;

  private:
    /**
     *
     */
    class DialogButton: public gui::Button
    {
    public:
      DialogButton(gui::Bounds const& bounds, ModalDialog& dialog);

    protected:
      ModalDialog& getDialog();

    private:
      ModalDialog* dialog_;
    };

    /**
     *
     */
    class OkButton: public DialogButton
    {
    public:
      OkButton(gui::Bounds const& bounds, ModalDialog& dialog);

      virtual void onClick();
    };

    /**
     *
     */
    class CancelButton: public DialogButton
    {
    public:
      CancelButton(gui::Bounds const& bounds, ModalDialog& dialog);

      virtual void onClick();
    };

    bool result_;

    CancelButton cancel_;
    OkButton     ok_;
  };

  /**
   * This class represents a dialog for configuring the settings for the tetris game.
   */
  class SettingsDialog: public ModalDialog
  {
  public:
    SettingsDialog(gui::Bounds const& bounds, Settings& settings);

  protected:
    virtual void updateData(bool save);

  private:
    Settings* settings_;

    gui::StaticText level_text_;
    gui::EditBox    level_box_;

    gui::StaticText lines_text_;
    gui::EditBox    lines_box_;

    gui::StaticText width_text_;
    gui::EditBox    width_box_;

    gui::StaticText height_text_;
    gui::EditBox    height_box_;

    gui::StaticText preview_text_;
    gui::EditBox    preview_box_;
  };
}


#endif
