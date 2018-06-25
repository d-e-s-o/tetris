// TestDecorator.cpp

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
#include "Widget1.hpp"
#include "Decorator1.hpp"
#include "Decorator2.hpp"
#include "TestDecorator.hpp"


namespace test
{
  TestDecorator::TestDecorator()
    : tst::TestCase<TestDecorator>(*this, "TestDecorator")
  {
    add(&TestDecorator::testCreate1);
    add(&TestDecorator::testCreate2);
    add(&TestDecorator::testInsertBefore1);
    add(&TestDecorator::testInsertBefore2);
    add(&TestDecorator::testInsertAfter1);
    add(&TestDecorator::testInsertAfter2);
    add(&TestDecorator::testRemove1);
    add(&TestDecorator::testRemove2);
    add(&TestDecorator::testRemove3);
  }

  void TestDecorator::setUp()
  {
    root_widget_ = new RootWidget1;
    widget_      = new Widget1;
    decorator_1_ = new Decorator1(*widget_);
    decorator_2_ = new Decorator1(*widget_);
    decorator_3_ = new Decorator1(*widget_);
    decorator_4_ = new Decorator2(*widget_);
    decorator_5_ = new Decorator1(*widget_);
  }

  void TestDecorator::tearDown()
  {
    delete decorator_5_;
    delete decorator_4_;
    delete decorator_3_;
    delete decorator_2_;
    delete decorator_1_;
    delete widget_;
    delete root_widget_;
  }

  void TestDecorator::testCreate1(tst::TestResult& result)
  {
    TESTASSERTOP(decorator_1_->getPrevious(), eq, nullptr);
    TESTASSERTOP(decorator_1_->getNext(), eq, nullptr);
    TESTASSERTOP(&decorator_1_->getFirst(), eq, decorator_1_);
    TESTASSERTOP(&decorator_1_->getLast(), eq, decorator_1_);

    TESTASSERTOP(decorator_2_->getPrevious(), eq, nullptr);
    TESTASSERTOP(decorator_2_->getNext(), eq, nullptr);
    TESTASSERTOP(&decorator_2_->getFirst(), eq, decorator_2_);
    TESTASSERTOP(&decorator_2_->getLast(), eq, decorator_2_);

    TESTASSERTOP(decorator_3_->getPrevious(), eq, nullptr);
    TESTASSERTOP(decorator_3_->getNext(), eq, nullptr);
    TESTASSERTOP(&decorator_3_->getFirst(), eq, decorator_3_);
    TESTASSERTOP(&decorator_3_->getLast(), eq, decorator_3_);

    TESTASSERTOP(decorator_5_->getPrevious(), eq, nullptr);
    TESTASSERTOP(decorator_5_->getNext(), eq, nullptr);
    TESTASSERTOP(&decorator_5_->getFirst(), eq, decorator_5_);
    TESTASSERTOP(&decorator_5_->getLast(), eq, decorator_5_);
  }

  void TestDecorator::testCreate2(tst::TestResult& result)
  {
    TESTASSERTOP(decorator_4_->getPrevious(), eq, nullptr);
    TESTASSERTOP(decorator_4_->getNext(), eq, &decorator_4_->decorator_1_);

    TESTASSERTOP(decorator_4_->decorator_1_.getPrevious(), eq, decorator_4_);
    TESTASSERTOP(decorator_4_->decorator_1_.getNext(), eq, &decorator_4_->decorator_2_);

    TESTASSERTOP(decorator_4_->decorator_2_.getPrevious(), eq, &decorator_4_->decorator_1_);
    TESTASSERTOP(decorator_4_->decorator_2_.getNext(), eq, &decorator_4_->decorator_3_);

    TESTASSERTOP(decorator_4_->decorator_3_.getPrevious(), eq, &decorator_4_->decorator_2_);
    TESTASSERTOP(decorator_4_->decorator_3_.getNext(), eq, nullptr);
  }

  void TestDecorator::testInsertBefore1(tst::TestResult& result)
  {
    // the order is important! (think about it, decorator1 and then 2 cannot work)
    decorator_2_->insertBefore(*decorator_3_);
    decorator_1_->insertBefore(*decorator_2_);

    TESTASSERTOP(decorator_1_->getPrevious(), eq, nullptr);
    TESTASSERTOP(decorator_1_->getNext(), eq, decorator_2_);

    TESTASSERTOP(decorator_2_->getPrevious(), eq, decorator_1_);
    TESTASSERTOP(decorator_2_->getNext(), eq, decorator_3_);

    TESTASSERTOP(decorator_3_->getPrevious(), eq, decorator_2_);
    TESTASSERTOP(decorator_3_->getNext(), eq, nullptr);
  }

  void TestDecorator::testInsertBefore2(tst::TestResult& result)
  {
    decorator_4_->insertBefore(*decorator_5_);
    decorator_3_->insertBefore(*decorator_4_);

    TESTASSERTOP(decorator_3_->getPrevious(), eq, nullptr);
    TESTASSERTOP(decorator_3_->getNext(), eq, decorator_4_);

    TESTASSERTOP(decorator_4_->getPrevious(), eq, decorator_3_);
    TESTASSERTOP(decorator_4_->getNext(), eq, &decorator_4_->decorator_1_);

    TESTASSERTOP(decorator_4_->decorator_1_.getPrevious(), eq, decorator_4_);
    TESTASSERTOP(decorator_4_->decorator_1_.getNext(), eq, &decorator_4_->decorator_2_);

    TESTASSERTOP(decorator_4_->decorator_2_.getPrevious(), eq, &decorator_4_->decorator_1_);
    TESTASSERTOP(decorator_4_->decorator_2_.getNext(), eq, &decorator_4_->decorator_3_);

    TESTASSERTOP(decorator_4_->decorator_3_.getPrevious(), eq, &decorator_4_->decorator_2_);
    TESTASSERTOP(decorator_4_->decorator_3_.getNext(), eq, decorator_5_);

    TESTASSERTOP(decorator_5_->getPrevious(), eq, &decorator_4_->getLast());
    TESTASSERTOP(decorator_5_->getNext(), eq, nullptr);
  }

  void TestDecorator::testInsertAfter1(tst::TestResult& result)
  {
    decorator_2_->insertAfter(*decorator_1_);
    decorator_3_->insertAfter(*decorator_2_);

    TESTASSERTOP(decorator_1_->getPrevious(), eq, nullptr);
    TESTASSERTOP(decorator_1_->getNext(), eq, decorator_2_);

    TESTASSERTOP(decorator_2_->getPrevious(), eq, decorator_1_);
    TESTASSERTOP(decorator_2_->getNext(), eq, decorator_3_);

    TESTASSERTOP(decorator_3_->getPrevious(), eq, decorator_2_);
    TESTASSERTOP(decorator_3_->getNext(), eq, nullptr);
  }

  void TestDecorator::testInsertAfter2(tst::TestResult& result)
  {
    decorator_4_->insertAfter(*decorator_3_);
    decorator_5_->insertAfter(*decorator_4_);

    TESTASSERTOP(decorator_3_->getPrevious(), eq, nullptr);
    TESTASSERTOP(decorator_3_->getNext(), eq, decorator_4_);

    TESTASSERTOP(decorator_4_->getPrevious(), eq, decorator_3_);
    TESTASSERTOP(decorator_4_->getNext(), eq, &decorator_4_->decorator_1_);

    TESTASSERTOP(decorator_4_->decorator_1_.getPrevious(), eq, decorator_4_);
    TESTASSERTOP(decorator_4_->decorator_1_.getNext(), eq, &decorator_4_->decorator_2_);

    TESTASSERTOP(decorator_4_->decorator_2_.getPrevious(), eq, &decorator_4_->decorator_1_);
    TESTASSERTOP(decorator_4_->decorator_2_.getNext(), eq, &decorator_4_->decorator_3_);

    TESTASSERTOP(decorator_4_->decorator_3_.getPrevious(), eq, &decorator_4_->decorator_2_);
    TESTASSERTOP(decorator_4_->decorator_3_.getNext(), eq, decorator_5_);

    TESTASSERTOP(decorator_5_->getPrevious(), eq, &decorator_4_->getLast());
    TESTASSERTOP(decorator_5_->getNext(), eq, nullptr);
  }

  void TestDecorator::testRemove1(tst::TestResult& result)
  {
    decorator_2_->insertAfter(*decorator_1_);
    decorator_3_->insertAfter(*decorator_2_);

    decorator_2_->remove();

    TESTASSERTOP(decorator_1_->getPrevious(), eq, nullptr);
    TESTASSERTOP(decorator_1_->getNext(), eq, decorator_3_);

    TESTASSERTOP(decorator_3_->getPrevious(), eq, decorator_1_);
    TESTASSERTOP(decorator_3_->getNext(), eq, nullptr);

    TESTASSERTOP(decorator_2_->getPrevious(), eq, nullptr);
    TESTASSERTOP(decorator_2_->getNext(), eq, nullptr);
  }

  void TestDecorator::testRemove2(tst::TestResult& result)
  {
    decorator_4_->insertAfter(*decorator_3_);
    decorator_5_->insertAfter(*decorator_4_);

    decorator_4_->remove();

    TESTASSERTOP(decorator_3_->getPrevious(), eq, nullptr);
    TESTASSERTOP(decorator_3_->getNext(), eq, decorator_5_);

    TESTASSERTOP(decorator_4_->getPrevious(), eq, nullptr);
    TESTASSERTOP(decorator_4_->getNext(), eq, &decorator_4_->decorator_1_);

    TESTASSERTOP(decorator_4_->decorator_3_.getNext(), eq, nullptr);

    TESTASSERTOP(decorator_5_->getPrevious(), eq, decorator_3_);
    TESTASSERTOP(decorator_5_->getNext(), eq, nullptr);
  }

  void TestDecorator::testRemove3(tst::TestResult& result)
  {
    decorator_4_->decorator_2_.remove();

    TESTASSERTOP(decorator_4_->decorator_1_.getPrevious(), eq, decorator_4_);
    TESTASSERTOP(decorator_4_->decorator_1_.getNext(), eq, &decorator_4_->decorator_3_);
    TESTASSERTOP(decorator_4_->decorator_2_.getPrevious(), eq, nullptr);
    TESTASSERTOP(decorator_4_->decorator_2_.getNext(), eq, nullptr);
    TESTASSERTOP(decorator_4_->decorator_3_.getPrevious(), eq, &decorator_4_->decorator_1_);
    TESTASSERTOP(decorator_4_->decorator_3_.getNext(), eq, nullptr);
  }
}
