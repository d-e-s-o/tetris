// SimpleBorder.hpp

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

#ifndef GUISIMPLEBORDER_HPP
#define GUISIMPLEBORDER_HPP

#include "gui/widget/control/theme/simple/SimpleThemeBase.hpp"
#include "gui/widget/control/theme/simple/SimpleTheme.hpp"
#include "gui/widget/control/theme/simple/SimpleTextureTheme.hpp"


namespace gui
{
  class Border;


  /**
   *
   */
  template<>
  struct SimpleThemeBase::SimpleControlThemeBase<Border>: public ControlTheme<Border>
  {
    SimpleControlThemeBase(Theme& theme);

    virtual void renderWidget(Border const& widget, Size const& size) const;

  protected:
    virtual void renderControl(Rectangle const& rectangle) const = 0;
    virtual void renderRightBorder(Rectangle const& rectangle) const = 0;
    virtual void renderTopBorder(Rectangle const& rectangle) const = 0;
    virtual void renderLeftBorder(Rectangle const& rectangle) const = 0;
    virtual void renderBottomBorder(Rectangle const& rectangle) const = 0;
  };


  /**
   *
   */
  template<>
  struct SimpleTheme::SimpleControlTheme<Border>
    : public IntermediateControlTheme<SimpleControlThemeBase<Border>, SimpleTheme>
  {
    SimpleControlTheme(SimpleTheme& theme);

  protected:
    virtual void renderControl(Rectangle const& rectangle) const;
    virtual void renderRightBorder(Rectangle const& rectangle) const;
    virtual void renderTopBorder(Rectangle const& rectangle) const;
    virtual void renderLeftBorder(Rectangle const& rectangle) const;
    virtual void renderBottomBorder(Rectangle const& rectangle) const;
  };


  /**
   *
   */
  template<>
  struct SimpleTextureTheme::SimpleTextureControlTheme<Border>
    : public IntermediateControlTheme<SimpleControlThemeBase<Border>, SimpleTextureTheme>
  {
    SimpleTextureControlTheme(SimpleTextureTheme& theme);

  protected:
    virtual void renderControl(Rectangle const& rectangle) const;
    virtual void renderRightBorder(Rectangle const& rectangle) const;
    virtual void renderTopBorder(Rectangle const& rectangle) const;
    virtual void renderLeftBorder(Rectangle const& rectangle) const;
    virtual void renderBottomBorder(Rectangle const& rectangle) const;
  };
}


#endif
