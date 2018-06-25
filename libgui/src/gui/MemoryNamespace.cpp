// MemoryNamespace.cpp

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

#include "gui/MemoryStream.hpp"
#include "gui/MemoryNamespace.hpp"


namespace gui
{
  /**
   * @copydoc Namespaces::open
   */
  MemoryNamespace::StreamPointer MemoryNamespace::open(String const& identifier) const
  {
    Entry const* entry = lookupEntry(identifier);

    if (entry != 0)
      return StreamPointer(new MemoryStream(entry->first, entry->second));

    return StreamPointer(0);
  }

  /**
   * @param identifier identifier of new entry to insert
   * @param data pointer to data in memory
   * @param size size of data in memory
   * @return
   */
  bool MemoryNamespace::insertEntry(String const& identifier, byte_t const* data, size_t size)
  {
    return entries_.insert(EntryMap::Entry(identifier, Entry(data, size)));
  }

  /**
   * @param identifier identifier of entry to remove
   * @return
   */
  bool MemoryNamespace::removeEntry(String const& identifier)
  {
    return entries_.remove(identifier);
  }

  /**
   * @param identifier identifier of entry to find
   * @return pointer to found entry or null if no entry was found
   */
  MemoryNamespace::Entry const* MemoryNamespace::lookupEntry(String const& identifier) const
  {
    EntryMap::ConstIterator it = entries_.find(identifier);

    if (it != entries_.end())
      return &it->second;

    return 0;
  }
}
