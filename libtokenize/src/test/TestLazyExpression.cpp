// TestLazyExpression.cpp

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

#include <tokenize/Sequence.hpp>
#include <tokenize/Alternative.hpp>
#include <tokenize/LazyExpression.hpp>

#include "TestLazyExpression.hpp"


namespace
{
  char const string_b[]       = "b";
  char const string_aba[]     = "aba";
  char const string_abab[]    = "abab";
  char const string_abaa[]    = "abaa";
  char const string_aaabaaa[] = "aaabaaa";
  char const string_aaacaaa[] = "aaacaaa";
  char const string_0[]       = "";
}


namespace test
{
  /**
   * @todo add tests covering value of Result::max
   */
  TestLazyExpression::TestLazyExpression()
    : TokenizeTestCase<TestLazyExpression>(*this, "TestLazyExpression")
  {
    add(&TestLazyExpression::testScan);
  }

  void TestLazyExpression::testScan(tst::TestResult& result)
  {
    auto e_ = LazyExpr();
    auto a  = T::T<'a'>();
    auto b  = T::T<'b'>();
    auto e  = (a + e_ + a) | b;

    TESTASSERTOP(e.scan(makeSymbolStream(string_b),   tokens_), eq, 1);
    TESTASSERTOP(e.scan(makeSymbolStream(string_aba), tokens_), lt,  0);
    TESTASSERTOP(e.scan(makeSymbolStream(string_0),   tokens_), lt,  0);

    e_.assign(e);

    TESTASSERTOP(e.scan(makeSymbolStream(string_b),       tokens_), eq, 1);
    TESTASSERTOP(e.scan(makeSymbolStream(string_aba),     tokens_), eq, 3);
    TESTASSERTOP(e.scan(makeSymbolStream(string_abab),    tokens_), eq, 3);
    TESTASSERTOP(e.scan(makeSymbolStream(string_abaa),    tokens_), eq, 3);
    TESTASSERTOP(e.scan(makeSymbolStream(string_aaabaaa), tokens_), eq, 7);
    TESTASSERTOP(e.scan(makeSymbolStream(string_aaacaaa), tokens_), lt,  0);
    TESTASSERTOP(e.scan(makeSymbolStream(string_0),       tokens_), lt,  0);

    e_.assign(b);

    TESTASSERTOP(e.scan(makeSymbolStream(string_b),       tokens_), eq, 1);
    TESTASSERTOP(e.scan(makeSymbolStream(string_aba),     tokens_), eq, 3);
    TESTASSERTOP(e.scan(makeSymbolStream(string_abab),    tokens_), eq, 3);
    TESTASSERTOP(e.scan(makeSymbolStream(string_abaa),    tokens_), eq, 3);
    TESTASSERTOP(e.scan(makeSymbolStream(string_aaabaaa), tokens_), lt,  0);
    TESTASSERTOP(e.scan(makeSymbolStream(string_aaacaaa), tokens_), lt,  0);
    TESTASSERTOP(e.scan(makeSymbolStream(string_0),       tokens_), lt,  0);
  }
}
