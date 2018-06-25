// TestAlternative.cpp

/***************************************************************************
 *   Copyright (C) 2012,2014 Daniel Mueller                                *
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

#include <tokenize/Alternative.hpp>
#include <tokenize/Sequence.hpp>

#include "TestAlternative.hpp"


namespace
{
  char const string_a[]   = "a";
  char const string_b[]   = "b";
  char const string_c[]   = "c";
  char const string_0[]   = "";
  char const string_aaa[] = "aaa";
}


namespace test
{
  /**
   * @todo add tests covering value of Result::max
   */
  TestAlternative::TestAlternative()
    : TokenizeTestCase<TestAlternative>(*this, "TestAlternative")
  {
    add(&TestAlternative::testScan1);
    add(&TestAlternative::testScan2);
  }

  void TestAlternative::testScan1(tst::TestResult& result)
  {
    auto e = T::T<'a'>() | T::T<'b'>();

    TESTASSERTOP(e.scan(makeSymbolStream(string_a), tokens_).last, eq, 1);
    TESTASSERTOP(e.scan(makeSymbolStream(string_b), tokens_).last, eq, 1);
    TESTASSERTOP(e.scan(makeSymbolStream(string_c), tokens_).last, lt,  0);
    TESTASSERTOP(e.scan(makeSymbolStream(string_0), tokens_).last, lt,  0);
  }

  void TestAlternative::testScan2(tst::TestResult& result)
  {
    auto a = T::T<'a'>();
    auto b = T::T<'b'>();

    // Alternative should always scan the left expression first, and only check further if that scan
    // failed
    auto e1 = b | a + a + a | a + a | a;
    auto e2 = b | a | a + a | a + a + a;

    TESTASSERTOP(e1.scan(makeSymbolStream(string_aaa), tokens_).last, eq, 3);
    TESTASSERTOP(e2.scan(makeSymbolStream(string_aaa), tokens_).last, eq, 1);
    TESTASSERTOP(e1.scan(makeSymbolStream(string_b),   tokens_).last, eq, 1);
    TESTASSERTOP(e2.scan(makeSymbolStream(string_b),   tokens_).last, eq, 1);
  }
}
