// Timer.hpp

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

#ifndef TMTIMER_HPP
#define TMTIMER_HPP

#include "Precision.hpp"


namespace tme
{
  /**
   *
   */
  template<template<typename> class TimeFn, typename T = float, Precision precision = PRECISION_S>
  class Timer
  {
  public:
    Timer(bool start = false);

    void start();

    T getTime() const;
    T getTimeAndRestart();

  private:
    TimeFn<T> time_fn_;

    T time_;
    T factor_;

    T calculateTime() const;
  };
}


namespace tme
{
  /**
   *
   */
  template< template<typename> class TimeFn, typename T, Precision precision>
  inline Timer<TimeFn, T, precision>::Timer(bool start)
    : time_fn_(),
      time_(),
      factor_(static_cast<T>(precision) / TimeFn<T>::NATIVE_PRECISION)
  {
    if (start)
      this->start();
  }

  /**
   *
   */
  template< template<typename> class TimeFn, typename T, Precision precision>
  inline void Timer<TimeFn, T, precision>::start()
  {
    time_ = calculateTime();
  }

  /**
   *
   */
  template< template<typename> class TimeFn, typename T, Precision precision>
  inline T Timer<TimeFn, T, precision>::getTime() const
  {
    return calculateTime() - time_;
  }

  /**
   *
   */
  template< template<typename> class TimeFn, typename T, Precision precision>
  inline T Timer<TimeFn, T, precision>::getTimeAndRestart()
  {
    T time = getTime();

    start();

    return time;
  }

  /**
   *
   */
  template< template<typename> class TimeFn, typename T, Precision precision>
  inline T Timer<TimeFn, T, precision>::calculateTime() const
  {
    return time_fn_() * factor_;
  }
}


#endif
