// TestPoint.cpp

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

#include <util/Point.hpp>

#include "TestPoint.hpp"


namespace test
{
  namespace
  {
    typedef utl::Point<int> Point;
  }


  TestPoint::TestPoint()
    : tst::TestCase<TestPoint>(*this, "TestPoint")
  {
    add(&TestPoint::testCreation);
    add(&TestPoint::testAssignAdd);
    add(&TestPoint::testAssignSub);
    add(&TestPoint::testUnaryMinus);
    add(&TestPoint::testEqual);
    add(&TestPoint::testUnequal);
    add(&TestPoint::testAdd);
    add(&TestPoint::testSub);
  }

  void TestPoint::testCreation(tst::TestResult& result)
  {
    Point p(1, 2);

    TESTASSERTOP(p.x, eq, 1);
    TESTASSERTOP(p.y, eq, 2);
  }

  void TestPoint::testAssignAdd(tst::TestResult& result)
  {
    Point p1(1, 2);
    Point p2(4, 5);

    p2 += p1;

    TESTASSERTOP(p2.x, eq, 5);
    TESTASSERTOP(p2.y, eq, 7);
  }

  void TestPoint::testAssignSub(tst::TestResult& result)
  {
    Point p1(1, 2);
    Point p2(4, 5);

    p2 -= p1;

    TESTASSERTOP(p2.x, eq, 3);
    TESTASSERTOP(p2.y, eq, 3);
  }

  void TestPoint::testUnaryMinus(tst::TestResult& result)
  {
    Point p1(1, 2);
    Point p2 = -p1;

    TESTASSERTOP(p2.x, eq, -1);
    TESTASSERTOP(p2.y, eq, -2);
  }

  void TestPoint::testEqual(tst::TestResult& result)
  {
    Point p1(1, 90);
    Point p2(1, 90);

    TESTASSERT(p1 == p2);
  }

  void TestPoint::testUnequal(tst::TestResult& result)
  {
    Point p1(1, 90);
    Point p2(1337, 90);

    TESTASSERT(p1 != p2);
  }

  void TestPoint::testAdd(tst::TestResult& result)
  {
    Point p1(7, 8);
    Point p2(4, 5);

    Point p3 = p2 + p1;

    TESTASSERTOP(p3.x, eq, 11);
    TESTASSERTOP(p3.y, eq, 13);
  }

  void TestPoint::testSub(tst::TestResult& result)
  {
    Point p1(4, 5);
    Point p2(7, 8);

    Point p3 = p1 - p2;

    TESTASSERTOP(p3.x, eq, -3);
    TESTASSERTOP(p3.y, eq, -3);
  }
}
