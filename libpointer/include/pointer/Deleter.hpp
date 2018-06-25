// Deleter.hpp

/***************************************************************************
 *   Copyright (C) 2012 Daniel Mueller (deso@posteo.net)                   *
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

#ifndef PTRDELETER_HPP
#define PTRDELETER_HPP


namespace ptr
{
  struct Deleter
  {
    template<typename T>
    void operator ()(T const* pointer) const;
  };

  struct ArrayDeleter
  {
    template<typename T>
    void operator ()(T const* pointer) const;
  };
}


namespace ptr
{
  /**
   * @param
   */
  template<typename T>
  void Deleter::operator ()(T const* pointer) const
  {
    delete pointer;
  }

  /**
   * @param
   */
  template<typename T>
  void ArrayDeleter::operator()(T const* p) const
  {
    delete[] p;
  }
}


#endif
