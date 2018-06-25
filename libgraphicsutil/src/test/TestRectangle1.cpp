// TestRectangle1.cpp

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

#include <util/Rectangle1.hpp>

#include "TestRectangle1.hpp"


namespace test
{
  namespace
  {
    typedef utl::Rectangle1<int, int> Rect;
  }


  TestRectangle1::TestRectangle1()
    : tst::TestCase<TestRectangle1>(*this, "TestRectangle1")
  {
    add(&TestRectangle1::testCreation);
    add(&TestRectangle1::testEqual);
    add(&TestRectangle1::testUnequal);
  }

  void TestRectangle1::testCreation(tst::TestResult& result)
  {
    Rect r(1, 2, 3, 4);

    TESTASSERTOP(r.x, eq, 1);
    TESTASSERTOP(r.y, eq, 2);
    TESTASSERTOP(r.w, eq, 3);
    TESTASSERTOP(r.h, eq, 4);
  }

  void TestRectangle1::testEqual(tst::TestResult& result)
  {
    Rect r1(1, 2, 3, 4);
    Rect r2(1, 2, 3, 4);

    TESTASSERT(r1 == r2);
  }

  void TestRectangle1::testUnequal(tst::TestResult& result)
  {
    Rect r1(1, 2, 3, 5555);
    Rect r2(1, 2, 3, 4);

    TESTASSERT(r1 != r2);
  }
}
