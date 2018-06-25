// TestBinaryHeap.cpp

/***************************************************************************
 *   Copyright (C) 2013-2014 Daniel Mueller (deso@posteo.net)              *
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

#include "TestBinaryHeap.hpp"


namespace test
{
  TestBinaryHeap::TestBinaryHeap()
    : tst::TestCase<TestBinaryHeap>(*this, "TestBinaryHeap")
  {
    add(&TestBinaryHeap::testInsert1);
    add(&TestBinaryHeap::testRemove1);
  }

  void TestBinaryHeap::setUp()
  {
    heap_ = Heap();
  }

  void TestBinaryHeap::testInsert1(tst::TestResult& result)
  {
    TESTASSERTOP(heap_.size(), eq, 0);

    heap_.insert(10);
    TESTASSERTOP(heap_.size(), eq, 1);
    TESTASSERTOP(heap_.top(), eq, 10);

    heap_.insert(20);
    TESTASSERTOP(heap_.size(), eq, 2);
    TESTASSERTOP(heap_.top(), eq, 10);

    heap_.insert(9);
    TESTASSERTOP(heap_.size(), eq, 3);
    TESTASSERTOP(heap_.top(), eq, 9);

    heap_.insert(8);
    TESTASSERTOP(heap_.size(), eq, 4);
    TESTASSERTOP(heap_.top(), eq, 8);

    heap_.insert(11);
    TESTASSERTOP(heap_.size(), eq, 5);
    TESTASSERTOP(heap_.top(), eq, 8);

    heap_.insert(8);
    TESTASSERTOP(heap_.size(), eq, 6);
    TESTASSERTOP(heap_.top(), eq, 8);

    heap_.insert(0);
    TESTASSERTOP(heap_.size(), eq, 7);
    TESTASSERTOP(heap_.top(), eq, 0);
  }

  void TestBinaryHeap::testRemove1(tst::TestResult& result)
  {
    heap_.insert(10);
    heap_.insert(2);
    heap_.insert(18);
    heap_.insert(10);
    heap_.insert(11);
    heap_.insert(7);

    TESTASSERTOP(heap_.size(), eq, 6);

    TESTASSERTOP(heap_.top(), eq, 2);
    TESTASSERTOP(heap_.remove(), eq, 2);
    TESTASSERTOP(heap_.size(), eq, 5);

    TESTASSERTOP(heap_.top(), eq, 7);
    TESTASSERTOP(heap_.remove(), eq, 7);
    TESTASSERTOP(heap_.size(), eq, 4);

    TESTASSERTOP(heap_.top(), eq, 10);
    TESTASSERTOP(heap_.remove(), eq, 10);
    TESTASSERTOP(heap_.size(), eq, 3);

    TESTASSERTOP(heap_.top(), eq, 10);
    TESTASSERTOP(heap_.remove(), eq, 10);
    TESTASSERTOP(heap_.size(), eq, 2);

    TESTASSERTOP(heap_.top(), eq, 11);
    TESTASSERTOP(heap_.remove(), eq, 11);
    TESTASSERTOP(heap_.size(), eq, 1);

    TESTASSERTOP(heap_.top(), eq, 18);
    TESTASSERTOP(heap_.remove(), eq, 18);
    TESTASSERTOP(heap_.size(), eq, 0);
  }
}
