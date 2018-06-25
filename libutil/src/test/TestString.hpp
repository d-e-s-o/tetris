// TestString.hpp

/***************************************************************************
 *   Copyright (C) 2014 Daniel Mueller (deso@posteo.net)                   *
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

#ifndef UTLTESTSTRING_HPP
#define UTLTESTSTRING_HPP

#include <test/TestCase.hpp>


namespace test
{
  /**
   *
   */
  class TestString: public tst::TestCase<TestString>
  {
  public:
    TestString();

    void testLength(tst::TestResult& result);

    void testCompareLess(tst::TestResult& result);
    void testCompareEqual(tst::TestResult& result);

    void testCopy(tst::TestResult& result);
  };
}


#endif
