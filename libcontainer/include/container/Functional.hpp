// Functional.hpp

/***************************************************************************
 *   Copyright (C) 2010-2012 Daniel Mueller (deso@posteo.net)              *
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

#ifndef CTRFUNCTIONAL_HPP
#define CTRFUNCTIONAL_HPP


namespace ctr
{
  /**
   * @todo deprecate and remove? so easy to implement with lambdas
   */
  template<typename T>
  struct Less
  {
    bool operator ()(T const& lhs, T const& rhs) const;
  };

  template<typename T>
  struct Greater
  {
    bool operator ()(T const& lhs, T const& rhs) const;
  };
}


namespace ctr
{
  template<typename T>
  bool Less<T>::operator ()(T const& lhs, T const& rhs) const
  {
    return lhs < rhs;
  }

  template<typename T>
  bool Greater<T>::operator ()(T const& lhs, T const& rhs) const
  {
    return lhs > rhs;
  }
}


#endif
