// TestUniquePointer.cpp

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
#include <pointer/UniquePointer.hpp>

#include "TestUniquePointer.hpp"


namespace test
{
  namespace
  {
    typedef ptr::UniquePointer<InstanceCounter const> Pointer;


    Pointer temporaryPointer()
    {
      return Pointer(new InstanceCounter);
    }
  }


  TestUniquePointer::TestUniquePointer()
    : InstanceCounterTestCase<TestUniquePointer>(*this, "TestUniquePointer")
  {
    add(&TestUniquePointer::testRelease1);
    add(&TestUniquePointer::testMove1);
    add(&TestUniquePointer::testMove2);
  }

  void TestUniquePointer::testRelease1(tst::TestResult& result)
  {
    {
      Pointer p1(new InstanceCounter);
      TESTASSERTOP(InstanceCounter::count, eq, 1);

      Pointer p2(new InstanceCounter);
      TESTASSERTOP(InstanceCounter::count, eq, 2);
    }

    TESTASSERTOP(InstanceCounter::count, eq, 0);
  }

  void TestUniquePointer::testMove1(tst::TestResult& result)
  {
    {
      Pointer p1(new InstanceCounter);
      TESTASSERTOP(InstanceCounter::count, eq, 1);

      Pointer p2(typ::move(p1));
      TESTASSERTOP(InstanceCounter::count, eq, 1);
    }

    TESTASSERTOP(InstanceCounter::count, eq, 0);
  }

  void TestUniquePointer::testMove2(tst::TestResult& result)
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
}
