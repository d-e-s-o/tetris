// TestFocusNext.hpp

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

#ifndef TESTTESTFOCUSNEXT_HPP
#define TESTTESTFOCUSNEXT_HPP

#include <test/TestCase.hpp>


namespace test
{
  class RootWidget1;
  class Container1;
  class Widget1;


  class TestFocusNext: public tst::TestCase<TestFocusNext>
  {
  public:
    TestFocusNext();

    void testFocusNext1(tst::TestResult& result);
    void testFocusNext2(tst::TestResult& result);
    void testFocusNext3(tst::TestResult& result);
    void testFocusNext4(tst::TestResult& result);

    void testFocusPrevious1(tst::TestResult& result);
    void testFocusPrevious2(tst::TestResult& result);
    void testFocusPrevious3(tst::TestResult& result);
    void testFocusPrevious4(tst::TestResult& result);

  protected:
    virtual void setUp();
    virtual void tearDown();

  private:
    RootWidget1* root_widget_;

    Container1* container_1_;

    Container1* container_2_;
    Widget1*    widget_2_1_;
    Widget1*    widget_2_2_;
    Widget1*    widget_2_3_;

    Container1* container_3_;
    Widget1*    widget_3_1_;
    Widget1*    widget_3_2_;
    Widget1*    widget_3_3_;

    Container1* container_4_;
    Widget1*    widget_4_1_;
    Widget1*    widget_4_2_;
    Widget1*    widget_4_3_;
    Container1* container_4_4_;
    Widget1*    widget_4_4_1_;
    Widget1*    widget_4_4_2_;

    Container1* container_5_;

    Widget1* widget_6_;
    Widget1* widget_7_;
    Widget1* widget_8_;
  };
}


#endif
