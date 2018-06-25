// TestAbstractField.cpp

/***************************************************************************
 *   Copyright (C) 2013-2014 Daniel Mueller (deso@posteo.net)              *
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

#include "test/TestAbstractField.hpp"


namespace test
{
  TestAbstractField::TestAbstractField()
    : tst::TestCase<TestAbstractField>(*this, "TestAbstractField"),
      field_()
  {
    add(&TestAbstractField::testWidth1);
    add(&TestAbstractField::testHeight1);
    add(&TestAbstractField::testAt1);
    add(&TestAbstractField::testAt2);
    add(&TestAbstractField::testLineComplete1);
    add(&TestAbstractField::testLineComplete2);
    add(&TestAbstractField::testClearLine1);
  }

  void TestAbstractField::setUp()
  {
    field_ = Field1();
  }

  void TestAbstractField::testWidth1(tst::TestResult& result)
  {
    TESTASSERTOP(field_.width(), eq, 6);
  }

  void TestAbstractField::testHeight1(tst::TestResult& result)
  {
    TESTASSERTOP(field_.height(), eq, 9);
  }

  void TestAbstractField::testAt1(tst::TestResult& result)
  {
    for (ttrs::coordinate_t x = 0; x < field_.width(); x++)
    {
      for (ttrs::coordinate_t y = 0; y < field_.height(); y++)
        TESTASSERT(!field_[x][y]);
    }
  }

  void TestAbstractField::testAt2(tst::TestResult& result)
  {
    field_[5][3] = true;
    TESTASSERT(field_[5][3]);

    field_[5][3] = false;
    TESTASSERT(!field_[5][3]);
  }

  void TestAbstractField::testLineComplete1(tst::TestResult& result)
  {
    for (ttrs::coordinate_t y = 0; y < field_.height(); y++)
      TESTASSERT(!field_.lineComplete(y));
  }

  void TestAbstractField::testLineComplete2(tst::TestResult& result)
  {
    for (ttrs::coordinate_t x = 0; x < field_.width(); x++)
      field_[x][1] = true;

    for (ttrs::coordinate_t y = 0; y < field_.height(); y++)
      TESTASSERT(field_.lineComplete(y) == (y == 1));

    for (ttrs::coordinate_t x = 0; x < field_.width(); x++)
      field_[x][5] = true;

    for (ttrs::coordinate_t y = 0; y < field_.height(); y++)
      TESTASSERT(field_.lineComplete(y) == (y == 1 || y == 5));
  }

  void TestAbstractField::testClearLine1(tst::TestResult& result)
  {
    for (ttrs::coordinate_t x = 0; x < field_.width(); x++)
    {
      field_[x][2] = true;
      field_[x][4] = true;
      field_[x][5] = true;
      field_[x][6] = true;
    }

    field_.clearLine(2);

    for (ttrs::coordinate_t y = 0; y < field_.height(); y++)
      TESTASSERT(field_.lineComplete(y) == (y == 3 || y == 4 || y == 5));

    field_.clearLine(2);

    for (ttrs::coordinate_t y = 0; y < field_.height(); y++)
      TESTASSERT(field_.lineComplete(y) == (y == 2 || y == 3 || y == 4));

    field_.clearLine(3);

    for (ttrs::coordinate_t y = 0; y < field_.height(); y++)
      TESTASSERT(field_.lineComplete(y) == (y == 2 || y == 3));

    field_.clearLine(3);

    for (ttrs::coordinate_t y = 0; y < field_.height(); y++)
      TESTASSERT(field_.lineComplete(y) == (y == 2));

    field_.clearLine(2);

    for (ttrs::coordinate_t y = 0; y < field_.height(); y++)
      TESTASSERT(!field_.lineComplete(y));
  }
}
