// TestString.cpp

/***************************************************************************
 *   Copyright (C) 2014 Daniel Mueller (deso@posteo.net)                   *
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

#include <util/String.hpp>

#include "TestString.hpp"


namespace test
{
  namespace
  {
    char const string1[] = {'a', 'b', '\0', 'a', 'b'};
    char const string2[] = {'a', 'b', 'c', '\0', 'a', 'b', 'c'};
  }


  TestString::TestString()
    : tst::TestCase<TestString>(*this, "TestString")
  {
    add(&TestString::testLength);
    add(&TestString::testCompareLess);
    add(&TestString::testCompareEqual);
    add(&TestString::testCopy);
  }

  void TestString::testLength(tst::TestResult& result)
  {
    TESTASSERTOP(utl::length("")  , eq, 0);
    TESTASSERTOP(utl::length("a") , eq, 1);
    TESTASSERTOP(utl::length("b") , eq, 1);
    TESTASSERTOP(utl::length("ab"), eq, 2);

    TESTASSERTOP(utl::length(string1), eq, 2);
    TESTASSERTOP(utl::length(string2), eq, 3);
  }

  void TestString::testCompareLess(tst::TestResult& result)
  {
    TESTASSERTOP(utl::compare("",   "a"), lt, 0);
    TESTASSERTOP(utl::compare("a",  "b"), lt, 0);
    TESTASSERTOP(utl::compare("a",  "z"), lt, 0);
    TESTASSERTOP(utl::compare("ab", "z"), lt, 0);

    TESTASSERTOP(utl::compare("aabb",  "aabbc"), lt, 0);
    TESTASSERTOP(utl::compare("aabbb", "aabbc"), lt, 0);

    TESTASSERTOP(utl::compare(string1, string2), lt, 0);
  }

  void TestString::testCompareEqual(tst::TestResult& result)
  {
    TESTASSERTOP(utl::compare("",  "") , eq, 0);
    TESTASSERTOP(utl::compare("a", "a"), eq, 0);

    TESTASSERTOP(utl::compare("azaz", "azaz"), eq, 0);

    TESTASSERTOP(utl::compare(string1, string1), eq, 0);
    TESTASSERTOP(utl::compare(string2, string2), eq, 0);
  }

  /**
   * @todo need more test cases!
   */
  void TestString::testCopy(tst::TestResult& result)
  {
    char buffer[12] = {};
    size_t size = sizeof(buffer);

    TESTASSERTOP(utl::copy("", buffer, size), eq, buffer + 1);
    TESTASSERTOP(utl::compare(buffer, ""), eq, 0);

    TESTASSERTOP(utl::copy("abc", buffer, size), eq, buffer + 4);
    TESTASSERTOP(utl::compare(buffer, "abc"), eq, 0);

    TESTASSERTOP(utl::copy("abcdefghijk", buffer, size), eq, buffer + size);
    TESTASSERTOP(utl::compare(buffer, "abcdefghijk"), eq, 0);

    TESTASSERTOP(utl::copy("abcdefghijkl", buffer, size), eq, buffer + size);
    TESTASSERTOP(utl::compare(buffer, "abcdefghijk"), eq, 0);

    TESTASSERTOP(utl::copy("abcdefghijklmnopqrst", buffer, size), eq, buffer + size);
    TESTASSERTOP(utl::compare(buffer, "abcdefghijk"), eq, 0);
  }
}
