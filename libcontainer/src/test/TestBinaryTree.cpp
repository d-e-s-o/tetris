// TestBinaryTree.cpp

/***************************************************************************
 *   Copyright (C) 2014 Daniel Mueller (deso@posteo.net)                   *
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

#include <type/Move.hpp>

#include "TestBinaryTree.hpp"


namespace test
{
  TestBinaryTree::TestBinaryTree()
    : tst::TestCase<TestBinaryTree>(*this, "TestBinaryTree")
  {
    add(&TestBinaryTree::testMoveConstruct);
    add(&TestBinaryTree::testMoveAssign);
  }

  void TestBinaryTree::testMoveConstruct(tst::TestResult& result)
  {
    Tree tree1;

    tree1.insert(1);
    tree1.insert(2);

    TESTASSERT(tree1.find(1) != tree1.end());
    TESTASSERT(tree1.find(2) != tree1.end());
    TESTASSERT(tree1.find(3) == tree1.end());

    Tree tree2 = typ::move(tree1);

    TESTASSERT(tree2.find(1) != tree2.end());
    TESTASSERT(tree2.find(2) != tree2.end());
    TESTASSERT(tree2.find(3) == tree2.end());

    TESTASSERT(tree1.find(1) == tree1.end());
    TESTASSERT(tree1.find(2) == tree1.end());
    TESTASSERT(tree1.find(3) == tree1.end());
  }

  void TestBinaryTree::testMoveAssign(tst::TestResult& result)
  {
    Tree tree1;
    Tree tree2;

    tree1.insert(1);
    tree1.insert(2);

    TESTASSERT(tree1.find(1) != tree1.end());
    TESTASSERT(tree1.find(2) != tree1.end());
    TESTASSERT(tree1.find(3) == tree1.end());

    tree2 = typ::move(tree1);

    TESTASSERT(tree2.find(1) != tree2.end());
    TESTASSERT(tree2.find(2) != tree2.end());
    TESTASSERT(tree2.find(3) == tree2.end());

    TESTASSERT(tree1.find(1) == tree1.end());
    TESTASSERT(tree1.find(2) == tree1.end());
    TESTASSERT(tree1.find(3) == tree1.end());
  }
}
