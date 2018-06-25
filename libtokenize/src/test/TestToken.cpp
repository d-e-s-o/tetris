// TestToken.cpp

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
#include <tokenize/Token.hpp>

#include "TestToken.hpp"


namespace
{
  char const string_abab[] = "abab";
}


namespace test
{
  /**
   * @todo add tests covering value of Result::max
   */
  TestToken::TestToken()
    : TokenizeTestCase<TestToken>(*this, "TestToken")
  {
    add(&TestToken::testScan);
  }

  void TestToken::testScan(tst::TestResult& result)
  {
    auto a = tok::makeToken<SymbolToken<TOKEN_TYPE_A> >(T::T<'a'>());
    auto b = T::T<'b'>();
    auto e = a + b + a;

    Token expected[] = {TOKEN_A, TOKEN_A};
    TESTASSERTOP(e.scan(makeSymbolStream(string_abab), tokens_).last, eq, 3);
    TESTASSERT(tokens_ == makeTokenStream(expected));
  }
}
