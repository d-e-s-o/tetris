// SimpleCheckBox.hpp

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

#ifndef GUISIMPLECHECKBOX_HPP
#define GUISIMPLECHECKBOX_HPP

#include "gui/widget/control/theme/simple/SimpleThemeBase.hpp"
#include "gui/widget/control/theme/simple/SimpleTheme.hpp"
#include "gui/widget/control/theme/simple/SimpleTextureTheme.hpp"


namespace gui
{
  class CheckBox;


  /**
   *
   */
  template<>
  struct SimpleThemeBase::SimpleControlThemeBase<CheckBox>: public ControlTheme<CheckBox>
  {
    SimpleControlThemeBase(Theme& theme);

    virtual void renderWidget(CheckBox const& widget, Size const& size) const;
    virtual void renderContent(CheckBox const& widget, Size const& size) const;

  protected:
    virtual void renderControl(Rectangle const& rectangle) const = 0;
    virtual void renderBox(Rectangle const& rectangle, bool checked) const = 0;
  };


  /**
   *
   */
  template<>
  struct SimpleTheme::SimpleControlTheme<CheckBox>
    : public IntermediateControlTheme<SimpleControlThemeBase<CheckBox>, SimpleTheme>
  {
    SimpleControlTheme(SimpleTheme& theme);

  protected:
    virtual void renderControl(Rectangle const& rectangle) const;
    virtual void renderBox(Rectangle const& rectangle, bool checked) const;
  };


  /**
   *
   */
  template<>
  struct SimpleTextureTheme::SimpleTextureControlTheme<CheckBox>
    : public IntermediateControlTheme<SimpleControlThemeBase<CheckBox>, SimpleTextureTheme>
  {
    SimpleTextureControlTheme(SimpleTextureTheme& theme);

  protected:
    virtual void renderControl(Rectangle const& rectangle) const;
    virtual void renderBox(Rectangle const& rectangle, bool checked) const;
  };
}


#endif
