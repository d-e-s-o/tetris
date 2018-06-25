// TestAnchors.cpp

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
#include "TestAnchors.hpp"


namespace test
{
  TestAnchors::TestAnchors()
    : tst::TestCase<TestAnchors>(*this, "TestAnchors")
  {
    add(&TestAnchors::testDefault);
    add(&TestAnchors::testLeftBottom);
    add(&TestAnchors::testRightBottom);
    add(&TestAnchors::testLeftTop);
    add(&TestAnchors::testRightTop);
    add(&TestAnchors::testLeftRightBottomTop);
  }

  void TestAnchors::setUp()
  {
    root_widget_ = new RootWidget1;

    container_1_ = new Container1(gui::Bounds(100, 100, 500, 400));
    widget_1_1_  = new Widget1(gui::Bounds(200, 100, 300, 200));
    widget_1_1_->setParent(container_1_);
  }

  void TestAnchors::tearDown()
  {
    delete widget_1_1_;
    delete container_1_;
    delete root_widget_;
  }

  void TestAnchors::testDefault(tst::TestResult& result)
  {
    TESTASSERTOP(container_1_->getHAnchors(), eq, gui::H_ANCHORS_LEFT);
    TESTASSERTOP(container_1_->getVAnchors(), eq, gui::V_ANCHORS_BOTTOM);
  }

  void TestAnchors::testLeftBottom(tst::TestResult& result)
  {
    widget_1_1_->setHAnchors(gui::H_ANCHORS_LEFT);
    widget_1_1_->setVAnchors(gui::V_ANCHORS_BOTTOM);

    container_1_->resize(container_1_->size() + gui::Size(100, 200));

    TESTASSERT(widget_1_1_->position() == gui::Position(200, 100));
    TESTASSERT(widget_1_1_->size()     == gui::Size(300, 200));
  }

  void TestAnchors::testRightBottom(tst::TestResult& result)
  {
    widget_1_1_->setHAnchors(gui::H_ANCHORS_RIGHT);
    widget_1_1_->setVAnchors(gui::V_ANCHORS_BOTTOM);

    container_1_->resize(container_1_->size() + gui::Size(100, 200));

    TESTASSERT(widget_1_1_->position() == gui::Position(300, 100));
    TESTASSERT(widget_1_1_->size()     == gui::Size(300, 200));
  }

  void TestAnchors::testLeftTop(tst::TestResult& result)
  {
    widget_1_1_->setHAnchors(gui::H_ANCHORS_LEFT);
    widget_1_1_->setVAnchors(gui::V_ANCHORS_TOP);

    container_1_->resize(container_1_->size() + gui::Size(100, 200));

    TESTASSERT(widget_1_1_->position() == gui::Position(200, 300));
    TESTASSERT(widget_1_1_->size()     == gui::Size(300, 200));
  }

  void TestAnchors::testRightTop(tst::TestResult& result)
  {
    widget_1_1_->setHAnchors(gui::H_ANCHORS_RIGHT);
    widget_1_1_->setVAnchors(gui::V_ANCHORS_TOP);

    container_1_->resize(container_1_->size() + gui::Size(100, 200));

    TESTASSERT(widget_1_1_->position() == gui::Position(300, 300));
    TESTASSERT(widget_1_1_->size()     == gui::Size(300, 200));
  }

  void TestAnchors::testLeftRightBottomTop(tst::TestResult& result)
  {
    widget_1_1_->setHAnchors(gui::H_ANCHORS_RIGHT  | gui::H_ANCHORS_LEFT);
    widget_1_1_->setVAnchors(gui::V_ANCHORS_BOTTOM | gui::V_ANCHORS_TOP);

    container_1_->resize(container_1_->size() + gui::Size(100, 200));

    TESTASSERT(widget_1_1_->position() == gui::Position(200, 100));
    TESTASSERT(widget_1_1_->size()     == gui::Size(400, 400));
  }
}
