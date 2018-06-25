// SimpleEditBox.cpp

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

#include <util/Util.hpp>
#include <util/Assert.hpp>
#include <util/RectangleFunctions.hpp>
#include <util/Rectangle1Functions.hpp>
#include <util/Rectangle2Functions.hpp>

#include "gui/renderer/Font.hpp"
#include "gui/widget/control/EditBox.hpp"
#include "gui/widget/control/theme/simple/SimpleThemeFunctions.hpp"
#include "gui/widget/control/theme/simple/SimpleEditBox.hpp"


namespace gui
{
  /**
   *
   */
  SimpleThemeBase::SimpleControlThemeBase<EditBox>::SimpleControlThemeBase(Theme& theme)
    : ControlTheme<EditBox>(theme)
  {
    font_data = getDefaultFontData();
    font      = createFont(theme, font_data);

    text_space = 3;
  }

  /**
   *
   */
  void SimpleThemeBase::SimpleControlThemeBase<EditBox>::renderWidget(EditBox const& widget, Size const& size) const
  {
    ASSERT(size == widget.size());

    renderControl(getRectangle(Point(), size));
  }

  /**
   * @todo find a way to shorten this function or at least splitt it a bit :x
   *       (though I seriously doubt that this is possible)
   */
  void SimpleThemeBase::SimpleControlThemeBase<EditBox>::renderContent(EditBox const& widget, Size const& size) const
  {
    ASSERT(size == utl::getSize(widget.clientArea()));

    String const& string = widget.getText();

    size_t index = utl::min(widget.getCaret(), widget.getSelection());
    size_t count = utl::max(widget.getCaret(), widget.getSelection()) - index;

    char_t caret        = TEXT('|');
    String caret_string = String(caret);

    // we need the position of the text WITH caret, to center it correctly vertical
    // we append the caret, so the x-position stays correct due to left alignment
    Bounds string_bounds = font->getBounds(string + caret_string);
    Bounds caret_bounds  = font->getBounds(caret);
    Margin margin        = Margin(text_space, text_space, text_space, text_space);
    Size   max_size      = getMaxSize(margin, size);

    Point point;
    point.x = getStringHPosition(string_bounds, max_size, H_ALIGNMENT_LEFT);
    point.y = getStringVPosition(string_bounds, max_size, V_ALIGNMENT_CENTERED);

    Renderer& renderer = getTheme().getRenderer();
    renderer.pushClippingRectangle(getRectangleFromMargin(margin, size));

    // render the first part - from beginning to caret or selection start
    if (index > 0)
    {
      String first = subString(string, 0, index);
      renderString(renderer, *font, first, font_data.font_color, point);
      point.x += font->getBounds(first).w;
    }

    PositionT caret_x = point.x - caret_bounds.x;

    // render the second part - the selection
    if (count > 0)
    {
      String second = subString(string, index, count);
      Bounds bounds = font->getBounds(second);

      bounds.x += point.x + caret_bounds.x;
      bounds.y  = point.y + string_bounds.y;
      bounds.h  = string_bounds.h;

      // render the rectangle to make the selected text look selected
      renderer.pushColor(select_color);
      renderer.renderRectangle(convert(bounds));
      renderer.popColor();

      renderString(renderer, *font, second, font_data.font_color, point);

      point.x += bounds.w;

      // if the caret is at the end of the selection
      if (widget.getCaret() > widget.getSelection())
        caret_x += bounds.w;
    }

    // the caret is to be rendered only if the widget is focused
    if (widget.focused())
      renderString(renderer, *font, caret_string, font_data.font_color, Point(caret_x, point.y));

    // render the third part - from selection end to string end
    if (index + count < string.size())
    {
      String third = subString(string, index + count);
      renderString(renderer, *font, third, font_data.font_color, point);
    }

    renderer.popClippingRectangle();
  }

  /**
   *
   */
  SimpleTheme::SimpleControlTheme<EditBox>::SimpleControlTheme(SimpleTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<EditBox>, SimpleTheme>(theme)
  {
    select_color = Color(0xF0, 0xF0, 0xF0);
    bkgd_color   = Color(0x49, 0x4E, 0x49);
  }

  /**
   *
   */
  void SimpleTheme::SimpleControlTheme<EditBox>::renderControl(Rectangle const& rectangle) const
  {
    renderRectangle(getTheme().getRenderer(), rectangle, bkgd_color);
  }

  /**
   *
   */
  SimpleTextureTheme::SimpleTextureControlTheme<EditBox>::SimpleTextureControlTheme(SimpleTextureTheme& theme)
     : IntermediateControlTheme<SimpleControlThemeBase<EditBox>, SimpleTextureTheme>(theme)
  {
    select_color = Color(0xB2, 0xB4, 0xBF);
    bkgd_color   = Color(0xFF, 0xFF, 0xFF);
  }

  /**
   *
   */
  void SimpleTextureTheme::SimpleTextureControlTheme<EditBox>::renderControl(Rectangle const& rectangle) const
  {
    Margin margin;
    margin.left   = getTheme().getPixelData().edit_box_.left_margin_;
    margin.bottom = getTheme().getPixelData().edit_box_.bottom_margin_;
    margin.right  = getTheme().getPixelData().edit_box_.right_margin_;
    margin.top    = getTheme().getPixelData().edit_box_.top_margin_;

    renderRectangle(getTheme(), rectangle, getTheme().getPixelData().edit_box_.widget_, bkgd_color, margin);
  }
}
