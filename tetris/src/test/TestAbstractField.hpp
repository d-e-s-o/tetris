// TestAbstractField.hpp

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

#ifndef TESTTESTABSTRACTFIELD_HPP
#define TESTTESTABSTRACTFIELD_HPP

#include <test/TestCase.hpp>

#include "test/Field1.hpp"


namespace test
{
  /**
   *
   */
  class TestAbstractField: public tst::TestCase<TestAbstractField>
  {
  public:
    TestAbstractField();

    void testWidth1(tst::TestResult& result);
    void testHeight1(tst::TestResult& result);

    void testAt1(tst::TestResult& result);
    void testAt2(tst::TestResult& result);

    void testLineComplete1(tst::TestResult& result);
    void testLineComplete2(tst::TestResult& result);

    void testClearLine1(tst::TestResult& result);

  protected:
    virtual void setUp();

  private:
    Field1 field_;
  };
}


#endif
