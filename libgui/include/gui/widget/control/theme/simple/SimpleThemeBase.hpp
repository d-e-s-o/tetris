// SimpleThemeBase.hpp

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

#ifndef GUISIMPLETHEMEBASE_HPP
#define GUISIMPLETHEMEBASE_HPP

#include "gui/widget/control/theme/Theme.hpp"


namespace gui
{
  /**
   *
   */
  class LIBGUI_EXPORT SimpleThemeBase: public Theme
  {
  public:
    template<typename CreatorT>
    SimpleThemeBase(Renderer& renderer, CreatorT const& creator);

    virtual wnd::MouseButton actionButton() const;
    virtual wnd::MouseButton menuButton() const;

    virtual wnd::Key actionKey() const;
    virtual wnd::Key leftKey() const;
    virtual wnd::Key rightKey() const;

  protected:
    template<typename WidgetT>
    struct SimpleControlThemeBase;
  };
}


namespace gui
{
  /**
   * @copydoc Theme::Theme
   */
  template<typename CreatorT>
  SimpleThemeBase::SimpleThemeBase(Renderer& renderer, CreatorT const& creator)
    : Theme(renderer, creator)
  {
  }
}


#endif
