// TestRectangle2.cpp

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

#include <util/Rectangle2.hpp>

#include "TestRectangle2.hpp"


namespace test
{
  namespace
  {
    typedef utl::Rectangle2<int> Rect;
  }


  TestRectangle2::TestRectangle2()
    : tst::TestCase<TestRectangle2>(*this, "TestRectangle2")
  {
    add(&TestRectangle2::testCreation);
    add(&TestRectangle2::testEqual);
    add(&TestRectangle2::testUnequal);
  }

  void TestRectangle2::testCreation(tst::TestResult& result)
  {
    Rect r(1, 2, 3, 4);

    TESTASSERTOP(r.x1_, eq, 1);
    TESTASSERTOP(r.y1_, eq, 2);
    TESTASSERTOP(r.x2_, eq, 3);
    TESTASSERTOP(r.y2_, eq, 4);
  }

  void TestRectangle2::testEqual(tst::TestResult& result)
  {
    Rect r1(1, 2, 3, 4);
    Rect r2(1, 2, 3, 4);

    TESTASSERT(r1 == r2);
  }

  void TestRectangle2::testUnequal(tst::TestResult& result)
  {
    Rect r1(1, 2, 3, 5555);
    Rect r2(1, 2, 3, 4);

    TESTASSERT(r1 != r2);
  }
}
