// Test.cpp

/***************************************************************************
 *   Copyright (C) 2006-2012 Daniel Mueller (deso@posteo.net)              *
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

#include "TestMemoryStream.hpp"
#include "TestMemoryNamespace.hpp"
#include "TestNamespaceManager.hpp"
#include "TestRenderer.hpp"
#include "TestWidget.hpp"
#include "TestShow.hpp"
#include "TestFocusIndex.hpp"
#include "TestFocusNext.hpp"
#include "TestAnchors.hpp"
#include "TestDecorator.hpp"
#include "TestButton.hpp"
#include "TestCheckBox.hpp"
#include "TestEditableText.hpp"


int main(int argc, char* argv[])
{
  tst::DefaultResult<std::ostream> result(std::cout, true);
  tst::TestSuite                   suite;

  suite.add(tst::createTestCase<test::TestMemoryStream>());
  suite.add(tst::createTestCase<test::TestMemoryNamespace>());
  suite.add(tst::createTestCase<test::TestNamespaceManager>());
  suite.add(tst::createTestCase<test::TestRenderer>());
  suite.add(tst::createTestCase<test::TestWidget>());
  suite.add(tst::createTestCase<test::TestShow>());
  suite.add(tst::createTestCase<test::TestFocusIndex>());
  suite.add(tst::createTestCase<test::TestFocusNext>());
  suite.add(tst::createTestCase<test::TestAnchors>());
  suite.add(tst::createTestCase<test::TestDecorator>());
  suite.add(tst::createTestCase<test::TestButton>());
  suite.add(tst::createTestCase<test::TestCheckBox>());
  suite.add(tst::createTestCase<test::TestEditableText>());

  std::cout << "Running Tests...\n";

  suite.run(result);

  std::cout << "-----------------------------\n";
  std::cout << "Summary:\n";

  result.printSummary();
  return 0;
}
