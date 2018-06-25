// TestAbstractStone.hpp

/***************************************************************************
 *   Copyright (C) 2013 Daniel Mueller (deso@posteo.net)                   *
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

#ifndef TESTTESTABSTRACTSTONE_HPP
#define TESTTESTABSTRACTSTONE_HPP

#include <test/TestCase.hpp>

#include "test/StoneFactory1.hpp"


namespace test
{
  /**
   *
   */
  class TestAbstractStone: public tst::TestCase<TestAbstractStone>
  {
  public:
    TestAbstractStone();

    void testMove1(tst::TestResult& result);
    void testMove2(tst::TestResult& result);

    void testRotate1(tst::TestResult& result);
    void testRotate2(tst::TestResult& result);

    void testCollides1(tst::TestResult& result);

    void testMerge1(tst::TestResult& result);
    void testMerge2(tst::TestResult& result);

  protected:
    virtual void setUp();

  private:
    StoneTypeManager type_manager_;
    StoneFactory1    factory_;
  };
}


#endif
