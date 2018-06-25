// TestFunction.cpp

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

#include <type/Function.hpp>

#include "TestFunction.hpp"


namespace test
{
  namespace
  {
    /**
     * @param function
     * @param arguments
     * @todo put this into the Function.hpp header?
     */
    template<typename FunctionT, typename ...ArgumentsT>
    typ::Function<FunctionT, ArgumentsT...> functionize(FunctionT function, ArgumentsT... arguments)
    {
      return typ::Function<FunctionT, ArgumentsT...>(function, arguments...);
    }

    /**
     * @param function
     * @param arguments
     */
    template<typename FunctionT, typename ...ArgumentsT>
    typ::DynamicFunctionImpl<FunctionT, ArgumentsT...>* functionized(FunctionT function, ArgumentsT... arguments)
    {
      return new typ::DynamicFunctionImpl<FunctionT, ArgumentsT...>(function, arguments...);
    }


    int shared_global = 0;

    int test1()
    {
      shared_global = 42;
      return 0;
    }

    int test2(int i)
    {
      shared_global = i;
      return i;
    }

    int test3(double d, int i)
    {
      shared_global = i;
      return i;
    }

    int test4(void* p, int i)
    {
      shared_global = i;
      return i;
    }

    int test5(void* p, int j, int k)
    {
      shared_global = j * k;
      return shared_global;
    }
  }


  TestFunction::TestFunction()
    : tst::TestCase<TestFunction>(*this, "TestFunction")
  {
    add(&TestFunction::testCall1);
    add(&TestFunction::testCall2);
    add(&TestFunction::testCall3);
    add(&TestFunction::testCall4);
  }

  void TestFunction::testCall1(tst::TestResult& result)
  {
    auto fn1 = functionize(&test1);
    auto fn2 = functionize(&test2, 43);
    auto fn3 = functionize(&test3, 1.0, 42);
    auto fn4 = functionize(&test4, nullptr, 41);
    void* p = 0;
    auto fn5 = functionize(&test5, nullptr, 2, 3);

    TESTASSERTOP(fn1(), eq, 0);
    TESTASSERTOP(shared_global, eq, 42);

    TESTASSERTOP(fn2(), eq, 43);
    TESTASSERTOP(shared_global, eq, 43);

    TESTASSERTOP(fn3(), eq, 42);
    TESTASSERTOP(shared_global, eq, 42);

    TESTASSERTOP(fn4(), eq, 41);
    TESTASSERTOP(shared_global, eq, 41);

    TESTASSERTOP(fn5(), eq, 6);
    TESTASSERTOP(shared_global, eq, 6);
  }

  void TestFunction::testCall2(tst::TestResult& result)
  {
    auto shared_local = 0;

    auto fn1 = functionize([](int i){ return 1; }, 0);
    auto fn2 = functionize([](int i){ return i; }, 44);
    auto fn3 = functionize([&shared_local](){ shared_local = 42; return shared_local; });
    auto fn4 = functionize([&shared_local](int i, int j){ shared_local = i * j; }, 20, 2);
    auto fn5 = functionize([&shared_local](void* p, int j){ shared_local = j; return p; }, nullptr, 2);

    TESTASSERTOP(fn1(), eq, 1);
    TESTASSERTOP(fn2(), eq, 44);
    TESTASSERTOP(fn3(), eq, 42);
    TESTASSERTOP(shared_local, eq, 42);

    fn4();
    TESTASSERTOP(shared_local, eq, 40);

    TESTASSERTOP(fn5(), eq, nullptr);
    TESTASSERTOP(shared_local, eq, 2);
  }

  void TestFunction::testCall3(tst::TestResult& result)
  {
    typ::DynamicFunction* fn1 = functionized(&test1);
    (*fn1)();
    delete fn1;
    TESTASSERTOP(shared_global, eq, 42);

    typ::DynamicFunction* fn2 = functionized(&test2, 56);
    (*fn2)();
    delete fn2;
    TESTASSERTOP(shared_global, eq, 56);
  }

  void TestFunction::testCall4(tst::TestResult& result)
  {
    auto shared_local = 0;

    typ::DynamicFunction* fn1 = functionized([&shared_local](int i){ shared_local = 12; return 1; }, 0);
    typ::DynamicFunction* fn2 = functionized([&shared_local](int i){ shared_local = i; }, 44);
    typ::DynamicFunction* fn3 = functionized([&shared_local](){ shared_local = 42; return shared_local; });
    typ::DynamicFunction* fn4 = functionized([&shared_local](int i, int j){ shared_local = i * j; }, 20, 2);

    (*fn1)();
    delete fn1;
    TESTASSERTOP(shared_local, eq, 12);

    (*fn2)();
    delete fn2;
    TESTASSERTOP(shared_local, eq, 44);

    (*fn3)();
    delete fn3;
    TESTASSERTOP(shared_local, eq, 42);

    (*fn4)();
    delete fn4;
    TESTASSERTOP(shared_local, eq, 40);
  }
}
