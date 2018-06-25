// TestAbstractStoneFactory.cpp

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

#include "test/StoneFactory1.hpp"
#include "test/TestAbstractStoneFactory.hpp"


namespace test
{
  TestAbstractStoneFactory::TestAbstractStoneFactory()
    : tst::TestCase<TestAbstractStoneFactory>(*this, "TestAbstractStoneFactory")
  {
    add(&TestAbstractStoneFactory::testCreate1);
    add(&TestAbstractStoneFactory::testCreateAll1);
  }

  void TestAbstractStoneFactory::testCreate1(tst::TestResult& result)
  {
    StoneFactory1 factory1(type_manager_);
    Stone1 single = factory1.createStone(STONE_1_SINGLE);

    // note that we kind of test the stone here as well but this is chicken-egg problem
    TESTASSERTOP(single.x()     , eq, 0);
    TESTASSERTOP(single.y()     , eq, 0);
    TESTASSERTOP(single.width() , eq, 1);
    TESTASSERTOP(single.height(), eq, 1);

    Stone1 line = factory1.createStone(STONE_4_LINE);

    TESTASSERTOP(line.x()     , eq, 0);
    TESTASSERTOP(line.y()     , eq, 0);
    TESTASSERTOP(line.width() , eq, 1);
    TESTASSERTOP(line.height(), eq, 4);
  }

  void TestAbstractStoneFactory::testCreateAll1(tst::TestResult& result)
  {
    TESTASSERTM(false, "implement me!");
  }
}
