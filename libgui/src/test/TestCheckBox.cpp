// TestCheckBox.cpp

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

#include <gui/event/MouseDownEvent.hpp>
#include <gui/event/MouseUpEvent.hpp>

#include "RootWidget1.hpp"
#include "CheckBox1.hpp"
#include "TestCheckBox.hpp"


namespace test
{
  TestCheckBox::TestCheckBox()
    : tst::TestCase<TestCheckBox>(*this, "TestCheckBox")
  {
    add(&TestCheckBox::testClick1);
    add(&TestCheckBox::testClick2);
    add(&TestCheckBox::testClick3);
  }

  void TestCheckBox::setUp()
  {
    root_widget_ = new RootWidget1;
    check_box_   = new CheckBox1(gui::Bounds(100, 200, 300, 400));
  }

  void TestCheckBox::tearDown()
  {
    delete check_box_;
    delete root_widget_;
  }

  void TestCheckBox::testClick1(tst::TestResult& result)
  {
    root_widget_->handleEvent(gui::MouseDownEvent(gui::Position(100, 200), wnd::MOUSE_BUTTON_LEFT));
    TESTASSERTOP(check_box_->click_called_, eq, 0);

    root_widget_->handleEvent(gui::MouseUpEvent(gui::Position(100, 200), wnd::MOUSE_BUTTON_LEFT));
    TESTASSERTOP(check_box_->click_called_, eq, 1);
  }

  void TestCheckBox::testClick2(tst::TestResult& result)
  {
    root_widget_->handleEvent(gui::MouseDownEvent(gui::Position(0, 0), wnd::MOUSE_BUTTON_LEFT));
    TESTASSERTOP(check_box_->click_called_, eq, 0);

    root_widget_->handleEvent(gui::MouseUpEvent(gui::Position(100, 200), wnd::MOUSE_BUTTON_LEFT));
    TESTASSERTOP(check_box_->click_called_, eq, 0);
  }

  void TestCheckBox::testClick3(tst::TestResult& result)
  {
    root_widget_->handleEvent(gui::MouseDownEvent(gui::Position(100, 200), wnd::MOUSE_BUTTON_LEFT));
    TESTASSERTOP(check_box_->click_called_, eq, 0);

    root_widget_->handleEvent(gui::MouseUpEvent(gui::Position(0, 0), wnd::MOUSE_BUTTON_LEFT));
    TESTASSERTOP(check_box_->click_called_, eq, 0);
  }
}
