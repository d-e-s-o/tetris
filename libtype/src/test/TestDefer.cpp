// TestDefer.cpp

/***************************************************************************
 *   Copyright (C) 2014 Daniel Mueller                                     *
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

#include <type/Defer.hpp>

#include "TestDefer.hpp"


namespace test
{
  namespace
  {
    int shared_global = 0;

    int test1(void* p, int j)
    {
      shared_global = j;
      return shared_global;
    }
  }


  TestDefer::TestDefer()
    : tst::TestCase<TestDefer>(*this, "TestDefer")
  {
    add(&TestDefer::testDefer1);
    add(&TestDefer::testDefer2);
    add(&TestDefer::testRelease1);
    add(&TestDefer::testRelease2);
  }

  void TestDefer::testDefer1(tst::TestResult& result)
  {
    int value = 0;
    {
      DEFERX([&value](){ value += 1; });
      TESTASSERTOP(value, eq, 0);
      DEFERX([&value](){ value += 2; });
      TESTASSERTOP(value, eq, 0);
      DEFERX([&value](){ value += 3; });
      TESTASSERTOP(value, eq, 0);
      DEFERX([&value](){ value += 4; });
      TESTASSERTOP(value, eq, 0);
      DEFERX([&value](){ value += 5; });
      TESTASSERTOP(value, eq, 0);
    }

    TESTASSERTOP(value, eq, 15);
  }

  void TestDefer::testDefer2(tst::TestResult& result)
  {
    TESTASSERTOP(shared_global, eq, 0);

    {
      DEFERX(test1, nullptr, 4);
      DEFERX(test1, nullptr, 1);
      TESTASSERTOP(shared_global, eq, 0);
    }

    TESTASSERTOP(shared_global, eq, 4);
  }

  void TestDefer::testRelease1(tst::TestResult& result)
  {
    int value = 0;
    {
      DEFER(d1, [&value](){ value += 1; });
      DEFER(d2, [&value](){ value += 2; });

      d2.release();
      d1.release();
    }

    TESTASSERTOP(value, eq, 0);
  }

  void TestDefer::testRelease2(tst::TestResult& result)
  {
    int value = 0;
    {
      DEFER(d1, [&value](){ value += 1; });
      DEFER(d2, [&value](){ value += 2; });
      DEFER(d3, [&value](){ value += 3; });
      DEFER(d4, [&value](){ value += 4; });

      // omit d3
      RELEASE(d1, d2, d4);
    }

    TESTASSERTOP(value, eq, 3);
  }
}
