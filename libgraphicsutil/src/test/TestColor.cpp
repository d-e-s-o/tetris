// TestColor.cpp

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

#include <util/Color.hpp>

#include "TestColor.hpp"


namespace
{
  typedef utl::Color<signed char> Color;

  signed char const MIN = 0;
  signed char const MAX = 100;
}

namespace utl
{
  template<>
  struct ColorTrait<signed char>
  {
    static signed char const min;
    static signed char const max;
  };


  signed char const ColorTrait<signed char>::min = MIN;
  signed char const ColorTrait<signed char>::max = MAX;
}


namespace test
{
  TestColor::TestColor()
    : tst::TestCase<TestColor>(*this, "TestColor")
  {
    add(&TestColor::testCreation1);
    add(&TestColor::testCreation2);
    add(&TestColor::testSetter1);
    add(&TestColor::testSetter2);
    add(&TestColor::testAssignAdd1);
    add(&TestColor::testAssignAdd2);
    add(&TestColor::testAssignSub1);
    add(&TestColor::testAssignSub2);
  }

  void TestColor::testCreation1(tst::TestResult& result)
  {
    Color c(0, 55, 12, 100);

    TESTASSERTOP(c.getRed(), eq, 0);
    TESTASSERTOP(c.getGreen(), eq, 55);
    TESTASSERTOP(c.getBlue(), eq, 12);
    TESTASSERTOP(c.getAlpha(), eq, 100);
  }

  void TestColor::testCreation2(tst::TestResult& result)
  {
    Color c(127, -20, 80, 101);

    TESTASSERTOP(c.getRed(), eq, MAX);
    TESTASSERTOP(c.getGreen(), eq, MIN);
    TESTASSERTOP(c.getBlue(), eq, 80);
    TESTASSERTOP(c.getAlpha(), eq, MAX);
  }

  void TestColor::testSetter1(tst::TestResult& result)
  {
    Color c;
    c.setRed(0);
    c.setGreen(55);
    c.setBlue(12);
    c.setAlpha(100);

    TESTASSERTOP(c.getRed(), eq, 0);
    TESTASSERTOP(c.getGreen(), eq, 55);
    TESTASSERTOP(c.getBlue(), eq, 12);
    TESTASSERTOP(c.getAlpha(), eq, 100);
  }

  void TestColor::testSetter2(tst::TestResult& result)
  {
    Color c;
    c.setRed(127);
    c.setGreen(-20);
    c.setBlue(80);
    c.setAlpha(101);

    TESTASSERTOP(c.getRed(), eq, MAX);
    TESTASSERTOP(c.getGreen(), eq, MIN);
    TESTASSERTOP(c.getBlue(), eq, 80);
    TESTASSERTOP(c.getAlpha(), eq, MAX);
  }

  void TestColor::testAssignAdd1(tst::TestResult& result)
  {
    Color c1(1, 2, 3, 4);
    Color c2(5, 6, 7, 8);

    c2 += c1;

    TESTASSERTOP(c2.getRed(), eq, 6);
    TESTASSERTOP(c2.getGreen(), eq, 8);
    TESTASSERTOP(c2.getBlue(), eq, 10);
    TESTASSERTOP(c2.getAlpha(), eq, 12);
  }

  void TestColor::testAssignAdd2(tst::TestResult& result)
  {
    Color c1(95, 95, 95, 95);
    Color c2(5, 6, 7, 8);

    c2 += c1;

    TESTASSERTOP(c2.getRed(), eq, MAX);
    TESTASSERTOP(c2.getGreen(), eq, MAX);
    TESTASSERTOP(c2.getBlue(), eq, MAX);
    TESTASSERTOP(c2.getAlpha(), eq, MAX);
  }

  void TestColor::testAssignSub1(tst::TestResult& result)
  {
    Color c1(1, 2, 3, 4);
    Color c2(5, 6, 7, 8);

    c2 -= c1;

    TESTASSERTOP(c2.getRed(), eq, 4);
    TESTASSERTOP(c2.getGreen(), eq, 4);
    TESTASSERTOP(c2.getBlue(), eq, 4);
    TESTASSERTOP(c2.getAlpha(), eq, 4);
  }

  void TestColor::testAssignSub2(tst::TestResult& result)
  {
    Color c1(8, 8, 8, 8);
    Color c2(5, 6, 7, 8);

    c2 -= c1;

    TESTASSERTOP(c2.getRed(), eq, MIN);
    TESTASSERTOP(c2.getGreen(), eq, MIN);
    TESTASSERTOP(c2.getBlue(), eq, MIN);
    TESTASSERTOP(c2.getAlpha(), eq, MIN);
  }
}
