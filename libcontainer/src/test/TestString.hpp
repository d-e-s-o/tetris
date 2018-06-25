// TestString.hpp

/***************************************************************************
 *   Copyright (C) 2012 Daniel Mueller (deso@posteo.net)                   *
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

#ifndef CTRTESTSTRING_HPP
#define CTRTESTSTRING_HPP

#include <test/TestCase.hpp>

#include <container/String.hpp>
#include <container/StringFunctions.hpp>


namespace test
{
  class TestString: public tst::TestCase<TestString>
  {
  public:
    TestString();

    void testCreation1(tst::TestResult& result);
    void testToString1(tst::TestResult& result);
    void testToString2(tst::TestResult& result);
    void testToString3(tst::TestResult& result);
    void testAppend1(tst::TestResult& result);
    void testEqual1(tst::TestResult& result);
    void testNotEqual1(tst::TestResult& result);
    void testLess1(tst::TestResult& result);

    void testSubString1(tst::TestResult& result);
    void testSubString2(tst::TestResult& result);
    void testFindSubString1(tst::TestResult& result);
    void testFindSubString2(tst::TestResult& result);

  protected:
    virtual void setUp();

  private:
    typedef ctr::String String;

    String string_;
  };
}


#endif
