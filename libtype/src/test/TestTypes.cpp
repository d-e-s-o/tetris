// TestTypes.cpp

/***************************************************************************
 *   Copyright (C) 2012,2014 Daniel Mueller                                *
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

#include <type/Types.hpp>

#include "TestTypes.hpp"


namespace test
{
  TestTypes::TestTypes()
    : tst::TestCase<TestTypes>(*this, "TestTypes")
  {
    add(&TestTypes::testSizes);
  }

  void TestTypes::testSizes(tst::TestResult& result)
  {
    TESTASSERTOP(sizeof(char_t),  eq, 1);
    TESTASSERTOP(sizeof(schar_t), eq, 1);
    TESTASSERTOP(sizeof(uchar_t), eq, 1);
    TESTASSERTOP(sizeof(byte_t),  eq, 1);

    TESTASSERTOP(sizeof(sint8_t), eq, 1);
    TESTASSERTOP(sizeof(uint8_t), eq, 1);

    TESTASSERTOP(sizeof(sint16_t), eq, 2);
    TESTASSERTOP(sizeof(uint16_t), eq, 2);

    TESTASSERTOP(sizeof(sint32_t), eq, 4);
    TESTASSERTOP(sizeof(uint32_t), eq, 4);

#if defined(HAS_64_BIT_INTEGRAL_TYPE)
    TESTASSERTOP(sizeof(sint64_t), eq, 8);
    TESTASSERTOP(sizeof(uint64_t), eq, 8);
#endif
  }
}
