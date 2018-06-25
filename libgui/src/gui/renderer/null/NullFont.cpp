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

#include "gui/renderer/null/NullFont.hpp"


namespace gui
{
  /**
   * @copydoc Font::render
   */
  void NullFont::render(String const& string, Position const& position) const
  {
  }

  /**
   * @copydoc Font::getBounds
   */
  Bounds NullFont::getBounds(char_t character) const
  {
    return Bounds();
  }

  /**
   * @copydoc Font::getBounds
   */
  Bounds NullFont::getBounds(String const& string) const
  {
    return Bounds();
  }

  /**
   * @copydoc Font::getMaxBounds
   */
  Bounds NullFont::getMaxBounds() const
  {
    return Bounds();
  }

  /**
   * @copydoc Font::size
   */
  SizeT NullFont::size() const
  {
    return SizeT();
  }
}
