// Test.cpp

/***************************************************************************
 *   Copyright (C) 2010-2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#include "TestArray.hpp"
#include "TestString.hpp"
#include "TestBinaryHeap.hpp"
#include "TestBinaryTree.hpp"
#include "TestSplayTree.hpp"
#include "TestSet.hpp"
#include "TestMap.hpp"
#include "TestStack.hpp"
#include "TestQueue.hpp"
#include "TestMoveIterator.hpp"


int main()
{
  tst::DefaultResult<std::ostream> result(std::cout, true);
  tst::TestSuite                   suite;

  suite.add(tst::createTestCase<test::TestArray>());
  suite.add(tst::createTestCase<test::TestString>());
  suite.add(tst::createTestCase<test::TestBinaryHeap>());
  suite.add(tst::createTestCase<test::TestBinaryTree>());
  suite.add(tst::createTestCase<test::TestSplayTree>());
  suite.add(tst::createTestCase<test::TestSet>());
  suite.add(tst::createTestCase<test::TestMap>());
  suite.add(tst::createTestCase<test::TestStack>());
  suite.add(tst::createTestCase<test::TestQueue>());
  suite.add(tst::createTestCase<test::TestMoveIterator>());

  std::cout << "Running Tests...\n";

  suite.run(result);

  std::cout << "-----------------------------\n";
  std::cout << "Summary:\n";

  result.printSummary();
  return 0;
}
