// FileStream.cpp

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

#include <util/Assert.hpp>

#include "base/Error.hpp"
#include "base/stream/FileStream.hpp"


namespace base
{
  namespace
  {
    /**
     * @return openmode used for opening the filestream with the desired read/write rights
     */
    inline std::fstream::openmode getOpenMode(bool writeable, bool readable)
    {
      std::fstream::openmode mode = std::ios::binary;

      if (writeable)
        mode |= std::ios::out;

      if (readable)
        mode |= std::ios::in;

      return mode;
    }
  }


  /**
   * The constructor creates a new filestream object for accessing the contents
   * of a given file.
   * @param[in] file filename (relative or absolute) to file that should be streamed
   */
  FileStream::FileStream(char const* file, bool writeable, bool readable)
    : stream_(file, getOpenMode(writeable, readable)),
      writeable_(writeable),
      readable_(readable)
  {
    if (!stream_)
    {
      throw Error("Error creating file stream",
                  "The file probably does not exist or is inaccessible");
    }
  }

  /**
   * @copydoc RandomAccessStream::Read
   */
  Stream::SizeT FileStream::read(Byte* data, SizeT size)
  {
    ASSERTOP(data, ne, nullptr);
    ASSERTOP(size, gt, 0);

    if (isReadable() && data != 0 && size > 0 && stream_.good())
    {
      stream_.read(reinterpret_cast<char*>(data), size);

      return stream_.gcount();
    }
    return 0;
  }

  /**
   * @copydoc RandomAccessStream::Write
   */
  Stream::SizeT FileStream::write(Byte* data, SizeT size)
  {
    ASSERTOP(data, ne, nullptr);
    ASSERTOP(size, gt, 0);

    if (isWriteable() && data != 0 && size > 0 && stream_.good())
    {
      SizeT old_pos = stream_.tellp();
      stream_.write(reinterpret_cast<char*>(data), size);
      SizeT new_pos = stream_.tellp();

      return new_pos - old_pos;
    }
    return 0;
  }

  /**
   * @copydoc RandomAccessStream::GetReadPosition
   */
  Stream::SizeT FileStream::getReadPosition() const
  {
    return static_cast<SizeT>(stream_.tellg());
  }

  /**
   * @copydoc RandomAccessStream::SetReadPosition
   */
  void FileStream::setReadPosition(SizeT position)
  {
    if (isReadable())
      stream_.seekg(position);
  }

  /**
   * @copydoc RandomAccessStream::GetWritePosition
   */
  Stream::SizeT FileStream::getWritePosition() const
  {
    return static_cast<SizeT>(stream_.tellp());
  }

  /**
   * @copydoc RandomAccessStream::SetWritePosition
   */
  void FileStream::setWritePosition(SizeT position)
  {
    if (isWriteable())
      stream_.seekp(position);
  }

  /**
   * @copydoc RandomAccessStream::IsAtReadEnd
   */
  bool FileStream::isAtReadEnd() const
  {
    return stream_.eof();
  }

  /**
   * @copydoc RandomAccessStream::IsAtWriteEnd
   */
  bool FileStream::isAtWriteEnd() const
  {
    return false;
  }

  /**
   * @copydoc RandomAccessStream::GetSize
   */
  Stream::SizeT FileStream::getSize() const
  {
    std::fstream::pos_type old_position = stream_.tellg();

    stream_.seekg(0, std::ios::end);
    std::fstream::pos_type position = stream_.tellg();

    stream_.seekg(old_position);
    return static_cast<SizeT>(position);
  }

  /**
   * @copydoc RandomAccessStream::IsWriteable
   */
  bool FileStream::isWriteable() const
  {
    // in Visual Studio this works, however I suspect it not to be conforming to the standard and
    // Sun Studio is with me
    //return (stream_.flags() & std::ios::out) == std::ios::out;
    return writeable_;
  }

  /**
   * @copydoc RandomAccessStream::IsReadable
   */
  bool FileStream::isReadable() const
  {
    //return (stream_.flags() & std::ios::in) == std::ios::in;
    return readable_;
  }
}
