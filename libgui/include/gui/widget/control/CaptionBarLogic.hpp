// CaptionBarLogic.hpp

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

#ifndef GUICAPTIONBARLOGIC_HPP
#define GUICAPTIONBARLOGIC_HPP

#include "gui/widget/WidgetFunctions.hpp"
#include "gui/widget/control/CaptureLogic.hpp"


namespace gui
{
  /**
   *
   */
  template<typename T>
  class CaptionBarLogic: public CaptureLogic<T>
  {
  public:
    CaptionBarLogic(T& caption_bar, Widget& widget);

    void onMouseDown(Position const& position, MouseButton button);
    void onMouseUp(Position const& position, MouseButton button);
    void onMouseMove(Position const& position);

  private:
    Widget*  widget_;
    Position mouse_last_;
  };
}


namespace gui
{
  /**
   *
   */
  template<typename T>
  CaptionBarLogic<T>::CaptionBarLogic(T& caption_bar, Widget& widget)
    : CaptureLogic<T>(caption_bar),
      widget_(&widget),
      mouse_last_()
  {
  }

  /**
   * This method sets the widget state to pressed if the button is the "right" one.
   */
  template<typename T>
  void CaptionBarLogic<T>::onMouseDown(Position const& position, MouseButton button)
  {
    // a click within the caption bars area sets a mouse capture to keep track of the movement
    if (button == this->getWidget().rootWidget()->getTheme().actionButton())
    {
      this->setCapture(true);
      mouse_last_ = position;
    }
  }

  /**
   *
   */
  template<typename T>
  void CaptionBarLogic<T>::onMouseUp(Position const& position, MouseButton button)
  {
    // mouse releases also release the capture
    if (this->isCaptured())
    {
      if (button == this->getWidget().rootWidget()->getTheme().actionButton())
        this->setCapture(false);
    }
  }

  /**
   *
   */
  template<typename T>
  void CaptionBarLogic<T>::onMouseMove(Position const& position)
  {
    if (this->isCaptured())
    {
      // move the widget by the amount the mouse was moved and update the last position
      Position amount = position - mouse_last_;
      move(*widget_, amount);
      mouse_last_ = position - amount;
    }
  }
}


#endif
