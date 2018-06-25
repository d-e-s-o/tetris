// Decltype.hpp

/***************************************************************************
 *   Copyright (C) 2012 Daniel Mueller                                     *
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

#ifndef TYPDECLTYPE_HPP
#define TYPDECLTYPE_HPP


namespace typ
{
  template <typename T>
  struct LambdaReturnType
  {
    typedef typename LambdaReturnType<decltype(&T::operator())>::Type Type;
  };


  template <typename ReturnT, typename ...ArgumentsT>
  constexpr ReturnT returnType(ReturnT (*)(ArgumentsT...));

  template <typename ReturnT, typename ClassT, typename ...ArgumentsT>
  constexpr ReturnT returnType(ReturnT (ClassT::*)(ArgumentsT...));

  // lambdas are bitches!
  template <typename ClassT>
  constexpr typename LambdaReturnType<ClassT>::Type returnType(ClassT);

  template <typename ReturnT, typename ClassT, typename ...ArgumentsT>
  constexpr ClassT classType(ReturnT (ClassT::*)(ArgumentsT...));

  template <typename ReturnT, typename ClassT, typename ...ArgumentsT>
  constexpr ClassT& classTypeR(ReturnT (ClassT::*)(ArgumentsT...));
}


namespace typ
{
  /**
   * Specializations of LambdaReturnType for various signatures.
   */

  template <typename R, typename C, typename... A>
  struct LambdaReturnType<R (C::*)(A...)>
  {
    typedef R Type;
  };

  template <typename R, typename C, typename... A>
  struct LambdaReturnType<R (C::*)(A...) const>
  {
    typedef R Type;
  };

  template <typename R, typename... A>
  struct LambdaReturnType<R (*)(A...)>
  {
    typedef R Type;
  };
}


#endif
