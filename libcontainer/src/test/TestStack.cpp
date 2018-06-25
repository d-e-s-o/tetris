// TestStack.cpp

/***************************************************************************
 *   Copyright (C) 2012,2014 Daniel Mueller (deso@posteo.net)              *
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

#include "TestStack.hpp"


namespace test
{
  TestStack::TestStack()
    : tst::TestCase<TestStack>(*this, "TestStack")
  {
    add(&TestStack::testPush1);
    add(&TestStack::testPop1);
  }

  void TestStack::setUp()
  {
    stack_ = Stack();
  }

  void TestStack::testPush1(tst::TestResult& result)
  {
    TESTASSERTOP(stack_.size(), eq, 0);

    stack_.push(1);
    TESTASSERTOP(stack_.size(), eq, 1);
    TESTASSERTOP(stack_.top(),  eq, 1);

    stack_.push(5);
    TESTASSERTOP(stack_.size(), eq, 2);
    TESTASSERTOP(stack_.top(),  eq, 5);
  }

  void TestStack::testPop1(tst::TestResult& result)
  {
    stack_.push(1);
    stack_.push(5);

    TESTASSERTOP(stack_.pop(),  eq, 5);
    TESTASSERTOP(stack_.size(), eq, 1);

    TESTASSERTOP(stack_.pop(),  eq, 1);
    TESTASSERTOP(stack_.size(), eq, 0);
  }
}
