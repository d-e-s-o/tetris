// TestSuite.hpp

/***************************************************************************
 *   Copyright (C) 2009-2010,2012 Daniel Mueller (deso@posteo.net)         *
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

#ifndef TSTTESTSUITE_HPP
#define TSTTESTSUITE_HPP

#include "TestBase.hpp"
#include "TestContainer.hpp"


namespace tst
{
  /**
   * This class is the base class for suites that may contain other
   * tests.
   */
  class TestSuite: public TestBase
  {
  public:
    TestSuite();

    TestSuite(TestSuite&&) = delete;
    TestSuite(TestSuite const&) = delete;

    TestSuite& operator =(TestSuite&&) = delete;
    TestSuite& operator =(TestSuite const&) = delete;

    virtual void run(TestResult& result);
    virtual bool add(TestBase& test);

  private:
    typedef TestContainer<TestBase*, 256> Tests;

    Tests tests_;
  };
}

namespace tst
{
  /**
   * The default constructor creates an empty TestSuite.
   */
  inline TestSuite::TestSuite()
    : tests_()
  {
  }

  /**
   * @copydoc TestBase::run
   */
  inline void TestSuite::run(TestResult& result)
  {
    for (auto it = tests_.begin(); it != tests_.end(); ++it)
      (*it)->run(result);
  }

  /**
   * This method can be used to add a new test (typically a TestSuite or
   * a TestCase) to the list of tests to execute.
   */
  inline bool TestSuite::add(TestBase& test)
  {
    if (&test != this)
      return tests_.add(&test);

    return false;
  }
}


#endif
