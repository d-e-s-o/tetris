// TestFieldFunctions.hpp

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

#ifndef TESTTESTFIELDFUNCTIONS_HPP
#define TESTTESTFIELDFUNCTIONS_HPP

#include <test/TestCase.hpp>

#include "test/Field1.hpp"


namespace test
{
  /**
   *
   */
  class TestFieldFunctions: public tst::TestCase<TestFieldFunctions>
  {
  public:
    TestFieldFunctions();

    void testLinesComplete1(tst::TestResult& result);
    void testClearLines1(tst::TestResult& result);

  protected:
    virtual void setUp();

  private:
    Field1 field_;
  };
}


#endif
