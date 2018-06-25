// TestStoneDropper.cpp

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

#include <container/ArrayFunctions.hpp>

#include <tetris/game/FieldFunctions.hpp>
#include <tetris/game/ai/Stone.hpp>
#include <tetris/game/ai/Field.hpp>
using namespace ttrs;
using namespace ttrs::ai;

#include "test/TestStoneDropper.hpp"


namespace test
{
  namespace
  {
    /**
     * @param fieldTemplate
     * @return
     */
    template<size_t Width, size_t Height>
    Field createField(uint_t (&fieldTemplate)[Height][Width])
    {
      Field field(Width, Height);

      for (size_t x = 0; x < Width; x++)
      {
        for (size_t y = 0; y < Height; y++)
          field[x][y] = fieldTemplate[Height - 1 - y][x] != 0;
      }
      return field;
    }

    /**
     * @param result
     * @param field
     * @param stones
     * @param actions
     * @return
     */
    Field applyActions(tst::TestResult& result, Field const& field, StoneList const& stones, ActionList const& actions)
    {
      TESTASSERTOP(stones.size(), gt, 0);
      TESTASSERTOP(actions.size(), gt, 0);

      size_t stone_index = 0;
      size_t action_index = 0;

      Field new_field = field;
      Stone stone = stones[stone_index];
      Action action = actions[action_index];

      while (true)
      {
        TESTASSERT(!stone.collidesWith(new_field));
        action_index++;

        if (action == Action::MERGE)
        {
          TESTASSERT(performOnCopy(Action::MOVE_DOWN, stone).collidesWith(new_field));

          stone.mergeWith(new_field);
          clearLines(new_field, stone);
          stone_index++;

          // in the non-error case this should be the way we exit the loop
          if (stone_index >= stones.size())
            break;
          else
            stone = stones[stone_index];
        }
        else
          perform(action, stone);

        if (action_index >= actions.size())
          break;
        else
          action = actions[action_index];
      }

      TESTASSERTOP(stone_index, eq, stones.size());
      TESTASSERTOP(action_index, eq, actions.size());
      return new_field;
    }


    /**
     * @param lhs
     * @param rhs
     * @return
     */
    bool operator ==(Field const& lhs, Field const& rhs)
    {
      if (lhs.width() != rhs.width() || lhs.height() != rhs.height())
        return false;

      for (ttrs::coordinate_t x = 0; x < lhs.width(); x++)
      {
        for (ttrs::coordinate_t y = 0; y < lhs.height(); y++)
        {
          if (lhs[x][y] != rhs[x][y])
            return false;
        }
      }
      return true;
    }
  }


  TestStoneDropper::TestStoneDropper()
    : tst::TestCase<TestStoneDropper>(*this, "TestStoneDropper"),
      type_manager_(),
      factory_(type_manager_),
      dropper_(),
      stones_()
  {
    add(&TestStoneDropper::testDropSingle1);
    add(&TestStoneDropper::testDropSingle2);
    add(&TestStoneDropper::testDropSingle3);
    add(&TestStoneDropper::testDropMultiple1);
    add(&TestStoneDropper::testDropMultiple2);
    add(&TestStoneDropper::testDropMultiple3);
    add(&TestStoneDropper::testDropMultiple4);
    add(&TestStoneDropper::testDropMultiple5);
  }

  void TestStoneDropper::setUp()
  {
    type_manager_ = StoneTypeManager();
    factory_      = StoneFactory2(type_manager_);
    dropper_      = StoneDropper();
    stones_       = StoneList();
  }

  void TestStoneDropper::testDropSingle1(tst::TestResult& result)
  {
    uint_t start_field[9][7] =
    {
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,1,1,1,1,1,1},
      {0,1,1,1,1,1,1},
      {0,1,1,1,1,1,1},
      {0,1,1,1,1,1,1},
      {0,1,1,1,1,1,1}
    };

    uint_t goal_field[9][7] =
    {
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,1,1,1,1,1,1},
      {0,1,1,1,1,1,1},
      {0,1,1,1,1,1,1},
      {0,1,1,1,1,1,1}
    };

    ctr::append(stones_, factory_.createAndMoveStone(STONE_1_SINGLE, 0, 8));

    TESTASSERT(testSearcher(result, start_field, goal_field));
  }

  void TestStoneDropper::testDropSingle2(tst::TestResult& result)
  {
    uint_t start_field[9][7] =
    {
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,1,1,1,1,1,1},
      {0,1,1,1,1,1,1},
      {0,1,1,1,1,1,1},
      {0,1,1,1,1,1,1},
      {0,1,1,1,1,1,1}
    };

    uint_t goal_field[9][7] =
    {
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,1,1,1,1,1,1}
    };

    ctr::append(stones_, factory_.createAndMoveStone(STONE_4_LINE, 6, 5));

    TESTASSERT(testSearcher(result, start_field, goal_field));
  }

  void TestStoneDropper::testDropSingle3(tst::TestResult& result)
  {
    uint_t start_field[9][7] =
    {
      {1,1,1,1,1,1,1},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0}
    };

    ctr::append(stones_, factory_.createAndMoveStone(STONE_1_SINGLE, 4, 8));

    auto actions = dropper_.search(createField(start_field), stones_);
    TESTASSERTOP(actions.size(), eq, 0);
  }

  void TestStoneDropper::testDropMultiple1(tst::TestResult& result)
  {
    uint_t start_field[9][7] =
    {
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {1,0,1,1,1,1,0},
      {1,0,1,1,1,1,0},
      {1,0,1,1,1,1,0},
      {1,0,1,1,1,1,0},
      {1,0,1,1,1,1,0}
    };

    uint_t goal_field[9][7] =
    {
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {1,0,1,1,1,1,0}
    };

    ctr::append(stones_, factory_.createAndMoveStone(STONE_4_LINE, 4, 5));
    ctr::append(stones_, factory_.createAndMoveStone(STONE_4_LINE, 4, 5));

    TESTASSERT(testSearcher(result, start_field, goal_field));
  }

  void TestStoneDropper::testDropMultiple2(tst::TestResult& result)
  {
    uint_t start_field[9][7] =
    {
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {1,1,1,0,1,1,1},
      {1,1,1,0,1,1,1},
      {1,1,1,0,1,1,1},
      {1,1,1,0,1,1,1},
      {1,1,1,0,1,1,1}
    };

    uint_t goal_field[9][7] =
    {
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {1,1,1,0,1,1,1},
      {1,1,1,0,1,1,1},
      {1,1,1,0,1,1,1}
    };

    ctr::append(stones_, factory_.createAndMoveStone(STONE_1_SINGLE, 0, 8));
    ctr::append(stones_, factory_.createAndMoveStone(STONE_1_SINGLE, 5, 8));

    TESTASSERT(testSearcher(result, start_field, goal_field));
  }

  void TestStoneDropper::testDropMultiple3(tst::TestResult& result)
  {
    uint_t start_field[9][7] =
    {
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {1,1,1,0,1,1,1},
      {1,1,1,0,1,1,1},
      {1,1,1,0,1,1,1},
      {1,1,1,0,1,1,1},
      {1,1,1,0,1,1,1}
    };

    uint_t goal_field[9][7] =
    {
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {1,1,1,0,1,1,1},
      {1,1,1,0,1,1,1}
    };

    ctr::append(stones_, factory_.createAndMoveStone(STONE_1_SINGLE, 0, 8));
    ctr::append(stones_, factory_.createAndMoveStone(STONE_1_SINGLE, 6, 8));
    ctr::append(stones_, factory_.createAndMoveStone(STONE_1_SINGLE, 3, 8));

    TESTASSERT(testSearcher(result, start_field, goal_field));
  }

  void TestStoneDropper::testDropMultiple4(tst::TestResult& result)
  {
    uint_t start_field[9][7] =
    {
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {1,1,1,1,0,0,1},
      {1,1,1,1,0,0,1},
      {1,1,1,0,0,0,1},
      {1,1,0,0,0,0,1},
      {1,1,1,0,0,0,1}
    };

    uint_t goal_field[9][7] =
    {
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0},
      {1,1,1,1,0,0,1},
      {1,1,1,1,0,0,1},
      {1,1,1,1,0,0,1}
    };

    ctr::append(stones_, factory_.createAndMoveStone(STONE_4_TRIANGLE, 0, 7));
    ctr::append(stones_, factory_.createAndMoveStone(STONE_4_BLOCK, 0, 7));

    TESTASSERT(testSearcher(result, start_field, goal_field));
  }

  void TestStoneDropper::testDropMultiple5(tst::TestResult& result)
  {
    uint_t start_field[12][14] =
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {1,1,1,1,1,1,1,1,1,1,1,1,1,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {0,0,0,0,0,0,0,0,0,0,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,0,1,1,1,1},
      {1,1,1,0,0,0,0,0,0,0,1,1,1,1},
      {1,1,1,0,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,0,1,1,1,1,1,1,1,1,1,1}
    };

    uint_t goal_field[12][14] =
    {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {1,1,1,1,1,1,1,1,1,1,1,1,1,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {0,0,0,0,0,0,0,0,0,0,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,0,1,1,1,1},
      {1,1,1,0,0,0,0,0,0,0,1,1,1,1}
    };

    ctr::append(stones_, factory_.createAndMoveStone(STONE_1_SINGLE, 0, 11));
    ctr::append(stones_, factory_.createAndMoveStone(STONE_1_SINGLE, 0, 11));

    TESTASSERT(testSearcher(result, start_field, goal_field));
  }

  /**
   * @param result
   * @param start_template
   * @param goal_template
   * @return
   */
  template<size_t Width, size_t Height>
  bool TestStoneDropper::testSearcher(tst::TestResult& result,
                                      uint_t (&start_template)[Height][Width],
                                      uint_t (&goal_template)[Height][Width])
  {
    auto start_field = createField(start_template);
    auto goal_field = createField(goal_template);
    auto actions = dropper_.search(start_field, stones_);
    auto result_field = applyActions(result, start_field, stones_, actions);

    return result_field == goal_field;
  }
}
