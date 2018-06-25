// TestAbstractStone.cpp

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

#include "test/Field1.hpp"
#include "test/Stone1.hpp"
#include "test/TestAbstractStone.hpp"


namespace test
{
  TestAbstractStone::TestAbstractStone()
    : tst::TestCase<TestAbstractStone>(*this, "TestAbstractStone"),
      type_manager_(),
      factory_(type_manager_)
  {
    add(&TestAbstractStone::testMove1);
    add(&TestAbstractStone::testMove2);
    add(&TestAbstractStone::testRotate1);
    add(&TestAbstractStone::testRotate2);
    add(&TestAbstractStone::testCollides1);
    add(&TestAbstractStone::testMerge1);
    add(&TestAbstractStone::testMerge2);
  }

  void TestAbstractStone::setUp()
  {
    type_manager_ = StoneTypeManager();
    factory_      = StoneFactory1(type_manager_);
  }

  void TestAbstractStone::testMove1(tst::TestResult& result)
  {
    Stone1 stone1 = factory_.createStone(STONE_1_SINGLE);

    stone1.moveBy(1, 5);
    TESTASSERTOP(stone1.x(), eq, 1);
    TESTASSERTOP(stone1.y(), eq, 5);

    stone1.moveBy(3, 2);
    TESTASSERTOP(stone1.x(), eq, 4);
    TESTASSERTOP(stone1.y(), eq, 7);
  }

  void TestAbstractStone::testMove2(tst::TestResult& result)
  {
    Stone1 stone1 = factory_.createStone(STONE_1_SINGLE);

    stone1.moveDown();

    TESTASSERTOP(stone1.x()     , eq, 0);
    TESTASSERTOP(stone1.y()     , eq, -1);
    TESTASSERTOP(stone1.width() , eq, 1);
    TESTASSERTOP(stone1.height(), eq, 1);

    stone1.moveLeft();

    TESTASSERTOP(stone1.x()     , eq, -1);
    TESTASSERTOP(stone1.y()     , eq, -1);
    TESTASSERTOP(stone1.width() , eq, 1);
    TESTASSERTOP(stone1.height(), eq, 1);

    stone1.moveDown();
    stone1.moveRight();

    TESTASSERTOP(stone1.x()     , eq, 0);
    TESTASSERTOP(stone1.y()     , eq, -2);
    TESTASSERTOP(stone1.width() , eq, 1);
    TESTASSERTOP(stone1.height(), eq, 1);
  }

  void TestAbstractStone::testRotate1(tst::TestResult& result)
  {
    Stone1 stone1 = factory_.createStone(STONE_1_SINGLE);

    stone1.rotateLeft();

    TESTASSERTOP(stone1.x()     , eq, 0);
    TESTASSERTOP(stone1.y()     , eq, 0);
    TESTASSERTOP(stone1.width() , eq, 1);
    TESTASSERTOP(stone1.height(), eq, 1);

    stone1.rotateLeft();

    TESTASSERTOP(stone1.x()     , eq, 0);
    TESTASSERTOP(stone1.y()     , eq, 0);
    TESTASSERTOP(stone1.width() , eq, 1);
    TESTASSERTOP(stone1.height(), eq, 1);
  }

  void TestAbstractStone::testRotate2(tst::TestResult& result)
  {
    Stone1 stone1 = factory_.createStone(STONE_4_LINE);

    stone1.rotateLeft();
    TESTASSERTOP(stone1.x()     , eq, -2);
    TESTASSERTOP(stone1.y()     , eq, 1);
    TESTASSERTOP(stone1.width() , eq, 4);
    TESTASSERTOP(stone1.height(), eq, 1);

    stone1.rotateRight();
    TESTASSERTOP(stone1.x()     , eq, 0);
    TESTASSERTOP(stone1.y()     , eq, 0);
    TESTASSERTOP(stone1.width() , eq, 1);
    TESTASSERTOP(stone1.height(), eq, 4);
  }

  void TestAbstractStone::testCollides1(tst::TestResult& result)
  {
    Field1 field;
    Stone1 single = factory_.createStone(STONE_1_SINGLE);
    Stone1 line   = factory_.createStone(STONE_4_LINE);

    TESTASSERT(!single.collidesWith(field));
    TESTASSERT(!line.collidesWith(field));

    line.rotateRight();
    TESTASSERT(line.collidesWith(field));

    line.rotateLeft();
    TESTASSERT(!line.collidesWith(field));

    line.rotateLeft();
    TESTASSERT(line.collidesWith(field));
  }

  void TestAbstractStone::testMerge1(tst::TestResult& result)
  {
    Field1 field;
    Stone1 single = factory_.createStone(STONE_1_SINGLE);

    TESTASSERT( single.mergeWith(field));
    TESTASSERT(!single.mergeWith(field));

    TESTASSERT( field[0][0]);
    TESTASSERT(!field[0][1]);
    TESTASSERT(!field[1][0]);
    TESTASSERT(!field[1][1]);
  }

  void TestAbstractStone::testMerge2(tst::TestResult& result)
  {
    Field1 field;
    Stone1 line = factory_.createStone(STONE_4_LINE);

    TESTASSERT( line.mergeWith(field));
    TESTASSERT(!line.mergeWith(field));

    TESTASSERT( field[0][0]);
    TESTASSERT( field[0][1]);
    TESTASSERT( field[0][2]);
    TESTASSERT( field[0][3]);
    TESTASSERT(!field[0][4]);
    TESTASSERT(!field[1][0]);
    TESTASSERT(!field[1][1]);
    TESTASSERT(!field[1][2]);
    TESTASSERT(!field[1][3]);
    TESTASSERT(!field[1][4]);
  }
}
