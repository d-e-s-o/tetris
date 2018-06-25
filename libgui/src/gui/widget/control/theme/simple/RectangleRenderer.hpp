// RectangleRenderer.hpp

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

#ifndef GUIRECTANGLERENDERER_HPP
#define GUIRECTANGLERENDERER_HPP

#include "gui/Color.hpp"
#include "gui/renderer/Rectangle.hpp"
#include "gui/widget/control/theme/simple/SimpleTextureThemeData.hpp"


namespace gui
{
  struct Margin;
  class SimpleTextureTheme;


  /**
   * This class is responsible for mapping a part of a texture onto a given rectangle. It handles
   * a given margin so that the resulting rectangle will not look stretched. Therefor the rectangle
   * will be splitt into smaller ones with smaller texture parts according to the margin.
   * @todo instead of calling Renderer::RenderRectangle directly in RenderRectangle we actually
   *       need to check first whether the texture part is not stretched, if so we need to render
   *       multiple quads
   * @todo we should cache the texture size so that ConvertPixels does not need to do that much
   *       divisions
   * @todo when creating a very small widget (like size(1, 1)) an assertion failes, fix this
   *       somehow
   */
  class RectangleRenderer
  {
  public:
    RectangleRenderer(SimpleTextureTheme& theme);

    void render(Rectangle const& rectangle, Rectangle const& pixels, Color const& color, Margin const& margin) const;

  private:
    SimpleTextureTheme* theme_;

    void renderWithMargin(Rectangle rectangle, Rectangle pixels, Margin const& margin) const;
    void renderRectangle(Rectangle const& rectangle, Rectangle const& pixels) const;

    template<typename Shrinker>
    void renderShrinker(Shrinker const& shrinker) const;
  };
}


namespace gui
{
  /**
   *
   */
  inline RectangleRenderer::RectangleRenderer(SimpleTextureTheme& theme)
    : theme_(&theme)
  {
  }
}


#endif
