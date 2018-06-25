// WidgetBase.hpp

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

#ifndef GUIWIDGETBASE_HPP
#define GUIWIDGETBASE_HPP

#include "gui/Config.hpp"
#include "gui/Position.hpp"
#include "gui/Size.hpp"
#include "gui/Bounds.hpp"
#include "gui/event/MouseButton.hpp"
#include "gui/event/Key.hpp"


namespace gui
{
  class FocusEvent;
  class PositionEvent;
  class BroadcastEvent;
  class WidgetEvent;
  class Renderer;
  class Widget;
  class Container;
  class RootWidget;


  /**
   * This abstract class defines the interface every Widget and every Decorator has to implement.
   * Due to that it is the base class for both classes.
   * @todo remove the size parameter from Render
   * @todo think about removing OnCanResize, do we really need it?
   */
  class LIBGUI_EXPORT WidgetBase
  {
  public:
    virtual ~WidgetBase() = 0;

    virtual void onGainFocus() = 0;
    virtual void onLooseFocus() = 0;
    virtual void onShow() = 0;
    virtual void onHide() = 0;
    virtual void onMouseDown(Position const& position, MouseButton button) = 0;
    virtual void onMouseUp(Position const& position, MouseButton button) = 0;
    virtual void onMouseMove(Position const& position) = 0;
    virtual void onMouseWheelDown(unsigned int units) = 0;
    virtual void onMouseWheelUp(unsigned int units) = 0;
    virtual void onKeyDown(Key key, ModifierKey modifier) = 0;
    virtual void onKeyUp(Key key, ModifierKey modifier) = 0;
    virtual void onChar(char_t character) = 0;
    virtual void onCanResize(Size const& size, bool& can_resize) = 0;
    virtual void onResize(Size const& size) = 0;
    virtual void onMove(Position const& position) = 0;

    virtual Bounds clientArea() const = 0;

    virtual Position absolutePosition() const = 0;
    virtual Position position() const = 0;
    virtual void move(Position const& position) = 0;

    virtual Size size() const = 0;
    virtual void resize(Size const& size) = 0;

  protected:
    friend class RootWidget;

    virtual void render(Size const& size) const = 0;

    virtual void handleFocusEvent(FocusEvent const& event) = 0;
    virtual void handlePositionEvent(PositionEvent const& event) = 0;
    virtual void handleBroadcastEvent(BroadcastEvent const& event) = 0;
    virtual void handleWidgetEvent(WidgetEvent const& event) = 0;
  };
}


#endif
