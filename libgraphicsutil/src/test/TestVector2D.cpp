// TestVector2D.cpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#include <util/Vector2D.hpp>
#include <util/Vector2DFunctions.hpp>

#include "TestVector2D.hpp"


namespace test
{
  namespace
  {
    typedef utl::Vector2D<int> Vector;
  }


  TestVector2D::TestVector2D()
    : tst::TestCase<TestVector2D>(*this, "TestVector2D")
  {
    add(&TestVector2D::testCreation);

    add(&TestVector2D::testAssignAdd);
    add(&TestVector2D::testAssignSub);
    add(&TestVector2D::testAssignMul);
    add(&TestVector2D::testAssignDiv);

    add(&TestVector2D::testUnaryMinus);

    add(&TestVector2D::testEqual);
    add(&TestVector2D::testUnequal);
    add(&TestVector2D::testAdd);
    add(&TestVector2D::testSub);
    add(&TestVector2D::testMul);
    add(&TestVector2D::testDiv);

    add(&TestVector2D::testScalarMul);

    add(&TestVector2D::testLength);
    add(&TestVector2D::testNormalize);
  }

  void TestVector2D::testCreation(tst::TestResult& result)
  {
    Vector v(1, 2);

    TESTASSERTOP(v.x, eq, 1);
    TESTASSERTOP(v.y, eq, 2);
  }

  void TestVector2D::testAssignAdd(tst::TestResult& result)
  {
    Vector v1(1, 2);
    Vector v2(4, 5);

    v2 += v1;

    TESTASSERTOP(v2.x, eq, 5);
    TESTASSERTOP(v2.y, eq, 7);
  }

  void TestVector2D::testAssignSub(tst::TestResult& result)
  {
    Vector v1(1, 2);
    Vector v2(4, 5);

    v2 -= v1;

    TESTASSERTOP(v2.x, eq, 3);
    TESTASSERTOP(v2.y, eq, 3);
  }

  void TestVector2D::testAssignMul(tst::TestResult& result)
  {
    Vector v(1, 2);
    v *= 5;

    TESTASSERTOP(v.x, eq, 5);
    TESTASSERTOP(v.y, eq, 10);
  }

  void TestVector2D::testAssignDiv(tst::TestResult& result)
  {
    Vector v(30, 60);
    v /= 15;

    TESTASSERTOP(v.x, eq, 2);
    TESTASSERTOP(v.y, eq, 4);
  }

  void TestVector2D::testUnaryMinus(tst::TestResult& result)
  {
    Vector v1(1, 2);
    Vector v2 = -v1;

    TESTASSERTOP(v2.x, eq, -1);
    TESTASSERTOP(v2.y, eq, -2);
  }

  void TestVector2D::testEqual(tst::TestResult& result)
  {
    Vector v1(1, 50);
    Vector v2(1, 50);

    TESTASSERT(v1 == v2);
  }

  void TestVector2D::testUnequal(tst::TestResult& result)
  {
    Vector v1(1, 50);
    Vector v2(12389, 50);

    TESTASSERT(v1 != v2);
  }

  void TestVector2D::testAdd(tst::TestResult& result)
  {
    Vector v1(7, 8);
    Vector v2(4, 5);

    Vector v3 = v2 + v1;

    TESTASSERTOP(v3.x, eq, 11);
    TESTASSERTOP(v3.y, eq, 13);
  }

  void TestVector2D::testSub(tst::TestResult& result)
  {
    Vector v1(4, 5);
    Vector v2(7, 8);

    Vector v3 = v1 - v2;

    TESTASSERTOP(v3.x, eq, -3);
    TESTASSERTOP(v3.y, eq, -3);
  }

  void TestVector2D::testMul(tst::TestResult& result)
  {
    Vector v1(4, 5);
    Vector v2 = v1 * 10;

    TESTASSERTOP(v2.x, eq, 40);
    TESTASSERTOP(v2.y, eq, 50);
  }

  void TestVector2D::testDiv(tst::TestResult& result)
  {
    Vector v1(1600, 1000);
    Vector v2 = v1 / 40;

    TESTASSERTOP(v2.x, eq, 40);
    TESTASSERTOP(v2.y, eq, 25);
  }

  void TestVector2D::testScalarMul(tst::TestResult& result)
  {
    Vector v1(1, 2);
    Vector v2(-7, 8);

    TESTASSERTOP(v1 * v2, eq, 9);
  }

  void TestVector2D::testLength(tst::TestResult& result)
  {
    Vector v1(5, 0);
    TESTASSERTOP(utl::length(v1), eq, 5);

    Vector v2(0, 6);
    TESTASSERTOP(utl::length(v2), eq, 6);
  }

  void TestVector2D::testNormalize(tst::TestResult& result)
  {
    Vector v(1000, 0);
    utl::normalize(v);
    TESTASSERTOP(utl::length(v), eq, 1);

    v = Vector(0, 990);
    utl::normalize(v);
    TESTASSERTOP(utl::length(v), eq, 1);
  }
}
