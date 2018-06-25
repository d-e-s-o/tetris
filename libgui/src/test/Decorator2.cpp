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

#include "Decorator2.hpp"


namespace test
{
  Decorator2::Decorator2(gui::Widget& widget)
    : Decorator(widget),
      decorator_1_(widget),
      decorator_2_(widget),
      decorator_3_(widget)
  {
    decorator_1_.insertAfter(*this);
    decorator_2_.insertAfter(decorator_1_);
    decorator_3_.insertAfter(decorator_2_);
  }

  gui::Decorator& Decorator2::getFirst()
  {
    return *this;
  }

  gui::Decorator& Decorator2::getLast()
  {
    return decorator_3_;
  }

  bool Decorator2::isChild(gui::Decorator const& decorator) const
  {
    return (&decorator == &decorator_1_) ||
           (&decorator == &decorator_2_) ||
           (&decorator == &decorator_3_);
  }
}
