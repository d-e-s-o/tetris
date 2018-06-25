// StaticText.cpp

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
#include "gui/widget/control/StaticText.hpp"


namespace gui
{
  /**
   * @copydoc Widget::Widget
   */
  StaticText::StaticText(Bounds const& bounds)
    : Widget(bounds),
      text_(),
      h_alignment_(H_ALIGNMENT_LEFT),
      v_alignment_(V_ALIGNMENT_CENTERED)
  {
    setFocusable(false);
    setAlwaysOnBottom(true);
  }

  /**
   * @return font used for rendering text on this control
   */
  Font const& StaticText::getFont() const
  {
    return *rootWidget()->getTheme().getControlTheme<StaticText>().font;
  }

  /**
   * @return space between the displayed text and the left edge of the client area
   */
  SizeT StaticText::textSpace() const
  {
    return rootWidget()->getTheme().getControlTheme<StaticText>().text_space;
  }

  /**
   * @copydoc Widget::renderWidget
   */
  void StaticText::renderWidget(Size const& size) const
  {
    ASSERTOP(rootWidget(), ne, nullptr);

    rootWidget()->getTheme().getControlTheme<StaticText>().renderWidget(*this, size);
  }

  /**
   * @copydoc Widget::renderContent
   */
  void StaticText::renderContent(Size const& size) const
  {
    ASSERTOP(rootWidget(), ne, nullptr);

    rootWidget()->getTheme().getControlTheme<StaticText>().renderContent(*this, size);
  }
}
