// TestMemoryStream.cpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#include <iostream>
#include <base/stream/MemoryStream.hpp>

#include "TestMemoryStream.hpp"


namespace test
{
  TestMemoryStream::TestMemoryStream()
    : tst::TestCase<TestMemoryStream>(*this, "TestMemoryStream")
  {
    add(&TestMemoryStream::testCreation1);
    add(&TestMemoryStream::testCreation2);
    add(&TestMemoryStream::testRead1);
    add(&TestMemoryStream::testRead2);
    add(&TestMemoryStream::testRead3);
    add(&TestMemoryStream::testRead4);
    add(&TestMemoryStream::testWrite1);
    add(&TestMemoryStream::testPosition1);
  }

  void TestMemoryStream::setUp()
  {
    size_   = 13;
    memory_ = new unsigned char[size_];

    std::fill_n(memory_, size_, 13);
  }

  void TestMemoryStream::tearDown()
  {
    delete [] memory_;

    memory_ = 0;
    size_   = 0;
  }

  void TestMemoryStream::testCreation1(tst::TestResult& result)
  {
    base::MemoryStream s(memory_, size_, true, true);

    TESTASSERTOP(s.getReadPosition(), eq, 0);
    TESTASSERTOP(s.getWritePosition(), eq, 0);
    TESTASSERTOP(s.getSize(), eq, size_);
    TESTASSERT(!s.isAtReadEnd());
    TESTASSERT(!s.isAtWriteEnd());
    TESTASSERT( s.isReadable());
    TESTASSERT( s.isWriteable());
  }

  void TestMemoryStream::testCreation2(tst::TestResult& result)
  {
    unsigned const char* memory = memory_;

    base::MemoryStream s(memory, size_);

    TESTASSERTOP(s.getReadPosition(), eq, 0);
    TESTASSERTOP(s.getWritePosition(), eq, 0);
    TESTASSERTOP(s.getSize(), eq, size_);
    TESTASSERT(!s.isAtReadEnd());
    TESTASSERT(!s.isAtWriteEnd());
    TESTASSERT( s.isReadable());
    TESTASSERT(!s.isWriteable());
  }

  void TestMemoryStream::testRead1(tst::TestResult& result)
  {
    unsigned char buffer[100] = {};

    for (int i = 0; i < 100; ++i)
      TESTASSERTOP(buffer[i], eq, 0);

    base::MemoryStream s(memory_, size_);
    TESTASSERTOP(s.read(buffer, size_), eq, size_);

    for (int i = 0; i < size_; ++i)
      TESTASSERTOP(buffer[i], eq, 13);

    for (int i = size_; i < 100; ++i)
      TESTASSERTOP(buffer[i], eq, 0);
  }

  void TestMemoryStream::testRead2(tst::TestResult& result)
  {
    unsigned char buffer[100] = {};

    base::MemoryStream s(memory_, size_);

    TESTASSERTOP(s.read(buffer, 100), eq, size_);
    TESTASSERTOP(s.getReadPosition(), eq, s.getSize());
    TESTASSERT(s.isAtReadEnd());
  }

  void TestMemoryStream::testRead3(tst::TestResult& result)
  {
    unsigned char buffer[100] = {};

    base::MemoryStream s(memory_, size_);

    TESTASSERTOP(s.read(buffer, 1), eq, 1);
    TESTASSERTOP(s.getReadPosition(), eq, 1);
    TESTASSERT(!s.isAtReadEnd());
  }

  void TestMemoryStream::testRead4(tst::TestResult& result)
  {
    unsigned char buffer[100] = {};

    base::MemoryStream s(memory_, size_);

    s.setReadPosition(3);
    TESTASSERTOP(s.getReadPosition(), eq, 3);
    TESTASSERTOP(s.read(buffer, 100), eq, 10);
  }

  void TestMemoryStream::testWrite1(tst::TestResult& result)
  {
    unsigned char buffer[100] = {};

    buffer[0]  = 't';
    buffer[1]  = 'e';
    buffer[2]  = 's';
    buffer[3]  = 't';
    buffer[10] = 'i';
    buffer[11] = 'n';
    buffer[12] = 'g';

    base::MemoryStream s(memory_, 12);
    TESTASSERTOP(s.write(buffer, 100), eq, 12);

    TESTASSERTOP(memory_[0], eq, 't');
    TESTASSERTOP(memory_[1], eq, 'e');
    TESTASSERTOP(memory_[2], eq, 's');
    TESTASSERTOP(memory_[3], eq, 't');
    TESTASSERTOP(memory_[10], eq, 'i');
    TESTASSERTOP(memory_[11], eq, 'n');
    TESTASSERTOP(memory_[12], eq, 13);

    for (int i = 4; i < 10; ++i)
      TESTASSERTOP(buffer[i], eq, 0);

    TESTASSERTOP(s.getWritePosition(), eq, 12);
    TESTASSERT(s.isAtWriteEnd());
  }

  void TestMemoryStream::testPosition1(tst::TestResult& result)
  {
    base::MemoryStream s(memory_, size_);

    s.setReadPosition(100);
    TESTASSERTOP(s.getReadPosition(), eq, size_);

    s.setWritePosition(100);
    TESTASSERTOP(s.getWritePosition(), eq, size_);
  }
}
