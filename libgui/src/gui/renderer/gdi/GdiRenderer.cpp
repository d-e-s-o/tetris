// GdiRenderer.cpp

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

#include "gui/Error.hpp"
#include "gui/renderer/gdi/GdiRenderer.hpp"


namespace gui
{
  /**
   * This function converts a Color value to a COLORREF used by windows
   * @todo check whether RGB sets the highest two bytes to zero (00RRGGBB)
   */
  inline COLORREF color2Colorref(Color const& color)
  {
    return RGB(color.getRed(), color.getGreen(), color.getBlue());
  }

  /**
   * The constructor creates a new renderer object for all GDI drawing. It needs
   * to be supplied a HDC for the actual rendering. It does not take ownership of
   * this dc.
   * @param[in] dc handle to a rendering context to use for actual rendering
   */
  GdiRenderer::GdiRenderer(HDC dc)
    : dc_(dc),
      texture_(0)
  {
    if (dc == 0)
      throw Error(_T("Error creating GDI renderer"), _T("No valid device context given (0)"));
  }

  /**
   * This method renders a sprite with given dimensions and color on the GDI
   * surface specified by rendering context supplied in constructor.
   * @param[in] dimensions absolute coordinates of the sprite
   * @param[in] color color of the sprite
   */
  void GdiRenderer::renderSprite(Dimensions const& dimensions, Color const& color) const
  {
    HBRUSH brush = CreateSolidBrush(Color2Colorref(color));

    if (brush != 0)
    {
      RECT rect;
      rect.left   = dimensions.x;
      rect.bottom = dimensions.y;
      rect.right  = dimensions.x + dimensions.w;
      rect.top    = dimensions.y + dimensions.h;

#ifndef NDEBUG
      int result =
#endif
      FillRect(dc_, &rect, brush);
      ASSERTOP(result, ne, 0);

      DeleteObject(brush);
    }
    else
    {
      ASSERT(false);
    }
  }

  void GdiRenderer::renderSprite(Dimensions const& dimensions, Texture const& texture) const
  {
  }

  void GdiRenderer::renderSprite(Dimensions const& dimensions, Texture const& texture, Color const& color) const
  {
  }
}
