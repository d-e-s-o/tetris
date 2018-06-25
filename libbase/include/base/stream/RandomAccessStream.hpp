// RandomAccessStream.hpp

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

#ifndef BASERANDOMACCESSSTREAM_HPP
#define BASERANDOMACCESSSTREAM_HPP

#include "Stream.hpp"


namespace base
{
  /**
   * This class represents a random access stream. That is a stream from which
   * data does not need to be read sequentially, but from any position.
   */
  class LIBBASE_EXPORT RandomAccessStream: public Stream
  {
  public:
    /**
     * @return current position of the read pointer
     */
    virtual SizeT getReadPosition() const = 0;

    /**
     * @param[in] new (absolute) position to set the read pointer to
     */
    virtual void setReadPosition(SizeT position) = 0;

    /**
     * @return current position of the write pointer
     */
    virtual SizeT getWritePosition() const = 0;

    /**
     * @param[in] new (absolute) position to set the write pointer to
     */
    virtual void setWritePosition(SizeT position) = 0;

    /**
     * @return number of bytes in the stream
     */
    virtual SizeT getSize() const = 0;
  };
}


#endif
