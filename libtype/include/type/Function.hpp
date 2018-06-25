// Function.hpp

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

#ifndef TYPFUNCTION_HPP
#define TYPFUNCTION_HPP

#include "type/Config.hpp"
#include "type/Tuple.hpp"
#include "type/Decltype.hpp"


namespace typ
{
  /**
   * This type represents a list of indices.
   */
  template<size_t ...>
  struct IndexList
  {
  };

  /**
   * @param Count number of indices
   * @param List list of indices
   */
  template<size_t Count, size_t ...List>
  struct IndexListGenerator: IndexListGenerator<Count - 1, Count - 1, List...>
  {
  };

  /**
   * This specialization terminates the recursion when the Count reaches zero.
   */
  template<size_t ...List>
  struct IndexListGenerator<0, List...>
  {
    typedef IndexList<List...> Type;
  };

  /**
   * @param FunctionT
   * @param ArgumentsT
   * @note I have no idea why but gcc insists on having me define everything inline here,
   *       otherwise strange "invalid use of incomplete type" messages pop up
   * @todo we need perfect forwarding here
   */
  template<typename FunctionT, typename ...ArgumentsT>
  class Function
  {
  private:
    FunctionT function_;

  public:
    typedef decltype(typ::returnType(function_)) ResultT;
    typedef typ::Tuple<ArgumentsT...> Arguments;

    /**
     *
     */
    Function(FunctionT function, ArgumentsT... arguments)
      : function_(function),
        arguments_(typ::makeTuple(arguments...))
    {
    }

    /**
     * @return
     */
    ResultT operator()()
    {
      // generate a list for each with indices [0..Number of Arguments-1]
      return invoke(typename IndexListGenerator<sizeof...(ArgumentsT)>::Type());
    }

    /**
     * @return a tuple of the function's arguments
     */
    Arguments const& arguments() const
    {
      return arguments_;
    }

  private:
    Arguments arguments_;

    /**
     * @param list only used for automatic template deduction, actual object is unused
     */
    template<size_t ...IndicesT>
    ResultT invoke(IndexList<IndicesT...> const& list)
    {
      // this is basically a get<> for each index in the given index list IndicesT
      return function_(typ::get<IndicesT>(arguments_)...);
    }
  };

  /**
   * Specialization of Function for functions accepting no arguments.
   * @param FunctionT
   */
  template<typename FunctionT>
  class Function<FunctionT>
  {
  private:
    FunctionT function_;

  public:
    typedef decltype(typ::returnType(function_)) ResultT;

    Function(FunctionT function)
      : function_(function)
    {
    }

    ResultT operator()()
    {
      return function_();
    }
  };

  /**
   * This class is the base class for the typ::DynamicFunctionImpl type. It provides the interface
   * for invoking a function of any type without having the type issues you get from the template
   * parameters associated with typ::Function or typ::DynamicFunction.
   */
  class DynamicFunction
  {
  public:
    virtual ~DynamicFunction() = default;
    virtual void operator()() = 0;
  };


  /**
   * @param FunctionT
   * @param ArgumentsT
   */
  template<typename FunctionT, typename ...ArgumentsT>
  class DynamicFunctionImpl: public DynamicFunction
  {
  public:
    /**
     * @copydoc Function::Function
     */
    DynamicFunctionImpl(FunctionT function, ArgumentsT... arguments)
      : function_(function, arguments...)
    {
    }

    /**
     * Execute the function given during construction.
     */
    virtual void operator()() override
    {
      function_();
    }

  private:
    Function<FunctionT, ArgumentsT...> function_;
  };
}


#endif
