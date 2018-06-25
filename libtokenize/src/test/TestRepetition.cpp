// TestRepetition.cpp

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

#include <tokenize/Repetition.hpp>

#include "TestRepetition.hpp"


namespace
{
  char const string_a[]       = "a";
  char const string_aa[]      = "aa";
  char const string_aaaaaba[] = "aaaaaba";
  char const string_b[]       = "b";
  char const string_0[]       = "";
}


namespace test
{
  /**
   * @todo add tests covering value of Result::max
   */
  TestRepetition::TestRepetition()
    : TokenizeTestCase<TestRepetition>(*this, "TestRepetition")
  {
    add(&TestRepetition::testScan1);
    add(&TestRepetition::testScan2);
    add(&TestRepetition::testScan3);
    add(&TestRepetition::testScan4);
  }

  void TestRepetition::testScan1(tst::TestResult& result)
  {
    auto e = T::T<'a'>() * tok::RepeatCount<0>();

    TESTASSERTOP(e.scan(makeSymbolStream(string_a), tokens_).last, eq, 0);
    TESTASSERTOP(e.scan(makeSymbolStream(string_0), tokens_).last, eq, 0);
  }

  void TestRepetition::testScan2(tst::TestResult& result)
  {
    auto e = T::T<'a'>() * tok::RepeatCount<1>();

    TESTASSERTOP(e.scan(makeSymbolStream(string_a),  tokens_).last, eq, 1);
    TESTASSERTOP(e.scan(makeSymbolStream(string_aa), tokens_).last, eq, 1);
    TESTASSERTOP(e.scan(makeSymbolStream(string_b),  tokens_).last, lt,  0);
    TESTASSERTOP(e.scan(makeSymbolStream(string_0),  tokens_).last, lt,  0);
  }

  void TestRepetition::testScan3(tst::TestResult& result)
  {
    auto e = T::T<'a'>() * tok::RepeatCount<0, -1>();

    TESTASSERTOP(e.scan(makeSymbolStream(string_a),       tokens_).last, eq, 1);
    TESTASSERTOP(e.scan(makeSymbolStream(string_aa),      tokens_).last, eq, 2);
    TESTASSERTOP(e.scan(makeSymbolStream(string_aaaaaba), tokens_).last, eq, 5);
    TESTASSERTOP(e.scan(makeSymbolStream(string_b),       tokens_).last, eq, 0);
    TESTASSERTOP(e.scan(makeSymbolStream(string_0),       tokens_).last, eq, 0);
  }

  void TestRepetition::testScan4(tst::TestResult& result)
  {
    // although this does not make much sense, it is a valid usage and should not result in an
    // endless loop
    auto e = (T::T<'a'>() * tok::RepeatCount<0, -1>()) * tok::RepeatCount<0, -1>();

    TESTASSERTOP(e.scan(makeSymbolStream(string_a),       tokens_).last, eq, 1);
    TESTASSERTOP(e.scan(makeSymbolStream(string_aa),      tokens_).last, eq, 2);
    TESTASSERTOP(e.scan(makeSymbolStream(string_aaaaaba), tokens_).last, eq, 5);
    TESTASSERTOP(e.scan(makeSymbolStream(string_b),       tokens_).last, eq, 0);
    TESTASSERTOP(e.scan(makeSymbolStream(string_0),       tokens_).last, eq, 0);
  }
}
