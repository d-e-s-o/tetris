// TestAlgorithm.hpp

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

#ifndef UTLTESTALGORITHM_HPP
#define UTLTESTALGORITHM_HPP

#include <test/TestCase.hpp>


namespace test
{
  /**
   * @todo add test for min, max and swap (and be it only for testing if the code compiles)
   * @todo split this test cases into (at least) two: one for generic algorithms and one for the
   *       copy, fill, and find stuff that requires the arrays
   */
  class TestAlgorithm: public tst::TestCase<TestAlgorithm>
  {
  public:
    TestAlgorithm();

    void testIncludes1(tst::TestResult& result);
    void testIncludes2(tst::TestResult& result);

    void testFill(tst::TestResult& result);

    void testFind(tst::TestResult& result);
    void testFindNot(tst::TestResult& result);
    void testFindBinary1(tst::TestResult& result);
    void testFindBinary2(tst::TestResult& result);

    void testCopy1(tst::TestResult& result);
    void testCopy2(tst::TestResult& result);
    void testCopy3(tst::TestResult& result);

  protected:
    virtual void setUp();

  private:
    static int const SIZE = 1024;

    int source_[SIZE];
    int destination_[SIZE];

    int* const source_begin_;
    int* const source_end_;

    int* const destination_begin_;
    int* const destination_end_;
  };
}


#endif
