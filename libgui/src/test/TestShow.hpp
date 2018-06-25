// TestShow.hpp

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

#ifndef TESTTESTSHOW_HPP
#define TESTTESTSHOW_HPP

#include <test/TestCase.hpp>


namespace test
{
  class RootWidget1;
  class Container2;
  class Widget2;


  class TestShow: public tst::TestCase<TestShow>
  {
  public:
    TestShow();

    void testCreation1(tst::TestResult& result);

    void testFocus1(tst::TestResult& result);

    void testShow1(tst::TestResult& result);
    void testShow2(tst::TestResult& result);
    void testShow3(tst::TestResult& result);

    void testHide1(tst::TestResult& result);
    void testHide2(tst::TestResult& result);
    void testHide3(tst::TestResult& result);

  protected:
    virtual void setUp();
    virtual void tearDown();

  private:
    RootWidget1* root_widget_;

    Container2* container_1_;

    Container2* container_1_1_;
    Widget2* widget_1_1_1_;
    Widget2* widget_1_1_2_;
    Widget2* widget_1_1_3_;

    Container2* container_1_2_;
    Widget2* widget_1_2_1_;
    Widget2* widget_1_2_2_;
    Widget2* widget_1_2_3_;

    Container2* container_1_3_;
    Widget2* widget_1_3_1_;
    Widget2* widget_1_3_2_;
    Widget2* widget_1_3_3_;

    Widget2* widget_1_4_;
    Widget2* widget_1_5_;
  };
}


#endif
