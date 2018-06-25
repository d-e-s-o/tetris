// TestOrientation.cpp

/***************************************************************************
 *   Copyright (C) 2013-2014 Daniel Mueller (deso@posteo.net)              *
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

#include <tetris/game/ai/Orientation.hpp>
using ttrs::ai::Orientation;

#include "test/TestOrientation.hpp"


namespace test
{
  namespace
  {
    Orientation const o0   = Orientation::ROTATED_0;
    Orientation const o90  = Orientation::ROTATED_90;
    Orientation const o180 = Orientation::ROTATED_180;
    Orientation const o270 = Orientation::ROTATED_270;

    Orientation const o090 = combine(o0, o90);
    Orientation const o0180 = combine(o0, o180);
    Orientation const o0270 = combine(o0, o270);

    Orientation const o090180 = combine(o090, o180);
    Orientation const o090180270 = combine(o090180, o270);
  }


  TestOrientation::TestOrientation()
    : tst::TestCase<TestOrientation>(*this, "TestOrientation")
  {
    add(&TestOrientation::testRotateLeft1);
    add(&TestOrientation::testRotateRight1);
    add(&TestOrientation::testContains1);
    add(&TestOrientation::testFull1);
  }

  void TestOrientation::testRotateLeft1(tst::TestResult& result)
  {
    TESTASSERT(rotateLeft(o0)   == o270);
    TESTASSERT(rotateLeft(o90)  == o0);
    TESTASSERT(rotateLeft(o180) == o90);
    TESTASSERT(rotateLeft(o270) == o180);
  }

  void TestOrientation::testRotateRight1(tst::TestResult& result)
  {
    TESTASSERT(rotateRight(o0)   == o90);
    TESTASSERT(rotateRight(o90)  == o180);
    TESTASSERT(rotateRight(o180) == o270);
    TESTASSERT(rotateRight(o270) == o0);
  }

  void TestOrientation::testContains1(tst::TestResult& result)
  {
    TESTASSERT(contains(o90, o90));
    TESTASSERT(contains(o090, o0));
    TESTASSERT(contains(o090, o90));

    TESTASSERT(!contains(o090, o180));
    TESTASSERT(!contains(o090, o270));

    TESTASSERT(contains(o090180, o0));
    TESTASSERT(contains(o090180, o90));
    TESTASSERT(contains(o090180, o090));

    TESTASSERT(!contains(o090180, o270));

    TESTASSERT(contains(o090180270, o0));
    TESTASSERT(contains(o090180270, o90));
    TESTASSERT(contains(o090180270, o270));
    TESTASSERT(contains(o090180270, o090180));
    TESTASSERT(contains(o090180270, o090180270));
  }

  void TestOrientation::testFull1(tst::TestResult& result)
  {
    TESTASSERT(!full(o90));
    TESTASSERT(!full(o180));
    TESTASSERT(!full(o270));
    TESTASSERT(!full(o090));
    TESTASSERT(!full(o0180));
    TESTASSERT(!full(o0270));
    TESTASSERT(!full(o090180));
    TESTASSERT( full(o090180270));
  }
}
