// TestButton.cpp

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
#include "Button1.hpp"
#include "TestButton.hpp"


namespace test
{
  TestButton::TestButton()
    : tst::TestCase<TestButton>(*this, "TestButton")
  {
    add(&TestButton::testClick1);
    add(&TestButton::testClick2);
    add(&TestButton::testClick3);
  }

  void TestButton::setUp()
  {
    root_widget_ = new RootWidget1;
    button_      = new Button1(gui::Bounds(100, 200, 300, 400));
  }

  void TestButton::tearDown()
  {
    delete button_;
    delete root_widget_;
  }

  void TestButton::testClick1(tst::TestResult& result)
  {
    root_widget_->handleEvent(gui::MouseDownEvent(gui::Position(100, 200), wnd::MOUSE_BUTTON_LEFT));
    TESTASSERTOP(button_->click_called_, eq, 0);

    root_widget_->handleEvent(gui::MouseUpEvent(gui::Position(100, 200), wnd::MOUSE_BUTTON_LEFT));
    TESTASSERTOP(button_->click_called_, eq, 1);
  }

  void TestButton::testClick2(tst::TestResult& result)
  {
    root_widget_->handleEvent(gui::MouseDownEvent(gui::Position(100, 200), wnd::MOUSE_BUTTON_LEFT));
    TESTASSERTOP(button_->click_called_, eq, 0);

    root_widget_->handleEvent(gui::MouseUpEvent(gui::Position(500, 700), wnd::MOUSE_BUTTON_LEFT));
    TESTASSERTOP(button_->click_called_, eq, 0);
  }

  void TestButton::testClick3(tst::TestResult& result)
  {
    root_widget_->handleEvent(gui::MouseDownEvent(gui::Position(0, 0), wnd::MOUSE_BUTTON_LEFT));
    TESTASSERTOP(button_->click_called_, eq, 0);

    root_widget_->handleEvent(gui::MouseUpEvent(gui::Position(100, 200), wnd::MOUSE_BUTTON_LEFT));
    TESTASSERTOP(button_->click_called_, eq, 0);
  }
}
