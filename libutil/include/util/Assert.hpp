// Assert.hpp

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

/**
 * This file provides assertion support. We offer two types of assertions:
 * 1) very simple ASSERT(boolean) style assertions
 * 2) more sophisticated ASSERTOP(value1, operation, value2) assertions
 *
 * The former (1) are relevant in contexts were not more more information apart from a boolean value is
 * available. The latter (2) can be used for binary operations such as all comparisons: ==, !=, <,
 * >, <=, and >=. Assertions of type (2) convey the values of the input parameters to the user.
 */

#ifndef UTLASSERT_HPP
#define UTLASSERT_HPP

#include "util/Config.hpp"
#include "util/AssertImpl.hpp"


#ifndef NDEBUG
extern "C" void __assert_fail(char const* assertion,
                              char const* file,
                              unsigned int line,
                              char const* function) throw();
#  define ASSERT(condition_)\
     ASSERT_IMPL(condition_, __assert_fail)
#  define ASSERTOP(first_, operation_, second_)\
     ASSERTOP_IMPL(first_, operation_, second_, __assert_fail)
#  define ASSERT_STATIC(condition_)\
     static_assert(condition_, "\"" #condition_ "\" failed")
#else
#  define ASSERT(condition_)
#  define ASSERTOP(first_, operation_, second_)
#  define ASSERT_STATIC(condition_)
#endif


#endif
