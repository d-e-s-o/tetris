// Slider.cpp

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

#include <util/Assert.hpp>

#include "gui/widget/RootWidget.hpp"
#include "gui/widget/control/theme/Theme.hpp"
#include "gui/widget/control/Slider.hpp"


namespace gui
{
  /**
   * @copydoc Widget::Widget
   */
  Slider::Slider(Bounds const& bounds)
    : Widget(bounds),
      logic_(*this),
      min_value_(0),
      max_value_(100),
      value_(0)
  {
    setAlwaysOnBottom(true);

    ASSERTOP(min_value_, lt, max_value_);
    ASSERTOP(value_, ge, min_value_);
    ASSERTOP(value_, le, max_value_);
  }

  /**
   * @copydoc Widget::onMouseDown
   */
  void Slider::onMouseDown(Position const& position, MouseButton button)
  {
    logic_.onMouseDown(position, button);
  }

  /**
   * @copydoc Widget::onMouseUp
   */
  void Slider::onMouseUp(Position const& position, MouseButton button)
  {
    logic_.onMouseUp(position, button);
  }

  /**
   * @copydoc Widget::onMouseMove
   */
  void Slider::onMouseMove(Position const& position)
  {
    logic_.onMouseMove(position);
  }

  /**
   * @copydoc Widget::onKeyDown
   */
  void Slider::onKeyDown(Key key, ModifierKey modifier)
  {
    logic_.onKeyDown(key, modifier);
  }

  /**
   * This method is called whenever the value of the slider changes.
   */
  void Slider::onChange()
  {
  }

  /**
   * With this method the lower bound of the slider can be set.
   * @param max_value new lower bound value of the slider
   * @note that if the min value is greater or equal the max value nothing will be done
   */
  void Slider::setMinValue(int min_value)
  {
    if (min_value < max_value_)
    {
      min_value_ = min_value;

      if (value_ < min_value)
        setValue(min_value);
    }
  }

  /**
   * With this method the upper bound of the slider can be set.
   * @param max_value new upper bound value of the slider
   * @note that of the max value is less or equal the min value nothing will be done
   */
  void Slider::setMaxValue(int max_value)
  {
    if (max_value > min_value_)
    {
      max_value_ = max_value;

      if (value_ > max_value)
        setValue(max_value);
    }
  }

  /**
   * This method set the value of the slider control. If the value to set is not within bounds
   * set with SetMinValue and SetMaxValue then the corresponding bound value (lower or upper) is
   * used.
   * @param position the new slider position
   */
  void Slider::setValue(int value)
  {
    if (value < min_value_)
      value = min_value_;
    else if (value > max_value_)
      value = max_value_;

    if (value != value_)
    {
      value_ = value;

      onChange();
    }
    ASSERTOP(value_, ge, min_value_);
    ASSERTOP(value_, le, max_value_);
  }

  /**
   * @return the space between the left and right edge of the client area and the beginning/end
   *         of the line
   */
  SizeT Slider::getLineSpace() const
  {
    return rootWidget()->getTheme().getControlTheme<Slider>().line_space;
  }

  /**
   * @return the height of the line the bar moves on
   */
  SizeT Slider::getLineHeight() const
  {
    return rootWidget()->getTheme().getControlTheme<Slider>().line_height;
  }

  /**
   * @return the space between the slider and the lower and upper edges of the client area
   */
  SizeT Slider::getSliderSpace() const
  {
    return rootWidget()->getTheme().getControlTheme<Slider>().slider_space;
  }

  /**
   * @return the width of the slider
   */
  SizeT Slider::getSliderWidth() const
  {
    return rootWidget()->getTheme().getControlTheme<Slider>().slider_width;
  }

  /**
   * @copydoc Widget::renderWidget
   */
  void Slider::renderWidget(Size const& size) const
  {
    ASSERTOP(rootWidget(), ne, nullptr);

    rootWidget()->getTheme().getControlTheme<Slider>().renderWidget(*this, size);
  }

  /**
   * @copydoc Widget::renderContent
   */
  void Slider::renderContent(Size const& size) const
  {
    ASSERTOP(rootWidget(), ne, nullptr);

    rootWidget()->getTheme().getControlTheme<Slider>().renderContent(*this, size);
  }
}
