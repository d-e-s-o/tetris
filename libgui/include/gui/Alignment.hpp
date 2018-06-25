// Alignment.hpp

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

#ifndef GUIALIGNMENT_HPP
#define GUIALIGNMENT_HPP


namespace gui
{
  /**
   * Enumeration for the different horizontal alignments that objects can have
   * @note H_ALIGNMENT_MIN and H_ALIGNMENT_MAX are not meant to be used directly, they should only
   *       be used for validation checking
   */
  enum HAlignment
  {
    H_ALIGNMENT_MIN,
    H_ALIGNMENT_LEFT,
    H_ALIGNMENT_CENTERED,
    H_ALIGNMENT_RIGHT,
    H_ALIGNMENT_MAX
  };

  /**
   * Enumeration for the different vertical alignments that objects can have
   * @note V_ALIGNMENT_MIN and V_ALIGNMENT_MAX are not meant to be used directly, they should only
   *       be used for validation checking
   */
  enum VAlignment
  {
    V_ALIGNMENT_MIN,
    V_ALIGNMENT_TOP,
    V_ALIGNMENT_CENTERED,
    V_ALIGNMENT_BOTTOM,
    V_ALIGNMENT_MAX
  };

  /**
   * This structure combines the two alignment into one. This is generally useful, as they often
   * appear together.
   */
  struct Alignment
  {
    HAlignment h_alignment;
    VAlignment v_alignment;

    Alignment(HAlignment h_alignment, VAlignment v_alignment);
  };
}


namespace gui
{
  /**
   * @param h_alignment horizontal alignment to set
   * @param v_alignment vertical alignment to set
   */
  inline Alignment::Alignment(HAlignment h_alignment, VAlignment v_alignment)
    : h_alignment(h_alignment),
      v_alignment(v_alignment)
  {
  }
}


#endif
