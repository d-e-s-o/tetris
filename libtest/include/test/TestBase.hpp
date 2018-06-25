// TestBase.hpp

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

#ifndef TSTTESTBASE_HPP
#define TSTTESTBASE_HPP


namespace tst
{
  class TestResult;


  /**
   * This is the base class to be used for actual test cases and test
   * suites (which contain test cases and/or other test suites).
   */
  class TestBase
  {
  public:
    virtual ~TestBase();

    /** Run all tests. */
    virtual void run(TestResult& result) = 0;
  };
}

namespace tst
{
  /** Destroy the test. */
  inline TestBase::~TestBase()
  {
  }
}


#endif
