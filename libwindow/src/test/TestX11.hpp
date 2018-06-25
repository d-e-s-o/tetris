// TestX11.hpp

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

#ifndef TESTTESTX11_HPP
#define TESTTESTX11_HPP

#include <X11/Xlib.h>
#include <test/TestCase.hpp>


namespace test
{
  class TestX11: public tst::TestCase<TestX11>
  {
  public:
    TestX11();

    void testCreate(tst::TestResult& result);
    void testMove(tst::TestResult& result);
    void testResize(tst::TestResult& result);
    void testClose(tst::TestResult& result);
    void testMouseMove(tst::TestResult& result);
    void testMouseDown(tst::TestResult& result);
    void testMouseUp(tst::TestResult& result);
    void testMouseWheelDown(tst::TestResult& result);
    void testMouseWheelUp(tst::TestResult& result);
    void testKeyDown(tst::TestResult& result);
    void testKeyUp(tst::TestResult& result);
    void testChar(tst::TestResult& result);

  protected:
    virtual void setUp();

  private:
    typedef void (TestX11::*TestFunction)(tst::TestResult&, Display*, ::Window);

    void doTest(tst::TestResult& result, TestFunction const& function);

    void moveFn(tst::TestResult& result, Display* display, ::Window window);
    void resizeFn(tst::TestResult& result, Display* display, ::Window window);
    void closeFn(tst::TestResult& result, Display* display, ::Window window);
    void mouseMoveFn(tst::TestResult& result, Display* display, ::Window window);
    void mouseDownFn(tst::TestResult& result, Display* display, ::Window window);
    void mouseUpFn(tst::TestResult& result, Display* display, ::Window window);
    void mouseWheelDownFn(tst::TestResult& result, Display* display, ::Window window);
    void mouseWheelUpFn(tst::TestResult& result, Display* display, ::Window window);
    void keyDownFn(tst::TestResult& result, Display* display, ::Window window);
    void keyUpFn(tst::TestResult& result, Display* display, ::Window window);
    void charFn(tst::TestResult& result, Display* display, ::Window window);
  };
}


#endif
