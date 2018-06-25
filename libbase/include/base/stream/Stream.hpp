// Stream.hpp

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

#ifndef BASESTREAM_HPP
#define BASESTREAM_HPP

#include "base/Config.hpp"


/**
 * @todo remove typedef
 */
typedef unsigned char Byte;


namespace base
{
  /**
   * This class is the base class for different data stream classes. A data stream represents a
   * "flow" of from or to a destination (read/write). This could be a file, a network connection
   * or even just another area in memory.
   * @note a stream is not meant to be copied
   * @todo maybe another method for checking for errors is needed (?) but also a way to recover
   *       from an error? how could such an error look like?
   */
  class LIBBASE_EXPORT Stream
  {
  public:
    /**
     *
     */
    typedef int SizeT;

    Stream();
    virtual ~Stream() = 0;

    /**
     * This methods read the given number of bytes from the stream into the given buffer.
     * @param[out] data buffer of size bytes that will receive the data read
     * @param[in] size buffer size in bytes
     * @return number of bytes actually read
     * @note if the return value is not equal to the size parameter check isEnded to see if an
     *       error occurred or we simply reached the end of the file
     */
    virtual SizeT read(Byte* data, SizeT size) = 0;

    /**
     * This methods writes the given number of bytes from the buffer into the stream.
     * @param[in] data buffer of size bytes that will be written to the stream
     * @param[in] size buffer size in bytes
     * @return number of bytes actually written
     * @note if the return value is not equal to the size parameter there has been an error
     */
    virtual SizeT write(Byte* data, SizeT size) = 0;

    /**
     * @return true if no more data is left to read, false otherwise
     */
    virtual bool isAtReadEnd() const = 0;

    /**
     * @return true if more data can be written to the stream, false otherwise
     */
    virtual bool isAtWriteEnd() const = 0;

    /**
     * @return true if data can be written to the stream, false if not
     */
    virtual bool isWriteable() const = 0;

    /**
     * @return true if data can be read from the stream, false if not
     */
    virtual bool isReadable() const = 0;

  private:
    Stream(Stream const&);
    Stream& operator =(Stream const&);
  };
}


namespace base
{
  /**
   * This is the default constructor. It makes the stream creatable.
   * @note if a stream has to be opened this has to be done in the constructor
   */
  inline Stream::Stream()
  {
  }

  /**
   * The destructor is virtual to allow subclasses.
   * @note if a stream has to be closed this has to be done in the destructor
   */
  inline Stream::~Stream()
  {
  }
}


#endif
