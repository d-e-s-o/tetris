// TestSet.cpp

/***************************************************************************
 *   Copyright (C) 2012,2014 Daniel Mueller (deso@posteo.net)              *
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

#include "TestSet.hpp"


namespace test
{
  TestSet::TestSet()
    : tst::TestCase<TestSet>(*this, "TestSet")
  {
    add(&TestSet::testInsert1);
  }

  void TestSet::setUp()
  {
    set_ = Set();
  }

  void TestSet::testInsert1(tst::TestResult& result)
  {
    TESTASSERTOP(set_.size(), eq, 0);

    set_.insert(1);

    TESTASSERTOP(set_.size(), eq, 1);
    TESTASSERT(set_.find(1) != set_.end());
    TESTASSERT(set_.find(2) == set_.end());
  }
}
