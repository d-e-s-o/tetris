// TestSplayTree.cpp

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

#include "TestSplayTree.hpp"


namespace test
{
  TestSplayTree::TestSplayTree()
    : tst::TestCase<TestSplayTree>(*this, "TestSplayTree")
  {
    add(&TestSplayTree::testInsert1);
    add(&TestSplayTree::testInsert2);
    add(&TestSplayTree::testInsert3);
    add(&TestSplayTree::testFind1);
    add(&TestSplayTree::testFindLowerBound1);
    add(&TestSplayTree::testFindLowerEqual1);
    add(&TestSplayTree::testRemove1);
    add(&TestSplayTree::testRemove2);
    add(&TestSplayTree::testClear1);
    add(&TestSplayTree::testIterate1);
    add(&TestSplayTree::testIterate2);
  }

  void TestSplayTree::setUp()
  {
    tree_ = Tree();
  }

  void TestSplayTree::testInsert1(tst::TestResult& result)
  {
    TESTASSERTOP(tree_.size(), eq, 0);

    TESTASSERT(tree_.insert(1));
    TESTASSERTOP(tree_.size(), eq, 1);

    TESTASSERT(tree_.insert(2));
    TESTASSERTOP(tree_.size(), eq, 2);
  }

  void TestSplayTree::testInsert2(tst::TestResult& result)
  {
    TESTASSERT(tree_.insert(1));
    TESTASSERT(tree_.insert(2));
    TESTASSERT(tree_.insert(3));
    TESTASSERT(tree_.insert(4));
    TESTASSERT(tree_.insert(5));
    TESTASSERT(tree_.insert(6));
    TESTASSERTOP(tree_.size(), eq, 6);

    TESTASSERT(!tree_.insert(1));
    TESTASSERTOP(tree_.size(), eq, 6);

    TESTASSERT(!tree_.insert(2));
    TESTASSERTOP(tree_.size(), eq, 6);

    TESTASSERTOP(*tree_.find(1), eq, 1);
    TESTASSERTOP(*tree_.find(2), eq, 2);
    TESTASSERTOP(*tree_.find(3), eq, 3);
    TESTASSERTOP(*tree_.find(4), eq, 4);
    TESTASSERTOP(*tree_.find(5), eq, 5);
    TESTASSERTOP(*tree_.find(6), eq, 6);
  }

  void TestSplayTree::testInsert3(tst::TestResult& result)
  {
    TESTASSERT(tree_.insert(6));
    TESTASSERT(tree_.insert(5));
    TESTASSERT(tree_.insert(4));
    TESTASSERT(tree_.insert(3));
    TESTASSERT(tree_.insert(2));
    TESTASSERT(tree_.insert(1));

    TESTASSERTOP(tree_.size(), eq, 6);

    TESTASSERTOP(*tree_.find(6), eq, 6);
    TESTASSERTOP(*tree_.find(5), eq, 5);
    TESTASSERTOP(*tree_.find(4), eq, 4);
    TESTASSERTOP(*tree_.find(3), eq, 3);
    TESTASSERTOP(*tree_.find(2), eq, 2);
    TESTASSERTOP(*tree_.find(1), eq, 1);
  }

  void TestSplayTree::testFind1(tst::TestResult& result)
  {
    tree_.insert(1);
    TESTASSERTOP(*tree_.find(1), eq, 1);

    tree_.insert(2);
    TESTASSERTOP(*tree_.find(1), eq, 1);
    TESTASSERTOP(*tree_.find(2), eq, 2);

    tree_.insert(3);
    TESTASSERTOP(*tree_.find(1), eq, 1);
    TESTASSERTOP(*tree_.find(2), eq, 2);
    TESTASSERTOP(*tree_.find(3), eq, 3);

    tree_.insert(4);
    TESTASSERTOP(*tree_.find(1), eq, 1);
    TESTASSERTOP(*tree_.find(2), eq, 2);
    TESTASSERTOP(*tree_.find(3), eq, 3);
    TESTASSERTOP(*tree_.find(4), eq, 4);

    tree_.insert(5);
    TESTASSERTOP(*tree_.find(1), eq, 1);
    TESTASSERTOP(*tree_.find(2), eq, 2);
    TESTASSERTOP(*tree_.find(3), eq, 3);
    TESTASSERTOP(*tree_.find(4), eq, 4);
    TESTASSERTOP(*tree_.find(5), eq, 5);
  }

  void TestSplayTree::testFindLowerBound1(tst::TestResult& result)
  {
    tree_.insert(2);
    TESTASSERT( tree_.findLowerBound(1) == tree_.end());
    TESTASSERTOP(*tree_.findLowerBound(2), eq, 2);
    TESTASSERTOP(*tree_.findLowerBound(3), eq, 2);

    tree_.insert(4);
    TESTASSERT( tree_.findLowerBound(1) == tree_.end());
    TESTASSERTOP(*tree_.findLowerBound(2), eq, 2);
    TESTASSERTOP(*tree_.findLowerBound(3), eq, 2);
    TESTASSERTOP(*tree_.findLowerBound(4), eq, 4);

    tree_.insert(7);
    TESTASSERT( tree_.findLowerBound(1) == tree_.end());
    TESTASSERTOP(*tree_.findLowerBound(2), eq, 2);
    TESTASSERTOP(*tree_.findLowerBound(3), eq, 2);
    TESTASSERTOP(*tree_.findLowerBound(4), eq, 4);
    TESTASSERTOP(*tree_.findLowerBound(5), eq, 4);
    TESTASSERTOP(*tree_.findLowerBound(6), eq, 4);
    TESTASSERTOP(*tree_.findLowerBound(7), eq, 7);
    TESTASSERTOP(*tree_.findLowerBound(8), eq, 7);

    tree_.insert(9);
    TESTASSERT( tree_.findLowerBound(1) == tree_.end());
    TESTASSERTOP(*tree_.findLowerBound(2), eq, 2);
    TESTASSERTOP(*tree_.findLowerBound(3), eq, 2);
    TESTASSERTOP(*tree_.findLowerBound(4), eq, 4);
    TESTASSERTOP(*tree_.findLowerBound(5), eq, 4);
    TESTASSERTOP(*tree_.findLowerBound(6), eq, 4);
    TESTASSERTOP(*tree_.findLowerBound(7), eq, 7);
    TESTASSERTOP(*tree_.findLowerBound(8), eq, 7);
    TESTASSERTOP(*tree_.findLowerBound(9), eq, 9);
    TESTASSERTOP(*tree_.findLowerBound(10), eq, 9);
  }

  void TestSplayTree::testFindLowerEqual1(tst::TestResult& result)
  {
    tree_.insert(2);
    TESTASSERT( tree_.findLowerEqual(1) == tree_.end());
    TESTASSERTOP(*tree_.findLowerEqual(2), eq, 2);
    TESTASSERTOP(*tree_.findLowerEqual(3), eq, 2);

    tree_.insert(4);
    TESTASSERT( tree_.findLowerEqual(1) ==  tree_.end());
    TESTASSERTOP(*tree_.findLowerEqual(2), eq, 2);
    TESTASSERTOP(*tree_.findLowerEqual(3), eq, 2);
    TESTASSERTOP(*tree_.findLowerEqual(4), le, 4);

    tree_.insert(7);
    TESTASSERT( tree_.findLowerEqual(1) == tree_.end());
    TESTASSERTOP(*tree_.findLowerEqual(2), eq, 2);
    TESTASSERTOP(*tree_.findLowerEqual(3), eq, 2);
    TESTASSERTOP(*tree_.findLowerEqual(4), le, 4);
    TESTASSERTOP(*tree_.findLowerEqual(5), le, 4);
    TESTASSERTOP(*tree_.findLowerEqual(6), le, 4);
    TESTASSERTOP(*tree_.findLowerEqual(7), le, 7);
    TESTASSERTOP(*tree_.findLowerEqual(8), le, 7);

    tree_.insert(9);
    TESTASSERT( tree_.findLowerEqual(1) == tree_.end());
    TESTASSERTOP(*tree_.findLowerEqual(2), eq, 2);
    TESTASSERTOP(*tree_.findLowerEqual(3), eq, 2);
    TESTASSERTOP(*tree_.findLowerEqual(4), le, 4);
    TESTASSERTOP(*tree_.findLowerEqual(5), le, 4);
    TESTASSERTOP(*tree_.findLowerEqual(6), le, 4);
    TESTASSERTOP(*tree_.findLowerEqual(7), le, 7);
    TESTASSERTOP(*tree_.findLowerEqual(8), le, 7);
    TESTASSERTOP(*tree_.findLowerEqual(9), le, 9);
    TESTASSERTOP(*tree_.findLowerEqual(10), le, 9);
  }

  void TestSplayTree::testRemove1(tst::TestResult& result)
  {
    tree_.insert(1);
    tree_.insert(2);
    tree_.insert(3);
    TESTASSERTOP(tree_.size(), eq, 3);

    TESTASSERT(tree_.remove(1));
    TESTASSERTOP(tree_.size(), eq, 2);
    TESTASSERT(tree_.find(1) == tree_.end());

    TESTASSERT(tree_.remove(2));
    TESTASSERTOP(tree_.size(), eq, 1);
    TESTASSERT(tree_.find(2) == tree_.end());

    TESTASSERT(tree_.remove(3));
    TESTASSERTOP(tree_.size(), eq, 0);
    TESTASSERT(tree_.find(3) == tree_.end());
  }

  void TestSplayTree::testRemove2(tst::TestResult& result)
  {
    tree_.insert(6);
    tree_.insert(5);
    tree_.insert(4);
    tree_.insert(3);
    tree_.insert(2);
    tree_.insert(1);

    TESTASSERT(tree_.remove(1));
    TESTASSERT(tree_.remove(2));
    TESTASSERT(tree_.remove(3));

    TESTASSERTOP(*tree_.find(4), eq, 4);
    TESTASSERTOP(*tree_.find(5), eq, 5);
    TESTASSERTOP(*tree_.find(6), eq, 6);
  }

  void TestSplayTree::testClear1(tst::TestResult& result)
  {
    for (int i = 0; i < 20; i++)
      tree_.insert(i);

    TESTASSERTOP( tree_.size(),  eq, 20);
    TESTASSERTOP(*tree_.find(5), eq, 5);

    tree_.clear();

    TESTASSERTOP(tree_.size(), eq, 0);
    TESTASSERT(tree_.find(5) == tree_.end());
  }

  void TestSplayTree::testIterate1(tst::TestResult& result)
  {
    int given1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int count1   = sizeof(given1) / sizeof(int);

    testIteration(result, given1, given1, count1);
  }

  void TestSplayTree::testIterate2(tst::TestResult& result)
  {
    int given2[]    = {999, -5, 10, 37, 42, 1, 57, 51, -100, 50000, 3};
    int expected2[] = {-100, -5, 1, 3, 10, 37, 42, 51, 57, 999, 50000};
    int count2      = sizeof(given2) / sizeof(int);

    testIteration(result, given2, expected2, count2);
  }

  void TestSplayTree::testIteration(tst::TestResult& result, int given[], int expected[], int count)
  {
    for (int i = 0; i < count; i++)
      tree_.insert(given[i]);

    Tree::ConstIterator it = tree_.begin();

    for (int i = 0; i < count; i++)
    {
      TESTASSERT(it != tree_.end());
      TESTASSERTOP(*it, eq, expected[i]);

      it++;
    }
    TESTASSERT(it == tree_.end());
  }
}
