// Error.cpp

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

#include "font/Error.hpp"


namespace fnt
{
  Error::Error(char_t const* message, char_t const* cause)
    : message_(message),
      cause_(cause)
  {
  }

  /**
   * The destructor is virtual so that derived classes can be created.
   */
  Error::~Error()
  {
  }

  /**
   * @return general message given in constructor
   */
  char_t const* Error::message() const
  {
    return message_;
  }

  /**
   * @return cause message given in constructor
   */
  char_t const* Error::cause() const
  {
    return cause_;
  }
}
