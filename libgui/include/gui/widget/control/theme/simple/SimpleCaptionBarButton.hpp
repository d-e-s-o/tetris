// SimpleCaptionBarButton.hpp

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

#ifndef GUISIMPLECAPTIONBARBUTTON_HPP
#define GUISIMPLECAPTIONBARBUTTON_HPP

#include "gui/widget/control/theme/simple/SimpleThemeBase.hpp"
#include "gui/widget/control/theme/simple/SimpleTheme.hpp"
#include "gui/widget/control/theme/simple/SimpleTextureTheme.hpp"


namespace gui
{
  class CaptionBarButton;


  /**
   *
   */
  template<>
  struct SimpleThemeBase::SimpleControlThemeBase<CaptionBarButton>: public ControlTheme<CaptionBarButton>
  {
    SimpleControlThemeBase(Theme& theme);

    virtual void renderWidget(CaptionBarButton const& widget, Size const& size) const;

  protected:
    virtual void renderControl(Rectangle const& rectangle, bool pressed) const = 0;
  };


  /**
   *
   */
  template<>
  struct SimpleTheme::SimpleControlTheme<CaptionBarButton>
    : public IntermediateControlTheme<SimpleControlThemeBase<CaptionBarButton>, SimpleTheme>
  {
    SimpleControlTheme(SimpleTheme& theme);

  protected:
    virtual void renderControl(Rectangle const& rectangle, bool pressed) const;
  };


  /**
   *
   */
  template<>
  struct SimpleTextureTheme::SimpleTextureControlTheme<CaptionBarButton>
    : public IntermediateControlTheme<SimpleControlThemeBase<CaptionBarButton>, SimpleTextureTheme>
  {
    SimpleTextureControlTheme(SimpleTextureTheme& theme);

  protected:
    virtual void renderControl(Rectangle const& rectangle, bool pressed) const;
  };
}


#endif
