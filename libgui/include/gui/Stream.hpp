// Stream.hpp

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

#ifndef GUISTREAM_HPP
#define GUISTREAM_HPP

#include "gui/Config.hpp"


namespace gui
{
  /**
   *
   */
  class LIBGUI_EXPORT Stream
  {
  public:
    /**
     * @param data buffer to copy data in
     * @param size size of 'buffer'
     * @return number of bytes copied into 'buffer'
     */
    virtual size_t read(byte_t* buffer, size_t size) = 0;

    /**
     * @return current position within the stream
     */
    virtual size_t position() const = 0;

    /**
     * @param position new position
     */
    virtual void reposition(size_t position) = 0;

    /**
     * @return size of the underlying resource in bytes
     */
    virtual size_t size() const = 0;
  };
}


#endif
