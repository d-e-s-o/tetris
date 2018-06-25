// TestString.cpp

/***************************************************************************
 *   Copyright (C) 2012,2014 Daniel Mueller (deso@posteo.net)              *
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

#include <test/Util.hpp>

#include "TestString.hpp"


namespace test
{
  namespace
  {
    char const string1[] = "abcdefghij";
    char const string2[] = "1234";
  }


  TestString::TestString()
    : tst::TestCase<TestString>(*this, "TestString"),
      string_()
  {
    add(&TestString::testCreation1);
    add(&TestString::testToString1);
    add(&TestString::testToString2);
    add(&TestString::testToString3);
    add(&TestString::testAppend1);
    add(&TestString::testEqual1);
    add(&TestString::testNotEqual1);
    add(&TestString::testLess1);
    add(&TestString::testSubString1);
    add(&TestString::testSubString2);
    add(&TestString::testFindSubString1);
    add(&TestString::testFindSubString2);
  }

  void TestString::setUp()
  {
    string_ = String(string1);
  }

  void TestString::testCreation1(tst::TestResult& result)
  {
    TESTASSERTOP(string_.size(), eq, 10);
    TESTASSERTOP(string_[0], eq, 'a');
    TESTASSERTOP(string_[1], eq, 'b');
    TESTASSERTOP(string_[2], eq, 'c');
    TESTASSERTOP(string_[3], eq, 'd');
    TESTASSERTOP(string_[4], eq, 'e');
    TESTASSERTOP(string_[5], eq, 'f');
    TESTASSERTOP(string_[6], eq, 'g');
    TESTASSERTOP(string_[7], eq, 'h');
    TESTASSERTOP(string_[8], eq, 'i');
    TESTASSERTOP(string_[9], eq, 'j');
  }

  void TestString::testToString1(tst::TestResult& result)
  {
    char const* string = string_.toString();

    TESTASSERTOP(string[0],  eq, 'a');
    TESTASSERTOP(string[1],  eq, 'b');
    TESTASSERTOP(string[2],  eq, 'c');
    TESTASSERTOP(string[3],  eq, 'd');
    TESTASSERTOP(string[4],  eq, 'e');
    TESTASSERTOP(string[5],  eq, 'f');
    TESTASSERTOP(string[6],  eq, 'g');
    TESTASSERTOP(string[7],  eq, 'h');
    TESTASSERTOP(string[8],  eq, 'i');
    TESTASSERTOP(string[9],  eq, 'j');
    TESTASSERTOP(string[10], eq, '\0');
  }

  void TestString::testToString2(tst::TestResult& result)
  {
    string_ += String(string2);

    char const* string = string_.toString();

    TESTASSERTOP(string[0],  eq, 'a');
    TESTASSERTOP(string[1],  eq, 'b');
    TESTASSERTOP(string[2],  eq, 'c');
    TESTASSERTOP(string[3],  eq, 'd');
    TESTASSERTOP(string[4],  eq, 'e');
    TESTASSERTOP(string[5],  eq, 'f');
    TESTASSERTOP(string[6],  eq, 'g');
    TESTASSERTOP(string[7],  eq, 'h');
    TESTASSERTOP(string[8],  eq, 'i');
    TESTASSERTOP(string[9],  eq, 'j');
    TESTASSERTOP(string[10], eq, '1');
    TESTASSERTOP(string[11], eq, '2');
    TESTASSERTOP(string[12], eq, '3');
    TESTASSERTOP(string[13], eq, '4');
    TESTASSERTOP(string[14], eq, '\0');
  }

  void TestString::testToString3(tst::TestResult& result)
  {
    String string("");

    TESTASSERTOP(string.size(), eq, 0);
    TESTASSERTOP(string.toString(), ne, nullptr);
  }

  void TestString::testAppend1(tst::TestResult& result)
  {
    string_ += String(string2);

    TESTASSERTOP(string_.size(), eq, 14);
    TESTASSERTOP(string_[0],  eq, 'a');
    TESTASSERTOP(string_[1],  eq, 'b');
    TESTASSERTOP(string_[2],  eq, 'c');
    TESTASSERTOP(string_[3],  eq, 'd');
    TESTASSERTOP(string_[4],  eq, 'e');
    TESTASSERTOP(string_[5],  eq, 'f');
    TESTASSERTOP(string_[6],  eq, 'g');
    TESTASSERTOP(string_[7],  eq, 'h');
    TESTASSERTOP(string_[8],  eq, 'i');
    TESTASSERTOP(string_[9],  eq, 'j');
    TESTASSERTOP(string_[10], eq, '1');
    TESTASSERTOP(string_[11], eq, '2');
    TESTASSERTOP(string_[12], eq, '3');
    TESTASSERTOP(string_[13], eq, '4');
    // dereferencing at an index greater to or equal to size is not allowed, but we want to whitebox
    // test the zero termination so work around that check by manual pointer manipulation
    TESTASSERTOP(*(&string_[13] + 1), eq, '\0');
  }

  void TestString::testEqual1(tst::TestResult& result)
  {
    TESTASSERT(string_ == String("abcdefghij"));
    TESTASSERT(string_ == String(string1));
  }

  void TestString::testNotEqual1(tst::TestResult& result)
  {
    TESTASSERT(string_ != String(""));
    TESTASSERT(string_ != String(string2));
    TESTASSERT(string_ != String(string1) + String("1"));
  }

  void TestString::testLess1(tst::TestResult& result)
  {
    TESTASSERT(tst::logicalXor(string_ < String(""),      String("") < string_));
    TESTASSERT(tst::logicalXor(string_ < String("Z"),     String("Z") < string_));
    TESTASSERT(tst::logicalXor(string_ < String(string2), String(string2) < string_));

    TESTASSERT(!(string_    < string_));
    TESTASSERT(!(string_    < String(string1) || String(string1) < string_));
    TESTASSERT(!(String("") < String("")      || String("")      < String("")));

    TESTASSERT(tst::logicalXor(String("win") < String("ver"), String("ver") < String("win")));
  }

  void TestString::testSubString1(tst::TestResult& result)
  {
    TESTASSERT(subString(string_, 0, 0) == String(""));
    TESTASSERT(subString(string_, 0, 1) == String("a"));
    TESTASSERT(subString(string_, 1, 1) == String("b"));
    TESTASSERT(subString(string_, 2, 4) == String("cdef"));
  }

  void TestString::testSubString2(tst::TestResult& result)
  {
    TESTASSERT(subString(string_, 0)  == String("abcdefghij"));
    TESTASSERT(subString(string_, 1)  == String("bcdefghij"));
    TESTASSERT(subString(string_, 2)  == String("cdefghij"));
    TESTASSERT(subString(string_, 8)  == String("ij"));
    TESTASSERT(subString(string_, 9)  == String("j"));
    TESTASSERT(subString(string_, 10) == String(""));
  }

  void TestString::testFindSubString1(tst::TestResult& result)
  {
    TESTASSERTOP(findSubString(String(""), String("")), eq, 0);
    TESTASSERTOP(findSubString(string_,    String("")), eq, 0);

    TESTASSERTOP(findSubString(string_, String("a")), eq, 0);
    TESTASSERTOP(findSubString(string_, String("b")), eq, 1);
    TESTASSERTOP(findSubString(string_, String("i")), eq, 8);
    TESTASSERTOP(findSubString(string_, String("j")), eq, 9);

    TESTASSERTOP(findSubString(string_, String("ab")), eq, 0);
    TESTASSERTOP(findSubString(string_, String("bc")), eq, 1);

    TESTASSERTOP(findSubString(string_, String("abc")), eq, 0);
    TESTASSERTOP(findSubString(string_, String("defgh")), eq, 3);
    TESTASSERTOP(findSubString(string_, String("abcdefghij")), eq, 0);

    TESTASSERTOP(findSubString(string_, String("abce")), eq, 10);
    TESTASSERTOP(findSubString(string_, String("defgi")), eq, 10);
    TESTASSERTOP(findSubString(string_, String("ghijk")), eq, 10);
  }

  void TestString::testFindSubString2(tst::TestResult& result)
  {
    TESTASSERTOP(findSubString(string_, String(""), 1), eq, 1);

    TESTASSERTOP(findSubString(string_, String("a"), 1), eq, 10);
    TESTASSERTOP(findSubString(string_, String("b"), 1), eq, 1);
    TESTASSERTOP(findSubString(string_, String("i"), 6), eq, 8);
    TESTASSERTOP(findSubString(string_, String("j"), 8), eq, 9);
    TESTASSERTOP(findSubString(string_, String("j"), 9), eq, 9);

    TESTASSERTOP(findSubString(string_, String("ab"), 1), eq, 10);
    TESTASSERTOP(findSubString(string_, String("bc"), 1), eq, 1);
    TESTASSERTOP(findSubString(string_, String("bc"), 2), eq, 10);

    TESTASSERTOP(findSubString(string_, String("abce"),  9), eq, 10);
    TESTASSERTOP(findSubString(string_, String("defgi"), 5), eq, 10);
    TESTASSERTOP(findSubString(string_, String("ghijk"), 2), eq, 10);
  }
}
