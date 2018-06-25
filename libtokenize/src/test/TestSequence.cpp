// TestSequence.cpp

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

#include "TestSequence.hpp"


namespace
{
  char const string_ab[]   = "ab";
  char const string_abab[] = "abab";
  char const string_b[]    = "b";
  char const string_0[]    = "";
}


namespace test
{
  /**
   * @todo add tests covering value of Result::max
   */
  TestSequence::TestSequence()
    : TokenizeTestCase<TestSequence>(*this, "TestSequence")
  {
    add(&TestSequence::testScan);
  }

  void TestSequence::testScan(tst::TestResult& result)
  {
    auto e = T::T<'a'>() + T::T<'b'>();

    TESTASSERTOP(e.scan(makeSymbolStream(string_ab),   tokens_).last, eq, 2);
    TESTASSERTOP(e.scan(makeSymbolStream(string_abab), tokens_).last, eq, 2);
    TESTASSERTOP(e.scan(makeSymbolStream(string_b),    tokens_).last, lt,  0);
    TESTASSERTOP(e.scan(makeSymbolStream(string_0),    tokens_).last, lt,  0);
  }
}
