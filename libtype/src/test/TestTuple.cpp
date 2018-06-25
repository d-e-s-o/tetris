// TestTuple.cpp

/***************************************************************************
 *   Copyright (C) 2013-2014 Daniel Mueller                                *
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

#include <type/Tuple.hpp>

#include "TestTuple.hpp"


namespace test
{
  namespace
  {
    struct Foo1
    {
      Foo1(long x)
        : x_(x)
      {
      }

      long x_;
    };


    struct Foo2
    {
      Foo2(int x, int y)
        : x_(x),
          y_(y)
      {
      }

      int x_;
      int y_;
    };
  }


  TestTuple::TestTuple()
    : tst::TestCase<TestTuple>(*this, "TestTuple")
  {
    add(&TestTuple::testGet1);
    add(&TestTuple::testGet2);
  }

  void TestTuple::testGet1(tst::TestResult& result)
  {
    auto t = typ::makeTuple(1, Foo1(-2), Foo2(42, 3), 4);
    TESTASSERTOP(t.get<0>(), eq, 1);
    TESTASSERTOP(typ::get<0>(t), eq, 1);

    TESTASSERTOP(t.get<1>().x_, eq, -2);
    TESTASSERTOP(typ::get<1>(t).x_, eq, -2);

    TESTASSERTOP(t.get<2>().x_, eq, 42);
    TESTASSERTOP(typ::get<2>(t).x_, eq, 42);

    TESTASSERTOP(t.get<2>().y_, eq, 3);
    TESTASSERTOP(typ::get<2>(t).y_, eq, 3);

    TESTASSERTOP(t.get<3>(), eq, 4);
    TESTASSERTOP(typ::get<3>(t), eq, 4);

    t.get<2>().y_ = 1337;
    TESTASSERTOP(t.get<2>().y_, eq, 1337);

    typ::get<2>(t).y_ = 1338;
    TESTASSERTOP(typ::get<2>(t).y_, eq, 1338);
  }

  void TestTuple::testGet2(tst::TestResult& result)
  {
    typ::Tuple<int, Foo2, void*> const t(42, Foo2(1, 2), nullptr);
    TESTASSERTOP(t.get<0>(), eq, 42);
    TESTASSERTOP(typ::get<0>(t), eq, 42);

    TESTASSERTOP(t.get<1>().x_, eq, 1);
    TESTASSERTOP(typ::get<1>(t).x_, eq, 1);

    TESTASSERTOP(t.get<1>().y_, eq, 2);
    TESTASSERTOP(typ::get<1>(t).y_, eq, 2);

    TESTASSERTOP(t.get<2>(), eq, nullptr);
    TESTASSERTOP(typ::get<2>(t), eq, nullptr);
  }
}
