// Container1.hpp

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

#ifndef TESTCONTAINER1_HPP
#define TESTCONTAINER1_HPP

#include <gui/widget/Container.hpp>


namespace test
{
  /**
   *
   */
  class Container1: public gui::Container
  {
  public:
    Container1();
    Container1(gui::Bounds const& bounds);

    using gui::Container::setFocusable;
    using gui::Container::isFocusable;
  };
}


namespace test
{
  inline Container1::Container1()
    : gui::Container(gui::Bounds(0, 0, 100, 100))
  {
  }

  inline Container1::Container1(gui::Bounds const& bounds)
    : gui::Container(bounds)
  {
  }
}


#endif
