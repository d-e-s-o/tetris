// ClickLogic.hpp

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

#ifndef GUICLICKLOGIC_HPP
#define GUICLICKLOGIC_HPP

#include <util/Assert.hpp>
#include <util/Rectangle1Functions.hpp>

#include "gui/widget/control/CaptureLogic.hpp"


namespace gui
{
  /**
   *
   */
  template<typename T>
  class ClickLogic: public CaptureLogic<T>
  {
  public:
    ClickLogic(T& widget);

    void onMouseDown(Position const& position, MouseButton button);
    void onMouseUp(Position const& position, MouseButton button);
    void onKeyDown(Key key, ModifierKey modifier);
    void onKeyUp(Key key, ModifierKey modifier);

    bool isPressed() const;

  protected:
    virtual void onClick() = 0;

  private:
    bool pressed_;
  };
}


namespace gui
{
  /**
   *
   */
  template<typename T>
  ClickLogic<T>::ClickLogic(T& widget)
    : CaptureLogic<T>(widget),
      pressed_(false)
  {
  }

  /**
   *
   */
  template<typename T>
  void ClickLogic<T>::onMouseDown(Position const& position, MouseButton button)
  {
    if (button == this->getWidget().rootWidget()->getTheme().actionButton())
    {
      ASSERT(!this->isCaptured());
      this->setCapture(true);
    }
  }

  /**
   *
   */
  template<typename T>
  void ClickLogic<T>::onMouseUp(Position const& position, MouseButton button)
  {
    if (this->isCaptured() &&
        button == this->getWidget().rootWidget()->getTheme().actionButton())
    {
      this->setCapture(false);

      Bounds bounds = utl::getRectangle(Position(), this->getWidget().size());

      if (contains(bounds, position))
        onClick();
    }
  }

  /**
   *
   */
  template<typename T>
  void ClickLogic<T>::onKeyDown(Key key, ModifierKey modifier)
  {
    if (key == this->getWidget().rootWidget()->getTheme().actionKey())
      pressed_ = true;
  }

  /**
   *
   */
  template<typename T>
  void ClickLogic<T>::onKeyUp(Key key, ModifierKey modifier)
  {
    if (pressed_ && key == this->getWidget().rootWidget()->getTheme().actionKey())
    {
      pressed_ = false;

      onClick();
    }
  }

  /**
   * This method checks, whether the widget is currently pressed or not.
   * @return true if button is pressed, false otherwise
   */
  template<typename T>
  inline bool ClickLogic<T>::isPressed() const
  {
    return pressed_ || this->isCaptured();
  }
}


#endif
