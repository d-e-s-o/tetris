// TestState.cpp

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

#include <tetris/game/ai/Stone.hpp>
using namespace ttrs::ai;

#include "test/TestState.hpp"


namespace test
{
  TestState::TestState()
    : tst::TestCase<TestState>(*this, "TestState"),
      type_manager_(),
      factory_(type_manager_)
  {
    add(&TestState::testCreate1);
    add(&TestState::testCompare1);
  }

  void TestState::setUp()
  {
    type_manager_ = StoneTypeManager();
    factory_      = StoneFactory2(type_manager_);

    state_ = State::initial(Field(10, 10), factory_.createAndMoveStone(STONE_2_LINE, 1, 1));
  }

  void TestState::testCreate1(tst::TestResult& result)
  {
    TESTASSERTM(false, "implement me!");
  }

  void TestState::testCompare1(tst::TestResult& result)
  {
    TESTASSERT(!State::compare(*state_, *state_));

    {
      StatePointer copy = State::derive(state_, Action::ROTATE_LEFT);
      TESTASSERT( State::compare(*state_, *copy));
      TESTASSERT(!State::compare(*copy, *state_));
    }

    {
      StatePointer copy = State::derive(state_, Action::MOVE_RIGHT);
      TESTASSERT( State::compare(*state_, *copy));
      TESTASSERT(!State::compare(*copy, *state_));
    }
  }
}
