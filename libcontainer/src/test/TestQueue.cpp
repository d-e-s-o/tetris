// TestQueue.cpp

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

#include "TestQueue.hpp"


namespace test
{
  TestQueue::TestQueue()
    : tst::TestCase<TestQueue>(*this, "TestQueue")
  {
    add(&TestQueue::testPushFront1);
    add(&TestQueue::testPushBack1);
    add(&TestQueue::testPopFront1);
    add(&TestQueue::testPopBack1);
  }

  void TestQueue::setUp()
  {
    queue_ = Queue();
  }

  void TestQueue::testPushFront1(tst::TestResult& result)
  {
    TESTASSERTOP(queue_.size(), eq, 0);

    queue_.pushFront(1);
    TESTASSERTOP(queue_.size(),  eq, 1);
    TESTASSERTOP(queue_.front(), eq, 1);

    queue_.pushFront(5);
    TESTASSERTOP(queue_.size(),  eq, 2);
    TESTASSERTOP(queue_.front(), eq, 5);

    TESTASSERTOP(* queue_.begin(),      eq, 5);
    TESTASSERTOP(*(queue_.begin() + 1), eq, 1);
  }

  void TestQueue::testPushBack1(tst::TestResult& result)
  {
    queue_.pushBack(2);
    TESTASSERTOP(queue_.size(), eq, 1);
    TESTASSERTOP(queue_.back(), eq, 2);

    queue_.pushBack(4);
    TESTASSERTOP(queue_.size(), eq, 2);
    TESTASSERTOP(queue_.back(), eq, 4);

    TESTASSERTOP(* queue_.begin(),      eq, 2);
    TESTASSERTOP(*(queue_.begin() + 1), eq, 4);
  }

  void TestQueue::testPopFront1(tst::TestResult& result)
  {
    queue_.pushFront(1);
    queue_.pushFront(5);

    TESTASSERTOP(queue_.popFront(), eq, 5);
    TESTASSERTOP(queue_.size(),     eq, 1);

    TESTASSERTOP(queue_.popFront(), eq, 1);
    TESTASSERTOP(queue_.size(),     eq, 0);
  }

  void TestQueue::testPopBack1(tst::TestResult& result)
  {
    queue_.pushBack(1);
    queue_.pushBack(5);

    TESTASSERTOP(queue_.popBack(), eq, 5);
    TESTASSERTOP(queue_.size(),    eq, 1);

    TESTASSERTOP(queue_.popBack(), eq, 1);
    TESTASSERTOP(queue_.size(),    eq, 0);
  }
}
