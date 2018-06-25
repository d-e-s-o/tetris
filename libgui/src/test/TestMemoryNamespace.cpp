// TestMemoryNamespace.cpp

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

#include <gui/String.hpp>

#include "TestMemoryNamespace.hpp"


namespace test
{
  namespace
  {
    byte_t const data[] = "this is some data stored in memory";
    size_t const size   = sizeof(data);

    gui::String const id = gui::String("identifier");
  }


  TestMemoryNamespace::TestMemoryNamespace()
    : tst::TestCase<TestMemoryNamespace>(*this, "TestMemoryNamespace")
  {
    add(&TestMemoryNamespace::testInsert1);
    add(&TestMemoryNamespace::testRemove1);
  }

  void TestMemoryNamespace::setUp()
  {
    memory_namespace_ = gui::MemoryNamespace();
  }

  void TestMemoryNamespace::testInsert1(tst::TestResult& result)
  {
    TESTASSERT(memory_namespace_.insertEntry(gui::String(id), data, size));

    TESTASSERT( memory_namespace_.open(id));
    TESTASSERT(!memory_namespace_.open(gui::String("")));
    TESTASSERT(!memory_namespace_.open(id + gui::String("1")));
  }

  void TestMemoryNamespace::testRemove1(tst::TestResult& result)
  {
    TESTASSERT(memory_namespace_.insertEntry(gui::String(id), data, size));
    TESTASSERT(memory_namespace_.open(id));

    TESTASSERT(!memory_namespace_.removeEntry(gui::String("")));
    TESTASSERT(!memory_namespace_.removeEntry(id + gui::String("1")));
    TESTASSERT( memory_namespace_.removeEntry(id));

    TESTASSERT(!memory_namespace_.open(id));
  }
}
