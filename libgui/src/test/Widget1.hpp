// Widget1.hpp

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

#ifndef TESTWIDGET1_HPP
#define TESTWIDGET1_HPP

#include <gui/widget/Widget.hpp>


namespace test
{
  class Widget1: public gui::Widget
  {
  public:
    Widget1();
    Widget1(gui::Bounds const& bounds);

    using gui::Widget::setFocusable;
    using gui::Widget::isFocusable;
  };
}


namespace test
{
  inline Widget1::Widget1()
    : gui::Widget(gui::Bounds(0, 0, 10, 10))
  {
  }

  inline Widget1::Widget1(gui::Bounds const& bounds)
    : gui::Widget(bounds)
  {
  }
}


#endif
