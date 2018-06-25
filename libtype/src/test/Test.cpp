// Test.cpp

/***************************************************************************
 *   Copyright (C) 2012-2013 Daniel Mueller                                *
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

#include <iostream>

#include <test/TestSuite.hpp>
#include <test/DefaultResult.hpp>

#include "TestTypes.hpp"
#include "TestTraits.hpp"
#include "TestMove.hpp"
#include "TestDecltype.hpp"
#include "TestTuple.hpp"
#include "TestFunction.hpp"
#include "TestDefer.hpp"
#include "TestUtil.hpp"


int main()
{
  tst::DefaultResult<std::ostream> result(std::cout, true);
  tst::TestSuite                   suite;

  suite.add(tst::createTestCase<test::TestTypes>());
  suite.add(tst::createTestCase<test::TestTraits>());
  suite.add(tst::createTestCase<test::TestMove>());
  suite.add(tst::createTestCase<test::TestDecltype>());
  suite.add(tst::createTestCase<test::TestTuple>());
  suite.add(tst::createTestCase<test::TestFunction>());
  suite.add(tst::createTestCase<test::TestDefer>());
  suite.add(tst::createTestCase<test::TestUtil>());

  std::cout << "Running Tests...\n";

  suite.run(result);

  std::cout << "-----------------------------\n";
  std::cout << "Summary:\n";

  result.printSummary();
  return 0;
}
