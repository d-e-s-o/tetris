// Hud.hpp

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

#ifndef TTRSHUD_HPP
#define TTRSHUD_HPP

#include <util/Assert.hpp>
#include <gui/widget/RootWidget.hpp>
#include <gui/widget/control/Button.hpp>
#include <gui/widget/control/StaticText.hpp>

#include "tetris/gui/FpsCounter.hpp"
#include "tetris/gui/SettingsDialog.hpp"


namespace ttrs
{
  class Window;
  class Settings;


  /**
   * @todo think about moving this class into libgui (or one with comparable functionality)
   */
  template<typename ObjectT>
  class CustomizableButton: public gui::Button
  {
  public:
    typedef void (ObjectT::*OnClickMethod)();

    CustomizableButton(gui::Bounds const& bounds, ObjectT& object, OnClickMethod on_click = 0);

    virtual void onClick();

    ObjectT& getObject() const;
    void setObject(ObjectT& object);

    OnClickMethod getOnClick() const;
    void setOnClick(OnClickMethod on_click);

  private:
    ObjectT*      object_;
    OnClickMethod on_click_;
  };


  /**
   * This class represents the whole graphical user interface in this game.
   */
  class Hud: public gui::RootWidget
  {
  public:
    Hud(gui::Renderer& renderer, Window& window, Settings& settings);

    virtual void onKeyDown(gui::Key key, gui::ModifierKey modifier);

    void update(float time);

    void setLevel(int level);
    void setPoints(int points);
    void setLines(int lines);

    void toggleFps();

  private:
    Window* window_;

    FpsCounter fps_;

    gui::StaticText level_;
    gui::StaticText points_;
    gui::StaticText lines_;

    CustomizableButton<Hud> new_game_;
    CustomizableButton<Hud> pause_game_;
    CustomizableButton<Hud> quite_game_;

    SettingsDialog settings_dialog_;

    void onNewGameClick();
    void onPauseGameClick();
    void onQuitGameClick();
  };
}


namespace ttrs
{
  /**
   * @param bounds
   * @param object
   * @param on_click
   */
  template<typename ObjectT>
  CustomizableButton<ObjectT>::CustomizableButton(gui::Bounds const& bounds, ObjectT& object, OnClickMethod on_click)
    : Button(bounds),
      object_(&object),
      on_click_(on_click)
  {
  }

  /**
   * @copydoc Button::onClick
   */
  template<typename ObjectT>
  void CustomizableButton<ObjectT>::onClick()
  {
    if (on_click_ != 0)
      (object_->*on_click_)();
  }

  /**
   * @return
   */
  template<typename ObjectT>
  ObjectT& CustomizableButton<ObjectT>::getObject() const
  {
    ASSERTOP(object_, ne, 0);
    return *object_;
  }

  /**
   * @param object
   */
  template<typename ObjectT>
  void CustomizableButton<ObjectT>::setObject(ObjectT& object)
  {
    object_ = &object;
  }

  /**
   * @return
   */
  template<typename ObjectT>
  typename CustomizableButton<ObjectT>::OnClickMethod CustomizableButton<ObjectT>::getOnClick() const
  {
    return on_click_;
  }

  /**
   * @param on_click
   */
  template<typename ObjectT>
  void CustomizableButton<ObjectT>::setOnClick(OnClickMethod on_click)
  {
    on_click_ = on_click;
  }
}


#endif
