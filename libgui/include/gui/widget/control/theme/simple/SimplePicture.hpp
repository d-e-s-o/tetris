// SimplePicture.hpp

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

#ifndef GUISIMPLEPICTURE_HPP
#define GUISIMPLEPICTURE_HPP

#include "gui/widget/control/theme/simple/SimpleThemeBase.hpp"
#include "gui/widget/control/theme/simple/SimpleTheme.hpp"
#include "gui/widget/control/theme/simple/SimpleTextureTheme.hpp"


namespace gui
{
  class Picture;


  /**
   *
   */
  template<>
  struct SimpleThemeBase::SimpleControlThemeBase<Picture>: public ControlTheme<Picture>
  {
    SimpleControlThemeBase(Theme& theme);

    virtual void renderWidget(Picture const& widget, Size const& size) const;
    virtual void renderContent(Picture const& widget, Size const& size) const;

  protected:
    virtual void renderControl(Rectangle const& rectangle) const = 0;
    virtual void renderPicture(Rectangle const& rectangle, Texture const* picture) const = 0;
  };


  /**
   *
   */
  template<>
  struct SimpleTheme::SimpleControlTheme<Picture>
    : public IntermediateControlTheme<SimpleControlThemeBase<Picture>, SimpleTheme>
  {
    SimpleControlTheme(SimpleTheme& theme);

  protected:
    virtual void renderControl(Rectangle const& rectangle) const;
    virtual void renderPicture(Rectangle const& rectangle, Texture const* picture) const;
  };


  /**
   *
   */
  template<>
  struct SimpleTextureTheme::SimpleTextureControlTheme<Picture>
    : public IntermediateControlTheme<SimpleControlThemeBase<Picture>, SimpleTextureTheme>
  {
    SimpleTextureControlTheme(SimpleTextureTheme& theme);

  protected:
    virtual void renderControl(Rectangle const& rectangle) const;
    virtual void renderPicture(Rectangle const& rectangle, Texture const* picture) const;
  };
}


#endif
