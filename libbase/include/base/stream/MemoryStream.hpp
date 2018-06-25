// MemoryStream.hpp

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

#ifndef BASEMEMORYSTREAM_HPP
#define BASEMEMORYSTREAM_HPP

#include "base/stream/RandomAccessStream.hpp"


namespace base
{
  /**
   * This class represents a stream in memory.
   */
  class LIBBASE_EXPORT MemoryStream: public RandomAccessStream
  {
  public:
    MemoryStream(Byte*       memory, SizeT size, bool writeable = true, bool readable = true);
    MemoryStream(Byte const* memory, SizeT size);

    virtual SizeT read(Byte* data, SizeT size);
    virtual SizeT write(Byte* data, SizeT size);

    virtual SizeT getReadPosition() const;
    virtual void  setReadPosition(SizeT position);

    virtual SizeT getWritePosition() const;
    virtual void  setWritePosition(SizeT position);

    virtual bool isAtReadEnd() const;
    virtual bool isAtWriteEnd() const;

    virtual SizeT getSize() const;

    virtual bool isWriteable() const;
    virtual bool isReadable() const;

  private:
    union LIBBASE_EXPORT Memory
    {
      Byte*       rw_;
      Byte const* ro_;

      Memory(Byte const* memory);
    };

    Memory memory_;
    SizeT  read_p_;
    SizeT  write_p_;
    SizeT  size_;

    bool writeable_;
    bool readable_;
  };
}


namespace base
{
  /**
   * @param memory pointer to memory to store
   */
  inline MemoryStream::Memory::Memory(Byte const* memory)
    : ro_(memory)
  {
  }
}


#endif
