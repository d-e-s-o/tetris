// Stream.hpp

/***************************************************************************
 *   Copyright (C) 2012,2019 Daniel Mueller (deso@posteo.net)              *
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

#ifndef FNTSTREAM_HPP
#define FNTSTREAM_HPP

#include <type/Types.hpp>


namespace fnt
{
  /**
   *
   */
  class Stream
  {
  public:
    virtual ~Stream() {}

    /**
     * @param position position in stream from where to read data
     * @param data buffer to copy data in
     * @param size size of 'buffer'
     * @return number of bytes copied into 'buffer'
     */
    virtual size_t read(size_t position, byte_t* buffer, size_t size) = 0;

    /**
     * @return size of the underlying resource in bytes
     */
    virtual size_t size() const = 0;
  };
}


#endif
