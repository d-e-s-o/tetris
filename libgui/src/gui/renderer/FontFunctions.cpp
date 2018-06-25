// FontFunctions.cpp

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

#include "gui/renderer/Font.hpp"
#include "gui/renderer/FontFunctions.hpp"


namespace gui
{
  /**
   * @param bounds calculated bounding box of the string
   * @param size maximum size of the bounding box
   * @param alignment horizontal alignment
   * @return x position within the given size to position the text according to the aligment
   */
  PositionT getStringHPosition(Bounds const& bounds, Size const& size, HAlignment alignment)
  {
    ASSERTOP(alignment, gt, H_ALIGNMENT_MIN);
    ASSERTOP(alignment, lt, H_ALIGNMENT_MAX);

    int w1 = size.x;
    int w2 = bounds.w;
    int x  = bounds.x;

    switch(alignment)
    {
    case H_ALIGNMENT_LEFT:
      // @todo check if this needs to be 0, x or -x
      return -x;

    case H_ALIGNMENT_CENTERED:
      return (w1 - w2) / 2 - x;

    case H_ALIGNMENT_RIGHT:
      return w1 - w2 - x;

    default:
      ASSERT(false);
    }
    return 0;
  }

  /**
   * @param bounds calculated bounding box of the string
   * @param size maximum size of the bounding box
   * @param alignment vertical alignment
   * @return y position within the given size to position the text according to the aligment
   */
  PositionT getStringVPosition(Bounds const& bounds, Size const& size, VAlignment alignment)
  {
    ASSERTOP(alignment, gt, V_ALIGNMENT_MIN);
    ASSERTOP(alignment, lt, V_ALIGNMENT_MAX);

    int h1 = size.y;
    int h2 = bounds.h;
    int y  = bounds.y;

    switch(alignment)
    {
    case V_ALIGNMENT_BOTTOM:
      return -y;

    case V_ALIGNMENT_CENTERED:
      return (h1 - h2) / 2 - y;

    case V_ALIGNMENT_TOP:
      return h1 - h2 - y;

    default:
      ASSERT(false);
    }
    return 0;
  }

  /**
   * This function calculates the string position within the bounding box with the specified
   * alignment.
   * @param font font to be used for calculating string bounds
   * @param size size of desired bounding box for the string
   * @param string string to be positionized
   * @param alignment alignment to be used for placing the string within the bounding box
   * @return position the string should be rendered at
   */
  Position getStringPosition(Font const& font,
                             Size const& size,
                             String const& string,
                             Alignment const& alignment)
  {
    Bounds bounds = font.getBounds(string);

    PositionT x = getStringHPosition(bounds, size, alignment.h_alignment);
    PositionT y = getStringVPosition(bounds, size, alignment.v_alignment);

    return Position(x, y);
  }

  /**
   * This function calculates the caret index based on a x value that represents a position (e.g.
   * from a mouse click that happened on that string rendered with that font) relative to the
   * strings origin.
   * @param font font to be used for calculating the text size
   * @param string string to get caret position in
   * @param x x-coordinate of the position on the string
   * @return index the caret should point to
   */
  size_t getCaretIndex(Font const& font, String const& string, PositionT x)
  {
    if (string.size() != 0)
    {
      size_t    index = 0;
      PositionT current_x = font.getBounds(*string.begin()).x;

      for (String::ConstIterator it = string.begin(); it != string.end(); ++it)
      {
        PositionT w = font.getBounds(*it).w;

        // if the x position happened on the current character
        if (current_x + w >= x)
        {
          // we check if it is within the first 2/3 of it, then the caret should be on the current
          // character, otherwise it should point to the next
          if (current_x + 2 * w / 3 >= x)
            return index;
          else
            return index + 1;
        }

        current_x += w;
        index     += 1;
      }
      return index;
    }
    return 0;
  }
}
