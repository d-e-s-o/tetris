// StreamBuffer.hpp

/***************************************************************************
 *   Copyright (C) 2009,2014 Daniel Mueller (deso@posteo.net)              *
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

#ifndef UTLSTREAMBUFFER_HPP
#define UTLSTREAMBUFFER_HPP

#include "util/Config.hpp"


namespace utl
{
  /**
   * This abstract class represents the interface to be used by various buffer objects used in
   * conjunction with OutStream.
   * @todo think about removing flush functionality or at least creating a derived class that
   *       provides it
   * @todo do we need this class?
   */
  class StreamBuffer
  {
  public:
    StreamBuffer() = default;
    StreamBuffer(StreamBuffer&&) = default;
    StreamBuffer(StreamBuffer const&) = delete;

    virtual ~StreamBuffer() = default;

    StreamBuffer& operator =(StreamBuffer&&) = default;
    StreamBuffer& operator =(StreamBuffer const&) = delete;

    virtual void put(byte_t element) = 0;
    virtual void put(byte_t const* elements, size_t size) = 0;

    virtual void flush() = 0;
  };
}

namespace utl
{
  /**
   * @param element byte to put into the buffer
   */
  inline void StreamBuffer::put(byte_t element)
  {
  }

  /**
   * @param elements array of bytes to put into buffer
   * @param size number of elements given in 'elements' array
   */
  inline void StreamBuffer::put(byte_t const* elements, size_t size)
  {
  }

  /**
   * This method forces a flush of the buffer contents.
   */
  inline void StreamBuffer::flush()
  {
  }
}


#endif
