// TestFieldFunctions.cpp

/***************************************************************************
 *   Copyright (C) 2013-2014 Daniel Mueller (deso@posteo.net)              *
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

#include <tetris/game/FieldFunctions.hpp>

#include "test/TestFieldFunctions.hpp"


namespace test
{
  TestFieldFunctions::TestFieldFunctions()
    : tst::TestCase<TestFieldFunctions>(*this, "TestFieldFunctions"),
      field_()
  {
    add(&TestFieldFunctions::testLinesComplete1);
    add(&TestFieldFunctions::testClearLines1);
  }

  void TestFieldFunctions::setUp()
  {
    field_ = Field1();
  }

  void TestFieldFunctions::testLinesComplete1(tst::TestResult& result)
  {
    // @todo implement me!
    TESTASSERTM(false, "implement me!");
  }

  void TestFieldFunctions::testClearLines1(tst::TestResult& result)
  {
    // @todo implement me!
    TESTASSERTM(false, "implement me!");
  }
}
