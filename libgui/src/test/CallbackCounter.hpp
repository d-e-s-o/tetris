// CallbackCounter.hpp

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

#ifndef TESTCALLBACKCOUNTER_HPP
#define TESTCALLBACKCOUNTER_HPP


namespace test
{
  template<typename BaseT>
  class CallbackCounter: public BaseT
  {
  public:
    int gain_focus_called_;
    int loose_focus_called_;
    int show_called_;
    int hide_called_;
    int mouse_down_called_;
    int mouse_up_called_;
    int mouse_move_called_;
    int mouse_wheel_down_called_;
    int mouse_wheel_up_called_;
    int key_down_called_;
    int key_up_called_;
    int char_called_;
    int can_resize_called_;
    int resize_called_;
    int move_called_;

    CallbackCounter(gui::Bounds const& bounds);

    virtual void onGainFocus();
    virtual void onLooseFocus();
    virtual void onShow();
    virtual void onHide();
    virtual void onMouseDown(gui::Position const& position, wnd::MouseButton button);
    virtual void onMouseUp(gui::Position const& position, wnd::MouseButton button);
    virtual void onMouseMove(gui::Position const& position);
    virtual void onMouseWheelDown(unsigned int units);
    virtual void onMouseWheelUp(unsigned int units);
    virtual void onKeyDown(wnd::Key key, wnd::ModifierKey modifier);
    virtual void onKeyUp(wnd::Key key, wnd::ModifierKey modifier);
    virtual void onChar(char_t character);
    virtual void onCanResize(gui::Size const& size, bool& can_resize);
    virtual void onResize(gui::Size const& size);
    virtual void onMove(gui::Position const& position);
  };
}


namespace test
{
  template<typename BaseT>
  CallbackCounter<BaseT>::CallbackCounter(gui::Bounds const& bounds)
    : BaseT(bounds),
      gain_focus_called_(0),
      loose_focus_called_(0),
      show_called_(0),
      hide_called_(0),
      mouse_down_called_(0),
      mouse_up_called_(0),
      mouse_move_called_(0),
      mouse_wheel_down_called_(0),
      mouse_wheel_up_called_(0),
      key_down_called_(0),
      key_up_called_(0),
      char_called_(0),
      can_resize_called_(0),
      resize_called_(0),
      move_called_(0)
  {
  }

  template<typename BaseT>
  void CallbackCounter<BaseT>::onGainFocus()
  {
    ++gain_focus_called_;
  }

  template<typename BaseT>
  void CallbackCounter<BaseT>::onLooseFocus()
  {
    ++loose_focus_called_;
  }

  template<typename BaseT>
  void CallbackCounter<BaseT>::onShow()
  {
    ++show_called_;
  }

  template<typename BaseT>
  void CallbackCounter<BaseT>::onHide()
  {
    ++hide_called_;
  }

  template<typename BaseT>
  void CallbackCounter<BaseT>::onMouseDown(gui::Position const& position, wnd::MouseButton button)
  {
    ++mouse_down_called_;
  }

  template<typename BaseT>
  void CallbackCounter<BaseT>::onMouseUp(gui::Position const& position, wnd::MouseButton button)
  {
    ++mouse_up_called_;
  }

  template<typename BaseT>
  void CallbackCounter<BaseT>::onMouseMove(gui::Position const& position)
  {
    ++mouse_move_called_;
  }

  template<typename BaseT>
  void CallbackCounter<BaseT>::onMouseWheelDown(unsigned int units)
  {
    ++mouse_wheel_down_called_;
  }

  template<typename BaseT>
  void CallbackCounter<BaseT>::onMouseWheelUp(unsigned int units)
  {
    ++mouse_wheel_up_called_;
  }

  template<typename BaseT>
  void CallbackCounter<BaseT>::onKeyDown(wnd::Key key, wnd::ModifierKey modifier)
  {
    ++key_down_called_;
  }

  template<typename BaseT>
  void CallbackCounter<BaseT>::onKeyUp(wnd::Key key, wnd::ModifierKey modifier)
  {
    ++key_up_called_;
  }

  template<typename BaseT>
  void CallbackCounter<BaseT>::onChar(char_t character)
  {
    ++char_called_;
  }

  template<typename BaseT>
  void CallbackCounter<BaseT>::onCanResize(gui::Size const& size, bool& can_resize)
  {
    ++can_resize_called_;
  }

  template<typename BaseT>
  void CallbackCounter<BaseT>::onResize(gui::Size const& size)
  {
    ++resize_called_;
  }

  template<typename BaseT>
  void CallbackCounter<BaseT>::onMove(gui::Position const& position)
  {
    ++move_called_;
  }
}


#endif
