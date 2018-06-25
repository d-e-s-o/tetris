// TestContainer.hpp

/***************************************************************************
 *   Copyright (C) 2009-2010,2012 Daniel Mueller (deso@posteo.net)         *
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

#ifndef TSTTESTCONTAINER_HPP
#define TSTTESTCONTAINER_HPP


namespace tst
{
  /**
   * Objects of this class can be used to group and store a set of test
   * related objects. Since dynamic allocation is not desired in some
   * scenarios, it uses a fixed (user-sizable) storage.
   */
  template<typename T, unsigned int MAX_TESTS>
  class TestContainer
  {
  public:
    typedef T* Iterator;

    TestContainer();

    TestContainer(TestContainer&&) = delete;
    TestContainer(TestContainer const&) = delete;

    TestContainer& operator =(TestContainer&&) = delete;
    TestContainer& operator =(TestContainer const&) = delete;

    bool add(T const& test);

    Iterator begin();
    Iterator end();

  private:
    T tests_[MAX_TESTS];
    int index_;
  };
}

namespace tst
{
  /**
   * The default constructor creates an empty TestContainer.
   */
  template<typename T, unsigned int MAX_TESTS>
  inline TestContainer<T, MAX_TESTS>::TestContainer()
    : index_(0)
  {
  }

  /**
   * This method can be used to add a new test to the container.
   * @param test test case or test suite to add
   * @return true if adding the test was successful, false if not
   */
  template<typename T, unsigned int MAX_TESTS>
  inline bool TestContainer<T, MAX_TESTS>::add(T const& test)
  {
    if (index_ < MAX_TESTS)
    {
      tests_[index_++] = test;
      return true;
    }
    return false;
  }

  /**
   * @return an iterator to the first test in the container
   */
  template<typename T, unsigned int MAX_TESTS>
  inline typename TestContainer<T, MAX_TESTS>::Iterator TestContainer<T, MAX_TESTS>::begin()
  {
    return &tests_[0];
  }

  /**
   * @return an iterator to one past the last test in the container
   */
  template<typename T, unsigned int MAX_TESTS>
  inline typename TestContainer<T, MAX_TESTS>::Iterator TestContainer<T, MAX_TESTS>::end()
  {
    return &tests_[index_];
  }
}


#endif
