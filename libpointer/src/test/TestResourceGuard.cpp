// TestResourceGuard.cpp

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

#include <pointer/ResourceGuard.hpp>
#include <pointer/Deleter.hpp>

#include "TestResourceGuard.hpp"


namespace test
{
  namespace
  {
    typedef ptr::ResourceGuard<InstanceCounter*, ptr::Deleter> Guard;
  }


  TestResourceGuard::TestResourceGuard()
    : InstanceCounterTestCase<TestResourceGuard>(*this, "TestResourceGuard")
  {
    add(&TestResourceGuard::testRelease1);
    add(&TestResourceGuard::testRelease2);
  }

  void TestResourceGuard::testRelease1(tst::TestResult& result)
  {
    {
      InstanceCounter* counter = new InstanceCounter();
      Guard guard(counter);

      TESTASSERTOP(InstanceCounter::count, eq, 1);
    }
    TESTASSERTOP(InstanceCounter::count, eq, 0);
  }

  void TestResourceGuard::testRelease2(tst::TestResult& result)
  {
    InstanceCounter* counter = 0;

    {
      counter = new InstanceCounter();
      Guard guard(counter);

      guard.release();
      TESTASSERTOP(InstanceCounter::count, eq, 1);
    }
    TESTASSERTOP(InstanceCounter::count, eq, 1);

    delete counter;
    TESTASSERTOP(InstanceCounter::count, eq, 0);
  }
}
