// GlyphMetrics.hpp

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

#ifndef FNTGLYPHMETRICS_HPP
#define FNTGLYPHMETRICS_HPP

#include "font/Config.hpp"


namespace fnt
{
  /**
   * This structure is used for describing the metrics of a given glyph. A rendered glyph is
   * always positioned relative to a baseline. This baseline is an more or less imaginary line
   * where all glyph "reside" on.
   * @note at the moment this structure does not support vertical rendered text
   */
  struct LIBFONT_EXPORT GlyphMetrics
  {
    /**
     * X-Position of the pen relative to the current position used for drawing the glyph (in
     * pixels)
     */
    int pen_x;

    /**
     * Y-Position of the pen relative to the baseline used for drawing the glyph (in pixels)
     */
    int pen_y;

    /**
     * Width of the rendered glyph image. It is identical to the actual width value of the image
     * (in pixels)
     * @todo think about removing this value as it is equal to the image width
     */
    int width;

    /**
     * Height of the rendered glyph image. It is identical to the actual height value of the image
     * (in pixels).
     * @todo think about removing this value as it is equal to the image height
     */
    int height;

    /**
     * Amount of pixels to move after drawing the glyph on the x-axis (to get the new pen position)
     */
    int advance;

    GlyphMetrics();
  };
}


#endif
