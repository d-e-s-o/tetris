// Field1.hpp

/***************************************************************************
 *   Copyright (C) 2013 Daniel Mueller (deso@posteo.net)                   *
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

#ifndef TESTFIELD1_HPP
#define TESTFIELD1_HPP

#include <tetris/game/AbstractField.hpp>


namespace test
{
  class Field1: public ttrs::AbstractField<bool>
  {
  public:
    static ttrs::dimension_t const WIDTH = 6;
    static ttrs::dimension_t const HEIGHT = 9;

    Field1();
  };
}


namespace test
{
  inline Field1::Field1()
    : AbstractField<bool>(WIDTH, HEIGHT)
  {
  }
}


#endif
