// TestSet.hpp

/***************************************************************************
 *   Copyright (C) 2012 Daniel Mueller (deso@posteo.net)                   *
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

#ifndef CTRTESTSET_HPP
#define CTRTESTSET_HPP

#include <test/TestCase.hpp>
#include <container/Set.hpp>


namespace test
{
  class TestSet: public tst::TestCase<TestSet>
  {
  public:
    TestSet();

    void testInsert1(tst::TestResult& result);

  protected:
    virtual void setUp();

  private:
    typedef ctr::Set<int> Set;

    Set set_;
  };
}


#endif
