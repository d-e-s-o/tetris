// TestVector3D.cpp

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

#include <util/Vector3D.hpp>
#include <util/Vector3DFunctions.hpp>

#include "TestVector3D.hpp"


namespace test
{
  namespace
  {
    typedef utl::Vector3D<int> Vector;
  }


  TestVector3D::TestVector3D()
    : tst::TestCase<TestVector3D>(*this, "TestVector3D")
  {
    add(&TestVector3D::testCreation);

    add(&TestVector3D::testAssignAdd);
    add(&TestVector3D::testAssignSub);
    add(&TestVector3D::testAssignMul);
    add(&TestVector3D::testAssignDiv);
    add(&TestVector3D::testAssignMod);

    add(&TestVector3D::testUnaryMinus);

    add(&TestVector3D::testEqual);
    add(&TestVector3D::testUnequal);
    add(&TestVector3D::testAdd);
    add(&TestVector3D::testSub);
    add(&TestVector3D::testMul);
    add(&TestVector3D::testDiv);
    add(&TestVector3D::testMod);

    add(&TestVector3D::testScalarMul);

    add(&TestVector3D::testLength);
    add(&TestVector3D::testNormalize);
  }

  void TestVector3D::testCreation(tst::TestResult& result)
  {
    Vector v(1, 2, 3);

    TESTASSERTOP(v.x, eq, 1);
    TESTASSERTOP(v.y, eq, 2);
    TESTASSERTOP(v.z, eq, 3);
  }

  void TestVector3D::testAssignAdd(tst::TestResult& result)
  {
    Vector v1(1, 2, 3);
    Vector v2(4, 5, 6);

    v2 += v1;

    TESTASSERTOP(v2.x, eq, 5);
    TESTASSERTOP(v2.y, eq, 7);
    TESTASSERTOP(v2.z, eq, 9);
  }

  void TestVector3D::testAssignSub(tst::TestResult& result)
  {
    Vector v1(1, 2, 3);
    Vector v2(4, 5, 6);

    v2 -= v1;

    TESTASSERTOP(v2.x, eq, 3);
    TESTASSERTOP(v2.y, eq, 3);
    TESTASSERTOP(v2.z, eq, 3);
  }

  void TestVector3D::testAssignMul(tst::TestResult& result)
  {
    Vector v(1, 2, 3);
    v *= 5;

    TESTASSERTOP(v.x, eq, 5);
    TESTASSERTOP(v.y, eq, 10);
    TESTASSERTOP(v.z, eq, 15);
  }

  void TestVector3D::testAssignDiv(tst::TestResult& result)
  {
    Vector v(30, 60, 90);
    v /= 15;

    TESTASSERTOP(v.x, eq, 2);
    TESTASSERTOP(v.y, eq, 4);
    TESTASSERTOP(v.z, eq, 6);
  }

  void TestVector3D::testAssignMod(tst::TestResult& result)
  {
    Vector v1(-7, 8, 9);
    Vector v2(1, 2, 3);

    v2 %= v1;

    TESTASSERTOP(v2.x, eq, -6);
    TESTASSERTOP(v2.y, eq, -30);
    TESTASSERTOP(v2.z, eq, 22);
  }

  void TestVector3D::testUnaryMinus(tst::TestResult& result)
  {
    Vector v1(1, 2, 3);
    Vector v2 = -v1;

    TESTASSERTOP(v2.x, eq, -1);
    TESTASSERTOP(v2.y, eq, -2);
    TESTASSERTOP(v2.z, eq, -3);
  }

  void TestVector3D::testEqual(tst::TestResult& result)
  {
    Vector v1(1, 50, 6000);
    Vector v2(1, 50, 6000);

    TESTASSERT(v1 == v2);
  }

  void TestVector3D::testUnequal(tst::TestResult& result)
  {
    Vector v1(1, 50, 6000);
    Vector v2(12389, 50, 6000);

    TESTASSERT(v1 != v2);
  }

  void TestVector3D::testAdd(tst::TestResult& result)
  {
    Vector v1(7, 8, 9);
    Vector v2(4, 5, 6);

    Vector v3 = v2 + v1;

    TESTASSERTOP(v3.x, eq, 11);
    TESTASSERTOP(v3.y, eq, 13);
    TESTASSERTOP(v3.z, eq, 15);
  }

  void TestVector3D::testSub(tst::TestResult& result)
  {
    Vector v1(4, 5, 6);
    Vector v2(7, 8, 9);

    Vector v3 = v1 - v2;

    TESTASSERTOP(v3.x, eq, -3);
    TESTASSERTOP(v3.y, eq, -3);
    TESTASSERTOP(v3.z, eq, -3);
  }

  void TestVector3D::testMul(tst::TestResult& result)
  {
    Vector v1(4, 5, 6);
    Vector v2 = v1 * 10;

    TESTASSERTOP(v2.x, eq, 40);
    TESTASSERTOP(v2.y, eq, 50);
    TESTASSERTOP(v2.z, eq, 60);
  }

  void TestVector3D::testDiv(tst::TestResult& result)
  {
    Vector v1(1600, 1000, 40);
    Vector v2 = v1 / 40;

    TESTASSERTOP(v2.x, eq, 40);
    TESTASSERTOP(v2.y, eq, 25);
    TESTASSERTOP(v2.z, eq, 1);
  }

  void TestVector3D::testMod(tst::TestResult& result)
  {
    Vector v1(-7, 8, 9);
    Vector v2(1, 2, 3);

    Vector v3 = v2 % v1;

    TESTASSERTOP(v3.x, eq, -6);
    TESTASSERTOP(v3.y, eq, -30);
    TESTASSERTOP(v3.z, eq, 22);
  }

  void TestVector3D::testScalarMul(tst::TestResult& result)
  {
    Vector v1(1, 2, 3);
    Vector v2(-7, 8, 9);

    TESTASSERTOP(v1 * v2, eq, 36);
  }

  void TestVector3D::testLength(tst::TestResult& result)
  {
    Vector v(4, 0, 3);
    TESTASSERTOP(utl::length(v), eq, 5);
  }

  void TestVector3D::testNormalize(tst::TestResult& result)
  {
    Vector v(1000, 0, 0);
    utl::normalize(v);
    TESTASSERTOP(utl::length(v), eq, 1);

    v = Vector(0, 990, 0);
    utl::normalize(v);
    TESTASSERTOP(utl::length(v), eq, 1);

    v = Vector(0, 0, 1337);
    utl::normalize(v);
    TESTASSERTOP(utl::length(v), eq, 1);
  }
}
