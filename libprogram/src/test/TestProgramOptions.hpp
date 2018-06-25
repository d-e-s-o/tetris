// TestProgramOptions.hpp

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

#ifndef TESTTESTPROGRAMOPTIONS_HPP
#define TESTTESTPROGRAMOPTIONS_HPP

#include <test/TestCase.hpp>


namespace test
{
  /**
   * @todo add tests for checking other "non-option" arguments (should be at back)
   * @todo add other tests :o
   * @todo it would also be nice to have less code duplicating way of doing all those unit tests,
   *       (the argc and argv thing and options) - but I cannot really think of any
   */
  class TestProgramOptions: public tst::TestCase<TestProgramOptions>
  {
  public:
    TestProgramOptions();

    void testCreation1(tst::TestResult& result);
    void testCreation2(tst::TestResult& result);
    void testNoArgument1(tst::TestResult& result);
    void testRequiredArgument1(tst::TestResult& result);
    void testOptionalArgument1(tst::TestResult& result);
    void testOptionalArgument2(tst::TestResult& result);
  };
}


#endif
