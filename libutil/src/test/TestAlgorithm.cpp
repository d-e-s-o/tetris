// TestAlgorithm.cpp

/***************************************************************************
 *   Copyright (C) 2010-2014 Daniel Mueller (deso@posteo.net)              *
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

#include "TestAlgorithm.hpp"


namespace test
{
  namespace
  {
    /**
     * A class representing some iterator used for testing correct behavior of the 'includes'
     * function in conjunction with iterators that might just wrap built-in types.
     */
    template<typename T>
    struct Iterator
    {
      /**
       * @param pointer some pointer
       */
      Iterator(T* pointer)
        : pointer_(pointer)
      {
      }

      /**
       * @return dereferenced pointer
       */
      T& operator *() const
      {
        return *pointer_;
      }

      T* pointer_;
    };


    /**
     * @param pointer some pointer
     * @return iterator object wrapping the given pointer
     */
    template<typename T>
    Iterator<T> iterator(T* pointer)
    {
      return Iterator<T>(pointer);
    }
  }


  TestAlgorithm::TestAlgorithm()
    : tst::TestCase<TestAlgorithm>(*this, "TestAlgorithm"),
      source_begin_(source_),
      source_end_(source_ + SIZE),
      destination_begin_(destination_),
      destination_end_(destination_ + SIZE)
  {
    add(&TestAlgorithm::testIncludes1);
    add(&TestAlgorithm::testIncludes2);
    add(&TestAlgorithm::testFill);
    add(&TestAlgorithm::testFind);
    add(&TestAlgorithm::testFindNot);
    add(&TestAlgorithm::testFindBinary1);
    add(&TestAlgorithm::testFindBinary2);
    add(&TestAlgorithm::testCopy1);
    add(&TestAlgorithm::testCopy2);
    add(&TestAlgorithm::testCopy3);
  }

  void TestAlgorithm::setUp()
  {
    for (int* it = source_begin_; it != source_end_; ++it)
      *it = 0;

    for (int* it = destination_begin_; it != destination_end_; ++it)
      *it = 0;
  }

  void TestAlgorithm::testIncludes1(tst::TestResult& result)
  {
    TESTASSERT( utl::includes(source_begin_, source_end_, source_begin_));
    TESTASSERT( utl::includes(source_begin_, source_end_, source_begin_ + 1));
    TESTASSERT( utl::includes(source_begin_, source_end_, source_end_));
    TESTASSERT(!utl::includes(source_begin_, source_end_, source_end_ + 1));
  }

  void TestAlgorithm::testIncludes2(tst::TestResult& result)
  {
    auto begin  = iterator(source_begin_);
    auto middle = iterator(source_begin_ + 10);
    auto end    = iterator(source_end_);
    auto after  = iterator(source_end_ + 1);

    TESTASSERT( utl::includes(source_begin_, source_end_, begin));
    TESTASSERT( utl::includes(source_begin_, source_end_, middle));
    TESTASSERT( utl::includes(source_begin_, source_end_, end));
    TESTASSERT(!utl::includes(source_begin_, source_end_, after));

    TESTASSERT( utl::includes(begin, end, source_begin_));
    TESTASSERT( utl::includes(begin, end, source_end_));
    TESTASSERT(!utl::includes(begin, end, source_end_ + 1));
  }

  void TestAlgorithm::testFill(tst::TestResult& result)
  {
    TESTASSERTOP(utl::find(source_begin_, source_end_, 0), eq, source_begin_);

    utl::fill(source_begin_, source_end_, 1);
    TESTASSERTOP(utl::find(source_begin_, source_end_, 0), eq, source_end_);

    utl::fill(source_begin_ + 20, source_end_ - 70, 0);
    TESTASSERTOP(utl::find(source_begin_,      source_end_, 0), eq, source_begin_ + 20);
    TESTASSERTOP(utl::find(source_begin_ + 21, source_end_, 1), eq, source_end_ - 70);
  }

  void TestAlgorithm::testFind(tst::TestResult& result)
  {
    TESTASSERTOP(utl::find(source_begin_, source_end_, 1), eq, source_end_);

    *(source_end_ - 1) = 1;
    TESTASSERTOP(utl::find(source_begin_, source_end_, 1), eq, source_end_ - 1);

    *(source_end_ - 16) = 1;
    TESTASSERTOP(utl::find(source_begin_, source_end_, 1), eq, source_end_ - 16);

    *(source_begin_ + 2) = 1;
    TESTASSERTOP(utl::find(source_begin_, source_end_, 1), eq, source_begin_ + 2);

    *(source_begin_) = 1;
    TESTASSERTOP(utl::find(source_begin_, source_end_, 1), eq, source_begin_);

    TESTASSERTOP(utl::find(source_begin_ + 3, source_end_, 1), eq, source_end_ - 16);
  }

  void TestAlgorithm::testFindNot(tst::TestResult& result)
  {
    TESTASSERTOP(utl::findNot(source_begin_, source_end_, 0), eq, source_end_);

    *(source_end_ - 1) = 1;
    TESTASSERTOP(utl::findNot(source_begin_, source_end_, 0), eq, source_end_ - 1);

    *(source_end_ - 16) = 1;
    TESTASSERTOP(utl::findNot(source_begin_, source_end_, 0), eq, source_end_ - 16);

    *(source_begin_ + 2) = 1;
    TESTASSERTOP(utl::findNot(source_begin_, source_end_, 0), eq, source_begin_ + 2);

    *(source_begin_) = 1;
    TESTASSERTOP(utl::findNot(source_begin_, source_end_, 0), eq, source_begin_);

    TESTASSERTOP(utl::findNot(source_begin_ + 3, source_end_, 0), eq, source_end_ - 16);
  }

  void TestAlgorithm::testFindBinary1(tst::TestResult& result)
  {
    int* p = destination_begin_;

    TESTASSERTOP(utl::findBinary(p, p, 0), eq, p);

    *p = 1;
    TESTASSERTOP(utl::findBinary(p, p + 1, 0), eq, p);
    TESTASSERTOP(utl::findBinary(p, p + 1, 1), eq, p);
    TESTASSERTOP(utl::findBinary(p, p + 1, 2), eq, p + 1);
  }

  void TestAlgorithm::testFindBinary2(tst::TestResult& result)
  {
    int* end = destination_begin_;
    *end++ = 0;
    *end++ = 7;
    *end++ = 12;
    *end++ = 15;
    *end++ = 16;
    *end++ = 2000;
    *end++ = 14444;

    TESTASSERTOP(utl::findBinary(destination_begin_, end,     0), eq, destination_begin_);
    TESTASSERTOP(utl::findBinary(destination_begin_, end,     1), eq, destination_begin_ + 1);
    TESTASSERTOP(utl::findBinary(destination_begin_, end,     4), eq, destination_begin_ + 1);
    TESTASSERTOP(utl::findBinary(destination_begin_, end,     7), eq, destination_begin_ + 1);
    TESTASSERTOP(utl::findBinary(destination_begin_, end,     8), eq, destination_begin_ + 2);
    TESTASSERTOP(utl::findBinary(destination_begin_, end,    12), eq, destination_begin_ + 2);
    TESTASSERTOP(utl::findBinary(destination_begin_, end,    13), eq, destination_begin_ + 3);
    TESTASSERTOP(utl::findBinary(destination_begin_, end,    15), eq, destination_begin_ + 3);
    TESTASSERTOP(utl::findBinary(destination_begin_, end,    16), eq, destination_begin_ + 4);
    TESTASSERTOP(utl::findBinary(destination_begin_, end,  1000), eq, destination_begin_ + 5);
    TESTASSERTOP(utl::findBinary(destination_begin_, end,  2000), eq, destination_begin_ + 5);
    TESTASSERTOP(utl::findBinary(destination_begin_, end,  2001), eq, destination_begin_ + 6);
    TESTASSERTOP(utl::findBinary(destination_begin_, end, 14444), eq, destination_begin_ + 6);
    TESTASSERTOP(utl::findBinary(destination_begin_, end, 30000), eq, destination_begin_ + 7);
  }

  void TestAlgorithm::testCopy1(tst::TestResult& result)
  {
    // simply copy from src to dst
    TESTASSERTOP(utl::find(destination_begin_, destination_end_, 0), eq, destination_begin_);

    utl::fill(source_begin_ + 1, source_end_ - 1, 1);
    utl::copy(source_begin_, source_end_, destination_begin_);

    TESTASSERTOP(utl::find(destination_begin_,     destination_end_, 0), eq, destination_begin_);
    TESTASSERTOP(utl::find(destination_begin_ + 1, destination_end_, 0), eq, destination_end_ - 1);

    // a small copy
    utl::fill(source_begin_, source_begin_ + 6, 0);
    utl::copy(source_begin_, source_begin_ + 6, destination_begin_);

    TESTASSERTOP(utl::find(destination_begin_, destination_end_, 1), eq, destination_begin_ + 6);
  }

  void TestAlgorithm::testCopy2(tst::TestResult& result)
  {
    int const OVERLAP_MAX         = 20;
    int const OVERLAP_VALUE_START = 10;
    int const RANGE_DIFF_SIZE     = 10;
    int const RANGE_SIZE          = 100;

    // copy with overlapping data
    for (int overlap = 0; overlap < OVERLAP_MAX; ++overlap)
    {
      // fill in some test data (each value different from the others)
      for (int i = 0; i < RANGE_DIFF_SIZE; ++i)
        destination_begin_[i] = OVERLAP_VALUE_START + i;

      utl::copy(destination_begin_, destination_begin_ + RANGE_SIZE, destination_begin_ + overlap);

      for (int i = 0; i < RANGE_DIFF_SIZE; ++i)
        TESTASSERTOP(destination_begin_[overlap + i], eq, OVERLAP_VALUE_START + i);

      TESTASSERTOP(destination_begin_[overlap + RANGE_DIFF_SIZE], eq, 0);

      // clean up
      utl::fill(destination_begin_, destination_end_, 0);
    }
  }

  void TestAlgorithm::testCopy3(tst::TestResult& result)
  {
    // test optimized version of copy
    // @todo implement me!
    //ASSERTM(false, "implement me!");
  }
}
