// TestMove.cpp

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

#include <type/Move.hpp>

#include "TestMove.hpp"


namespace test
{
  namespace
  {
    struct Foo
    {
      Foo(int i)
        : i(i)
      {
      }

      Foo(Foo const&) = delete;
      Foo(Foo&& other)
        : i(other.i)
      {
        other.i = 0;
      }

      Foo& operator =(Foo const&) = delete;
      Foo& operator =(Foo&& other)
      {
        i = other.i;
        other.i = 0;
      }

      int i;
    };
  }


  TestMove::TestMove()
    : tst::TestCase<TestMove>(*this, "TestMove")
  {
    add(&TestMove::testMove1);
    add(&TestMove::testMove2);
    add(&TestMove::testMove3);
    add(&TestMove::testForward1);
  }

  void TestMove::testMove1(tst::TestResult& result)
  {
    Foo foo1(42);
    TESTASSERTOP(foo1.i, eq, 42);

    Foo foo2 = typ::move(foo1);
    TESTASSERTOP(foo2.i, eq, 42);
    TESTASSERTOP(foo1.i, eq, 0);
  }

  void TestMove::testMove2(tst::TestResult& result)
  {
    Foo  foo1(42);
    Foo& foo2 = foo1;

    Foo foo3 = typ::move(foo2);
    TESTASSERTOP(foo3.i, eq, 42);
    TESTASSERTOP(foo2.i, eq, 0);
    TESTASSERTOP(foo1.i, eq, 0);
  }

  void TestMove::testMove3(tst::TestResult& result)
  {
    Foo foo1(42);
    Foo foo2(43);
    TESTASSERTOP(foo2.i, eq, 43);

    foo2 = typ::move(foo1);
    TESTASSERTOP(foo2.i, eq, 42);
    TESTASSERTOP(foo1.i, eq, 0);
  }

  void TestMove::testForward1(tst::TestResult& result)
  {
    //Foo foo2 = typ::forward(Foo(43));
    //TESTASSERTOP(foo2.i, eq, 43);
  }
}
