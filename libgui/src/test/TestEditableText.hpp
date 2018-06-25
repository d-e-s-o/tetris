// TestEditableText.hpp

/***************************************************************************
 *   Copyright (C) 2006-2012 Daniel Mueller (deso@posteo.net)              *
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

#ifndef TESTTESTEDITABLETEXT_HPP
#define TESTTESTEDITABLETEXT_HPP

#include <test/TestCase.hpp>


namespace gui
{
  class EditableText;
}

namespace test
{
  class TestEditableText: public tst::TestCase<TestEditableText>
  {
  public:
    TestEditableText();

    void testConstruction1(tst::TestResult& result);
    void testSetText1(tst::TestResult& result);
    void testSetCaret1(tst::TestResult& result);
    void testSetCaret2(tst::TestResult& result);
    void testSetCaret3(tst::TestResult& result);
    void testMoveCaret1(tst::TestResult& result);
    void testMoveCaret2(tst::TestResult& result);
    void testMoveCaret3(tst::TestResult& result);
    void testMoveCaret4(tst::TestResult& result);
    void testInsertChar1(tst::TestResult& result);
    void testInsertChar2(tst::TestResult& result);
    void testInsertChar3(tst::TestResult& result);
    void testEraseChar1(tst::TestResult& result);
    void testEraseChar2(tst::TestResult& result);
    void testEraseChar3(tst::TestResult& result);
    void testEraseChar4(tst::TestResult& result);

  protected:
    virtual void setUp();
    virtual void tearDown();

  private:
    gui::EditableText* text_;
  };
}


#endif
