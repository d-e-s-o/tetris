// TestWidget.cpp

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

#include "Widget1.hpp"
#include "RootWidget1.hpp"
#include "TestWidget.hpp"


namespace test
{
  TestWidget::TestWidget()
    : tst::TestCase<TestWidget>(*this, "TestWidget")
  {
    add(&TestWidget::testCreation1);
    add(&TestWidget::testCreation2);
  }

  void TestWidget::testCreation1(tst::TestResult& result)
  {
    // has to throw exception because no root widget was created before
    try
    {
      Widget1 widget;
      TESTASSERTM(false, "no exception was thrown");
    }
    catch(...)
    {
    }
  }

  void TestWidget::testCreation2(tst::TestResult& result)
  {
    RootWidget1 root_widget;
    Widget1     widget(gui::Bounds(0, 0, 1000, 1000));

    TESTASSERT(widget.position() == gui::Position(0, 0));
    TESTASSERT(widget.size() == gui::Size(1000, 1000));
  }
}
