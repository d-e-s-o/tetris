// TestSharedPointer.cpp

/***************************************************************************
 *   Copyright (C) 2012,2014 Daniel Mueller (deso@posteo.net)              *
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

#include <type/Move.hpp>
#include <test/Util.hpp>
#include <pointer/SharedPointer.hpp>

#include "TestSharedPointer.hpp"


namespace test
{
  namespace
  {
    typedef ptr::SharedPointer<InstanceCounter> Pointer;
  }


  TestSharedPointer::TestSharedPointer()
    : InstanceCounterTestCase<TestSharedPointer>(*this, "TestSharedPointer")
  {
    add(&TestSharedPointer::testRelease1);
    add(&TestSharedPointer::testRelease2);
    add(&TestSharedPointer::testMove1);
    add(&TestSharedPointer::testMove2);
    add(&TestSharedPointer::testEqual1);
    add(&TestSharedPointer::testNotEqual1);
    add(&TestSharedPointer::testLess1);
    add(&TestSharedPointer::testLess2);
  }

  void TestSharedPointer::testRelease1(tst::TestResult& result)
  {
    {
      ptr::SharedPointer<InstanceCounter> p1(new InstanceCounter);
      TESTASSERTOP(InstanceCounter::count, eq, 1);

      ptr::SharedPointer<InstanceCounter> p2(new InstanceCounter);
      TESTASSERTOP(InstanceCounter::count, eq, 2);
    }

    TESTASSERTOP(InstanceCounter::count, eq, 0);
  }

  void TestSharedPointer::testRelease2(tst::TestResult& result)
  {
    {
      Pointer p1(new InstanceCounter);
      TESTASSERTOP(InstanceCounter::count, eq, 1);

      Pointer p2(p1);
      Pointer p3 = p2;
      TESTASSERTOP(InstanceCounter::count, eq, 1);

      Pointer p4(new InstanceCounter);
      TESTASSERTOP(InstanceCounter::count, eq, 2);

      p4 = p3;
      TESTASSERTOP(InstanceCounter::count, eq, 1);
    }

    TESTASSERTOP(InstanceCounter::count, eq, 0);
  }

  void TestSharedPointer::testMove1(tst::TestResult& result)
  {
    {
      Pointer p1(new InstanceCounter);
      TESTASSERTOP(InstanceCounter::count, eq, 1);

      Pointer p2(typ::move(p1));
      TESTASSERTOP(InstanceCounter::count, eq, 1);
    }

    TESTASSERTOP(InstanceCounter::count, eq, 0);
  }

  void TestSharedPointer::testMove2(tst::TestResult& result)
  {
    {
      Pointer p1(new InstanceCounter);
      TESTASSERTOP(InstanceCounter::count, eq, 1);

      Pointer p2(new InstanceCounter);
      TESTASSERTOP(InstanceCounter::count, eq, 2);

      p2 = typ::move(p1);
      TESTASSERTOP(InstanceCounter::count, eq, 1);
    }

    TESTASSERTOP(InstanceCounter::count, eq, 0);
  }

  void TestSharedPointer::testEqual1(tst::TestResult& result)
  {
    Pointer p1(new InstanceCounter);
    Pointer p2 = p1;

    TESTASSERTOP(p1, eq, p2);
  }

  void TestSharedPointer::testNotEqual1(tst::TestResult& result)
  {
    Pointer p1(new InstanceCounter);
    Pointer p2(new InstanceCounter);

    TESTASSERT(p1 != p2);
  }

  void TestSharedPointer::testLess1(tst::TestResult& result)
  {
    Pointer p1(new InstanceCounter);
    Pointer p2 = p1;

    TESTASSERT(!(p1 < p2) && !(p1 > p2));
  }

  void TestSharedPointer::testLess2(tst::TestResult& result)
  {
    Pointer p1(new InstanceCounter);
    Pointer p2(new InstanceCounter);

    TESTASSERT(tst::logicalXor(p1 < p2, p1 > p2));
  }
}
