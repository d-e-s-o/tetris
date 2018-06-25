// TestTraits.cpp

/***************************************************************************
 *   Copyright (C) 2012,2014 Daniel Mueller                                *
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

#include <type/Traits.hpp>

#include "TestTraits.hpp"


namespace test
{
  namespace
  {
    struct Foo
    {
    };
  }


  TestTraits::TestTraits()
    : tst::TestCase<TestTraits>(*this, "TestTraits")
  {
    add(&TestTraits::testEqual1);
    add(&TestTraits::testEqual2);
    add(&TestTraits::testRemoveConst1);
    add(&TestTraits::testRemovePointer1);
    add(&TestTraits::testRemoveReference1);

    add(&TestTraits::testIsBuiltIn1);
    add(&TestTraits::testIsBuiltIn2);

    add(&TestTraits::testMakeConst1);
  }

  void TestTraits::testEqual1(tst::TestResult& result)
  {
    TESTASSERT((typ::Equal<int,        int       >::Value));
    TESTASSERT((typ::Equal<double,     double    >::Value));
    TESTASSERT((typ::Equal<int const*, int const*>::Value));
  }

  void TestTraits::testEqual2(tst::TestResult& result)
  {
    TESTASSERT((!typ::Equal<int,         double    >::Value));
    TESTASSERT((!typ::Equal<double,      void*     >::Value));
    TESTASSERT((!typ::Equal<void const*, int const*>::Value));
  }

  void TestTraits::testRemoveConst1(tst::TestResult& result)
  {
    TESTASSERT((typ::Equal<typ::RemoveConst<int const          >::Type, int              >::Value));
    TESTASSERT((typ::Equal<typ::RemoveConst<void const*** const>::Type, void const***    >::Value));
    TESTASSERT((typ::Equal<typ::RemoveConst<double const&      >::Type, double const&    >::Value));
    TESTASSERT((typ::Equal<typ::RemoveConst<int const* const&  >::Type, int const* const&>::Value));
  }

  void TestTraits::testRemovePointer1(tst::TestResult& result)
  {
    TESTASSERT((typ::Equal<typ::RemovePointer<void              >::Type, void              >::Value));
    TESTASSERT((typ::Equal<typ::RemovePointer<int const         >::Type, int const         >::Value));
    TESTASSERT((typ::Equal<typ::RemovePointer<int const*        >::Type, int const         >::Value));
    TESTASSERT((typ::Equal<typ::RemovePointer<float const&      >::Type, float const&      >::Value));
    TESTASSERT((typ::Equal<typ::RemovePointer<char const* const&>::Type, char const* const&>::Value));
  }

  void TestTraits::testRemoveReference1(tst::TestResult& result)
  {
    TESTASSERT((typ::Equal<typ::RemoveReference<int const         >::Type, int const        >::Value));
    TESTASSERT((typ::Equal<typ::RemoveReference<int const*        >::Type, int const*       >::Value));
    TESTASSERT((typ::Equal<typ::RemoveReference<int const&        >::Type, int const        >::Value));
    TESTASSERT((typ::Equal<typ::RemoveReference<char const* const&>::Type, char const* const>::Value));
    TESTASSERT((typ::Equal<typ::RemoveReference<void* const&      >::Type, void* const      >::Value));
  }

  void TestTraits::testIsBuiltIn1(tst::TestResult& result)
  {
    TESTASSERT(typ::IsBuiltIn<int  const        >::Value);
    TESTASSERT(typ::IsBuiltIn<void const*       >::Value);
    TESTASSERT(typ::IsBuiltIn<double            >::Value);
    TESTASSERT(typ::IsBuiltIn<void const* const&>::Value);
    TESTASSERT(typ::IsBuiltIn<double const*****&>::Value);
    TESTASSERT(typ::IsBuiltIn<Foo*              >::Value);
    TESTASSERT(typ::IsBuiltIn<Foo const* const  >::Value);
    TESTASSERT(typ::IsBuiltIn<Foo*&             >::Value);
  }

  void TestTraits::testIsBuiltIn2(tst::TestResult& result)
  {
    TESTASSERT(!typ::IsBuiltIn<Foo       >::Value);
    TESTASSERT(!typ::IsBuiltIn<Foo&      >::Value);
    TESTASSERT(!typ::IsBuiltIn<Foo const >::Value);
    TESTASSERT(!typ::IsBuiltIn<Foo const&>::Value);
  }

  void TestTraits::testMakeConst1(tst::TestResult& result)
  {
    TESTASSERT((typ::Equal<typ::MakeConst<int              >::Type, int const        >::Value));
    TESTASSERT((typ::Equal<typ::MakeConst<int const        >::Type, int const        >::Value));
    TESTASSERT((typ::Equal<typ::MakeConst<void*            >::Type, void* const      >::Value));
    TESTASSERT((typ::Equal<typ::MakeConst<void const*      >::Type, void const* const>::Value));
    TESTASSERT((typ::Equal<typ::MakeConst<char&            >::Type, char const&      >::Value));
    TESTASSERT((typ::Equal<typ::MakeConst<int const* const&>::Type, int const* const&>::Value));
  }
}
