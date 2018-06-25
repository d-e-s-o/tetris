// AssertImpl.hpp

/***************************************************************************
 *   Copyright (C) 2014 Daniel Mueller (deso@posteo.net)                   *
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

#ifndef UTLASSERTIMPL_HPP
#define UTLASSERTIMPL_HPP

#include <type/Types.hpp>
#include <type/Traits.hpp>

#include "util/Config.hpp"
#include "util/io/MemoryBuffer.hpp"
#include "util/io/OutStream.hpp"


namespace utl
{
  /**
   * A valid fail function for our macro has to provide a signature of
   * this type.
   */
  typedef void (AssertFailFunction)(char const* assertion,
                                    char const* file,
                                    unsigned int line,
                                    char const* function);
}


/**
 * Clients can make use of this define to implement custom assertions.
 * @param condition_ condition to test
 * @param fail_function_ pointer to function to invoke in case the
 *        condition is not fulfilled
 * @note 'fail_function_' should accept the same parameters as specified
 *       for 'AssertFailFunction', it can be a lambda expression,
 *       however
 * @see utl::AssertFailFunction
 */
#define ASSERT_IMPL(condition_, fail_function_)\
  if (!(condition_))\
    fail_function_(#condition_, __FILE__, __LINE__, __FUNCTION__)

/**
 * @param first_ first parameter to the given operation
 * @param operation_ operation to invoke on 'first_' and 'second_'
 * @param second_ second parameter to the given operation
 * @param fail_function_ pointer to function to invoke in case the
 *        condition is not fulfilled
 * @note 'fail_function_' should accept the same parameters as specified
 *       for 'AssertFailFunction', it can be a lambda expression,
 *       however
 * @see utl::AssertFailFunction
 */
#define ASSERTOP_IMPL(first_, operation_, second_, fail_function_)\
  /* invoke our 'assertOp' function which resides in namespace 'utl' */\
  utl::assertOp(\
    /*\
     * Create our operation object. This is pretty tricky: 'operation_ is a\
     * string and we know it has to reference an object in namespace\
     * 'utl', so we paste them together. Also note that the object is\
     * a template, so we need to retrieve the types of the two arguments\
     * first.\
     */\
    utl::operation_<typename typ::RemoveReference<decltype(first_)>::Type,\
                    typename typ::RemoveReference<decltype(second_)>::Type>(first_, second_),\
    /* and of course the usual suspects in this context */\
    __FILE__, __FUNCTION__, __LINE__,\
    fail_function_\
  )


namespace utl
{
  // it's tough to get a reasonable implementation without too much macro magic
  #define FUNCTOR(name_, operation_)\
    struct name_\
    {\
      template<typename T1, typename T2>\
      bool operator ()(T1 const& value1, T2 const& value2)\
      {\
        return value1 operation_ value2;\
      }\
      char const* operation() const\
      {\
        return #operation_;\
      }\
    };\

  FUNCTOR(lessEqual,    <=);
  FUNCTOR(less,         < );
  FUNCTOR(greaterEqual, >=);
  FUNCTOR(greater,      > );
  FUNCTOR(equal,        ==);
  FUNCTOR(unequal,      !=);
  #undef FUNCTOR


  /**
   * This class represents an operation to invoke whose result is to be checked. An object of this
   * type stores the two arguments to the operation to be able to print their values upon request.
   */
  template<typename T1, typename T2, typename OperationT>
  class Operation
  {
  public:
    /**
     * @param value1 first argument to pass to given operation
     * @param value2 second argument to pass to given operation
     */
    Operation(T1 const& value1, T2 const& value2)
      : value1_(&value1),
        value2_(&value2)
    {
    }

    /**
     * @return result of 'OperationT' on given values
     */
    bool operator ()() const
    {
      return OperationT()(*value1_, *value2_);
    }

    /**
     * @param stream stream to which to write string representation of operation
     */
    void write(utl::OutStream& stream) const
    {
      stream << *value1_ << ' ' << OperationT().operation() << ' ' << *value2_;
    }

  private:
    T1 const* value1_;
    T2 const* value2_;
  };


  // Define all our operation objects. Names are kept short intentionally to (hopefully) keep
  // assertions concise but understandable.
  // - lt => less than
  // - le => less (than or) equal
  // - gt => greater than
  // - ge => greater (than or) equal
  // - eq => equal
  // - ne => not equal
  template<typename T1, typename T2>
  struct lt: Operation<T1, T2, less>         { using Operation<T1, T2, less>::Operation; };
  template<typename T1, typename T2>
  struct le: Operation<T1, T2, lessEqual>    { using Operation<T1, T2, lessEqual>::Operation; };
  template<typename T1, typename T2>
  struct gt: Operation<T1, T2, greater>      { using Operation<T1, T2, greater>::Operation; };
  template<typename T1, typename T2>
  struct ge: Operation<T1, T2, greaterEqual> { using Operation<T1, T2, greaterEqual>::Operation; };
  template<typename T1, typename T2>
  struct eq: Operation<T1, T2, equal>        { using Operation<T1, T2, equal>::Operation; };
  template<typename T1, typename T2>
  struct ne: Operation<T1, T2, unequal>      { using Operation<T1, T2, unequal>::Operation; };


  /**
   * @param operation the operation to execute
   * @param file a file name, retrieved using __FILE__, for instance
   * @param function a function name, retrieved using __FUNCTION__, for instance
   * @param line a line number, retrieved using __LINE__, for instance
   * @param fail_function pointer to a function to invoke in case the operation failed
   * @note 'fail_function' should accept the same parameters as AssertFailFunction, however, it is
   *       made a template to also potentially allow for lambda expressions etc.
   * @see Operation
   * @see AssertFailFunction
   */
  template<typename OperationT, typename FailFunctionT>
  void assertOp(OperationT const& operation,
                char const* file,
                char const* function,
                unsigned int line,
                FailFunctionT const& fail_function)
  {
    if (!operation())
    {
      typedef utl::MemoryBuffer<256, NoWrite> Buffer;
      typedef utl::OutStream Stream;

      NoWrite writer;
      Buffer buffer(writer);
      Stream stream(buffer);

      /*
       * Write a string representation of the given operation in our
       * stream object
       */
      operation.write(stream);

      /*
       * The buffer used for storing the stream's immediate output will
       * now contain a user readable string of the operation that failed
       * and its input parameters.
       */
      fail_function((char const*)buffer.buffer(), file, line, function);
    }
  }
}


#endif
