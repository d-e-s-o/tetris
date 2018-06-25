// CharacterEvent.hpp

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

#ifndef GUICHARACTEREVENT_HPP
#define GUICHARACTEREVENT_HPP

#include "gui/Config.hpp"
#include "gui/event/FocusEvent.hpp"


namespace gui
{
  /**
   * This is the event that is sent whenever a key with an associated character
   * was pressed.
   */
  class LIBGUI_EXPORT CharacterEvent: public FocusEvent
  {
  public:
    CharacterEvent(char_t character);

    virtual void callHandler(WidgetBase& widget) const;

  private:
    char_t character_;
  };
}


#endif