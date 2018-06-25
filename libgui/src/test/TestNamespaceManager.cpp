// TestNamespaceManager.cpp

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

#include "TestNamespaceManager.hpp"


namespace test
{
  namespace
  {
    typedef gui::Namespace::StreamPointer Stream;


    struct Entry
    {
      gui::String identifier;

      byte_t const* data;
      size_t const  data_size;
    };

    byte_t const data_1[] = {'d', 'a', 't', 'a', '_', '1'};
    byte_t const data_2[] = {'d', 'a', 't', 'a', '_', '2'};
    byte_t const data_3[] = {'d', 'a', 't', 'a', '_', '3'};
    byte_t const data_4[] = {'d', 'a', 't', 'a', '_', '4'};

    Entry const entry1 = {gui::String("identifier_1"), data_1, sizeof(data_1)};
    Entry const entry2 = {gui::String("identifier_2"), data_2, sizeof(data_2)};
    Entry const entry3 = {gui::String("identifier_3"), data_3, sizeof(data_3)};
    Entry const entry4 = {gui::String("identifier_4"), data_4, sizeof(data_4)};

    gui::String const prefix_ns1 = gui::String("mem1");
    gui::String const prefix_ns2 = gui::String("mem2");
    gui::String const separator  = gui::String("://");
  }


  TestNamespaceManager::TestNamespaceManager()
    : tst::TestCase<TestNamespaceManager>(*this, "TestNamespaceManager")
  {
    add(&TestNamespaceManager::testOpen1);
    add(&TestNamespaceManager::testOpen2);
  }

  void TestNamespaceManager::setUp()
  {
    memory_namespace_1_ = gui::MemoryNamespace();
    memory_namespace_1_.insertEntry(entry1.identifier, entry1.data, entry1.data_size);
    memory_namespace_1_.insertEntry(entry2.identifier, entry2.data, entry2.data_size);
    memory_namespace_1_.insertEntry(entry3.identifier, entry3.data, entry3.data_size);

    memory_namespace_2_ = gui::MemoryNamespace();
    memory_namespace_2_.insertEntry(entry4.identifier, entry4.data, entry4.data_size);

    namespace_manager_ = gui::NamespaceManager();
    namespace_manager_.registerNamespace(memory_namespace_1_, prefix_ns1);
    namespace_manager_.registerNamespace(memory_namespace_2_, prefix_ns2);
  }

  void TestNamespaceManager::testOpen1(tst::TestResult& result)
  {
    Stream p4 = namespace_manager_.open(prefix_ns2 + separator + entry4.identifier);
    Stream p3 = namespace_manager_.open(prefix_ns1 + separator + entry3.identifier);
    Stream p2 = namespace_manager_.open(prefix_ns1 + separator + entry2.identifier);
    Stream p1 = namespace_manager_.open(prefix_ns1 + separator + entry1.identifier);

    TESTASSERT(p4);
    TESTASSERT(p3);
    TESTASSERT(p2);
    TESTASSERT(p1);
  }

  void TestNamespaceManager::testOpen2(tst::TestResult& result)
  {
    Stream p4 = namespace_manager_.open(prefix_ns2 + separator + entry4.identifier);
    TESTASSERT(p4);

    byte_t buffer[sizeof(data_4)] = {};
    size_t count = p4->read(buffer, entry4.data_size);

    TESTASSERTOP(count, eq, entry4.data_size);

    gui::String content(buffer, buffer + count);
    gui::String entry(entry4.data, entry4.data + entry4.data_size);

    TESTASSERT(content == entry);
  }
}
