// TestNamespaceManager.hpp

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

#ifndef GUITESTRESOURCEMANAGER_HPP
#define GUITESTRESOURCEMANAGER_HPP

#include <test/TestCase.hpp>

#include "gui/MemoryNamespace.hpp"
#include "gui/NamespaceManager.hpp"


namespace test
{
  class TestNamespaceManager: public tst::TestCase<TestNamespaceManager>
  {
  public:
    TestNamespaceManager();

    void testOpen1(tst::TestResult& result);
    void testOpen2(tst::TestResult& result);

  protected:
    virtual void setUp();

  private:
    gui::MemoryNamespace  memory_namespace_1_;
    gui::MemoryNamespace  memory_namespace_2_;
    gui::NamespaceManager namespace_manager_;
  };
}


#endif
