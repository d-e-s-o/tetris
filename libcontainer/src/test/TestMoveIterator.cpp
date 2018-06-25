// TestMoveIterator.cpp

/***************************************************************************
 *   Copyright (C) 2012,2014 Daniel Mueller (deso@posteo.net)              *
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

#include <util/Algorithm.hpp>
#include <container/MoveIterator.hpp>

#include "Moveable.hpp"
#include "TestMoveIterator.hpp"


namespace test
{
  TestMoveIterator::TestMoveIterator()
    : tst::TestCase<TestMoveIterator>(*this, "TestMoveIterator")
  {
    add(&TestMoveIterator::testCopy);
  }

  void TestMoveIterator::testCopy(tst::TestResult& result)
  {
    Moveable movesables1[5] = {Moveable(1),  Moveable(2),  Moveable(3),  Moveable(4), Moveable(5)};
    Moveable movesables2[9] = {Moveable(6),  Moveable(7),  Moveable(8),  Moveable(9), Moveable(10),
                               Moveable(11), Moveable(12), Moveable(13), Moveable(14)};

    utl::copy(ctr::makeMoveIterator(&movesables1[0]),
              ctr::makeMoveIterator(&movesables1[5]),
              ctr::makeMoveIterator(&movesables2[1]));

    TESTASSERTOP(movesables1[0].value_, eq, 0);
    TESTASSERTOP(movesables1[1].value_, eq, 0);
    TESTASSERTOP(movesables1[2].value_, eq, 0);
    TESTASSERTOP(movesables1[3].value_, eq, 0);
    TESTASSERTOP(movesables1[4].value_, eq, 0);

    TESTASSERTOP(movesables2[0].value_, eq, 6);
    TESTASSERTOP(movesables2[1].value_, eq, 1);
    TESTASSERTOP(movesables2[2].value_, eq, 2);
    TESTASSERTOP(movesables2[3].value_, eq, 3);
    TESTASSERTOP(movesables2[4].value_, eq, 4);
    TESTASSERTOP(movesables2[5].value_, eq, 5);
    TESTASSERTOP(movesables2[6].value_, eq, 12);
    TESTASSERTOP(movesables2[7].value_, eq, 13);
    TESTASSERTOP(movesables2[8].value_, eq, 14);
  }
}
