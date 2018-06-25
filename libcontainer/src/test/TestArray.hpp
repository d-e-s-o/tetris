// TestArray.hpp

/***************************************************************************
 *   Copyright (C) 2009,2012 Daniel Mueller (deso@posteo.net)              *
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

#ifndef CTRTESTARRAY_HPP
#define CTRTESTARRAY_HPP

#include <test/TestCase.hpp>

#include <container/Array.hpp>
#include <container/ArrayFunctions.hpp>


namespace test
{
  class TestArray: public tst::TestCase<TestArray>
  {
  public:
    TestArray();

    void testCreation1(tst::TestResult& result);
    void testCreation2(tst::TestResult& result);

    void testMove1(tst::TestResult& result);
    void testMove2(tst::TestResult& result);

    void testGrow1(tst::TestResult& result);

    void testReplace1(tst::TestResult& result);
    void testReplace2(tst::TestResult& result);
    void testReplace3(tst::TestResult& result);
    void testReplace4(tst::TestResult& result);
    void testReplace5(tst::TestResult& result);
    void testReplace6(tst::TestResult& result);

    void testAppend1(tst::TestResult& result);
    void testAppend2(tst::TestResult& result);

    void testInsert1(tst::TestResult& result);
    void testInsert2(tst::TestResult& result);
    void testInsert3(tst::TestResult& result);

    void testRemove1(tst::TestResult& result);

  protected:
    virtual void setUp();

  private:
    typedef ctr::Array<int> Array;

    Array array_1_;
    Array array_2_;
  };
}


#endif
