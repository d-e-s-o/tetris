// TestOptions.cpp

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

#include <type/Util.hpp>
#include <container/String.hpp>
#include <options/Options.hpp>

#include "TestOptions.hpp"


namespace
{
  /**
   *
   */
  template<size_t N>
  opt::Error evaluate(ctr::String const& option_string, opt::Option (& options)[N])
  {
    return opt::evaluate(option_string.begin(), option_string.end(), options, N);
  }


  opt::Option options[] = {{opt::OPTION_TYPE_NORMAL,            "long1",     '1'},
                           {opt::OPTION_TYPE_ALLOW_MULTIPLE,    0,           '2'},
                           {opt::OPTION_TYPE_OPTIONAL_ARGUMENT, "long3",      0 },
                           {opt::OPTION_TYPE_REQUIRED_ARGUMENT, 0,           '4'},
                           {opt::OPTION_TYPE_NORMAL,            "long5-test", 0 }};
}


namespace test
{
  TestOptions::TestOptions()
    : tst::TestCase<TestOptions>(*this, "TestOptions")
  {
    add(&TestOptions::testEvaluate1);
    add(&TestOptions::testEvaluate2);
    add(&TestOptions::testEvaluate3);
    add(&TestOptions::testEvaluate4);
    add(&TestOptions::testEvaluate5);
    add(&TestOptions::testEvaluateFull1);
  }

  void TestOptions::testEvaluate1(tst::TestResult& result)
  {
    opt::Option const& o = options[0];

    evaluateString("");
    TESTASSERTOP(e_.type, eq, opt::ERROR_NONE);

    evaluateString("   ");
    TESTASSERTOP(e_.type, eq, opt::ERROR_NONE);

    evaluateString(" --long1");
    TESTASSERTOP(e_.type, eq, opt::ERROR_NONE);
    TESTASSERTOP(o.count          , eq, 1);
    TESTASSERTOP(o.argument_index , eq, 0);
    TESTASSERTOP(o.argument_length, eq, 0);

    evaluateString("-1  ");
    TESTASSERTOP(e_.type, eq, opt::ERROR_NONE);
    TESTASSERTOP(o.count          , eq, 1);
    TESTASSERTOP(o.argument_index , eq, 0);
    TESTASSERTOP(o.argument_length, eq, 0);

    evaluateString("-1 --long0");
    TESTASSERTOP(e_.type, eq, opt::ERROR_UNKNOWN);
    TESTASSERTOP(e_.string_index , eq, 5);
    TESTASSERTOP(e_.string_length, eq, 5);

    evaluateString("-1 test");
    TESTASSERTOP(e_.type, eq, opt::ERROR_ARGUMENT);
    TESTASSERTOP(e_.option_index , eq, 0);
    TESTASSERTOP(e_.string_index , eq, 3);
    TESTASSERTOP(e_.string_length, eq, 4);

    evaluateString("--long1 -1");
    TESTASSERTOP(e_.type, eq, opt::ERROR_TOO_MANY);
    TESTASSERTOP(e_.option_index, eq, 0);

    evaluateString("-long1");
    TESTASSERTOP(e_.type, eq, opt::ERROR_TOKEN);
    TESTASSERTOP(e_.string_index , eq, 0);
    TESTASSERTOP(e_.string_length, eq, 1);

    evaluateString("---1ong1");
    TESTASSERTOP(e_.type, eq, opt::ERROR_TOKEN);
    TESTASSERTOP(e_.string_index , eq, 0);
    TESTASSERTOP(e_.string_length, eq, 2);

    evaluateString("--1");
    TESTASSERTOP(e_.type, eq, opt::ERROR_TOKEN);
    TESTASSERTOP(e_.string_index , eq, 0);
    TESTASSERTOP(e_.string_length, eq, 2);

    evaluateString("-");
    TESTASSERTOP(e_.type, eq, opt::ERROR_TOKEN);

    evaluateString("-1 -- $ #$%^&*ISHAJKHSABSdash%##@@$");
    TESTASSERTOP(e_.type, eq, opt::ERROR_NONE);
    TESTASSERTOP(o.count, eq, 1);
  }

  void TestOptions::testEvaluate2(tst::TestResult& result)
  {
    opt::Option const& o = options[1];

    evaluateString("");
    TESTASSERTOP(e_.type, eq, opt::ERROR_NONE);
    TESTASSERTOP(o.count, eq, 0);

    evaluateString("-2");
    TESTASSERTOP(e_.type, eq, opt::ERROR_NONE);
    TESTASSERTOP(o.count          , eq, 1);
    TESTASSERTOP(o.argument_index , eq, 0);
    TESTASSERTOP(o.argument_length, eq, 0);

    evaluateString("-2 -2");
    TESTASSERTOP(e_.type, eq, opt::ERROR_NONE);
    TESTASSERTOP(o.count, eq, 2);

    evaluateString("-2 -2 -2");
    TESTASSERTOP(e_.type, eq, opt::ERROR_NONE);
    TESTASSERTOP(o.count, eq, 3);

    evaluateString("--long2");
    TESTASSERTOP(e_.type, eq, opt::ERROR_UNKNOWN);
    TESTASSERTOP(e_.string_index , eq, 2);
    TESTASSERTOP(e_.string_length, eq, 5);
  }

  void TestOptions::testEvaluate3(tst::TestResult& result)
  {
    opt::Option const& o = options[2];

    evaluateString("--long3");
    TESTASSERTOP(e_.type, eq, opt::ERROR_NONE);
    TESTASSERTOP(o.count          , eq, 1);
    TESTASSERTOP(o.argument_index , eq, 0);
    TESTASSERTOP(o.argument_length, eq, 0);

    evaluateString("--long3=argument3");
    TESTASSERTOP(e_.type, eq, opt::ERROR_NONE);
    TESTASSERTOP(o.count          , eq, 1);
    TESTASSERTOP(o.argument_index , eq, 8);
    TESTASSERTOP(o.argument_length, eq, 9);

    evaluateString("--long3=\"long quoted argument\"");
    TESTASSERTOP(e_.type, eq, opt::ERROR_NONE);
    TESTASSERTOP(o.count          , eq, 1);
    TESTASSERTOP(o.argument_index , eq, 9);
    TESTASSERTOP(o.argument_length, eq, 20);
  }

  void TestOptions::testEvaluate4(tst::TestResult& result)
  {
    opt::Option const& o = options[3];

    evaluateString("-4");
    TESTASSERTOP(e_.type, eq, opt::ERROR_NO_ARGUMENT);
    TESTASSERTOP(e_.option_index, eq, 3);

    evaluateString("-4 argument4");
    TESTASSERTOP(e_.type, eq, opt::ERROR_NONE);
    TESTASSERTOP(o.count          , eq, 1);
    TESTASSERTOP(o.argument_index , eq, 3);
    TESTASSERTOP(o.argument_length, eq, 9);
  }

  void TestOptions::testEvaluate5(tst::TestResult& result)
  {
    opt::Option const& o = options[4];

    evaluateString("--long5-test");
    TESTASSERTOP(e_.type, eq, opt::ERROR_NONE);
    TESTASSERTOP(o.count, eq, 1);

    evaluateString("--long5-test-");
    TESTASSERTOP(e_.type, eq, opt::ERROR_TOKEN);
    TESTASSERTOP(e_.string_index , eq, 12);
    TESTASSERTOP(e_.string_length, eq, 1);
  }

  void TestOptions::testEvaluateFull1(tst::TestResult& result)
  {
    evaluateString("-4 arg4 --long1 -2 --long3=arg3 -2");
    TESTASSERTOP(e_.type, eq, opt::ERROR_NONE);
    TESTASSERTOP(options[0].count, eq, 1);
    TESTASSERTOP(options[1].count, eq, 2);
    TESTASSERTOP(options[2].count, eq, 1);
    TESTASSERTOP(options[3].count, eq, 1);
    TESTASSERTOP(options[2].argument_index , eq, 27);
    TESTASSERTOP(options[2].argument_length, eq, 4);
    TESTASSERTOP(options[3].argument_index , eq, 3);
    TESTASSERTOP(options[3].argument_length, eq, 4);
  }

  /**
   * @param string
   */
  void TestOptions::evaluateString(char const* string)
  {
    // the evaluation accumulates the results of multiple runs -- we do not want this behavior for
    // our testing purposes so we reset the fields of interest manually for each test
    for (size_t i = 0; i < typ::arraySize(options); i++)
    {
      options[i].count           = 0;
      options[i].argument_index  = 0;
      options[i].argument_length = 0;
    }

    e_ = evaluate(ctr::String(string), options);
  }
}
