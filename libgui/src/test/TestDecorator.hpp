// TestDecorator.hpp

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

#ifndef TESTTESTDECORATOR_HPP
#define TESTTESTDECORATOR_HPP

#include <test/TestCase.hpp>


namespace test
{
  class RootWidget1;
  class Widget1;
  class Decorator1;
  class Decorator2;


  class TestDecorator: public tst::TestCase<TestDecorator>
  {
  public:
    TestDecorator();

    void testCreate1(tst::TestResult& result);
    void testCreate2(tst::TestResult& result);
    void testInsertBefore1(tst::TestResult& result);
    void testInsertBefore2(tst::TestResult& result);
    void testInsertAfter1(tst::TestResult& result);
    void testInsertAfter2(tst::TestResult& result);
    void testRemove1(tst::TestResult& result);
    void testRemove2(tst::TestResult& result);
    void testRemove3(tst::TestResult& result);

  protected:
    virtual void setUp();
    virtual void tearDown();

  private:
    RootWidget1* root_widget_;
    Widget1*     widget_;

    Decorator1* decorator_1_;
    Decorator1* decorator_2_;
    Decorator1* decorator_3_;

    Decorator2* decorator_4_; // thats the only "container"

    Decorator1* decorator_5_;
  };
}


#endif
