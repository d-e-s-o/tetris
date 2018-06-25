// SimpleThemeFunctions.hpp

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

#ifndef GUISIMPLETHEMEFUNCTIONS_HPP
#define GUISIMPLETHEMEFUNCTIONS_HPP

#include <util/Assert.hpp>

#include "gui/Margin.hpp"
#include "gui/Error.hpp"
#include "gui/renderer/Renderer.hpp"
#include "gui/renderer/FontFunctions.hpp"
#include "gui/widget/control/theme/Theme.hpp"
#include "gui/widget/control/theme/simple/RectangleRenderer.hpp"

/**
 * @todo clean up here -- that looks horrible!
 */

namespace gui
{
  Theme::FontData getDefaultFontData();

  Font* createFont(Theme& theme, Theme::FontData const& font_data);

  SizeT calculateValueOffset(SizeT width, int min, int max, int value);

  Size getMaxSize(Margin const& margin, Size const& size);

  Rectangle getRectangleFromMargin(Margin const& margin, Size const& size);

  void renderString(Renderer& renderer,
                    Font const& font,
                    String const& string,
                    Color const& color,
                    Position const& position);

  void renderMarginString(Renderer& renderer,
                          Font const& font,
                          String const& string,
                          Color const& color,
                          Size const& size,
                          Alignment const& alignment,
                          Margin const& margin);

  void renderRectangle(Renderer& renderer, Rectangle const& rectangle, Color const& color);

  void renderRectangle(SimpleTextureTheme& theme,
                       Rectangle const& rectangle,
                       Pixels const& pixels,
                       Color const& color,
                       Margin const& margin);

  void renderRectangle(SimpleTextureTheme& theme,
                       Rectangle const& rectangle,
                       Pixels const& pixels,
                       Color const& color);
}


namespace gui
{
  /**
   * @return default font data every control (with a font) may use
   */
  inline Theme::FontData getDefaultFontData()
  {
    /**
     * @todo this really should be configurable
     */
    Theme::FontData data = {String(TEXT("mem://vera.ttf")), Color(), 12};
    return data;
  }

  /**
   * @param theme theme to use the renderer of for creating the font
   * @param font_data data to be used for creating the font
   */
  inline Font* createFont(Theme& theme, Theme::FontData const& font_data)
  {
    Font* font = theme.getRenderer().createFont(font_data.font_name, font_data.font_size);

    if (font == nullptr)
      throw Error(TEXT("Error creating theme"), TEXT("Renderer failed creating font"));

    return font;
  }

  /**
   * @param width width of the area to display the value
   * @param min minimal value the control can have
   * @param max maximal value the control can have
   * @param value current value the control has
   * @return offset of the "value signalizer" relative to the start of the line
   * @note this function is for internal use only
   */
  inline SizeT calculateValueOffset(SizeT width, int min, int max, int value)
  {
    ASSERTOP(max - min, gt, 0);

    return width * value / (max - min);
  }

  /**
   *
   */
  inline Size getMaxSize(Margin const& margin, Size const& size)
  {
    return Size(size.x - margin.right  - margin.left,
                size.y - margin.bottom - margin.top);
  }

  /**
   *
   */
  inline Rectangle getRectangleFromMargin(Margin const& margin, Size const& size)
  {
    return Rectangle(margin.left,
                     margin.bottom,
                     size.x - margin.top,
                     size.y - margin.right);
  }

  /**
   * @param renderer renderer to use for rendering the text
   * @param font font to be used by the renderer
   * @param string string to render
   * @param color color to be used for rendering the string
   * @param position position the text should be rendered at
   */
  inline void renderString(Renderer& renderer,
                           Font const& font,
                           String const& string,
                           Color const& color,
                           Position const& position)
  {
    renderer.pushColor(color);
    renderer.pushFont(font);

    renderer.renderString(string, position);

    renderer.popFont();
    renderer.popColor();
  }

  /**
   * @param renderer renderer to use
   * @param font font to use for rendering the text
   * @param string string to be rendered
   * @param color color font should have
   * @param size size of the area to render the text in
   * @param alignment alignment to be used for aligning the text
   * @note I know the parameter list ist f*cking long, but I dont know how to shorten it
   */
  inline void renderMarginString(Renderer& renderer,
                                 Font const& font,
                                 String const& string,
                                 Color const& color,
                                 Size const& size,
                                 Alignment const& alignment,
                                 Margin const& margin)
  {
    if (string.size() > 0)
    {
      Position point = getStringPosition(font, getMaxSize(margin, size), string, alignment);

      renderer.pushClippingRectangle(getRectangleFromMargin(margin, size));
      renderString(renderer, font, string, color, point);
      renderer.popClippingRectangle();
    }
  }


  /**
   * @param renderer renderer to use for rendering the rectangle
   * @param rectangle rectangle to render
   * @param color color to be used for rendering the rectangle
   * @param texture texture to be used on the rectangle (the whole texture will be used, not
   *        only a part)
   */
  inline void renderRectangle(Renderer& renderer, Rectangle const& rectangle, Color const& color)
  {
    renderer.pushTexture(nullptr);
    renderer.pushColor(color);

    renderer.renderRectangle(rectangle);

    renderer.popColor();
    renderer.popTexture();
  }

  /**
   *
   */
  inline void renderRectangle(SimpleTextureTheme& theme,
                              Rectangle const& rectangle,
                              Pixels const& pixels,
                              Color const& color,
                              Margin const& margin)
  {
    RectangleRenderer renderer(theme);
    renderer.render(rectangle, pixels, color, margin);
  }

  /**
   *
   */
  inline void renderRectangle(SimpleTextureTheme& theme,
                              Rectangle const& rectangle,
                              Pixels const& pixels,
                              Color const& color)
  {
    renderRectangle(theme, rectangle, pixels, color, Margin(0, 0, 0, 0));
  }
}


#endif
