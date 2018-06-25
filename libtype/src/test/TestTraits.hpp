// TestTraits.hpp

/***************************************************************************
 *   Copyright (C) 2012 Daniel Mueller                                     *
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

#ifndef TYPTESTTRAITS_HPP
#define TYPTESTTRAITS_HPP

#include <test/TestCase.hpp>


namespace test
{
  class TestTraits: public tst::TestCase<TestTraits>
  {
  public:
    TestTraits();

    void testEqual1(tst::TestResult& result);
    void testEqual2(tst::TestResult& result);

    void testRemoveConst1(tst::TestResult& result);
    void testRemovePointer1(tst::TestResult& result);
    void testRemoveReference1(tst::TestResult& result);

    void testIsBuiltIn1(tst::TestResult& result);
    void testIsBuiltIn2(tst::TestResult& result);

    void testMakeConst1(tst::TestResult& result);
  };
}


#endif
