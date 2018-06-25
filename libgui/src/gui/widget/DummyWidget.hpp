// DummyWidget.hpp

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

#ifndef GUIDUMMYWIDGET_HPP
#define GUIDUMMYWIDGET_HPP

#include "gui/widget/WidgetBase.hpp"


namespace gui
{
  /**
   * This class implements the WidgetBase interface but does exactly nothing.
   * It is meant for implementation purposes only!
   */
  class DummyWidget: public WidgetBase
  {
  public:
    virtual void onGainFocus();
    virtual void onLooseFocus();
    virtual void onShow();
    virtual void onHide();
    virtual void onMouseDown(Position const& position, MouseButton button);
    virtual void onMouseUp(Position const& position, MouseButton button);
    virtual void onMouseMove(Position const& position);
    virtual void onMouseWheelDown(unsigned int units);
    virtual void onMouseWheelUp(unsigned int units);
    virtual void onKeyDown(Key key, ModifierKey modifier);
    virtual void onKeyUp(Key key, ModifierKey modifier);
    virtual void onChar(char_t character);
    virtual void onCanResize(Size const& size, bool& can_resize);
    virtual void onResize(Size const& size);
    virtual void onMove(Position const& position);

    virtual RootWidget* rootWidget() const;
    virtual Widget*     focusedWidget() const;

    virtual Bounds clientArea() const;

    virtual Position absolutePosition() const;
    virtual Position position() const;
    virtual void move(Position const& position);

    virtual Size size() const;
    virtual void resize(Size const& size);

  protected:
    virtual void render(Size const& size) const;

    virtual void handleFocusEvent(FocusEvent const& event);
    virtual void handlePositionEvent(PositionEvent const& event);
    virtual void handleBroadcastEvent(BroadcastEvent const& event);
    virtual void handleWidgetEvent(WidgetEvent const& event);
  };
}


#endif
