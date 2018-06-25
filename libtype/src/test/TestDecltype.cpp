// TestDecltype.cpp

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

#include <type/Decltype.hpp>

#include "TestDecltype.hpp"


namespace test
{
  namespace
  {
    double test1(int i)
    {
      return 0;
    }

    struct Foo
    {
      Foo test2()
      {
        return *this;
      }
    };
  }


  TestDecltype::TestDecltype()
    : tst::TestCase<TestDecltype>(*this, "TestDecltype")
  {
    add(&TestDecltype::testType1);
    add(&TestDecltype::testType2);
    add(&TestDecltype::testType3);
  }

  void TestDecltype::testType1(tst::TestResult& result)
  {
    typedef decltype(typ::returnType(test1)) Type;

    // @todo could also use typ::Equal<> here
    Type i = 0.0;
    TESTASSERT(true);
  }

  void TestDecltype::testType2(tst::TestResult& result)
  {
    auto fn1 = [](){ return 0; };

    typedef decltype(typ::returnType(fn1)) Type;
    Type i = 0;

    TESTASSERT(true);
  }

  void TestDecltype::testType3(tst::TestResult& result)
  {
    typedef decltype(typ::returnType(&Foo::test2)) Type;

    Type i = Foo();
    TESTASSERT(true);
  }
}
