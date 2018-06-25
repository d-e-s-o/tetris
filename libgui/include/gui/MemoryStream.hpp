// MemoryStream.hpp

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

#ifndef GUIMEMORYSTREAM_HPP
#define GUIMEMORYSTREAM_HPP

#include "gui/Config.hpp"
#include "gui/Stream.hpp"


namespace gui
{
  /**
   * This class implements the Stream interface for data in memory.
   */
  class LIBGUI_EXPORT MemoryStream: public Stream
  {
  public:
    MemoryStream(byte_t const* data, size_t size);

    virtual size_t read(byte_t* buffer, size_t size);

    virtual size_t position() const;
    virtual void reposition(size_t position);

    virtual size_t size() const;

  private:
    byte_t const* data_;
    size_t        size_;
    size_t        index_;
  };
}


#endif
