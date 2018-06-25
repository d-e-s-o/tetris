// GroupBox.cpp

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
#include "gui/widget/control/GroupBox.hpp"


namespace gui
{
  /**
   * @copydoc Decorator::Decorator
   */
  GroupBoxBorder::GroupBoxBorder(Widget& widget)
    : Decorator(widget),
      text_()
  {
  }

  /**
   * @copydoc Widget::Widget
   */
  GroupBox::GroupBox(Bounds const& bounds)
    : Container(bounds),
      border_(*this)
  {
    setFocusable(false);
    setAlwaysOnBottom(true);
  }

  /**
   * @return font used for rendering text on this control
   */
  Font const& GroupBox::getFont() const
  {
    return *rootWidget()->getTheme().getControlTheme<GroupBox>().font;
  }

  /**
   * @copydoc Widget::renderWidget
   */
  void GroupBox::renderWidget(Size const& size) const
  {
    ASSERTOP(rootWidget(), ne, nullptr);

    rootWidget()->getTheme().getControlTheme<GroupBox>().renderWidget(*this, size);
  }

  /**
   * @copydoc Widget::renderContent
   */
  void GroupBox::renderContent(Size const& size) const
  {
    ASSERTOP(rootWidget(), ne, nullptr);

    rootWidget()->getTheme().getControlTheme<GroupBox>().renderContent(*this, size);
  }
}
