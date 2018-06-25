/***************************************************************************
 *   Copyright (C) 2012 Daniel Mueller (deso@posteo.net)                   *
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

#ifndef GUIROOTWIDGETVIEWPORT_HPP
#define GUIROOTWIDGETVIEWPORT_HPP

#include "gui/renderer/Viewport.hpp"

namespace gui
{
  class RootWidget;


  /**
   * This class implements the Viewport interface by using the RootWidget for specifying the actual
   * viewport size.
   * @see Viewport
   */
  class RootWidgetViewport: public Viewport
  {
  public:
    RootWidgetViewport(RootWidget const& root_widget);

    virtual Position offset() const;
    virtual Size     size() const;

  private:
    RootWidget const* root_widget_;
  };
}


#endif
