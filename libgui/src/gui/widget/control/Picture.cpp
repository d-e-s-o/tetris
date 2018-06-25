// Picture.cpp

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
#include "gui/widget/control/Picture.hpp"


namespace gui
{
  /**
   * @copydoc Widget::Widget
   */
  Picture::Picture(Bounds const& bounds)
    : Widget(bounds),
      picture_(nullptr)
  {
    setFocusable(false);
    setAlwaysOnBottom(true);
  }

  /**
   * @return space between the displayed picture and the edges of the client area
   */
  SizeT Picture::getPictureSpace() const
  {
    return rootWidget()->getTheme().getControlTheme<Picture>().picture_space;
  }

  /**
   * @copydoc Widget::renderWidget
   */
  void Picture::renderWidget(Size const& size) const
  {
    ASSERTOP(rootWidget(), ne, nullptr);

    rootWidget()->getTheme().getControlTheme<Picture>().renderWidget(*this, size);
  }

  /**
   * @copydoc Widget::renderContent
   */
  void Picture::renderContent(Size const& size) const
  {
    ASSERTOP(rootWidget(), ne, nullptr);

    rootWidget()->getTheme().getControlTheme<Picture>().renderContent(*this, size);
  }
}
