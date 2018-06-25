// NamespaceManager.cpp

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

#include "gui/NamespaceManager.hpp"


namespace gui
{
  /**
   * @param separator
   */
  NamespaceManager::NamespaceManager(String const& separator)
    : namespaces_(),
      separator_(separator)
  {
  }

  /**
   * @param ns
   * @param uri_prefix
   * @return
   * @note the order in which the registered namespaces are stored and searched during a call to
   *       open() is not defined
   * @see NamespaceManager::open
   */
  bool NamespaceManager::registerNamespace(Namespace const& ns, String const& uri_prefix)
  {
    return namespaces_.insert(Namespaces::Entry(uri_prefix, &ns));
  }

  /**
   * @param uri resource identifier
   * @return pointer to stream for accessing the opened resource or pointer to null
   */
  Namespace::StreamPointer NamespaceManager::open(String const& uri) const
  {
    for (Namespaces::ConstIterator it = namespaces_.begin(); it != namespaces_.end(); ++it)
    {
      String const& prefix = it->first + separator_;

      if (isPrefix(prefix, uri))
        return it->second->open(subString(uri, prefix.size()));
    }
    return Namespace::StreamPointer(0);
  }

  /**
   * @param prefix prefix string to check for prefix property in 'string'
   * @param string string to check if it contains the given prefix 'prefix'
   * @return true if the given string 'prefix' is a prefix of string 'string', false otherwise
   */
  bool NamespaceManager::isPrefix(String const& prefix, String const& string) const
  {
    if (string.size() >= prefix.size())
      return subString(string, 0, prefix.size()) == prefix;

    return false;
  }
}
