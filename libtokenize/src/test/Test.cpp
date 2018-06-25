// Test.cpp

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

#include <iostream>

#include <test/TestSuite.hpp>
#include <test/DefaultResult.hpp>

#include "TestTerminal.hpp"
#include "TestTerminalRange.hpp"
#include "TestTerminalCustom.hpp"
#include "TestSequence.hpp"
#include "TestAlternative.hpp"
#include "TestRepetition.hpp"
#include "TestToken.hpp"
#include "TestTokenize.hpp"


int main()
{
  tst::DefaultResult<std::ostream> result(std::cout, true);
  tst::TestSuite                   suite;

  suite.add(tst::createTestCase<test::TestTerminal>());
  suite.add(tst::createTestCase<test::TestTerminalRange>());
  suite.add(tst::createTestCase<test::TestTerminalCustom>());
  suite.add(tst::createTestCase<test::TestSequence>());
  suite.add(tst::createTestCase<test::TestAlternative>());
  suite.add(tst::createTestCase<test::TestRepetition>());
  suite.add(tst::createTestCase<test::TestToken>());
  suite.add(tst::createTestCase<test::TestTokenize>());

  std::cout << "Running Tests...\n";

  suite.run(result);

  std::cout << "-----------------------------\n";
  std::cout << "Summary:\n";

  result.printSummary();
  return 0;
}
