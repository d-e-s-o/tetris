// SimplePicture.cpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#include <util/Assert.hpp>
#include <util/Rectangle1Functions.hpp>
#include <util/Rectangle2Functions.hpp>

#include "gui/widget/control/Picture.hpp"
#include "gui/widget/control/theme/simple/SimpleThemeFunctions.hpp"
#include "gui/widget/control/theme/simple/SimplePicture.hpp"


namespace gui
{
  /**
   *
   */
  SimpleThemeBase::SimpleControlThemeBase<Picture>::SimpleControlThemeBase(Theme& theme)
    : ControlTheme<Picture>(theme)
  {
    picture_space = 2;
  }

  /**
   *
   */
  void SimpleThemeBase::SimpleControlThemeBase<Picture>::renderWidget(Picture const& widget, Size const& size) const
  {
    ASSERT(size == widget.size());

    renderControl(getRectangle(Point(), size));
  }

  /**
   *
   */
  void SimpleThemeBase::SimpleControlThemeBase<Picture>::renderContent(Picture const& widget, Size const& size) const
  {
    ASSERT(size == utl::getSize(widget.clientArea()));

    Rectangle rectangle = Rectangle(picture_space,
                                    picture_space,
                                    size.x - picture_space,
                                    size.y - picture_space);

    renderPicture(rectangle, widget.getPicture());
  }

  /**
   *
   */
  SimpleTheme::SimpleControlTheme<Picture>::SimpleControlTheme(SimpleTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<Picture>, SimpleTheme>(theme)
  {
    blend_color = Color(0xFF, 0xFF, 0xFF);
    bkgd_color  = Color(0x68, 0x6A, 0x65);
  }

  /**
   *
   */
  void SimpleTheme::SimpleControlTheme<Picture>::renderControl(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme().getRenderer(), rectangle, bkgd_color);
  }

  /**
   *
   */
  void SimpleTheme::SimpleControlTheme<Picture>::renderPicture(Rectangle const& rectangle, Texture const* picture) const
  {
    if (picture != 0)
    {
      Renderer& renderer = getTheme().getRenderer();

      renderer.pushColor(blend_color);
      renderer.pushTexture(picture);

      renderer.renderRectangle(rectangle);

      renderer.popTexture();
      renderer.popColor();
    }
  }

  /**
   *
   */
  SimpleTextureTheme::SimpleTextureControlTheme<Picture>::SimpleTextureControlTheme(SimpleTextureTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<Picture>, SimpleTextureTheme>(theme)
  {
    blend_color = Color(0xFF, 0xFF, 0xFF);
    bkgd_color  = Color(0xFF, 0xFF, 0xFF);
  }

  /**
   *
   */
  void SimpleTextureTheme::SimpleTextureControlTheme<Picture>::renderControl(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme(), rectangle, getTheme().getPixelData().picture_.widget_, bkgd_color);
  }

  /**
   *
   */
  void SimpleTextureTheme::SimpleTextureControlTheme<Picture>::renderPicture(Rectangle const& rectangle, Texture const* picture) const
  {
    if (picture != 0)
    {
      Renderer& renderer = getTheme().getRenderer();

      renderer.pushColor(blend_color);
      renderer.pushTexture(picture);

      renderer.renderRectangle(rectangle, TextureRectangle(0.0f, 0.0f, 1.0f, 1.0f));

      renderer.popTexture();
      renderer.popColor();
    }
    else
      renderRectangle(getTheme(), rectangle, getTheme().getPixelData().picture_.picture_empty_, blend_color);
  }
}
