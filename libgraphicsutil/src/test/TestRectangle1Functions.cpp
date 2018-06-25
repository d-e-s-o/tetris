// TestRectangle1Functions.cpp

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
#include <util/Rectangle1Functions.hpp>

#include "TestRectangle1Functions.hpp"


namespace test
{
  namespace
  {
    typedef utl::Point<int>                    Position;
    typedef utl::Point<unsigned int>           Size;
    typedef utl::Rectangle1<int, unsigned int> Rect;
  }


  TestRectangle1Functions::TestRectangle1Functions()
    : tst::TestCase<TestRectangle1Functions>(*this, "TestRectangle1Functions")
  {
    add(&TestRectangle1Functions::testContains);
    add(&TestRectangle1Functions::testGetRectangle);
    add(&TestRectangle1Functions::testSetPosition);
    add(&TestRectangle1Functions::testMove);
    add(&TestRectangle1Functions::testSetSize);
    add(&TestRectangle1Functions::testGrow);
    add(&TestRectangle1Functions::testGetPosition);
    add(&TestRectangle1Functions::testGetSize);
  }

  void TestRectangle1Functions::testContains(tst::TestResult& result)
  {
    Rect r(15, -25, 10, 20);

    TESTASSERT( utl::contains(r, Position(15, -25)));
    TESTASSERT(!utl::contains(r, Position(14, -25)));
    TESTASSERT(!utl::contains(r, Position(15, -26)));

    TESTASSERT( utl::contains(r, Position(25, -5)));
    TESTASSERT(!utl::contains(r, Position(26, -5)));
    TESTASSERT(!utl::contains(r, Position(25, -4)));

    TESTASSERT(!utl::contains(r, Position(15, 20)));
  }

  void TestRectangle1Functions::testGetRectangle(tst::TestResult& result)
  {
    Position p1(20, 40);
    Size     p2(60, 80);

    TESTASSERT(utl::getRectangle(p1, p2) == Rect(20, 40, 60, 80));
  }

  void TestRectangle1Functions::testSetPosition(tst::TestResult& result)
  {
    Rect r(20, 40, 60, 80);
    utl::setPosition(r, Position(100, 120));

    TESTASSERT(r == Rect(100, 120, 60, 80));
  }

  void TestRectangle1Functions::testMove(tst::TestResult& result)
  {
    Rect r(20, 40, 60, 80);
    utl::move(r, Position(40, 20));

    TESTASSERT(r == Rect(60, 60, 60, 80));
  }

  void TestRectangle1Functions::testSetSize(tst::TestResult& result)
  {
    Rect r(20, 40, 60, 80);
    utl::setSize(r, Size(40, 20));

    TESTASSERT(r == Rect(20, 40, 40, 20));
  }

  void TestRectangle1Functions::testGrow(tst::TestResult& result)
  {
    Rect r(20, 40, 60, 80);

    utl::grow(r, Size(40, 20));
    TESTASSERTOP(r.w, eq, 100);
    TESTASSERTOP(r.h, eq, 100);
  }

  void TestRectangle1Functions::testGetPosition(tst::TestResult& result)
  {
    Rect r(20, 40, 60, 80);

    TESTASSERT(utl::getPosition(r) == Position(20, 40));
  }

  void TestRectangle1Functions::testGetSize(tst::TestResult& result)
  {
    Rect r(20, 40, 60, 80);

    TESTASSERT(utl::getSize(r) == Size(60, 80));
  }
}
