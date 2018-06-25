// Precision.hpp

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

#ifndef TMPRECISION_HPP
#define TMPRECISION_HPP


namespace tme
{
  /**
   * Enumeration for the different precisions a timer or time function can
   * have.
   */
  enum Precision
  {
    PRECISION_NS = 1000000000, // nano seconds
    PRECISION_US = 1000000,    // micro seconds
    PRECISION_MS = 1000,       // mili seconds
    PRECISION_S  = 1           // seconds
  };
}


#endif
