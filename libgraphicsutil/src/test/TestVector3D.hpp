// TestVector3D.hpp

/***************************************************************************
 *   Copyright (C) 2006-2012 Daniel Mueller (deso@posteo.net)              *
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

#ifndef TESTTESTVECTOR3D_HPP
#define TESTTESTVECTOR3D_HPP

#include <test/TestCase.hpp>


namespace test
{
  class TestVector3D: public tst::TestCase<TestVector3D>
  {
  public:
    TestVector3D();

    void testCreation(tst::TestResult& result);

    void testAssignAdd(tst::TestResult& result);
    void testAssignSub(tst::TestResult& result);
    void testAssignMul(tst::TestResult& result);
    void testAssignDiv(tst::TestResult& result);
    void testAssignMod(tst::TestResult& result);

    void testUnaryMinus(tst::TestResult& result);

    void testEqual(tst::TestResult& result);
    void testUnequal(tst::TestResult& result);
    void testAdd(tst::TestResult& result);
    void testSub(tst::TestResult& result);
    void testMul(tst::TestResult& result);
    void testDiv(tst::TestResult& result);
    void testMod(tst::TestResult& result);

    void testScalarMul(tst::TestResult& result);

    void testLength(tst::TestResult& result);
    void testNormalize(tst::TestResult& result);
  };
}


#endif
