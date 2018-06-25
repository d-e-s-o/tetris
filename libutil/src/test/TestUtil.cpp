// TestUtil.cpp

/***************************************************************************
 *   Copyright (C) 2014 Daniel Mueller (deso@posteo.net)                   *
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

#include <util/Util.hpp>

#include "TestUtil.hpp"


namespace test
{
  TestUtil::TestUtil()
    : tst::TestCase<TestUtil>(*this, "TestUtil")
  {
    add(&TestUtil::testRoundDown1);
  }

  void TestUtil::testRoundDown1(tst::TestResult& result)
  {
    TESTASSERTOP(utl::roundDown(0x1fff, 0x1000), eq, 0x1000);
    TESTASSERTOP(utl::roundDown(1, 0x1000), eq, 0);
    TESTASSERTOP(utl::roundDown(5, 0x1000), eq, 0);
    TESTASSERTOP(utl::roundDown(0x1000 - 1, 0x1000), eq, 0);
    TESTASSERTOP(utl::roundDown(0x1000, 0x1000), eq, 0x1000);
  }
}
