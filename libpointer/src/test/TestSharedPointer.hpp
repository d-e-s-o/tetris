// TestSharedPointer.hpp

/***************************************************************************
 *   Copyright (C) 2012 Daniel Mueller (deso@posteo.net)                   *
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

#ifndef TESTTESTSHAREDPOINTER_HPP
#define TESTTESTSHAREDPOINTER_HPP

#include "InstanceCounterTestCase.hpp"


namespace test
{
  class TestSharedPointer: public InstanceCounterTestCase<TestSharedPointer>
  {
  public:
    TestSharedPointer();

    void testRelease1(tst::TestResult& result);
    void testRelease2(tst::TestResult& result);

    void testMove1(tst::TestResult& result);
    void testMove2(tst::TestResult& result);

    void testEqual1(tst::TestResult& result);
    void testNotEqual1(tst::TestResult& result);
    void testLess1(tst::TestResult& result);
    void testLess2(tst::TestResult& result);
  };
}


#endif
