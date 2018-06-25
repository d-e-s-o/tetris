// TestArray.cpp

/***************************************************************************
 *   Copyright (C) 2010-2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#include <type/Move.hpp>
#include <type/Util.hpp>

#include "TestArray.hpp"


namespace test
{
  namespace
  {
    int const array_1[]    = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9};
    int const array_1_size = typ::arraySize(array_1);

    int const array_2[]    = {20, 21, 22, 23, 24, 25, 26, 27, 28, 29};
    int const array_2_size = typ::arraySize(array_2);
  }


  TestArray::TestArray()
    : tst::TestCase<TestArray>(*this, "TestArray"),
      array_1_(),
      array_2_()
  {
    add(&TestArray::testCreation1);
    add(&TestArray::testCreation2);
    add(&TestArray::testMove1);
    add(&TestArray::testMove2);
    add(&TestArray::testGrow1);
    add(&TestArray::testReplace1);
    add(&TestArray::testReplace2);
    add(&TestArray::testReplace3);
    add(&TestArray::testReplace4);
    add(&TestArray::testReplace5);
    add(&TestArray::testReplace6);
    add(&TestArray::testAppend1);
    add(&TestArray::testAppend2);
    add(&TestArray::testInsert1);
    add(&TestArray::testInsert2);
    add(&TestArray::testInsert3);
    add(&TestArray::testRemove1);
  }

  void TestArray::setUp()
  {
    array_1_ = Array(&array_1[0], &array_1[0] + array_1_size);
    array_2_ = Array(&array_2[0], &array_2[0] + array_2_size);
  }

  void TestArray::testCreation1(tst::TestResult& result)
  {
    Array array;
    TESTASSERTOP(array.size(), eq, 0);
    TESTASSERTOP(array.capacity(), eq, 0);
  }

  void TestArray::testCreation2(tst::TestResult& result)
  {
    TESTASSERTOP(array_1_.size(), eq, 10);
    TESTASSERTOP(array_1_[0], eq, 0);
    TESTASSERTOP(array_1_[1], eq, 1);
    TESTASSERTOP(array_1_[2], eq, 2);
    TESTASSERTOP(array_1_[3], eq, 3);
    TESTASSERTOP(array_1_[4], eq, 4);
    TESTASSERTOP(array_1_[5], eq, 5);
    TESTASSERTOP(array_1_[6], eq, 6);
    TESTASSERTOP(array_1_[7], eq, 7);
    TESTASSERTOP(array_1_[8], eq, 8);
    TESTASSERTOP(array_1_[9], eq, 9);

    TESTASSERTOP(array_2_.size(), eq, 10);
    TESTASSERTOP(array_2_[0], eq, 20);
    TESTASSERTOP(array_2_[1], eq, 21);
    TESTASSERTOP(array_2_[2], eq, 22);
    TESTASSERTOP(array_2_[3], eq, 23);
    TESTASSERTOP(array_2_[4], eq, 24);
    TESTASSERTOP(array_2_[5], eq, 25);
    TESTASSERTOP(array_2_[6], eq, 26);
    TESTASSERTOP(array_2_[7], eq, 27);
    TESTASSERTOP(array_2_[8], eq, 28);
    TESTASSERTOP(array_2_[9], eq, 29);
  }

  void TestArray::testMove1(tst::TestResult& result)
  {
    Array array = typ::move(array_1_);

    TESTASSERTOP(array_1_.size(), eq, 0);
    TESTASSERTOP(array_1_.capacity(), eq, 0);

    TESTASSERTOP(array.size(), eq, 10);
    TESTASSERTOP(array[0], eq, 0);
    TESTASSERTOP(array[1], eq, 1);
    TESTASSERTOP(array[2], eq, 2);
    TESTASSERTOP(array[3], eq, 3);
    TESTASSERTOP(array[4], eq, 4);
    TESTASSERTOP(array[5], eq, 5);
    TESTASSERTOP(array[6], eq, 6);
    TESTASSERTOP(array[7], eq, 7);
    TESTASSERTOP(array[8], eq, 8);
    TESTASSERTOP(array[9], eq, 9);
  }

  void TestArray::testMove2(tst::TestResult& result)
  {
    Array array;
    TESTASSERTOP(array.size(), eq, 0);
    TESTASSERTOP(array.capacity(), eq, 0);

    array = typ::move(array_1_);

    TESTASSERTOP(array_1_.size(), eq, 0);
    TESTASSERTOP(array_1_.capacity(), eq, 0);

    TESTASSERTOP(array.size(), eq, 10);
    TESTASSERTOP(array[0], eq, 0);
    TESTASSERTOP(array[1], eq, 1);
    TESTASSERTOP(array[2], eq, 2);
    TESTASSERTOP(array[3], eq, 3);
    TESTASSERTOP(array[4], eq, 4);
    TESTASSERTOP(array[5], eq, 5);
    TESTASSERTOP(array[6], eq, 6);
    TESTASSERTOP(array[7], eq, 7);
    TESTASSERTOP(array[8], eq, 8);
    TESTASSERTOP(array[9], eq, 9);
  }

  void TestArray::testGrow1(tst::TestResult& result)
  {
    Array array;

    TESTASSERTOP(array.size(), eq, 0);

    array.grow(1, 2);
    TESTASSERTOP(array.size(), eq, 1);
    TESTASSERTOP(array[0], eq, 2);

    array.grow(2, 4);
    array.grow(1, 0);
    TESTASSERTOP(array.size(), eq, 2);
    TESTASSERTOP(array[0], eq, 2);
    TESTASSERTOP(array[1], eq, 4);
  }

  /**
   * @todo add tests for the expected return value
   */
  void TestArray::testReplace1(tst::TestResult& result)
  {
    array_1_.replace(array_1_.begin() + 5, array_1_.begin() + 10, array_1_.begin(), array_1_.begin() + 5);

    TESTASSERTOP(array_1_.size(), eq, 10);
    TESTASSERTOP(array_1_[0], eq, 0);
    TESTASSERTOP(array_1_[1], eq, 1);
    TESTASSERTOP(array_1_[2], eq, 2);
    TESTASSERTOP(array_1_[3], eq, 3);
    TESTASSERTOP(array_1_[4], eq, 4);
    TESTASSERTOP(array_1_[5], eq, 0);
    TESTASSERTOP(array_1_[6], eq, 1);
    TESTASSERTOP(array_1_[7], eq, 2);
    TESTASSERTOP(array_1_[8], eq, 3);
    TESTASSERTOP(array_1_[9], eq, 4);
  }

  /**
   * @todo add tests for the expected return value
   */
  void TestArray::testReplace2(tst::TestResult& result)
  {
    array_1_.replace(array_1_.begin(), array_1_.end(), array_1_.begin() + 2, array_1_.begin() + 7);

    TESTASSERTOP(array_1_.size(), eq, 5);
    TESTASSERTOP(array_1_[0], eq, 2);
    TESTASSERTOP(array_1_[1], eq, 3);
    TESTASSERTOP(array_1_[2], eq, 4);
    TESTASSERTOP(array_1_[3], eq, 5);
    TESTASSERTOP(array_1_[4], eq, 6);
  }

  /**
   * @todo add tests for the expected return value
   */
  void TestArray::testReplace3(tst::TestResult& result)
  {
    array_1_.replace(array_1_.begin(), array_1_.begin(), array_1_.begin(), array_1_.end());

    TESTASSERTOP(array_1_.size(), eq, 20);
    TESTASSERTOP(array_1_[0] , eq, 0);
    TESTASSERTOP(array_1_[1] , eq, 1);
    TESTASSERTOP(array_1_[2] , eq, 2);
    TESTASSERTOP(array_1_[3] , eq, 3);
    TESTASSERTOP(array_1_[4] , eq, 4);
    TESTASSERTOP(array_1_[5] , eq, 5);
    TESTASSERTOP(array_1_[6] , eq, 6);
    TESTASSERTOP(array_1_[7] , eq, 7);
    TESTASSERTOP(array_1_[8] , eq, 8);
    TESTASSERTOP(array_1_[9] , eq, 9);
    TESTASSERTOP(array_1_[10], eq, 0);
    TESTASSERTOP(array_1_[11], eq, 1);
    TESTASSERTOP(array_1_[12], eq, 2);
    TESTASSERTOP(array_1_[13], eq, 3);
    TESTASSERTOP(array_1_[14], eq, 4);
    TESTASSERTOP(array_1_[15], eq, 5);
    TESTASSERTOP(array_1_[16], eq, 6);
    TESTASSERTOP(array_1_[17], eq, 7);
    TESTASSERTOP(array_1_[18], eq, 8);
    TESTASSERTOP(array_1_[19], eq, 9);
  }

  /**
   * @todo add tests for the expected return value
   */
  void TestArray::testReplace4(tst::TestResult& result)
  {
    array_1_.replace(array_1_.begin(), array_1_.end(), array_2_.begin(), array_2_.end());

    TESTASSERTOP(array_1_.size(), eq, 10);
    TESTASSERTOP(array_1_[0], eq, 20);
    TESTASSERTOP(array_1_[1], eq, 21);
    TESTASSERTOP(array_1_[2], eq, 22);
    TESTASSERTOP(array_1_[3], eq, 23);
    TESTASSERTOP(array_1_[4], eq, 24);
    TESTASSERTOP(array_1_[5], eq, 25);
    TESTASSERTOP(array_1_[6], eq, 26);
    TESTASSERTOP(array_1_[7], eq, 27);
    TESTASSERTOP(array_1_[8], eq, 28);
    TESTASSERTOP(array_1_[9], eq, 29);
  }

  /**
   * @todo add tests for the expected return value
   */
  void TestArray::testReplace5(tst::TestResult& result)
  {
    array_1_.replace(array_1_.begin(), array_1_.end(), array_2_.begin() + 1, array_2_.begin() + 6);

    TESTASSERTOP(array_1_.size(), eq, 5);
    TESTASSERTOP(array_1_[0], eq, 21);
    TESTASSERTOP(array_1_[1], eq, 22);
    TESTASSERTOP(array_1_[2], eq, 23);
    TESTASSERTOP(array_1_[3], eq, 24);
    TESTASSERTOP(array_1_[4], eq, 25);
  }

  /**
   * @todo add tests for the expected return value
   */
  void TestArray::testReplace6(tst::TestResult& result)
  {
    array_1_.replace(array_1_.begin() + 1, array_1_.begin() + 6, array_2_.begin(), array_2_.end());

    TESTASSERTOP(array_1_.size(), eq, 15);
    TESTASSERTOP(array_1_[0] , eq, 0);
    TESTASSERTOP(array_1_[1] , eq, 20);
    TESTASSERTOP(array_1_[2] , eq, 21);
    TESTASSERTOP(array_1_[3] , eq, 22);
    TESTASSERTOP(array_1_[4] , eq, 23);
    TESTASSERTOP(array_1_[5] , eq, 24);
    TESTASSERTOP(array_1_[6] , eq, 25);
    TESTASSERTOP(array_1_[7] , eq, 26);
    TESTASSERTOP(array_1_[8] , eq, 27);
    TESTASSERTOP(array_1_[9] , eq, 28);
    TESTASSERTOP(array_1_[10], eq, 29);
    TESTASSERTOP(array_1_[11], eq, 6);
    TESTASSERTOP(array_1_[12], eq, 7);
    TESTASSERTOP(array_1_[13], eq, 8);
    TESTASSERTOP(array_1_[14], eq, 9);
  }

  /**
   * @todo add tests for the expected return value
   */
  void TestArray::testAppend1(tst::TestResult& result)
  {
    append(array_1_, 20);

    TESTASSERTOP(array_1_.size(), eq, 11);
    TESTASSERTOP(array_1_[10], eq, 20);
  }

  /**
   * @todo add tests for the expected return value
   */
  void TestArray::testAppend2(tst::TestResult& result)
  {
    append(array_1_, array_2_.begin(), array_2_.end());

    TESTASSERTOP(array_1_.size(), eq, 20);
    TESTASSERTOP(array_1_[10], eq, 20);
    TESTASSERTOP(array_1_[19], eq, 29);
  }

  /**
   * @todo add tests for the expected return value
   */
  void TestArray::testInsert1(tst::TestResult& result)
  {
    insert(array_1_, 0, 20);

    TESTASSERTOP(array_1_.size(), eq, 11);
    TESTASSERTOP(array_1_[0] , eq, 20);
    TESTASSERTOP(array_1_[1] , eq, 0);
    TESTASSERTOP(array_1_[10], eq, 9);

    insert(array_1_, 5, 30);

    TESTASSERTOP(array_1_.size(), eq, 12);
    TESTASSERTOP(array_1_[0] , eq, 20);
    TESTASSERTOP(array_1_[1] , eq, 0);
    TESTASSERTOP(array_1_[4] , eq, 3);
    TESTASSERTOP(array_1_[5] , eq, 30);
    TESTASSERTOP(array_1_[6] , eq, 4);
    TESTASSERTOP(array_1_[11], eq, 9);

    insert(array_1_, 12, 40);

    TESTASSERTOP(array_1_.size(), eq, 13);
    TESTASSERTOP(array_1_[0] , eq, 20);
    TESTASSERTOP(array_1_[11], eq, 9);
    TESTASSERTOP(array_1_[12], eq, 40);
  }

  /**
   * @todo add tests for the expected return value
   */
  void TestArray::testInsert2(tst::TestResult& result)
  {
    insert(array_1_, 0, array_2_.begin(), array_2_.end());

    TESTASSERTOP(array_1_.size(), eq, 20);
    TESTASSERTOP(array_1_[0] , eq, 20);
    TESTASSERTOP(array_1_[9] , eq, 29);
    TESTASSERTOP(array_1_[10], eq, 0);
    TESTASSERTOP(array_1_[19], eq, 9);
  }

  /**
   * @todo add tests for the expected return value
   */
  void TestArray::testInsert3(tst::TestResult& result)
  {
    Array array(6);
    append(array, 1337);
    append(array, 1338);
    append(array, 1339);
    insert(array, 0, 1336);

    TESTASSERTOP(array.size(), eq, 4);
    TESTASSERTOP(array[0], eq, 1336);
    TESTASSERTOP(array[1], eq, 1337);
    TESTASSERTOP(array[2], eq, 1338);
    TESTASSERTOP(array[3], eq, 1339);
  }

  /**
   * @todo add tests for the expected return value
   */
  void TestArray::testRemove1(tst::TestResult& result)
  {
    remove(array_1_, 0, 1);

    TESTASSERTOP(array_1_.size(), eq, 9);
    TESTASSERTOP(array_1_[0], eq, 1);
    TESTASSERTOP(array_1_[8], eq, 9);

    remove(array_1_, 8, 1);

    TESTASSERTOP(array_1_.size(), eq, 8);
    TESTASSERTOP(array_1_[0], eq, 1);
    TESTASSERTOP(array_1_[7], eq, 8);

    remove(array_1_, 2, 3);

    TESTASSERTOP(array_1_.size(), eq, 5);
    TESTASSERTOP(array_1_[0], eq, 1);
    TESTASSERTOP(array_1_[1], eq, 2);
    TESTASSERTOP(array_1_[2], eq, 6);
    TESTASSERTOP(array_1_[3], eq, 7);
    TESTASSERTOP(array_1_[4], eq, 8);
  }
}
