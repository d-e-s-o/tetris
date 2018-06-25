// Anchors.hpp

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

#ifndef GUIANCHORS_HPP
#define GUIANCHORS_HPP

#include "gui/Config.hpp"


namespace gui
{
  /**
   * The horizontal anchors define the horizontal movement/stretching of a widget's children.
   * - H_ANCHORS_MIN is not meant to be actually used as value, it may only be used for checking
   *   if a given value is valid (-> larger than H_ANCHORS_MIN)
   * - H_ANCHORS_LEFT makes the widget always keep the same space relative to the parent's left
   *   edge, if the parent is resized
   * - H_ANCHORS_RIGHT makes the widget always keep the same space relative to the parent's right
   *   edge, if the parent is resized
   * - H_ANCHORS_MAX is not meant to be actually used as value, it may only be used for checking
   *   if a given value is valid (-> smaller than H_ANCHORS_MAX)
   * Values can be or'ed (|). If thats the case the widget will be resized, to keep the space to
   * the left and right edge.
   */
  enum LIBGUI_EXPORT HAnchors
  {
    H_ANCHORS_MIN    = 1 << 0,
    H_ANCHORS_LEFT   = 1 << 1,
    H_ANCHORS_RIGHT  = 1 << 2,
    H_ANCHORS_MAX    = 1 << 3
  };


  /**
   * The vertical anchors define the vertical movement/stretching of a widgets children.
   * - V_ANCHORS_MIN is not meant to be actually used as value, it may only be used for checking
   *   if a given value is valid (-> larger than V_ANCHORS_MIN)
   * - V_ANCHORS_BOTTOM makes the widget always keep the same space relative to the parent's bottom
   *   edge, if the parent is resized
   * - V_ANCHORS_TOP makes the widget always keep the same space relative to the parent's top
   *   edge, if the parent is resized
   * - V_ANCHORS_MAX is not meant to be actually used as value, it may only be used for checking
   *   if a given value is valid (-> smaller than V_ANCHORS_MAX)
   * Values can be or'ed (|). If thats the case the widget will be resized, to keep the space to
   * the top and bottom corner.
   */
  enum LIBGUI_EXPORT VAnchors
  {
    V_ANCHORS_MIN    = 1 << 0,
    V_ANCHORS_BOTTOM = 1 << 1,
    V_ANCHORS_TOP    = 1 << 2,
    V_ANCHORS_MAX    = 1 << 3
  };

  template<typename Anchors>
  Anchors operator |(Anchors lhs, Anchors rhs);

  template<typename Anchors>
  bool isAnchorSet(Anchors anchors, Anchors to_check);
}


namespace gui
{
  /**
   * @param lhs left hand anchors
   * @param rhs right hand anchors
   * @return bitwise or'ed anchors
   */
  template<typename Anchors>
  inline Anchors operator |(Anchors lhs, Anchors rhs)
  {
    // add 0 to implicitly convert into unsigned or whatever it may be
    return static_cast<Anchors>((lhs + 0) | rhs);
  }

  /**
   * @param anchors value to check if containing other given anchors
   * @param to_check anchors to check if they are part of the given anchors
   * @return true if the values to check for are set in the first anchors
   */
  template<typename Anchors>
  inline bool isAnchorSet(Anchors anchors, Anchors to_check)
  {
    return ((anchors + 0) & to_check) == to_check;
  }
}


#endif
