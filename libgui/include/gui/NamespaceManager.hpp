// NamespaceManager.hpp

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

#ifndef GUINAMESPACEMANAGER_HPP
#define GUINAMESPACEMANAGER_HPP

#include <container/Map.hpp>
#include <container/String.hpp>

#include "gui/Config.hpp"
#include "gui/Namespace.hpp"


namespace gui
{
  /**
   * This class manages various namespaces, for instance, the namespace of all local files, from
   * which resources can be retrieved.
   */
  class LIBGUI_EXPORT NamespaceManager
  {
  public:
    explicit NamespaceManager(String const& separator = String(TEXT("://")));

    bool registerNamespace(Namespace const& ns, String const& uri_prefix);

    Namespace::StreamPointer open(String const& uri) const;

  private:
    typedef ctr::Map<String, Namespace const*> Namespaces;

    Namespaces namespaces_;
    String     separator_;

    bool isPrefix(String const& prefix, String const& string) const;
  };
}


#endif
