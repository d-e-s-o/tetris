// MemoryStream.cpp

/***************************************************************************
 *   Copyright (C) 2012,2014 Daniel Mueller (deso@posteo.net)              *
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

#include <util/Util.hpp>
#include <util/Assert.hpp>
#include <util/Algorithm.hpp>

#include "gui/MemoryStream.hpp"


namespace gui
{
  /**
   * @param data
   * @param size
   */
  MemoryStream::MemoryStream(byte_t const* data, size_t size)
    : Stream(),
      data_(data),
      size_(size),
      index_(0)
  {
  }

  /**
   * @copydoc Stream::read
   */
  size_t MemoryStream::read(byte_t* buffer, size_t size)
  {
    ASSERTOP(index_, ge, 0);
    ASSERTOP(index_, le, size_);

    size_t to_copy = utl::min(size_ - index_, size);
    utl::copy(data_ + index_, data_ + index_ + to_copy, buffer);

    index_ += to_copy;
    ASSERTOP(index_, ge, 0);
    ASSERTOP(index_, le, size_);

    return to_copy;
  }

  /**
   * @copydoc Stream::position
   */
  size_t MemoryStream::position() const
  {
    return index_;
  }

  /**
   * @copydoc::Stream::reposition
   */
  void MemoryStream::reposition(size_t position)
  {
    ASSERTOP(position, ge, 0);
    ASSERTOP(position, le, size_);

    index_ = position;
  }

  /**
   * @copydoc Stream::size
   */
  size_t MemoryStream::size() const
  {
    return size_;
  }
}
