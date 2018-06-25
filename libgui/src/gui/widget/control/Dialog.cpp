// Dialog.cpp

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

#include "gui/widget/RootWidget.hpp"
#include "gui/widget/control/theme/Theme.hpp"
#include "gui/widget/control/Dialog.hpp"


namespace gui
{
  /**
   * @copydoc Container::Container
   */
  Dialog::Dialog(Bounds const& bounds)
    : Container(bounds),
      caption_bar_(*this),
      border_(*this, true)
  {
    setFirst(&caption_bar_);
    border_.insertAfter(caption_bar_);
  }

  /**
   * @copydoc Container::renderWidget
   */
  void Dialog::renderWidget(Size const& size) const
  {
    ASSERTOP(rootWidget(), ne, nullptr);

    rootWidget()->getTheme().getControlTheme<Dialog>().renderWidget(*this, size);
  }

  /**
   * @copydoc Container::renderContent
   */
  void Dialog::renderContent(Size const& size) const
  {
    ASSERTOP(rootWidget(), ne, nullptr);

    rootWidget()->getTheme().getControlTheme<Dialog>().renderContent(*this, size);
  }
}
