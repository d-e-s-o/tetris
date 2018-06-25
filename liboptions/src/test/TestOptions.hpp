// TestOptions.hpp

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

#ifndef TESTTESTOPTIONS_HPP
#define TESTTESTOPTIONS_HPP

#include <options/Error.hpp>
#include <test/TestCase.hpp>


namespace test
{
  class TestOptions: public tst::TestCase<TestOptions>
  {
  public:
    TestOptions();

    void testEvaluate1(tst::TestResult& result);
    void testEvaluate2(tst::TestResult& result);
    void testEvaluate3(tst::TestResult& result);
    void testEvaluate4(tst::TestResult& result);
    void testEvaluate5(tst::TestResult& result);

    void testEvaluateFull1(tst::TestResult& result);

  private:
    opt::Error e_;

    void evaluateString(char const* string);
  };
}


#endif
