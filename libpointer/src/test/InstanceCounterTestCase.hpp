// InstanceCounterTestCase.hpp

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

#ifndef TESTTESTINSTANCECOUNTERTESTCASE_HPP
#define TESTTESTINSTANCECOUNTERTESTCASE_HPP

#include <test/TestCase.hpp>

#include "InstanceCounter.hpp"


namespace test
{
  template<typename T>
  class InstanceCounterTestCase: public tst::TestCase<T>
  {
  public:
    InstanceCounterTestCase(T& instance, char const* name);

    void testSetUp(tst::TestResult& result);

  protected:
    virtual void setUp();
  };
}


namespace test
{
  template<typename T>
  InstanceCounterTestCase<T>::InstanceCounterTestCase(T& instance, char const* name)
    : tst::TestCase<T>(instance, name)
  {
    this->add(&InstanceCounterTestCase<T>::testSetUp);
  }

  template<typename T>
  void InstanceCounterTestCase<T>::testSetUp(tst::TestResult& result)
  {
    TESTASSERTOP(InstanceCounter::count, eq, 0);
  }

  template<typename T>
  void InstanceCounterTestCase<T>::setUp()
  {
    InstanceCounter::count = 0;
  }
}


#endif
