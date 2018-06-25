// SimpleTheme.hpp

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

#ifndef GUISIMPLETHEME_HPP
#define GUISIMPLETHEME_HPP

#include "gui/widget/control/theme/simple/SimpleThemeBase.hpp"


namespace gui
{
  /**
   * This class represents a pretty simple theme. It uses just colored rectanlges (and of course a
   * font) to render all controls.
   */
  class LIBGUI_EXPORT SimpleTheme: public SimpleThemeBase
  {
  public:
    SimpleTheme(Renderer& renderer);

  protected:
    template<typename WidgetT>
    struct SimpleControlTheme;
  };
}


#endif
