// QueryPerformance.hpp

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

#ifndef TMQUERYPERFOMANCE_HPP
#define TMQUERYPERFOMANCE_HPP

#include "time/Precision.hpp"


namespace tme
{
  /**
   * This functor uses the windows QueryPerformanceCount function for precise timing.
   */
  template<typename T>
  class QueryPerformance
  {
  public:
    static Precision const NATIVE_PRECISION = PRECISION_S;

    QueryPerformance();

    T operator()() const;

  private:
    LARGE_INTEGER frequency_;
  };
}


namespace tme
{
  /**
   * The constructor creates a new QueryPerformance object and initializes the performance
   * frequency.
   */
  template<typename T>
  QueryPerformance<T>::QueryPerformance()
  {
    QueryPerformanceFrequency(&frequency_);
  }

  /**
   * @return current time value
   */
  template<typename T>
  T QueryPerformance<T>::operator()() const
  {
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    return static_cast<T>(time.QuadPart) / frequency_.QuadPart;
  }
}


#endif
