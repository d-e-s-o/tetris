// Deferer.hpp

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

#ifndef TYPDEFER_HPP
#define TYPDEFER_HPP

#include "type/Config.hpp"
#include "type/Function.hpp"


namespace typ
{
  /**
   * @param FunctionT
   * @param ArgumentsT
   */
  template<typename FunctionT, typename ...ArgumentsT>
  class Deferer
  {
  public:
    Deferer(FunctionT function, ArgumentsT... arguments);
    Deferer(Deferer const&) = delete;
    Deferer(Deferer&&) = default;
    ~Deferer();

    Deferer operator =(Deferer const&) = delete;
    Deferer operator =(Deferer&&) = delete;

    void release();

  private:
    Function<FunctionT, ArgumentsT...> function_;
    bool released_;
  };


  template<typename FunctionT, typename ...ArgumentsT>
  Deferer<FunctionT, ArgumentsT...> defer(FunctionT function, ArgumentsT... arguments);

  template<typename DefererT, typename ...DeferersT>
  void release(DefererT& deferer, DeferersT&... deferers);

  template<typename DefererT>
  void release(DefererT& deferer);

#define CONCATENATE_HELPER(X,Y) X##Y
#define CONCATENATE(X,Y) CONCATENATE_HELPER(X,Y)
#define DEFERX(x__, ...)\
  auto CONCATENATE(d, __LINE__) = typ::defer(x__, ##__VA_ARGS__)
#define DEFER(n__, x__, ...)\
  auto n__ = typ::defer(x__, ##__VA_ARGS__)
#define RELEASE(...)\
  typ::release(__VA_ARGS__)
}


namespace typ
{
  /**
   * @param function some function to be invoked when the Deferer object is destroyed
   * @param arguments arguments to the given function
   */
  template<typename FunctionT, typename ...ArgumentsT>
  inline Deferer<FunctionT, ArgumentsT...>::Deferer(FunctionT function, ArgumentsT... arguments)
    : function_(function, arguments...),
      released_(false)
  {
  }

  /**
   * The destructor destroys the Deferer object and invokes the to-be-defered function.
   */
  template<typename FunctionT, typename ...ArgumentsT>
  inline Deferer<FunctionT, ArgumentsT...>::~Deferer()
  {
    if (!released_)
      function_();
  }

  /**
   * This method releases the deferer from its job of invoking the passed in function when it is
   * destroyed.
   */
  template<typename FunctionT, typename ...ArgumentsT>
  inline void Deferer<FunctionT, ArgumentsT...>::release()
  {
    released_ = true;
  }

  /**
   * @param function
   * @param arguments
   */
  template<typename FunctionT, typename ...ArgumentsT>
  inline Deferer<FunctionT, ArgumentsT...> defer(FunctionT function, ArgumentsT... arguments)
  {
    return Deferer<FunctionT, ArgumentsT...>(function, arguments...);
  }

  /**
   * @param deferer
   * @param deferers
   */
  template<typename DefererT, typename ...DeferersT>
  inline void release(DefererT& deferer, DeferersT&... deferers)
  {
    deferer.release();
    release(deferers...);
  }

  /**
   * This function releases a single Deferer object. It is used for ending the recursion of the
   * variadic release function.
   */
  template<typename DefererT>
  inline void release(DefererT& deferer)
  {
    deferer.release();
  }
}


#endif
