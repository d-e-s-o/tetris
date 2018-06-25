// TestFocusIndex.hpp

/***************************************************************************
 *   Copyright (C) 2006-2012 Daniel Mueller (deso@posteo.net)              *
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

#ifndef TESTTESTFOCUSINDEX_HPP
#define TESTTESTFOCUSINDEX_HPP

#include <test/TestCase.hpp>


namespace test
{
  class RootWidget1;
  class Container1;
  class Widget1;


  class TestFocusIndex: public tst::TestCase<TestFocusIndex>
  {
  public:
    TestFocusIndex();

    void testGetIndex1(tst::TestResult& result);
    void testIncreaseIndex1(tst::TestResult& result);
    void testIncreaseIndex2(tst::TestResult& result);
    void testDecreaseIndex1(tst::TestResult& result);
    void testDecreaseIndex2(tst::TestResult& result);

  protected:
    virtual void setUp();
    virtual void tearDown();

  private:
    RootWidget1* root_widget_;
    Widget1*    widget_1_;
    Widget1*    widget_2_;
    Widget1*    widget_3_;
  };
}


#endif
