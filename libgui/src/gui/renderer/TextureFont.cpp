// TextureFont.cpp

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
#include "gui/renderer/TextureFont.hpp"


namespace gui
{
  /**
   *
   */
  TextureFont::TextureFont(SizeT size, char_t first_char, char_t char_count)
    : first_char_(first_char),
      char_count_(char_count),
      bounds_(),
      max_bounds_(),
      size_(size)
  {
    if (first_char_ < 0)
      throw Error(TEXT("Error creating texture font"), TEXT("Character code cannot be zero"));

    if (char_count_ <= 0)
      throw Error(TEXT("Error creating texture font"), TEXT("Character count to create is zero"));
  }

  /**
   * @copydoc Font::getBounds
   */
  Bounds TextureFont::getBounds(char_t character) const
  {
    return getGlyphBounds(character);
  }

  /**
   * @copydoc Font::getBounds
   */
  Bounds TextureFont::getBounds(String const& string) const
  {
    Bounds bounds;

    if (string.size() != 0)
    {
      bounds.x = getGlyphBounds(string[0]).x;

      for (String::ConstIterator it = string.begin(), end = string.end(); it != end; ++it)
      {
        Bounds const& glyph = getGlyphBounds(*it);

        bounds.w += glyph.w;

        if (glyph.y < bounds.y)
        {
          // if the y position changed we need to adjust the height, because the latter is
          // relative to it
          bounds.h += bounds.y - glyph.y;
          bounds.y  = glyph.y;
        }

        if (glyph.h > bounds.h)
          bounds.h = glyph.h;
      }
    }
    return bounds;
  }

  /**
   * @copydoc Font::getMaxBounds
   */
  Bounds TextureFont::getMaxBounds() const
  {
    return max_bounds_;
  }

  /**
   * @copydoc Font::size
   */
  SizeT TextureFont::size() const
  {
    return size_;
  }

  /**
   * @param data glyph data with metrices that will be copied into the vector to hold all the
   *        bounding information
   */
  void TextureFont::updateBounds(GlyphBounds const& bounds)
  {
    bounds_ = bounds;

    updateMaxBounds(bounds);
  }

  /**
   * @param character character code to get bounds from
   * @throw Error if no bounds are found for the given character code
   */
  Bounds const& TextureFont::getGlyphBounds(char_t character) const
  {
    GlyphBounds::difference_type i = character - first_char_;
    ASSERTOP(i, ge, 0);
    ASSERTOP(i, lt, static_cast<GlyphBounds::difference_type>(bounds_.size()));

    if (i < 0 || i >= static_cast<GlyphBounds::difference_type>(bounds_.size()))
      throw Error(TEXT("Error retrieving glyph bounds"), TEXT("Invalid character code"));

    return bounds_[i];
  }

  /**
   * This method is used to (re)calculate the maximum bounds from the given glyph bounds.
   * @param bounds glyph bounds to calculate maximum bounds from
   * @see Font::getMaxBounds
   */
  void TextureFont::updateMaxBounds(GlyphBounds const& bounds)
  {
    if (!bounds.empty())
    {
      max_bounds_ = bounds.front();

      for (GlyphBounds::const_iterator it = bounds.begin(), end = bounds.end(); it != end; ++it)
      {
        if (it->x < max_bounds_.x)
          max_bounds_.x = it->x;

        if (it->y < max_bounds_.y)
          max_bounds_.y = it->y;

        if (it->x + it->w > max_bounds_.w)
          max_bounds_.w = it->x + it->w;

        if (it->y + it->h > max_bounds_.h)
          max_bounds_.h = it->y + it->h;
      }
    }
    else
      max_bounds_ = Bounds();
  }
}
