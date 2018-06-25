// TestEditableText.cpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#include <gui/widget/control/EditableText.hpp>

#include "TestEditableText.hpp"


namespace test
{
  TestEditableText::TestEditableText()
    : tst::TestCase<TestEditableText>(*this, "TestEditableText")
  {
    add(&TestEditableText::testConstruction1);
    add(&TestEditableText::testSetText1);
    add(&TestEditableText::testSetCaret1);
    add(&TestEditableText::testSetCaret2);
    add(&TestEditableText::testSetCaret3);
    add(&TestEditableText::testMoveCaret1);
    add(&TestEditableText::testMoveCaret2);
    add(&TestEditableText::testMoveCaret3);
    add(&TestEditableText::testMoveCaret4);
    add(&TestEditableText::testInsertChar1);
    add(&TestEditableText::testInsertChar2);
    add(&TestEditableText::testInsertChar3);
    add(&TestEditableText::testEraseChar1);
    add(&TestEditableText::testEraseChar2);
    add(&TestEditableText::testEraseChar3);
    add(&TestEditableText::testEraseChar4);
  }

  void TestEditableText::setUp()
  {
    text_ = new gui::EditableText;
  }

  void TestEditableText::tearDown()
  {
    delete text_;
  }

  void TestEditableText::testConstruction1(tst::TestResult& result)
  {
    TESTASSERTOP(text_->getText().size(), eq, 0);
    TESTASSERTOP(text_->getCaret(), eq, 0);
    TESTASSERTOP(text_->getSelection(), eq, 0);
  }

  void TestEditableText::testSetText1(tst::TestResult& result)
  {
    text_->setText(gui::String(TEXT("test")));

    TESTASSERT(text_->getText() == gui::String(TEXT("test")));
    TESTASSERTOP(text_->getCaret(), eq, 4);
    TESTASSERTOP(text_->getSelection(), eq, 4);
  }

  void TestEditableText::testSetCaret1(tst::TestResult& result)
  {
    text_->setText(gui::String(TEXT("test1")));
    text_->setCaret(gui::EditableText::CARET_BEGIN);

    TESTASSERTOP(text_->getCaret(), eq, 0);
    TESTASSERTOP(text_->getSelection(), eq, 0);

    text_->setCaret(gui::EditableText::CARET_END);

    TESTASSERTOP(text_->getCaret(), eq, 5);
    TESTASSERTOP(text_->getSelection(), eq, 5);

    text_->setCaret(1);

    TESTASSERTOP(text_->getCaret(), eq, 1);
    TESTASSERTOP(text_->getSelection(), eq, 1);
  }

  void TestEditableText::testSetCaret2(tst::TestResult& result)
  {
    text_->setCaret(1);

    TESTASSERTOP(text_->getCaret(), eq, 0);
    TESTASSERTOP(text_->getSelection(), eq, 0);

    text_->setText(gui::String(TEXT("test2")));
    text_->setCaret(6);

    TESTASSERTOP(text_->getCaret(), eq, 5);
    TESTASSERTOP(text_->getSelection(), eq, 5);
  }

  void TestEditableText::testSetCaret3(tst::TestResult& result)
  {
    text_->setText(gui::String(TEXT("testhg")));
    text_->setCaret(1);

    TESTASSERTOP(text_->getCaret(), eq, 1);
    TESTASSERTOP(text_->getSelection(), eq, 1);

    text_->setCaret(gui::EditableText::CARET_END, true);

    TESTASSERTOP(text_->getCaret(), eq, 6);
    TESTASSERTOP(text_->getSelection(), eq, 1);
  }

  void TestEditableText::testMoveCaret1(tst::TestResult& result)
  {
    text_->moveCaretLeft(false);

    TESTASSERTOP(text_->getCaret(), eq, 0);
    TESTASSERTOP(text_->getSelection(), eq, 0);

    text_->moveCaretLeft(true);

    TESTASSERTOP(text_->getCaret(), eq, 0);
    TESTASSERTOP(text_->getSelection(), eq, 0);

    text_->setText(gui::String(TEXT("test12")));
    text_->moveCaretLeft(false);

    TESTASSERTOP(text_->getCaret(), eq, 5);
    TESTASSERTOP(text_->getSelection(), eq, 5);

    text_->moveCaretLeft(true);
    TESTASSERTOP(text_->getCaret(), eq, 4);
    TESTASSERTOP(text_->getSelection(), eq, 5);
  }

  void TestEditableText::testMoveCaret2(tst::TestResult& result)
  {
    text_->moveCaretRight(false);

    TESTASSERTOP(text_->getCaret(), eq, 0);
    TESTASSERTOP(text_->getSelection(), eq, 0);

    text_->moveCaretRight(true);

    TESTASSERTOP(text_->getCaret(), eq, 0);
    TESTASSERTOP(text_->getSelection(), eq, 0);

    text_->setText(gui::String(TEXT("test12")));
    text_->setCaret(gui::EditableText::CARET_BEGIN);
    text_->moveCaretRight(false);

    TESTASSERTOP(text_->getCaret(), eq, 1);
    TESTASSERTOP(text_->getSelection(), eq, 1);

    text_->moveCaretRight(true);
    TESTASSERTOP(text_->getCaret(), eq, 2);
    TESTASSERTOP(text_->getSelection(), eq, 1);
  }

  void TestEditableText::testMoveCaret3(tst::TestResult& result)
  {
    text_->setText(gui::String(TEXT("testabcdefgh")));
    text_->moveCaretLeft(true);
    text_->moveCaretLeft(true);
    text_->moveCaretLeft(true);
    text_->moveCaretLeft(true);

    TESTASSERTOP(text_->getCaret(), eq, 8);
    TESTASSERTOP(text_->getSelection(), eq, 12);

    text_->moveCaretLeft(false);

    TESTASSERTOP(text_->getCaret(), eq, 8);
    TESTASSERTOP(text_->getSelection(), eq, 8);
  }

  void TestEditableText::testMoveCaret4(tst::TestResult& result)
  {
    text_->setText(gui::String(TEXT("testabc")));
    text_->setCaret(gui::EditableText::CARET_BEGIN);
    text_->moveCaretRight(true);
    text_->moveCaretRight(true);
    text_->moveCaretRight(true);
    text_->moveCaretRight(true);

    TESTASSERTOP(text_->getCaret(), eq, 4);
    TESTASSERTOP(text_->getSelection(), eq, 0);

    text_->moveCaretRight(false);

    TESTASSERTOP(text_->getCaret(), eq, 4);
    TESTASSERTOP(text_->getSelection(), eq, 4);
  }

  void TestEditableText::testInsertChar1(tst::TestResult& result)
  {
    text_->insertCharacter(TEXT('a'));

    TESTASSERT(text_->getText() == gui::String(TEXT("a")));
    TESTASSERTOP(text_->getCaret(), eq, 1);
    TESTASSERTOP(text_->getSelection(), eq, 1);

    text_->insertCharacter(TEXT('b'));

    TESTASSERT(text_->getText() == gui::String(TEXT("ab")));
    TESTASSERTOP(text_->getCaret(), eq, 2);
    TESTASSERTOP(text_->getSelection(), eq, 2);
  }

  void TestEditableText::testInsertChar2(tst::TestResult& result)
  {
    text_->setText(gui::String(TEXT("test123")));
    text_->insertCharacter(TEXT('a'));

    TESTASSERT(text_->getText() == gui::String(TEXT("test123a")));
    TESTASSERTOP(text_->getCaret(), eq, 8);
    TESTASSERTOP(text_->getSelection(), eq, 8);

    text_->setCaret(gui::EditableText::CARET_BEGIN);
    text_->insertCharacter(TEXT('b'));

    TESTASSERT(text_->getText() == gui::String(TEXT("btest123a")));
    TESTASSERTOP(text_->getCaret(), eq, 1);
    TESTASSERTOP(text_->getSelection(), eq, 1);

    text_->setCaret(4);
    text_->insertCharacter(TEXT('c'));

    TESTASSERT(text_->getText() == gui::String(TEXT("btesct123a")));
    TESTASSERTOP(text_->getCaret(), eq, 5);
    TESTASSERTOP(text_->getSelection(), eq, 5);
  }

  void TestEditableText::testInsertChar3(tst::TestResult& result)
  {
    text_->setText(gui::String(TEXT("abcdefghijk")));
    text_->moveCaretLeft(true);
    text_->moveCaretLeft(true);
    text_->moveCaretLeft(true);
    text_->moveCaretLeft(true);
    text_->insertCharacter(TEXT('x'));

    TESTASSERT(text_->getText() == gui::String(TEXT("abcdefgx")));
  }

  void TestEditableText::testEraseChar1(tst::TestResult& result)
  {
    text_->eraseLeftCharacter();

    TESTASSERTOP(text_->getText().size(), eq, 0);
    TESTASSERTOP(text_->getCaret(), eq, 0);
    TESTASSERTOP(text_->getSelection(), eq, 0);

    text_->setText(gui::String(TEXT("test1234")));
    text_->eraseLeftCharacter();

    TESTASSERT(text_->getText() == gui::String(TEXT("test123")));
    TESTASSERTOP(text_->getCaret(), eq, 7);
    TESTASSERTOP(text_->getSelection(), eq, 7);

    text_->setCaret(4);
    text_->eraseLeftCharacter();

    TESTASSERT(text_->getText() == gui::String(TEXT("tes123")));
    TESTASSERTOP(text_->getCaret(), eq, 3);
    TESTASSERTOP(text_->getSelection(), eq, 3);
  }

  void TestEditableText::testEraseChar2(tst::TestResult& result)
  {
    text_->eraseRightCharacter();

    TESTASSERTOP(text_->getText().size(), eq, 0);
    TESTASSERTOP(text_->getCaret(), eq, 0);
    TESTASSERTOP(text_->getSelection(), eq, 0);

    text_->setText(gui::String(TEXT("test12345")));
    text_->setCaret(gui::EditableText::CARET_BEGIN);
    text_->eraseRightCharacter();

    TESTASSERT(text_->getText() == gui::String(TEXT("est12345")));
    TESTASSERTOP(text_->getCaret(), eq, 0);
    TESTASSERTOP(text_->getSelection(), eq, 0);

    text_->setCaret(6);
    text_->eraseRightCharacter();

    TESTASSERT(text_->getText() == gui::String(TEXT("est1235")));
    TESTASSERTOP(text_->getCaret(), eq, 6);
    TESTASSERTOP(text_->getSelection(), eq, 6);
  }

  void TestEditableText::testEraseChar3(tst::TestResult& result)
  {
    text_->setText(gui::String(TEXT("123test456")));
    text_->moveCaretLeft(true);
    text_->moveCaretLeft(true);
    text_->moveCaretLeft(true);
    text_->eraseLeftCharacter();

    TESTASSERT(text_->getText() == gui::String(TEXT("123test")));
    TESTASSERTOP(text_->getCaret(), eq, 7);
    TESTASSERTOP(text_->getSelection(), eq, 7);
  }

  void TestEditableText::testEraseChar4(tst::TestResult& result)
  {
    text_->setText(gui::String(TEXT("123test4567")));
    text_->setCaret(gui::EditableText::CARET_BEGIN);
    text_->moveCaretRight(true);
    text_->moveCaretRight(true);
    text_->moveCaretRight(true);
    text_->moveCaretRight(true);
    text_->moveCaretRight(true);
    text_->eraseRightCharacter();

    TESTASSERT(text_->getText() == gui::String(TEXT("st4567")));
    TESTASSERTOP(text_->getCaret(), eq, 0);
    TESTASSERTOP(text_->getSelection(), eq, 0);
  }
}
