// EditBoxLogic.hpp

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

#ifndef GUIEDITBOXLOGIC_HPP
#define GUIEDITBOXLOGIC_HPP

#include <util/Assert.hpp>

#include "gui/widget/control/CaptureLogic.hpp"
#include "gui/widget/control/theme/Theme.hpp"


namespace gui
{
  /**
   * This class is responsible for being able to move the EditBox' caret with the mouse
   * @note this class is a template because otherwise we had to include EditBox which would be
   *       a cyclic dependency
   */
  template<typename T>
  class EditBoxLogic: public CaptureLogic<T>
  {
  public:
    EditBoxLogic(T& widget);

    void onMouseDown(Position const& position, MouseButton button);
    void onMouseUp(Position const& position, MouseButton button);
    void onMouseMove(Position const& position);

  private:
    void setSelectionFromX(PositionT x, bool reset);
  };
}


namespace gui
{
  /**
   *
   */
  template<typename T>
  inline EditBoxLogic<T>::EditBoxLogic(T& widget)
    : CaptureLogic<T>(widget)
  {
  }

  /**
   * @copydoc EditBox::onMouseDown
   */
  template<typename T>
  inline void EditBoxLogic<T>::onMouseDown(Position const& position, MouseButton button)
  {
    T const& widget = this->getWidget();

    if (widget.focused() || widget.getCaret() == widget.getSelection())
    {
      if (button == widget.rootWidget()->getTheme().actionButton())
      {
        ASSERT(!this->isCaptured());

        this->setCapture(true);
        this->setSelectionFromX(position.x, true);
      }
    }
  }

  /**
   * @copydoc EditBox::onMouseUp
   */
  template<typename T>
  inline void EditBoxLogic<T>::onMouseUp(Position const& position, MouseButton button)
  {
    if (button == this->getWidget().rootWidget()->getTheme().actionButton())
      this->setCapture(false);
  }

  /**
   * @copydoc EditBox::onMouseMove
   */
  template<typename T>
  inline void EditBoxLogic<T>::onMouseMove(Position const& position)
  {
    if (this->isCaptured())
      setSelectionFromX(position.x, false);
  }

  /**
   *
   */
  template<typename T>
  void EditBoxLogic<T>::setSelectionFromX(PositionT x, bool reset)
  {
    T&           widget = this->getWidget();
    Theme const& theme  = widget.rootWidget()->getTheme();

    SizeT       space = theme.getControlTheme<EditBox>().text_space;
    Font const* font  = theme.getControlTheme<EditBox>().font;

    size_t caret = getCaretIndex(*font, widget.getText(), x - space);
    ASSERTOP(caret, ge, 0);
    ASSERTOP(caret, le, widget.getText().size());

    widget.setCaret(caret, !reset);
  }
}


#endif
