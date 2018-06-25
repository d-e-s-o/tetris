// Dialog.hpp

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

#ifndef GUIDIALOG_HPP
#define GUIDIALOG_HPP

#include "gui/widget/Container.hpp"
#include "gui/widget/control/CaptionBar.hpp"
#include "gui/widget/control/Border.hpp"


namespace gui
{
  /**
   * This class represents a container for widgets. A dialog generally has a caption bar which
   * displays a text and a border. The first one also makes it moveable with the mouse.
   */
  class LIBGUI_EXPORT Dialog: public Container
  {
  public:
    Dialog(Bounds const& bounds);

    String const& getCaption() const;
    void setCaption(String const& caption);

  protected:
    virtual void renderWidget(Size const& size) const;
    virtual void renderContent(Size const& size) const;

  private:
    CaptionBar caption_bar_;
    Border     border_;
  };
}


namespace gui
{
  /**
   * @return current caption of the Dialog
   */
  inline String const& Dialog::getCaption() const
  {
    return caption_bar_.getCaption();
  }

  /**
   * @param caption new caption to set for the dialog
   */
  inline void Dialog::setCaption(String const& caption)
  {
    caption_bar_.setCaption(caption);
  }
}


#endif
