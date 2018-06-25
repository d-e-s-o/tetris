// TestRenderer.cpp

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
#include "Renderer1.hpp"
#include "TestRenderer.hpp"


namespace test
{
  namespace
  {
    gui::SizeT const W = RootWidget1::WIDTH;
    gui::SizeT const H = RootWidget1::HEIGHT;
  }


  TestRenderer::TestRenderer()
    : tst::TestCase<TestRenderer>(*this, "TestRenderer")
  {
    add(&TestRenderer::testPushRectangle1);
    add(&TestRenderer::testPushRectangle2);
    add(&TestRenderer::testPushRectangle3);
  }

  void TestRenderer::setUp()
  {
    renderer_ = new Renderer1;
    renderer_->pushClippingRectangle(gui::Rectangle(0, 0, W, H));
  }

  void TestRenderer::tearDown()
  {
    renderer_->popClippingRectangle();
    delete renderer_;
  }

  void TestRenderer::testPushRectangle1(tst::TestResult& result)
  {
    TESTASSERT(renderer_->getClippingRectangle() == gui::Rectangle(0, 0, W, H));

    renderer_->pushClippingRectangle(gui::Rectangle(0, 0, 0, 0));
    TESTASSERT(renderer_->getClippingRectangle() == gui::Rectangle(0, 0, 0, 0));
    TESTASSERT(renderer_->getClippingOrigin() == gui::Point(0, 0));
    renderer_->popClippingRectangle();

    renderer_->pushClippingRectangle(gui::Rectangle(100, 200, W, H));
    TESTASSERT(renderer_->getClippingRectangle() == gui::Rectangle(100, 200, W, H));
    TESTASSERT(renderer_->getClippingOrigin() == gui::Point(0, 0));
    renderer_->popClippingRectangle();

    renderer_->pushClippingRectangle(gui::Rectangle(100, 200, W, H));
    TESTASSERT(renderer_->getClippingRectangle() == gui::Rectangle(100, 200, W, H));
    TESTASSERT(renderer_->getClippingOrigin() == gui::Point(0, 0));
    renderer_->popClippingRectangle();

    renderer_->pushClippingRectangle(gui::Rectangle(100, 200, W, H));
    TESTASSERT(renderer_->getClippingRectangle() == gui::Rectangle(100, 200, W, H));
    TESTASSERT(renderer_->getClippingOrigin() == gui::Point(0, 0));
    renderer_->popClippingRectangle();
  }

  void TestRenderer::testPushRectangle2(tst::TestResult& result)
  {
    renderer_->pushClippingRectangle(gui::Rectangle(-100, 200, 0, 400));
    TESTASSERT(renderer_->getClippingRectangle() == gui::Rectangle(0, 200, 0, 400));
    TESTASSERT(renderer_->getClippingOrigin() == gui::Point(-100, 0));
    renderer_->popClippingRectangle();

    renderer_->pushClippingRectangle(gui::Rectangle(100, -200, 200, 0));
    TESTASSERT(renderer_->getClippingRectangle() == gui::Rectangle(100, 0, 200, 0));
    TESTASSERT(renderer_->getClippingOrigin() == gui::Point(0, -200));
    renderer_->popClippingRectangle();

    renderer_->pushClippingRectangle(gui::Rectangle(-100, -200, 400, 400));
    TESTASSERT(renderer_->getClippingRectangle() == gui::Rectangle(0, 0, 400, 400));
    TESTASSERT(renderer_->getClippingOrigin() == gui::Point(-100, -200));
    renderer_->popClippingRectangle();

    renderer_->pushClippingRectangle(gui::Rectangle(-100, -200, 0, 0));
    TESTASSERT(renderer_->getClippingRectangle() == gui::Rectangle(0, 0, 0, 0));
    TESTASSERT(renderer_->getClippingOrigin() == gui::Point(-100, -200));
    renderer_->popClippingRectangle();

    renderer_->pushClippingRectangle(gui::Rectangle(-300, -400, -200, -200));
    TESTASSERT(renderer_->getClippingRectangle() == gui::Rectangle(0, 0, 0, 0));
    TESTASSERT(renderer_->getClippingOrigin() == gui::Point(-300, -400));
    renderer_->popClippingRectangle();
  }

  void TestRenderer::testPushRectangle3(tst::TestResult& result)
  {
    renderer_->pushClippingRectangle(gui::Rectangle(W + 100, H + 100, W + 300, W + 400));
    TESTASSERT(renderer_->getClippingRectangle() == gui::Rectangle(W, H, W, H));
    TESTASSERT(renderer_->getClippingOrigin() == gui::Point(0, 0));
    renderer_->popClippingRectangle();

    renderer_->pushClippingRectangle(gui::Rectangle(400, 400, 1000, 1100));
    TESTASSERT(renderer_->getClippingRectangle() == gui::Rectangle(400, 400, 1000, 1000));
    TESTASSERT(renderer_->getClippingOrigin() == gui::Point(0, 0));

      renderer_->pushClippingRectangle(gui::Rectangle(800, 600, 1200, 1000));
      TESTASSERT(renderer_->getClippingRectangle() == gui::Rectangle(1000, 1000, 1000, 1000));
      TESTASSERT(renderer_->getClippingOrigin() == gui::Point(0, 0));
      renderer_->popClippingRectangle();

    renderer_->popClippingRectangle();
  }
}
