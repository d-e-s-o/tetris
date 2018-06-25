// TestFocusIndex.cpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#include "RootWidget1.hpp"
#include "Container1.hpp"
#include "Widget1.hpp"
#include "TestFocusIndex.hpp"


namespace test
{
  TestFocusIndex::TestFocusIndex()
    : tst::TestCase<TestFocusIndex>(*this, "TestFocusIndex")
  {
    add(&TestFocusIndex::testGetIndex1);
    add(&TestFocusIndex::testIncreaseIndex1);
    add(&TestFocusIndex::testIncreaseIndex2);
    add(&TestFocusIndex::testDecreaseIndex1);
    add(&TestFocusIndex::testDecreaseIndex2);
  }

  void TestFocusIndex::setUp()
  {
    root_widget_ = new RootWidget1;
    widget_1_ = new Widget1;
    widget_2_ = new Widget1;
    widget_3_ = new Widget1;

  }

  void TestFocusIndex::tearDown()
  {
    delete widget_3_;
    delete widget_2_;
    delete widget_1_;
    delete root_widget_;
  }

  void TestFocusIndex::testGetIndex1(tst::TestResult& result)
  {
    TESTASSERTOP(root_widget_->focusIndex(), eq, 0);

    TESTASSERTOP(widget_1_->focusIndex(), eq, 0);
    TESTASSERTOP(widget_2_->focusIndex(), eq, 1);
    TESTASSERTOP(widget_3_->focusIndex(), eq, 2);
  }

  void TestFocusIndex::testIncreaseIndex1(tst::TestResult& result)
  {
    TESTASSERT(!root_widget_->increaseFocusIndex());
    TESTASSERTOP(root_widget_->focusIndex(), eq, 0);

    TESTASSERT(!widget_3_->increaseFocusIndex());
    TESTASSERTOP(widget_3_->focusIndex(), eq, 2);
  }

  void TestFocusIndex::testIncreaseIndex2(tst::TestResult& result)
  {
    TESTASSERT(widget_1_->increaseFocusIndex());
    TESTASSERTOP(widget_1_->focusIndex(), eq, 1);
    TESTASSERTOP(widget_2_->focusIndex(), eq, 0);

    TESTASSERT(widget_2_->increaseFocusIndex());
    TESTASSERTOP(widget_2_->focusIndex(), eq, 1);
    TESTASSERTOP(widget_1_->focusIndex(), eq, 0);
  }

  void TestFocusIndex::testDecreaseIndex1(tst::TestResult& result)
  {
    TESTASSERT(!root_widget_->decreaseFocusIndex());
    TESTASSERTOP(root_widget_->focusIndex(), eq, 0);

    TESTASSERT(!widget_1_->decreaseFocusIndex());
    TESTASSERTOP(widget_1_->focusIndex(), eq, 0);
  }

  void TestFocusIndex::testDecreaseIndex2(tst::TestResult& result)
  {
    TESTASSERT(widget_3_->decreaseFocusIndex());
    TESTASSERTOP(widget_3_->focusIndex(), eq, 1);
    TESTASSERTOP(widget_2_->focusIndex(), eq, 2);

    TESTASSERT(widget_2_->decreaseFocusIndex());
    TESTASSERTOP(widget_2_->focusIndex(), eq, 1);
    TESTASSERTOP(widget_3_->focusIndex(), eq, 2);
  }
}
