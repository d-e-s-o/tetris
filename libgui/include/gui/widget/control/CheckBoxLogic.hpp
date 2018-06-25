// CheckBoxLogic.hpp

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

#ifndef GUICHECKBOXLOGIC_HPP
#define GUICHECKBOXLOGIC_HPP

#include <util/Rectangle1Functions.hpp>
#include "gui/widget/control/ClickLogic.hpp"


namespace gui
{
  /**
   *
   */
  template<typename T>
  class CheckBoxLogic: public ClickLogic<T>
  {
  public:
    CheckBoxLogic(T& widget);

  protected:
    virtual void onClick();
  };
}


namespace gui
{
  /**
   *
   */
  template<typename T>
  inline CheckBoxLogic<T>::CheckBoxLogic(T& widget)
    : ClickLogic<T>(widget)
  {
  }

  /**
   *
   */
  template<typename T>
  void CheckBoxLogic<T>::onClick()
  {
    T& widget = this->getWidget();

    widget.setChecked(!widget.isChecked());
  }
}


#endif
