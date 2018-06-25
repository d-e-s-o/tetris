// WidgetEvent.hpp

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

#ifndef GUIWIDGETEVENT_HPP
#define GUIWIDGETEVENT_HPP

#include "gui/event/EventBase.hpp"


namespace gui
{
  class Widget;


  /**
   * This class is the base class for all events that go to a special widget.
   */
  class WidgetEvent: public EventBase
  {
  public:
    virtual void dispatchEvent(RootWidget& root_widget) const;

    virtual Widget& getWidget() const = 0;
  };


  template<typename T>
  class WidgetEventBase: public WidgetEvent
  {
  public:
    WidgetEventBase(T& widget);

    virtual T& getWidget() const;

  private:
    mutable T* widget_;
  };
}


namespace gui
{
  template<typename T>
  inline WidgetEventBase<T>::WidgetEventBase(T& widget)
    : widget_(&widget)
  {
  }

  template<typename T>
  inline T& WidgetEventBase<T>::getWidget() const
  {
    return *widget_;
  }
}


#endif
