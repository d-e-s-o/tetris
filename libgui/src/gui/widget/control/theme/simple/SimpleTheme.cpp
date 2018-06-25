// SimpleTheme.cpp

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

#include "gui/widget/control/theme/simple/SimpleStaticText.hpp"
#include "gui/widget/control/theme/simple/SimpleButton.hpp"
#include "gui/widget/control/theme/simple/SimpleCheckBox.hpp"
#include "gui/widget/control/theme/simple/SimpleEditBox.hpp"
#include "gui/widget/control/theme/simple/SimpleSlider.hpp"
#include "gui/widget/control/theme/simple/SimpleProgressBar.hpp"
#include "gui/widget/control/theme/simple/SimplePicture.hpp"
#include "gui/widget/control/theme/simple/SimpleGroupBox.hpp"
#include "gui/widget/control/theme/simple/SimpleDialog.hpp"
#include "gui/widget/control/theme/simple/SimpleCaptionBar.hpp"
#include "gui/widget/control/theme/simple/SimpleCaptionBarButton.hpp"
#include "gui/widget/control/theme/simple/SimpleBorder.hpp"
#include "gui/widget/control/theme/simple/SimpleTheme.hpp"


namespace gui
{
  /**
   * @copydoc SimpleThemeBase::SimpleThemeBase
   */
  SimpleTheme::SimpleTheme(Renderer& renderer)
    : SimpleThemeBase(renderer, ControlThemeCreator<SimpleControlTheme, SimpleTheme>(*this))
  {
  }
}
