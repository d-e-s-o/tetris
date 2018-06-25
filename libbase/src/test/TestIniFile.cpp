// TestIniFile.cpp

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

#include <cstdio>
#include <iterator>
#include <fstream>

#include <base/IniFile.hpp>

#include "TestIniFile.hpp"


namespace test
{
  namespace
  {
    char const* EMPTY_FILE     = "empty.dat";
    char const* NOT_EMPTY_FILE = "not_empty.dat";
    char const* NO_FILE        = "no.dat";


    /**
     * This function reads the first line from the file and removes it, then returns it.
     * @param file file to read line from
     * @return first line read from file
     */
    std::string getLine(std::string const& file)
    {
      std::string line;
      std::vector<std::string> lines;

      {
        std::ifstream stream(file.c_str());
        std::getline(stream, line);

        std::string temp;

        while (std::getline(stream, temp))
          lines.push_back(temp);
      }

      {
        std::ofstream stream(file.c_str(), std::ios::out | std::ios::trunc);
        std::copy(lines.begin(), lines.end(), std::ostream_iterator<std::string>(stream, "\n"));
      }
      return line;
    }

    void testNotThrow(char const* filename, tst::TestResult& result)
    {
      try
      {
        base::IniFile file(filename);
      }
      catch (...)
      {
        TESTASSERTM(false, "Unexpected exception");
      }
    }
  }


  TestIniFile::TestIniFile()
    : tst::TestCase<TestIniFile>(*this, "TestIniFile")
  {
    add(&TestIniFile::testCreation1);
    add(&TestIniFile::testCreation2);
    add(&TestIniFile::testCreation3);
    add(&TestIniFile::testRead1);
    add(&TestIniFile::testRead2);
    add(&TestIniFile::testRead3);
    add(&TestIniFile::testRead4);
    add(&TestIniFile::testWrite1);
    add(&TestIniFile::testWrite2);
    add(&TestIniFile::testWrite3);
    add(&TestIniFile::testWrite4);
  }

  void TestIniFile::setUp()
  {
    std::ofstream empty(EMPTY_FILE);
    empty << "";
    empty.close();

    std::ofstream not_empty(NOT_EMPTY_FILE);
    not_empty << "[section_1]\n";
    not_empty << "\n";
    not_empty << "\n";
    not_empty << "[section_2]\n";
    not_empty << "\n";
    not_empty << "key1 = 1\n";
    not_empty << "key2=2\n";
    not_empty << "key3 =3\n";
    not_empty << "\n";
    not_empty << "key4= 4\n";
    not_empty << " key5 = 5\n";
    not_empty << "         key6                =              6\n";
    not_empty << "\tkey6\t=\t7\n";
    not_empty << "[section_3]\n";
    not_empty << "key1 = 8\n";
    not_empty << "[]\n";
    not_empty << "\n";
    not_empty << "\n";
    not_empty << "[section_4]\n";
    not_empty << "key1 = 9\n";
    not_empty << "[section_2]\n";
    not_empty << "key7 = 10\n";
    not_empty << "key8 = 11\n";
    not_empty << "[section_3]\n";
    not_empty << "key2 = 12\n";
    not_empty << "[section_4]\n";
    not_empty << "key1 = 13\n";
    not_empty << "key2 = 14\n";
    not_empty << "key2 = 15\n";
    not_empty.close();

    std::remove(NO_FILE);
  }

  void TestIniFile::tearDown()
  {
    std::remove(NO_FILE);
    std::remove(NOT_EMPTY_FILE);
    std::remove(EMPTY_FILE);
  }

  void TestIniFile::testCreation1(tst::TestResult& result)
  {
    testNotThrow(EMPTY_FILE, result);
  }

  void TestIniFile::testCreation2(tst::TestResult& result)
  {
    testNotThrow(NOT_EMPTY_FILE, result);
  }

  void TestIniFile::testCreation3(tst::TestResult& result)
  {
    testNotThrow(NO_FILE, result);
  }

  void TestIniFile::testRead1(tst::TestResult& result)
  {
    base::IniFile file(NOT_EMPTY_FILE);

    // test reading data from not existing key
    int value = -1;
    TESTASSERT(!file.readValue("section_1", "key1", value));
    TESTASSERTOP(value, eq, -1);
  }

  void TestIniFile::testRead2(tst::TestResult& result)
  {
    base::IniFile file(NOT_EMPTY_FILE);

    int value = 0;

    // test reading data from keys with different formats
    TESTASSERT(file.readValue("section_2", "key1", value));
    TESTASSERTOP(value, eq, 1);

    TESTASSERT(file.readValue("section_2", "key2", value));
    TESTASSERTOP(value, eq, 2);

    TESTASSERT(file.readValue("section_2", "key3", value));
    TESTASSERTOP(value, eq, 3);

    TESTASSERT(file.readValue("section_2", "key4", value));
    TESTASSERTOP(value, eq, 4);

    TESTASSERT(file.readValue("section_2", "key5", value));
    TESTASSERTOP(value, eq, 5);

    TESTASSERT(file.readValue("section_2", "key6", value));
    TESTASSERTOP(value, eq, 6);

    TESTASSERT(file.readValue("section_2", "key7", value));
    TESTASSERTOP(value, eq, 10);

    TESTASSERT(file.readValue("section_2", "key8", value));
    TESTASSERTOP(value, eq, 11);
  }

  void TestIniFile::testRead3(tst::TestResult& result)
  {
    base::IniFile file(NOT_EMPTY_FILE);

    int value = 0;

    // test reading value from two sections with same name
    TESTASSERT(file.readValue("section_3", "key1", value));
    TESTASSERTOP(value, eq, 8);

    TESTASSERT(file.readValue("section_3", "key2", value));
    TESTASSERTOP(value, eq, 12);
  }

  void TestIniFile::testRead4(tst::TestResult& result)
  {
    base::IniFile file(NOT_EMPTY_FILE);

    int value = 0;

    // test reading data from section with two equal keys
    TESTASSERT(file.readValue("section_4", "key1", value));
    TESTASSERTOP(value, eq, 9);

    TESTASSERT(file.readValue("section_4", "key2", value));
    TESTASSERTOP(value, eq, 14);
  }

  void TestIniFile::testWrite1(tst::TestResult& result)
  {
    base::IniFile file(EMPTY_FILE);

    // test writing single value
    TESTASSERT(file.writeValue("section_1", "key1", 1));
    file.saveToFile(EMPTY_FILE);

    TESTASSERT(getLine(EMPTY_FILE) == "[section_1]");
    TESTASSERT(getLine(EMPTY_FILE) == "key1 = 1");
    TESTASSERT(getLine(EMPTY_FILE) == "");
  }

  void TestIniFile::testWrite2(tst::TestResult& result)
  {
    base::IniFile file(EMPTY_FILE);

    // test writing two keys into a section, but writing to another section in between
    TESTASSERT(file.writeValue("section_1", "key1", 1));
    TESTASSERT(file.writeValue("section_2", "key1", 2));
    TESTASSERT(file.writeValue("section_1", "key2", 3));
    file.saveToFile(EMPTY_FILE);

    TESTASSERT(getLine(EMPTY_FILE) == "[section_1]");
    TESTASSERT(getLine(EMPTY_FILE) == "key1 = 1");
    TESTASSERT(getLine(EMPTY_FILE) == "key2 = 3");
    TESTASSERT(getLine(EMPTY_FILE) == "[section_2]");
    TESTASSERT(getLine(EMPTY_FILE) == "key1 = 2");
    TESTASSERT(getLine(EMPTY_FILE) == "");
  }

  void TestIniFile::testWrite3(tst::TestResult& result)
  {
    base::IniFile file(EMPTY_FILE);

    // test updating a key
    TESTASSERT(file.writeValue("section_1", "key1", 1));
    TESTASSERT(file.writeValue("section_2", "key1", 2));
    TESTASSERT(file.writeValue("section_1", "key1", 3));
    file.saveToFile(EMPTY_FILE);

    TESTASSERT(getLine(EMPTY_FILE) == "[section_1]");
    TESTASSERT(getLine(EMPTY_FILE) == "key1 = 3");
    TESTASSERT(getLine(EMPTY_FILE) == "[section_2]");
    TESTASSERT(getLine(EMPTY_FILE) == "key1 = 2");
    TESTASSERT(getLine(EMPTY_FILE) == "");
  }

  void TestIniFile::testWrite4(tst::TestResult& result)
  {
    base::IniFile file(EMPTY_FILE);

    TESTASSERT(file.writeValue("section_1", "key1", 1));
    TESTASSERT(file.writeValue("section_1", "key2", 2));
    TESTASSERT(file.writeValue("section_1", "key3", 3));
    TESTASSERT(file.writeValue("section_2", "key1", 4));
    TESTASSERT(file.writeValue("section_2", "key2", 5));
    TESTASSERT(file.writeValue("section_2", "key3", 6));
    TESTASSERT(file.writeValue("section_1", "key4", 7));
    TESTASSERT(file.writeValue("section_1", "key5", 8));
    TESTASSERT(file.writeValue("section_1", "key6", 9));
    TESTASSERT(file.writeValue("section_3", "key1", 10));
    TESTASSERT(file.writeValue("section_3", "key2", 11));
    TESTASSERT(file.writeValue("section_3", "key3", 12));
    file.saveToFile(EMPTY_FILE);

    TESTASSERT(getLine(EMPTY_FILE) == "[section_1]");
    TESTASSERT(getLine(EMPTY_FILE) == "key1 = 1");
    TESTASSERT(getLine(EMPTY_FILE) == "key2 = 2");
    TESTASSERT(getLine(EMPTY_FILE) == "key3 = 3");
    TESTASSERT(getLine(EMPTY_FILE) == "key4 = 7");
    TESTASSERT(getLine(EMPTY_FILE) == "key5 = 8");
    TESTASSERT(getLine(EMPTY_FILE) == "key6 = 9");
    TESTASSERT(getLine(EMPTY_FILE) == "[section_2]");
    TESTASSERT(getLine(EMPTY_FILE) == "key1 = 4");
    TESTASSERT(getLine(EMPTY_FILE) == "key2 = 5");
    TESTASSERT(getLine(EMPTY_FILE) == "key3 = 6");
    TESTASSERT(getLine(EMPTY_FILE) == "[section_3]");
    TESTASSERT(getLine(EMPTY_FILE) == "key1 = 10");
    TESTASSERT(getLine(EMPTY_FILE) == "key2 = 11");
    TESTASSERT(getLine(EMPTY_FILE) == "key3 = 12");
    TESTASSERT(getLine(EMPTY_FILE) == "");
  }
}
