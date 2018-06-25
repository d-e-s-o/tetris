// Slider.hpp

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

#ifndef GUISLIDER_HPP
#define GUISLIDER_HPP

#include <util/Assert.hpp>

#include "gui/widget/Widget.hpp"
#include "gui/widget/control/SliderLogic.hpp"


namespace gui
{
  /**
   * This class represents a slider control for manipulating an integer value within variable
   * bounds. Depending on the theme it may consist of a horizontal line with a vertical bar on it
   * which signalizes the current value.
   * @todo rename this one to HorizontalSlider and create base class and create VerticalSlider
   */
  class LIBGUI_EXPORT Slider: public Widget
  {
  public:
    Slider(Bounds const& bounds);

    virtual void onMouseDown(Position const& position, MouseButton button);
    virtual void onMouseUp(Position const& position, MouseButton button);
    virtual void onMouseMove(Position const& position);
    virtual void onKeyDown(Key key, ModifierKey modifier);

    virtual void onChange();

    int getMinValue() const;
    void setMinValue(int min_value);

    int getMaxValue() const;
    void setMaxValue(int max_value);

    int getValue() const;
    void setValue(int value);

    SizeT getLineSpace() const;
    SizeT getLineHeight() const;
    SizeT getSliderSpace() const;
    SizeT getSliderWidth() const;

  protected:
    virtual void renderWidget(Size const& size) const;
    virtual void renderContent(Size const& size) const;

  private:
    SliderLogic<Slider> logic_;

    int min_value_;
    int max_value_;
    int value_;
  };
}


namespace gui
{
  /**
   * @return lower bound of the sliders value
   */
  inline int Slider::getMinValue() const
  {
    return min_value_;
  }

  /**
   * @return upper bound of the sliders value
   */
  inline int Slider::getMaxValue() const
  {
    return max_value_;
  }

  /**
   * @return current position of the slider
   */
  inline int Slider::getValue() const
  {
    ASSERTOP(value_, ge, min_value_);
    ASSERTOP(value_, le, max_value_);
    return value_;
  }
}


#endif
