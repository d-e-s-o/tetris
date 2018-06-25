// TestMap.cpp

/***************************************************************************
 *   Copyright (C) 2010-2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#include "TestMap.hpp"


namespace test
{
  TestMap::TestMap()
    : tst::TestCase<TestMap>(*this, "TestMap")
  {
    add(&TestMap::testInsert1);
  }

  void TestMap::setUp()
  {
    map_ = Map();
  }

  void TestMap::testInsert1(tst::TestResult& result)
  {
    TESTASSERTOP(map_.size(), eq, 0);

    map_.insert(Map::Entry(1, 20));

    TESTASSERTOP(map_.size(), eq, 1);
    TESTASSERT(*map_.find(1) == Map::Entry(1, 20));
    TESTASSERT( map_.find(2) == map_.end());
  }
}
