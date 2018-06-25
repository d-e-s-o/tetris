// SliderLogic.hpp

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

#ifndef GUISLIDERLOGIC_HPP
#define GUISLIDERLOGIC_HPP

#include <util/Assert.hpp>

#include "gui/widget/control/CaptureLogic.hpp"


namespace gui
{
  /**
   *
   */
  template<typename T>
  class SliderLogic: public CaptureLogic<T>
  {
  public:
    SliderLogic(T& widget);

    void onMouseDown(Position const& position, MouseButton button);
    void onMouseUp(Position const& position, MouseButton button);
    void onMouseMove(Position const& position);
    void onKeyDown(Key key, ModifierKey modifier);

  private:
    void setValueFromX(PositionT x);
  };
}


namespace gui
{
  /**
   *
   */
  template<typename T>
  SliderLogic<T>::SliderLogic(T& widget)
    : CaptureLogic<T>(widget)
  {
  }

  /**
   * @copydoc Slider::onMouseDown
   */
  template<typename T>
  void SliderLogic<T>::onMouseDown(Position const& position, MouseButton button)
  {
    if (button == this->getWidget().rootWidget()->getTheme().actionButton())
    {
      ASSERT(!this->isCaptured());

      this->setCapture(true);
      this->setValueFromX(position.x);
    }
  }

  /**
   * @copydoc Slider::onMouseUp
   */
  template<typename T>
  void SliderLogic<T>::onMouseUp(Position const& position, MouseButton button)
  {
    if (button == this->getWidget().rootWidget()->getTheme().actionButton())
    {
      this->setCapture(false);
      this->setValueFromX(position.x);
    }
  }

  /**
   * @copydoc Slider::onMouseMove
   */
  template<typename T>
  void SliderLogic<T>::onMouseMove(Position const& position)
  {
    if (this->isCaptured())
      this->setValueFromX(position.x);
  }

  template<typename T>
  void SliderLogic<T>::onKeyDown(Key key, ModifierKey modifier)
  {
    T& widget = this->getWidget();

    if (key == widget.rootWidget()->getTheme().leftKey())
      widget.setValue(widget.getValue() - 1);

    if (key == widget.rootWidget()->getTheme().rightKey())
      widget.setValue(widget.getValue() + 1);
  }

  /**
   * This method calculates and sets the slider value from a given x coordinate, where a click
   * or something like that happened.
   * @param x x-position relative to client area origin
   */
  template<typename T>
  void SliderLogic<T>::setValueFromX(PositionT x)
  {
    T& widget = this->getWidget();

    SizeT space = widget.getLineSpace();
    SizeT width = widget.clientArea().w - 2 * space;

    int min = widget.getMinValue();
    int max = widget.getMaxValue();

    // add 0.5 to make it look more smooth when scrolling over a small range (max - min) and in
    // general make better "matches"
    int value = static_cast<int>(1.0f * (x - space) * (max - min) / width + 0.5f);
    widget.setValue(value);
  }
}


#endif
