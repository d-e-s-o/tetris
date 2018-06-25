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

#ifndef TESTDECORATOR2_HPP
#define TESTDECORATOR2_HPP

#include <gui/widget/Decorator.hpp>
#include "Decorator1.hpp"


namespace test
{
  /**
   * Test class for a Decorator "container". The first one is the Decorator itself, then
   * decorator_1_, decorator_2_ and last is decorator_3_.
   */
  class Decorator2: public gui::Decorator
  {
  public:
    Decorator1 decorator_1_;
    Decorator1 decorator_2_;
    Decorator1 decorator_3_;

    Decorator2(gui::Widget& widget);

    using Decorator::getNext;
    using Decorator::setNext;
    using Decorator::getPrevious;
    using Decorator::setPrevious;

    virtual Decorator& getFirst();
    virtual Decorator& getLast();

    virtual bool isChild(Decorator const& decorator) const;
  };
}


#endif
