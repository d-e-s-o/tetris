// TestTokenize.cpp

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

#include <tokenize/Tokenize.hpp>

#include "TestTokenize.hpp"


namespace
{
  char const string_ab[]    = "a*b";
  char const string_aaab[]  = "a+a+a*b";
  char const string_aaaab[] = "a+a+a+a*b";
}


namespace test
{
  /**
   * @todo add tests covering value of Result::max
   */
  TestTokenize::TestTokenize()
    : TokenizeTestCase<TestTokenize>(*this, "TestTokenize")
  {
    add(&TestTokenize::testScan1);
  }

  void TestTokenize::testScan1(tst::TestResult& result)
  {
    auto inf  = tok::RepeatCount<0, -1>();
    auto a    = tok::makeToken<SymbolToken<TOKEN_TYPE_A> >(T::T<'a'>());
    auto b    = tok::makeToken<SymbolToken<TOKEN_TYPE_B> >(T::T<'b'>());
    auto plus = tok::makeToken<SymbolToken<TOKEN_TYPE_PLUS> >(T::T<'+'>());
    auto mult = tok::makeToken<SymbolToken<TOKEN_TYPE_STAR> >(T::T<'*'>());

    auto expr = a + ((plus + a) * inf) + mult + b;

    Token expected1[] = {TOKEN_A, TOKEN_STAR, TOKEN_B};
    Tokens tokens1;
    TESTASSERTOP(expr.scan(makeSymbolStream(string_ab), tokens1).last, eq, 3);
    TESTASSERT(tokens1 == makeTokenStream(expected1));

    Token expected2[] = {TOKEN_A, TOKEN_PLUS, TOKEN_A, TOKEN_PLUS, TOKEN_A, TOKEN_STAR, TOKEN_B};
    Tokens tokens2;
    TESTASSERTOP(expr.scan(makeSymbolStream(string_aaab), tokens2).last, eq, 7);
    TESTASSERT(tokens2 == makeTokenStream(expected2));

    Token expected3[] = {TOKEN_A, TOKEN_PLUS, TOKEN_A, TOKEN_PLUS, TOKEN_A, TOKEN_PLUS, TOKEN_A, TOKEN_STAR, TOKEN_B};
    Tokens tokens3;
    TESTASSERTOP(expr.scan(makeSymbolStream(string_aaaab), tokens3).last, eq, 9);
    TESTASSERT(tokens3 == makeTokenStream(expected3));
  }
}
