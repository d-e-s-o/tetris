// TestFocusNext.cpp

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
#include "TestFocusNext.hpp"


namespace test
{
  TestFocusNext::TestFocusNext()
    : tst::TestCase<TestFocusNext>(*this, "TestFocusNext")
  {
    add(&TestFocusNext::testFocusNext1);
    add(&TestFocusNext::testFocusNext2);
    add(&TestFocusNext::testFocusNext3);
    add(&TestFocusNext::testFocusNext4);
    add(&TestFocusNext::testFocusPrevious1);
    add(&TestFocusNext::testFocusPrevious2);
    add(&TestFocusNext::testFocusPrevious3);
    add(&TestFocusNext::testFocusPrevious4);
  }

  void TestFocusNext::setUp()
  {
    root_widget_ = new RootWidget1;

      // empty container
      container_1_ = new Container1;

      // focusable container with 3 widgets, 2nd hidden
      container_2_ = new Container1;
        widget_2_1_ = new Widget1;
        widget_2_1_->setParent(container_2_);
        widget_2_2_ = new Widget1;
        widget_2_2_->setParent(container_2_);
        widget_2_2_->hide();
        widget_2_3_ = new Widget1;
        widget_2_3_->setParent(container_2_);

      // non focusable container with 3 widgets
      container_3_ = new Container1;
      container_3_->setFocusable(false);
        widget_3_1_ = new Widget1;
        widget_3_1_->setParent(container_3_);
        widget_3_2_ = new Widget1;
        widget_3_2_->setParent(container_3_);
        widget_3_3_ = new Widget1;
        widget_3_3_->setParent(container_3_);

      // container with 3 widgets, 1st not focusable and another container with 2 widgets
      container_4_ = new Container1;
        widget_4_1_ = new Widget1;
        widget_4_1_->setParent(container_4_);
        widget_4_1_->setFocusable(false);
        widget_4_2_ = new Widget1;
        widget_4_2_->setParent(container_4_);
        widget_4_3_ = new Widget1;
        widget_4_3_->setParent(container_4_);

        container_4_4_ = new Container1;
        container_4_4_->setParent(container_4_);
          widget_4_4_1_ = new Widget1;
          widget_4_4_1_->setParent(container_4_4_);
          widget_4_4_2_ = new Widget1;
          widget_4_4_2_->setParent(container_4_4_);

      // empty non focusable container
      container_5_ = new Container1;
      container_5_->setFocusable(false);

      // three widgets belonging to the root widget, 1st hidden, third not focusable
      widget_6_ = new Widget1;
      widget_6_->hide();
      widget_7_ = new Widget1;
      widget_8_ = new Widget1;
      widget_8_->setFocusable(false);
  }

  void TestFocusNext::tearDown()
  {
      delete widget_8_;
      delete widget_7_;
      delete widget_6_;
      delete container_5_;
          delete widget_4_4_2_;
          delete widget_4_4_1_;
        delete container_4_4_;
        delete widget_4_3_;
        delete widget_4_2_;
        delete widget_4_1_;
      delete container_4_;
        delete widget_3_3_;
        delete widget_3_2_;
        delete widget_3_1_;
      delete container_3_;
        delete widget_2_3_;
        delete widget_2_2_;
        delete widget_2_1_;
      delete container_2_;
      delete container_1_;
    delete root_widget_;
  }

  void TestFocusNext::testFocusNext1(tst::TestResult& result)
  {
    root_widget_->focus();
    root_widget_->focusNext();
    TESTASSERT(widget_3_1_->focused());

    root_widget_->focusNext();
    TESTASSERT(widget_3_2_->focused());

    root_widget_->focusNext();
    TESTASSERT(widget_3_3_->focused());

    root_widget_->focusNext();
    TESTASSERT(widget_7_->focused());

    root_widget_->focusNext();
    TESTASSERT(widget_3_1_->focused());
  }

  void TestFocusNext::testFocusNext2(tst::TestResult& result)
  {
    container_1_->focus();
    TESTASSERT(container_1_->focused());

    container_1_->focusNext();
    TESTASSERT(container_1_->focused());
  }

  void TestFocusNext::testFocusNext3(tst::TestResult& result)
  {
    container_2_->focus();
    container_2_->focusNext();
    TESTASSERT(widget_2_1_->focused());

    container_2_->focusNext();
    TESTASSERT(widget_2_3_->focused());

    container_2_->focusNext();
    TESTASSERT(widget_2_1_->focused());
  }

  void TestFocusNext::testFocusNext4(tst::TestResult& result)
  {
    container_4_->focus();
    container_4_->focusNext();
    TESTASSERT(widget_4_2_->focused());

    container_4_->focusNext();
    TESTASSERT(widget_4_3_->focused());

    container_4_->focusNext();
    TESTASSERT(widget_4_2_->focused());

    container_4_4_->focus();
    container_4_4_->focusNext();
    TESTASSERT(widget_4_4_1_->focused());

    container_4_4_->focusNext();
    TESTASSERT(widget_4_4_2_->focused());

    container_4_4_->focusNext();
    TESTASSERT(widget_4_4_1_->focused());
  }

  void TestFocusNext::testFocusPrevious1(tst::TestResult& result)
  {
    root_widget_->focus();
    root_widget_->focusPrevious();
    TESTASSERT(widget_7_->focused());

    root_widget_->focusPrevious();
    TESTASSERT(widget_3_3_->focused());

    root_widget_->focusPrevious();
    TESTASSERT(widget_3_2_->focused());

    root_widget_->focusPrevious();
    TESTASSERT(widget_3_1_->focused());

    root_widget_->focusPrevious();
    TESTASSERT(widget_7_->focused());
  }

  void TestFocusNext::testFocusPrevious2(tst::TestResult& result)
  {
    container_1_->focus();
    TESTASSERT(container_1_->focused());

    container_1_->focusPrevious();
    TESTASSERT(container_1_->focused());
  }

  void TestFocusNext::testFocusPrevious3(tst::TestResult& result)
  {
    container_2_->focus();
    container_2_->focusPrevious();
    TESTASSERT(widget_2_3_->focused());

    container_2_->focusPrevious();
    TESTASSERT(widget_2_1_->focused());

    container_2_->focusPrevious();
    TESTASSERT(widget_2_3_->focused());
  }

  void TestFocusNext::testFocusPrevious4(tst::TestResult& result)
  {
    container_4_->focus();
    container_4_->focusPrevious();
    TESTASSERT(widget_4_3_->focused());

    container_4_->focusPrevious();
    TESTASSERT(widget_4_2_->focused());

    container_4_->focusPrevious();
    TESTASSERT(widget_4_3_->focused());

    container_4_4_->focus();
    container_4_4_->focusPrevious();
    TESTASSERT(widget_4_4_2_->focused());

    container_4_4_->focusPrevious();
    TESTASSERT(widget_4_4_1_->focused());

    container_4_4_->focusPrevious();
    TESTASSERT(widget_4_4_2_->focused());
  }
}
