// TokenizeTestCase.hpp

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

#ifndef TESTTOKENIZETESTCASE_HPP
#define TESTTOKENIZETESTCASE_HPP

#include <test/TestCase.hpp>

#include "Types.hpp"


namespace test
{
  template<typename T>
  class TokenizeTestCase: public tst::TestCase<T>
  {
  public:
   TokenizeTestCase(T& instance, char const* name = 0);

  protected:
    virtual void setUp();

    Result r_;
    Tokens tokens_;
  };
}


namespace test
{
  template<typename T>
  TokenizeTestCase<T>::TokenizeTestCase(T& instance, char const* name)
    : tst::TestCase<T>(instance, name),
      tokens_()
  {
  }

  template<typename T>
  void TokenizeTestCase<T>::setUp()
  {
    tokens_ = Tokens();
  }
}


#endif
