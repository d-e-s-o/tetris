// TestQueue.hpp

/***************************************************************************
 *   Copyright (C) 2012 Daniel Mueller (deso@posteo.net)                   *
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

#ifndef CTRTESTQUEUE_HPP
#define CTRTESTQUEUE_HPP

#include <test/TestCase.hpp>
#include <container/Queue.hpp>


namespace test
{
  class TestQueue: public tst::TestCase<TestQueue>
  {
  public:
    TestQueue();

    void testPushFront1(tst::TestResult& result);
    void testPushBack1(tst::TestResult& result);
    void testPopFront1(tst::TestResult& result);
    void testPopBack1(tst::TestResult& result);

  protected:
    virtual void setUp();

  private:
    typedef ctr::Queue<int> Queue;

    Queue queue_;
  };
}


#endif
