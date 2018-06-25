// Clock.hpp

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

#ifndef TMCLOCK_HPP
#define TMCLOCK_HPP

#include <ctime>

#include "time/Precision.hpp"


namespace tme
{
  /**
   * Functor for calculating time via clock() function from <ctime>.
   */
  template<typename T>
  struct Clock
  {
    static Precision const NATIVE_PRECISION = PRECISION_S;

    T operator()() const;
  };
}


namespace tme
{
  /**
   *
   */
  template<typename T>
  Precision const Clock<T>::NATIVE_PRECISION;


  /**
   *
   */
  template<typename T>
  T Clock<T>::operator()() const
  {
    return clock() / static_cast<T>(CLOCKS_PER_SEC);
  }
}


#endif
