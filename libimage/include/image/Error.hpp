// Error.hpp

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

#ifndef IMGERROR_HPP
#define IMGERROR_HPP

#include "image/Config.hpp"


namespace img
{
  /**
   *
   */
  class LIBIMAGE_EXPORT Error
  {
  public:
    Error(char_t const* message, char_t const* cause);
    Error(Error&& other) = default;
    Error(Error const& other) = default;

    virtual ~Error();

    Error& operator =(Error&& other) = default;
    Error& operator =(Error const& other) = default;

    char_t const* message() const;
    char_t const* cause() const;

  private:
    char_t const* message_;
    char_t const* cause_;
  };
}


#endif
