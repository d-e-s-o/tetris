// TestStoneDropper.hpp

/***************************************************************************
 *   Copyright (C) 2013 Daniel Mueller (deso@posteo.net)                   *
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

#ifndef TESTTESTSTONEDROPPER_HPP
#define TESTTESTSTONEDROPPER_HPP

#include <test/TestCase.hpp>
#include <tetris/game/ai/StoneDropper.hpp>

#include "test/StoneFactory2.hpp"


namespace test
{
  /**
   * Unit test for tetris/game/ai/StoneDropper.hpp
   */
  class TestStoneDropper: public tst::TestCase<TestStoneDropper>
  {
  public:
    TestStoneDropper();

    void testDropSingle1(tst::TestResult& result);
    void testDropSingle2(tst::TestResult& result);
    void testDropSingle3(tst::TestResult& result);

    void testDropMultiple1(tst::TestResult& result);
    void testDropMultiple2(tst::TestResult& result);
    void testDropMultiple3(tst::TestResult& result);
    void testDropMultiple4(tst::TestResult& result);
    void testDropMultiple5(tst::TestResult& result);

  protected:
    virtual void setUp();

  private:
    StoneTypeManager type_manager_;
    StoneFactory2    factory_;

    ttrs::ai::StoneDropper dropper_;
    ttrs::ai::StoneList    stones_;

    template<size_t Width, size_t Height>
    bool testSearcher(tst::TestResult& result,
                      uint_t (&start_template)[Height][Width],
                      uint_t (&goal_template)[Height][Width]);
  };
}


#endif
