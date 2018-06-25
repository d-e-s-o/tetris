// TestRectangle2Functions.cpp

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
#include <util/Rectangle2Functions.hpp>

#include "TestRectangle2Functions.hpp"


namespace test
{
  namespace
  {
    typedef utl::Point<int>      Point;
    typedef utl::Rectangle2<int> Rect;
  }


  TestRectangle2Functions::TestRectangle2Functions()
    : tst::TestCase<TestRectangle2Functions>(*this, "TestRectangle2Functions")
  {
    add(&TestRectangle2Functions::testContains);
    add(&TestRectangle2Functions::testGetRectangle);
    add(&TestRectangle2Functions::testMove);
  }

  void TestRectangle2Functions::testContains(tst::TestResult& result)
  {
    Rect r(15, -25, 25, 0);

    TESTASSERT( utl::contains(r, Point(15, -25)));
    TESTASSERT(!utl::contains(r, Point(14, -25)));
    TESTASSERT(!utl::contains(r, Point(15, -26)));

    TESTASSERT( utl::contains(r, Point(25, 0)));
    TESTASSERT(!utl::contains(r, Point(26, 0)));
    TESTASSERT(!utl::contains(r, Point(25, 1)));

    TESTASSERT(!utl::contains(r, Point(15, 20)));
  }

  void TestRectangle2Functions::testGetRectangle(tst::TestResult& result)
  {
    Point p1(20, 40);
    Point p2(60, 80);

    TESTASSERT(utl::getRectangle(p1, p2) == Rect(20, 40, 60, 80));
  }

  void TestRectangle2Functions::testMove(tst::TestResult& result)
  {
    Rect r(20, 40, 60, 80);
    utl::move(r, Point(40, 20));

    TESTASSERT(r == Rect(60, 60, 100, 100));
  }
}
