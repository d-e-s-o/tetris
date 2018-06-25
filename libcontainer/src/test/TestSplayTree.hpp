// TestSplayTree.hpp

/***************************************************************************
 *   Copyright (C) 2010-2012 Daniel Mueller (deso@posteo.net)              *
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

#ifndef CTRTESTSPLAYTREE_HPP
#define CTRTESTSPLAYTREE_HPP

#include <test/TestCase.hpp>
#include <container/SplayTree.hpp>


namespace test
{
  class TestSplayTree: public tst::TestCase<TestSplayTree>
  {
  public:
    TestSplayTree();

    void testInsert1(tst::TestResult& result);
    void testInsert2(tst::TestResult& result);
    void testInsert3(tst::TestResult& result);

    void testFind1(tst::TestResult& result);

    void testFindLowerBound1(tst::TestResult& result);
    void testFindLowerEqual1(tst::TestResult& result);

    void testRemove1(tst::TestResult& result);
    void testRemove2(tst::TestResult& result);

    void testClear1(tst::TestResult& result);

    void testIterate1(tst::TestResult& result);
    void testIterate2(tst::TestResult& result);

  protected:
    virtual void setUp();

  private:
    typedef ctr::SplayTree<int> Tree;

    Tree tree_;

    void testIteration(tst::TestResult& result, int given[], int expected[], int count);
  };
}


#endif
