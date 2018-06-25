// TestTerminal.cpp

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

#include <tokenize/Terminal.hpp>

#include "TestTerminal.hpp"


namespace
{
  char const string_a[] = "a";
  char const string_b[] = "b";
  char const string_0[] = "";
}


namespace test
{
  TestTerminal::TestTerminal()
    : TokenizeTestCase<TestTerminal>(*this, "TestTerminal")
  {
    add(&TestTerminal::testScan1);
    add(&TestTerminal::testScan2);
  }

  void TestTerminal::testScan1(tst::TestResult& result)
  {
    auto e = T::T<'a'>();

    r_ = e.scan(makeSymbolStream(string_a), tokens_);
    TESTASSERTOP(r_.last, eq, 1);
    TESTASSERTOP(r_.max , eq, 1);

    r_ = e.scan(makeSymbolStream(string_b), tokens_);
    TESTASSERTOP(r_.last, lt, 0);
    TESTASSERTOP(r_.max, eq, 0);

    r_ = e.scan(makeSymbolStream(string_0), tokens_);
    TESTASSERTOP(r_.last, lt, 0);
    TESTASSERTOP(r_.max, eq, 0);
  }

  void TestTerminal::testScan2(tst::TestResult& result)
  {
    r_ = TB().scan(makeSymbolStream(string_a), tokens_);
    TESTASSERTOP(r_.last, eq, 0);
    TESTASSERTOP(r_.max , eq, 0);

    r_ = TE().scan(makeSymbolStream(string_a), tokens_);
    TESTASSERTOP(r_.last, eq, -1);
    TESTASSERTOP(r_.max , eq, 0);

    r_ = TB().scan(makeSymbolStream(string_0), tokens_);
    TESTASSERTOP(r_.last, eq, 0);
    TESTASSERTOP(r_.max , eq, 0);

    r_ = TE().scan(makeSymbolStream(string_0), tokens_);
    TESTASSERTOP(r_.last, eq, 0);
    TESTASSERTOP(r_.max , eq, 0);
  }
}
