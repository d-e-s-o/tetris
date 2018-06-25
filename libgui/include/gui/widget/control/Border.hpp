// Border.hpp

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

#ifndef GUIBORDER_HPP
#define GUIBORDER_HPP

#include "gui/widget/Decorator.hpp"


namespace gui
{
  /**
   *
   */
  class LIBGUI_EXPORT Border: public Decorator
  {
  public:
    Border(Widget& widget, bool no_top_border);

    bool hasNoTopBorder() const;

    SizeT width() const;
    SizeT innerSpace() const;
    SizeT outerSpace() const;

  protected:
    virtual void renderWidget(Size const& size) const;

    virtual void handlePositionEvent(PositionEvent const& event);

    virtual void shrinkClientArea(Bounds& bounds) const;

  private:
    bool no_top_border_;

    bool isPositionInBorder(Position const& position) const;
  };
}


namespace gui
{
  /**
   * @return true if the border is only used for left, bottom and right side, not for top
   * @note this is especially useful for dialogs or similar widgets
   */
  inline bool Border::hasNoTopBorder() const
  {
    return no_top_border_;
  }
}


#endif
