// CaptureLogic.hpp

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

#ifndef GUICAPTURELOGIC_HPP
#define GUICAPTURELOGIC_HPP

#include <util/Assert.hpp>

#include "gui/widget/RootWidget.hpp"


namespace gui
{
  /**
   *
   */
  template<typename T>
  class CaptureLogic
  {
  public:
    CaptureLogic(T& widget);
    ~CaptureLogic();

    void setCapture(bool set);
    bool isCaptured() const;

  protected:
    T& getWidget();

  private:
    T* widget_;
    bool captured_;
  };
}


namespace gui
{
  /**
   *
   */
  template<typename T>
  CaptureLogic<T>::CaptureLogic(T& widget)
    : widget_(&widget),
      captured_(false)
  {
  }

  /**
   *
   */
  template<typename T>
  CaptureLogic<T>::~CaptureLogic()
  {
    if (isCaptured())
      setCapture(false);
  }

  /**
   *
   */
  template<typename T>
  inline T& CaptureLogic<T>::getWidget()
  {
    ASSERTOP(widget_, ne, nullptr);
    return *widget_;
  }

  /**
   * @return true if the widget currently has captured the mouse, false if not
   */
  template<typename T>
  inline bool CaptureLogic<T>::isCaptured() const
  {
    return captured_;
  }

  /**
   * @param set true if the mouse capture should be set for the current widget, false if it should
   *        be removed
   */
  template<typename T>
  inline void CaptureLogic<T>::setCapture(bool set)
  {
    ASSERTOP(widget_->rootWidget(), ne, nullptr);

    widget_->rootWidget()->setMouseCapture(set ? widget_ : nullptr);
    captured_ = set;
  }
}


#endif
