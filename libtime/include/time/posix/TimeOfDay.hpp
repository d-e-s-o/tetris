// TimeOfDay.hpp

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

#ifndef TMTIMEOFDAY_HPP
#define TMTIMEOFDAY_HPP

#include <sys/time.h>

#include "time/Precision.hpp"


namespace tme
{
  /**
   * Functor for calculating time using the gettimeofday function.
   */
  template<typename T>
  struct TimeOfDay
  {
    static Precision const NATIVE_PRECISION = PRECISION_US;

    T operator()() const;
  };
}


namespace tme
{
  /**
   * @return current "time of day"
   * @todo this modulo operation is not really nice, find a better way (?)
   */
  template<typename T>
  T TimeOfDay<T>::operator()() const
  {
    timeval tv = {};
    gettimeofday(&tv, 0);
    return static_cast<T>(tv.tv_sec % (60 * 60 * 24) * PRECISION_US) + tv.tv_usec;
  }
}


#endif
