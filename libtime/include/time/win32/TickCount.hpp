// TickCount.hpp

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

#ifndef TMTICKCOUNT_HPP
#define TMTICKCOUNT_HPP

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "time/Precision.hpp"


namespace tme
{
  /**
   * Functor for calculating time with Windows' GetTickCount function.
   */
  template<typename T>
  struct TickCount
  {
    static Precision const NATIVE_PRECISION = PRECISION_MS;

    T operator()() const;
  };
}


namespace tme
{
  /**
   * @return current tick count
   */
  template<typename T>
  T TickCount<T>::operator()() const
  {
    return static_cast<T>(GetTickCount());
  }
}


#endif
