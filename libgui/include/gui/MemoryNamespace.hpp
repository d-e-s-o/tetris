// MemoryNamespace.hpp

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

#ifndef GUIMEMORYNAMESPACE_HPP
#define GUIMEMORYNAMESPACE_HPP

#include <container/Map.hpp>
#include <container/Pair.hpp>

#include "gui/Config.hpp"
#include "gui/Namespace.hpp"


namespace gui
{
  /**
   *
   */
  class LIBGUI_EXPORT MemoryNamespace: public Namespace
  {
  public:
    // use compiler generated default constructor, copy constructor and assignment operator

    virtual StreamPointer open(String const& identifier) const;

    bool insertEntry(String const& identifier, byte_t const* data, size_t size);
    bool removeEntry(String const& identifier);

  private:
    /**
     * An entry consists of a pointer to data in memory and the corresponding size.
     */
    typedef ctr::Pair<byte_t const*, size_t> Entry;

    /**
     *
     */
    typedef ctr::Map<String const, Entry const> EntryMap;

    EntryMap entries_;

    Entry const* lookupEntry(String const& identifier) const;
  };
}


#endif
