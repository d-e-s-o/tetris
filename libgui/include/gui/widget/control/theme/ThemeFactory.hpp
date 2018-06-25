// ThemeFactory.hpp

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

#ifndef GUITHEMEFACTORY_HPP
#define GUITHEMEFACTORY_HPP

#include "gui/Config.hpp"


namespace gui
{
  class Theme;
  class RootWidget;


  /**
   * A ThemeFactory can be used to create a theme. They are used by the RootWidget
   * @see RootWidget
   * @todo we should use an Allocator to create the theme, then we also need a DestroyTheme method
   */
  class LIBGUI_EXPORT ThemeFactory
  {
  public:
    ThemeFactory();
    virtual ~ThemeFactory();

    /**
     * This method is used to create a new theme object for the given root
     * widget and all widgets belonging to it.
     * @param root_widget root widget to create theme for
     * @return newly created theme object, it has to be free'd using delete
     */
    virtual Theme* createTheme(RootWidget& root_widget) const = 0;

  private:
    ThemeFactory(ThemeFactory const&);
    ThemeFactory& operator =(ThemeFactory const&);
  };
}


#endif
