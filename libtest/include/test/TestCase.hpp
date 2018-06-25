// TestCase.hpp

/***************************************************************************
 *   Copyright (C) 2009-2010,2012-2014 Daniel Mueller (deso@posteo.net)    *
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

#ifndef TSTTESTCASE_HPP
#define TSTTESTCASE_HPP

#include <util/AssertImpl.hpp>

#include "TestBase.hpp"
#include "TestResult.hpp"
#include "TestContainer.hpp"


namespace tst
{
  /**
   * This class is the base class for all classes that are to be tested.
   */
  template<typename T>
  class TestCase: public TestBase
  {
  public:
    typedef void (T::*Test)(TestResult&);

    TestCase(T& instance, char const* name = nullptr);

    TestCase(TestCase&&) = delete;
    TestCase(TestCase const&) = delete;

    TestCase& operator =(TestCase&&) = delete;
    TestCase& operator =(TestCase const&) = delete;

    virtual void run(TestResult& result);
    virtual bool add(Test const& test);

  protected:
    virtual void setUp();
    virtual void tearDown();

  private:
    /* We have a fixed upper limit of tests that we support. */
    typedef TestContainer<Test, 256> Tests;

    T* instance_;
    char const* name_;
    Tests tests_;
  };


  /**
   * This little helper function creates and returns a statically
   * allocated instance of the given test case. This allows some more
   * convinient creating and adding to suites.
   */
  template<typename T>
  T& createTestCase();


  /**
   * Test framework exception used for signaling fatal assertion
   * failures, i.e., ones that have to terminate the current test
   * function.
   */
  struct FatalFailure
  {
  };


  /** @cond never */
  #define FAIL_LAMBDA\
    [&result](char const* assertion,\
              char const* file,\
              unsigned int line,\
              char const* function)\
    {\
      result.failed(file, line, assertion);\
    }
  /** @endcond never */

  /**
   * Test that an assertion holds, include the given message in the
   * reported error if not.
   * @param assertion_ boolean value to check for trueness
   * @param message_ message to include in error report
   */
  #define TESTASSERTM(assertion_, message_)\
    do\
    {\
      result.checked(__FILE__, __LINE__);\
      if (!(assertion_))\
        result.failed(__FILE__, __LINE__, message_);\
    } while (false)

  /**
   * Test that an assertion holds.
   * @param assertion_ boolean value to check for trueness
   */
  #define TESTASSERT(assertion_)\
    do\
    {\
      result.checked(__FILE__, __LINE__);\
      ASSERT_IMPL(assertion_, FAIL_LAMBDA);\
    } while (false)

  /**
   * Test that an assertion holds.
   *
   * The given operation is applied to the two operands and the result
   * is asserted.
   * @param first_ the first parameter to the given operation
   * @param operation_ the operation to apply to the two parameters
   * @param second_ the second parameter to the operation
   */
  #define TESTASSERTOP(first_, operation_, second_)\
    do\
    {\
      result.checked(__FILE__, __LINE__);\
      ASSERTOP_IMPL(first_, operation_, second_, FAIL_LAMBDA);\
    } while (0)

  /**
   * Test that an assertion holds, exit current test (and print
   * message) if not.
   * @param assertion_ boolean value to check for trueness
   * @param message_ message to include in error report
   */
  #define TESTASSERTFATALM(assertion_, message_)\
    do\
    {\
      result.checked(__FILE__, __LINE__);\
      if (!(assertion_))\
      {\
        result.failed(__FILE__, __LINE__, message_);\
        throw tst::FatalFailure();\
      }\
    } while(false)

  /**
   * Test that an assertion holds, exit current test if not.
   * @param assertion_ boolean value to check for trueness
   */
  #define TESTASSERTFATAL(assertion_)\
    TESTASSERTFATALM(assertion_, nullptr)

  /** @cond never */
  #define TESTTHROWSIMPL(exception_type_, expression_, message_)\
    do\
    {\
      auto success = true;\
      result.checked(__FILE__, __LINE__);\
      try\
      {\
        expression_;\
        success = false;\
      }\
      catch (exception_type_)\
      {\
      }\
      if (!success)\
        result.failed(__FILE__, __LINE__, message_);\
    } while(false)
  /** @endcond never */

  /**
   * Test that an expression throws any exception.
   * @param expression_ expression to execute
   */
  #define TESTTHROWSANY(expression_)\
    TESTTHROWSIMPL(..., expression_, nullptr)

  /**
   * Test that an expression throws any exception, include the given
   * message in the reported error if not.
   * @param expression_ expression to execute
   * @param message_ message to include in error report
   */
  #define TESTTHROWSANYM(expression_, message_)\
    TESTTHROWSIMPL(..., expression_, message_)

  /**
   * Test that an expression throws a specific exception.
   * @param exception_type_ type of the exception expected
   * @param expression_ expression to execute
   */
  #define TESTTHROWS(exception_type_, expression_)\
    TESTTHROWSIMPL(exception_type_, expression_, nullptr)

  /**
   * Test that an expression throws a specific exception, include the
   * given message in the reported error if not.
   * @param exception_type_ type of the exception expected
   * @param expression_ expression to execute
   * @param message_ message to include in error report
   */
  #define TESTTHROWSM(exception_type_, expression_, message_)\
    TESTTHROWSIMPL(exception_type_, expression_, message_)
}

namespace tst
{
  /**
   * @return a newly created test case
   */
  template<typename T>
  inline T& createTestCase()
  {
    static T t;
    return t;
  }

  /**
   * The default constructor creates an empty TestCase.
   */
  template<typename T>
  inline TestCase<T>::TestCase(T& instance, char const* name)
    : instance_(&instance),
      name_(name),
      tests_()
  {
  }

  /**
   * @copydoc TestBase::run
   */
  template<typename T>
  inline void TestCase<T>::run(TestResult& result)
  {
    result.startTest(name_);

    for (auto it = tests_.begin(); it != tests_.end(); ++it)
    {
      result.startTestFunction();
      setUp();

      try
      {
        /* Run the test method. */
        (instance_->*(*it))(result);
      }
      catch(FatalFailure const& failure)
      {
        /* There is nothing to be done here. */
      }
      catch(...)
      {
        /*
         * @todo It would be great to report the correct file and line
         *       number here, but that would require pretty
         *       sophisticated means.
         */
        TESTASSERTM(false, "Unexpected exception");
      }

      tearDown();
      result.endTestFunction();
    }

    result.endTest();
  }

  /**
   * This method can be used to add a new test function to the list of
   * tests to execute.
   * @param test a test case or test suite to add
   * @return true if adding the test was successful, false if not
   */
  template<typename T>
  inline bool TestCase<T>::add(Test const& test)
  {
    if (test != nullptr)
      return tests_.add(test);

    return false;
  }

  /**
   * This method can be overwritten to do some initialization work
   * before each test.
   */
  template<typename T>
  inline void TestCase<T>::setUp()
  {
  }

  /**
   * This method can be overwritten to undo the initialization work
   * done in setUp. It is called right after the test finished.
   */
  template<typename T>
  inline void TestCase<T>::tearDown()
  {
  }
}


#endif
