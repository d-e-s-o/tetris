// Test.cpp

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

#include <iostream>

#include <test/TestSuite.hpp>
#include <test/DefaultResult.hpp>

#include "test/TestAbstractStoneFactory.hpp"
#include "test/TestAbstractField.hpp"
#include "test/TestAbstractStone.hpp"
#include "test/TestFieldFunctions.hpp"
#include "test/TestOrientation.hpp"
#include "test/TestState.hpp"
#include "test/TestStoneDropper.hpp"


int main()
{
  tst::DefaultResult<std::ostream> result(std::cout, true);
  tst::TestSuite                   suite;

  suite.add(tst::createTestCase<test::TestAbstractStoneFactory>());
  suite.add(tst::createTestCase<test::TestAbstractField>());
  suite.add(tst::createTestCase<test::TestAbstractStone>());
  suite.add(tst::createTestCase<test::TestFieldFunctions>());
  suite.add(tst::createTestCase<test::TestOrientation>());
  suite.add(tst::createTestCase<test::TestState>());
  suite.add(tst::createTestCase<test::TestStoneDropper>());

  std::cout << "Running Tests...\n";

  suite.run(result);

  std::cout << "-----------------------------\n";
  std::cout << "Summary:\n";

  result.printSummary();
  return 0;
}
