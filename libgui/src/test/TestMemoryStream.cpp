// TestMemoryStream.cpp

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

#include "gui/String.hpp"

#include "TestMemoryStream.hpp"


namespace test
{
  namespace
  {
    byte_t const data[]    = "this is some data stored in memory";
    size_t const data_size = sizeof(data) - 1; // ignore terminating zero byte
    byte_t       buffer[data_size];
  }


  TestMemoryStream::TestMemoryStream()
    : tst::TestCase<TestMemoryStream>(*this, "TestMemoryStream"),
      stream_(data, data_size)
  {
    add(&TestMemoryStream::testRead1);
    add(&TestMemoryStream::testPosition1);
    add(&TestMemoryStream::testReposition1);
  }

  void TestMemoryStream::setUp()
  {
    stream_ = gui::MemoryStream(data, data_size);
  }

  void TestMemoryStream::testRead1(tst::TestResult& result)
  {
    TESTASSERTOP(stream_.read(buffer, 0), eq, 0);

    TESTASSERTOP(stream_.read(buffer, 10), eq, 10);
    TESTASSERT(gui::String(buffer, buffer + 10) == gui::String("this is so"));

    TESTASSERTOP(stream_.read(buffer, 6), eq, 6);
    TESTASSERT(gui::String(buffer, buffer + 6) == gui::String("me dat"));

    TESTASSERTOP(stream_.read(buffer, data_size), eq, 18);
    TESTASSERT(gui::String(buffer, buffer + 18) == gui::String("a stored in memory"));

    TESTASSERTOP(stream_.read(buffer, data_size), eq, 0);
    TESTASSERT(gui::String(buffer, buffer) == gui::String(""));
  }

  void TestMemoryStream::testPosition1(tst::TestResult& result)
  {
    TESTASSERTOP(stream_.position(), eq, 0);
    TESTASSERTOP(stream_.read(buffer, 10), eq, 10);
    TESTASSERTOP(stream_.position(), eq, 10);
  }

  void TestMemoryStream::testReposition1(tst::TestResult& result)
  {
    TESTASSERTOP(stream_.read(buffer, 10), eq, 10);
    TESTASSERT(gui::String(buffer, buffer + 10) == gui::String("this is so"));

    stream_.reposition(1);

    TESTASSERTOP(stream_.read(buffer, 10), eq, 10);
    TESTASSERT(gui::String(buffer, buffer + 10) == gui::String("his is som"));
  }
}
