// TestUtil.cpp

/***************************************************************************
 *   Copyright (C) 2014 Daniel Mueller                                     *
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

#include <type/Util.hpp>

#include "TestUtil.hpp"


namespace test
{
  TestUtil::TestUtil()
    : tst::TestCase<TestUtil>(*this, "TestUtil")
  {
    add(&TestUtil::testTypeBits);
    add(&TestUtil::testArraySize);
  }

  void TestUtil::testTypeBits(tst::TestResult& result)
  {
    // @todo use ASSERTOP_STATIC
    static_assert(typ::typeBits<uint8_t>()  == 8, "");
    static_assert(typ::typeBits<uint16_t>() == 16, "");
    static_assert(typ::typeBits<uint32_t>() == 32, "");
    static_assert(typ::typeBits<uint64_t>() == 64, "");

    static_assert(typ::typeBits(uint8_t())  == 8, "");
    static_assert(typ::typeBits(uint16_t()) == 16, "");
    static_assert(typ::typeBits(uint32_t()) == 32, "");
    static_assert(typ::typeBits(uint64_t()) == 64, "");
  }

  void TestUtil::testArraySize(tst::TestResult& result)
  {
    // @todo use ASSERTOP_STATIC
    uint8_t array1[12];
    static_assert(typ::arraySize(array1) == 12, "");

    uint16_t array2[100];
    static_assert(typ::arraySize(array2) == 100, "");

    uint64_t array3[1];
    static_assert(typ::arraySize(array3) == 1, "");
  }
}
