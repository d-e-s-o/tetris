// Test.cpp

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

#include <iostream>

#include <test/TestSuite.hpp>
#include <test/DefaultResult.hpp>

#include "TestPoint.hpp"
#include "TestRectangle1.hpp"
#include "TestRectangle1Functions.hpp"
#include "TestRectangle2.hpp"
#include "TestRectangle2Functions.hpp"
#include "TestColor.hpp"
#include "TestVector2D.hpp"
#include "TestVector3D.hpp"


int main()
{
  tst::DefaultResult<std::ostream> result(std::cout, true);
  tst::TestSuite                   suite;

  suite.add(tst::createTestCase<test::TestPoint>());
  suite.add(tst::createTestCase<test::TestRectangle1>());
  suite.add(tst::createTestCase<test::TestRectangle1Functions>());
  suite.add(tst::createTestCase<test::TestRectangle2>());
  suite.add(tst::createTestCase<test::TestRectangle2Functions>());
  suite.add(tst::createTestCase<test::TestColor>());
  suite.add(tst::createTestCase<test::TestVector2D>());
  suite.add(tst::createTestCase<test::TestVector3D>());

  std::cout << "Running Tests...\n";

  suite.run(result);

  std::cout << "-----------------------------\n";
  std::cout << "Summary:\n";

  result.printSummary();
  return 0;
}
