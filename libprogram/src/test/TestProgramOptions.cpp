// TestProgramOptions.cpp

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

#include <type/Util.hpp>
#include <program/ProgramOptions.hpp>

#include "TestProgramOptions.hpp"


namespace test
{
  TestProgramOptions::TestProgramOptions()
    : tst::TestCase<TestProgramOptions>(*this, "TestProgramOptions")
  {
    add(&TestProgramOptions::testCreation1);
    add(&TestProgramOptions::testCreation2);
    add(&TestProgramOptions::testNoArgument1);
    add(&TestProgramOptions::testRequiredArgument1);
    add(&TestProgramOptions::testOptionalArgument1);
    add(&TestProgramOptions::testOptionalArgument2);
  }

  void TestProgramOptions::testCreation1(tst::TestResult& result)
  {
    char  arg1[] = "path";
    char  arg2[] = "--test";
    char* argv[] = {arg1, arg2};
    int   argc   = typ::arraySize(argv);

    pgm::ProgramOptions::Options options;
    options.push_back(pgm::ProgramOptions::Option('\0', ctr::StringA("test"), pgm::ProgramOptions::ARGUMENT_TYPE_NONE));

    // all have to throw because one argument is erroneous
    TESTTHROWSANY(pgm::ProgramOptions(0,    argv,    options));
    TESTTHROWSANY(pgm::ProgramOptions(argc, nullptr, options));
    TESTTHROWSANY(pgm::ProgramOptions(argc, argv, pgm::ProgramOptions::Options()));
  }

  void TestProgramOptions::testCreation2(tst::TestResult& result)
  {
    // has to throw because short and long option are empty
    TESTTHROWSANY(pgm::ProgramOptions::Option('\0', ctr::StringA(""), pgm::ProgramOptions::ARGUMENT_TYPE_NONE));
  }

  void TestProgramOptions::testNoArgument1(tst::TestResult& result)
  {
    char  arg1[] = "path";
    char  arg2[] = "--test1";
    char  arg3[] = "-3";
    char* argv[] = {arg1, arg2, arg3};
    int   argc   = typ::arraySize(argv);

    pgm::ProgramOptions::Options options;
    options.push_back(pgm::ProgramOptions::Option('\0', ctr::StringA("test1"), pgm::ProgramOptions::ARGUMENT_TYPE_NONE));
    options.push_back(pgm::ProgramOptions::Option('2',  ctr::StringA("test2"), pgm::ProgramOptions::ARGUMENT_TYPE_NONE));
    options.push_back(pgm::ProgramOptions::Option('3',  ctr::StringA("test3"), pgm::ProgramOptions::ARGUMENT_TYPE_NONE));

    pgm::ProgramOptions program_options(argc, argv, options);

    TESTASSERT( program_options.GetOption(0).available);
    TESTASSERT(!program_options.GetOption(1).available);
    TESTASSERT( program_options.GetOption(2).available);
  }

  void TestProgramOptions::testRequiredArgument1(tst::TestResult& result)
  {
    char  arg1[] = "path";
    char  arg2[] = "--test";
    char  arg3[] = "arg";
    char* argv[] = {arg1, arg2, arg3};
    int   argc   = typ::arraySize(argv);

    pgm::ProgramOptions::Options options;
    options.push_back(pgm::ProgramOptions::Option('\0', ctr::StringA("test"), pgm::ProgramOptions::ARGUMENT_TYPE_REQUIRED));

    pgm::ProgramOptions program_options(argc, argv, options);

    TESTASSERT(program_options.GetOption(0).available);
    TESTASSERT(program_options.GetOption(0).argument == ctr::StringA("arg"));
  }

  void TestProgramOptions::testOptionalArgument1(tst::TestResult& result)
  {
    char  arg1[] = "path";
    char  arg2[] = "--test=arg";
    char* argv[] = {arg1, arg2};
    int   argc   = typ::arraySize(argv);

    pgm::ProgramOptions::Options options;
    options.push_back(pgm::ProgramOptions::Option('\0', ctr::StringA("test"), pgm::ProgramOptions::ARGUMENT_TYPE_OPTIONAL));

    pgm::ProgramOptions program_options(argc, argv, options);

    TESTASSERT(program_options.GetOption(0).available);
    TESTASSERT(program_options.GetOption(0).argument == ctr::StringA("arg"));
  }

  void TestProgramOptions::testOptionalArgument2(tst::TestResult& result)
  {
    char  arg1[] = "path";
    char  arg2[] = "--test";
    char* argv[] = {arg1, arg2};
    int   argc   = 2;

    pgm::ProgramOptions::Options options;
    options.push_back(pgm::ProgramOptions::Option('\0', ctr::StringA("test"), pgm::ProgramOptions::ARGUMENT_TYPE_OPTIONAL));

    pgm::ProgramOptions program_options(argc, argv, options);

    TESTASSERT(program_options.GetOption(0).available);
    TESTASSERTOP(program_options.GetOption(0).argument.size(), eq, 0);
  }
}
