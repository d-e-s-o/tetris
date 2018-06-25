// TestShow.cpp

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
#include "CallbackCounter.hpp"
#include "TestShow.hpp"


namespace test
{
  class Widget2: public CallbackCounter<Widget1>
  {
  public:
    Widget2()
      : CallbackCounter<Widget1>(gui::Bounds(0, 0, 10, 10))
    {
    }
  };

  class Container2: public CallbackCounter<Container1>
  {
  public:
    Container2()
      : CallbackCounter<Container1>(gui::Bounds(0, 0, 100, 100))
    {
    }
  };


  TestShow::TestShow()
    : tst::TestCase<TestShow>(*this, "TestShow")
  {
    add(&TestShow::testCreation1);
    add(&TestShow::testFocus1);
    add(&TestShow::testShow1);
    add(&TestShow::testShow2);
    add(&TestShow::testShow3);
    add(&TestShow::testHide1);
    add(&TestShow::testHide2);
    add(&TestShow::testHide3);
  }

  void TestShow::setUp()
  {
    root_widget_ = new RootWidget1;
      container_1_ = new Container2;
        container_1_1_ = new Container2;
        container_1_1_->setParent(container_1_);
          widget_1_1_1_ = new Widget2;
          widget_1_1_1_->setParent(container_1_1_);
          widget_1_1_2_ = new Widget2;
          widget_1_1_2_->setParent(container_1_1_);
          widget_1_1_3_ = new Widget2;
          widget_1_1_3_->setParent(container_1_1_);
        container_1_2_ = new Container2;
        container_1_2_->setParent(container_1_);
          widget_1_2_1_ = new Widget2;
          widget_1_2_1_->setParent(container_1_2_);
          widget_1_2_2_ = new Widget2;
          widget_1_2_2_->setParent(container_1_2_);
          widget_1_2_3_ = new Widget2;
          widget_1_2_3_->setParent(container_1_2_);
        container_1_3_ = new Container2;
        container_1_3_->setParent(container_1_);
          widget_1_3_1_ = new Widget2;
          widget_1_3_1_->setParent(container_1_3_);
          widget_1_3_2_ = new Widget2;
          widget_1_3_2_->setParent(container_1_3_);
          widget_1_3_3_ = new Widget2;
          widget_1_3_3_->setParent(container_1_3_);

        widget_1_4_ = new Widget2;
        widget_1_4_->setParent(container_1_);
        widget_1_5_ = new Widget2;
        widget_1_5_->setParent(container_1_);
  }

  void TestShow::tearDown()
  {
        delete widget_1_5_;
        delete widget_1_4_;
          delete widget_1_3_3_;
          delete widget_1_3_2_;
          delete widget_1_3_1_;
        delete container_1_3_;
          delete widget_1_2_3_;
          delete widget_1_2_2_;
          delete widget_1_2_1_;
        delete container_1_2_;
          delete widget_1_1_3_;
          delete widget_1_1_2_;
          delete widget_1_1_1_;
        delete container_1_1_;
      delete container_1_;
    delete root_widget_;
  }

  void TestShow::testCreation1(tst::TestResult& result)
  {
    TESTASSERTOP(container_1_->gain_focus_called_, eq, 0);
    TESTASSERTOP(container_1_->loose_focus_called_, eq, 0);
    TESTASSERTOP(container_1_->show_called_, eq, 0);
    TESTASSERTOP(container_1_->hide_called_, eq, 0);

    TESTASSERTOP(container_1_->getParent(),     eq, root_widget_);
    TESTASSERTOP(container_1_->rootWidget(), eq, root_widget_);
  }

  void TestShow::testFocus1(tst::TestResult& result)
  {
    TESTASSERTOP(container_1_->show_called_, eq, 0);
    TESTASSERTOP(container_1_->hide_called_, eq, 0);
    TESTASSERTOP(container_1_->gain_focus_called_, eq, 0);
    TESTASSERTOP(container_1_->loose_focus_called_, eq, 0);

    container_1_->focus();
    TESTASSERT(container_1_->focused());

    TESTASSERTOP(container_1_->gain_focus_called_, eq, 1);
    TESTASSERTOP(container_1_->loose_focus_called_, eq, 0);

    container_1_->focus();
    TESTASSERT(container_1_->focused());

    TESTASSERTOP(container_1_->gain_focus_called_, eq, 1);
    TESTASSERTOP(container_1_->loose_focus_called_, eq, 0);
  }

  void TestShow::testShow1(tst::TestResult& result)
  {
    container_1_->hide();
    container_1_->show();
    TESTASSERT(container_1_->shown());
    TESTASSERT(container_1_->visible());
    TESTASSERT(!container_1_->focused());

    TESTASSERTOP(container_1_->show_called_, eq, 1);
    TESTASSERTOP(container_1_1_->show_called_, eq, 1);
    TESTASSERTOP(widget_1_1_1_->show_called_, eq, 1);
    TESTASSERTOP(widget_1_1_2_->show_called_, eq, 1);
    TESTASSERTOP(widget_1_1_3_->show_called_, eq, 1);
    TESTASSERTOP(container_1_2_->show_called_, eq, 1);
    TESTASSERTOP(widget_1_2_1_->show_called_, eq, 1);
    TESTASSERTOP(widget_1_2_2_->show_called_, eq, 1);
    TESTASSERTOP(widget_1_2_3_->show_called_, eq, 1);
    TESTASSERTOP(container_1_3_->show_called_, eq, 1);
    TESTASSERTOP(widget_1_3_1_->show_called_, eq, 1);
    TESTASSERTOP(widget_1_3_2_->show_called_, eq, 1);
    TESTASSERTOP(widget_1_3_3_->show_called_, eq, 1);
    TESTASSERTOP(widget_1_4_->show_called_, eq, 1);
    TESTASSERTOP(widget_1_5_->show_called_, eq, 1);

    TESTASSERTOP(container_1_->hide_called_, eq, 1);
    TESTASSERTOP(container_1_1_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_1_1_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_1_2_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_1_3_->hide_called_, eq, 1);
    TESTASSERTOP(container_1_2_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_2_1_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_2_2_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_2_3_->hide_called_, eq, 1);
    TESTASSERTOP(container_1_3_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_3_1_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_3_2_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_3_3_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_4_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_5_->hide_called_, eq, 1);
  }

  void TestShow::testShow2(tst::TestResult& result)
  {
    container_1_->hide();
    TESTASSERTOP(container_1_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_4_->hide_called_, eq, 1);

    widget_1_4_->hide();
    TESTASSERTOP(widget_1_4_->hide_called_, eq, 1);

    container_1_1_->hide();
    TESTASSERTOP(container_1_1_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_1_1_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_1_2_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_1_3_->hide_called_, eq, 1);

    container_1_->show();

    TESTASSERTOP(container_1_->show_called_, eq, 1);
    TESTASSERTOP(container_1_1_->show_called_, eq, 0);
    TESTASSERTOP(widget_1_1_1_->show_called_, eq, 0);
    TESTASSERTOP(widget_1_1_2_->show_called_, eq, 0);
    TESTASSERTOP(widget_1_1_3_->show_called_, eq, 0);
    TESTASSERTOP(container_1_2_->show_called_, eq, 1);
    TESTASSERTOP(widget_1_2_1_->show_called_, eq, 1);
    TESTASSERTOP(widget_1_2_2_->show_called_, eq, 1);
    TESTASSERTOP(widget_1_2_3_->show_called_, eq, 1);
    TESTASSERTOP(container_1_3_->show_called_, eq, 1);
    TESTASSERTOP(widget_1_3_1_->show_called_, eq, 1);
    TESTASSERTOP(widget_1_3_2_->show_called_, eq, 1);
    TESTASSERTOP(widget_1_3_3_->show_called_, eq, 1);
    TESTASSERTOP(widget_1_4_->show_called_, eq, 0);
    TESTASSERTOP(widget_1_5_->show_called_, eq, 1);
  }

  void TestShow::testShow3(tst::TestResult& result)
  {
    TESTASSERTOP(container_1_->show_called_, eq, 0);
    TESTASSERTOP(container_1_->hide_called_, eq, 0);

    container_1_->hide();

    TESTASSERTOP(container_1_->show_called_, eq, 0);
    TESTASSERTOP(container_1_->hide_called_, eq, 1);

    container_1_->show();

    TESTASSERTOP(container_1_->show_called_, eq, 1);
    TESTASSERTOP(container_1_->hide_called_, eq, 1);

    container_1_->show();

    TESTASSERTOP(container_1_->show_called_, eq, 1);
    TESTASSERTOP(container_1_->hide_called_, eq, 1);
  }

  void TestShow::testHide1(tst::TestResult& result)
  {
    container_1_->hide();

    TESTASSERTOP(container_1_->hide_called_, eq, 1);
    TESTASSERTOP(container_1_1_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_1_1_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_1_2_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_1_3_->hide_called_, eq, 1);
    TESTASSERTOP(container_1_2_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_2_1_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_2_2_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_2_3_->hide_called_, eq, 1);
    TESTASSERTOP(container_1_3_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_3_1_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_3_2_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_3_3_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_4_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_5_->hide_called_, eq, 1);
  }

  void TestShow::testHide2(tst::TestResult& result)
  {
    widget_1_4_->hide();
    TESTASSERTOP(widget_1_4_->hide_called_, eq, 1);

    container_1_1_->hide();
    TESTASSERTOP(container_1_1_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_1_1_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_1_2_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_1_3_->hide_called_, eq, 1);

    container_1_->hide();

    TESTASSERTOP(container_1_->hide_called_, eq, 1);
    TESTASSERTOP(container_1_1_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_1_1_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_1_2_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_1_3_->hide_called_, eq, 1);
    TESTASSERTOP(container_1_2_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_2_1_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_2_2_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_2_3_->hide_called_, eq, 1);
    TESTASSERTOP(container_1_3_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_3_1_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_3_2_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_3_3_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_4_->hide_called_, eq, 1);
    TESTASSERTOP(widget_1_5_->hide_called_, eq, 1);
  }

  void TestShow::testHide3(tst::TestResult& result)
  {
    container_1_->hide();
    TESTASSERTOP(container_1_->hide_called_, eq, 1);

    container_1_->hide();
    TESTASSERTOP(container_1_->hide_called_, eq, 1);
  }
}
