// MemoryStream.cpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#include <algorithm>
#include <util/Assert.hpp>

#include "base/stream/MemoryStream.hpp"


namespace base
{
  /**
   * @param[in] memory memory to be accessed with the stream
   * @param[in] size size of the memory area
   * @param[in] writeable true of write actions are allowed
   * @param[in] readable true of read actions are allowed
   */
  MemoryStream::MemoryStream(Byte* memory, SizeT size, bool writeable, bool readable)
    : memory_(memory),
      size_(size),
      read_p_(0),
      write_p_(0),
      writeable_(writeable),
      readable_(readable)
  {
    ASSERTOP(memory, ne, nullptr);
    ASSERTOP(size, gt, 0);
  }

  /**
   * @param[in] memory memory to be accessed with the stream
   * @param[in] size size of the memory area
   */
  MemoryStream::MemoryStream(Byte const* memory, SizeT size)
    : memory_(memory),
      size_(size),
      read_p_(0),
      write_p_(0),
      writeable_(false),
      readable_(true)
  {
    ASSERTOP(memory, ne, nullptr);
    ASSERTOP(size, gt, 0);
  }

  /**
   * @copydoc RandomAccessStream::Read
   */
  Stream::SizeT MemoryStream::read(Byte* data, SizeT size)
  {
    ASSERTOP(data, ne, nullptr);
    ASSERTOP(size, gt, 0);

    if (readable_ && data != nullptr && size > 0)
    {
      SizeT remaining = size_ - read_p_;

      if (size > remaining)
        size = remaining;

      if (size > 0)
      {
        std::copy(memory_.ro_ + read_p_, memory_.ro_ + read_p_ + size, data);

        read_p_ += size;
      }
      return size;
    }
    return 0;
  }

  /**
   * @copydoc RandomAccessStream::Write
   */
  Stream::SizeT MemoryStream::write(Byte* data, SizeT size)
  {
    ASSERTOP(data, ne, nullptr);
    ASSERTOP(size, gt, 0);

    if (writeable_ && data != nullptr && size > 0)
    {
      SizeT remaining = size_ - write_p_;

      if (size > remaining)
        size = remaining;

      if (size > 0)
      {
        std::copy(data, data + size, memory_.rw_ + write_p_);

        write_p_ += size;
      }
      return size;
    }
    return 0;
  }

  /**
   * @copydoc RandomAccessStream::GetReadPosition
   */
  Stream::SizeT MemoryStream::getReadPosition() const
  {
    return read_p_;
  }

  /**
   * @copydoc RandomAccessStream::SetReadPosition
   */
  void MemoryStream::setReadPosition(SizeT position)
  {
    ASSERTOP(position, ge, 0);

    if (readable_)
    {
      if (position > size_)
        read_p_ = size_;
      else
        read_p_ = position;
    }
  }

  /**
   * @copydoc RandomAccessStream::GetWritePosition
   */
  Stream::SizeT MemoryStream::getWritePosition() const
  {
    return write_p_;
  }

  /**
   * @copydoc RandomAccessStream::SetWritePosition
   */
  void MemoryStream::setWritePosition(SizeT position)
  {
    ASSERTOP(position, ge, 0);

    if (writeable_)
    {
      if (position > size_)
        write_p_ = size_;
      else
        write_p_ = position;
    }
  }

  /**
   * @copydoc RandomAccessStream::IsAtReadEnd
   */
  bool MemoryStream::isAtReadEnd() const
  {
    return read_p_ >= size_;
  }

  /**
   * @copydoc RandomAccessStream::IsAtWriteEnd
   */
  bool MemoryStream::isAtWriteEnd() const
  {
    return write_p_ >= size_;
  }

  /**
   * @copydoc RandomAccessStream::GetSize
   */
  Stream::SizeT MemoryStream::getSize() const
  {
    return size_;
  }

  /**
   * @copydoc RandomAccessStream::IsWriteable
   */
  bool MemoryStream::isWriteable() const
  {
    return writeable_;
  }

  /**
   * @copydoc RandomAccessStream::IsReadable
   */
  bool MemoryStream::isReadable() const
  {
    return readable_;
  }
}
