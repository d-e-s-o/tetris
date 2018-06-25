// TestFunction.hpp

/***************************************************************************
 *   Copyright (C) 2014 Daniel Mueller                                     *
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

#ifndef TYPTESTFUNCTION_HPP
#define TYPTESTFUNCTION_HPP

#include <test/TestCase.hpp>


namespace test
{
  class TestFunction: public tst::TestCase<TestFunction>
  {
  public:
    TestFunction();

    void testCall1(tst::TestResult& result);
    void testCall2(tst::TestResult& result);
    void testCall3(tst::TestResult& result);
    void testCall4(tst::TestResult& result);
  };
}


#endif
