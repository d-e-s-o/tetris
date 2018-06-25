// Namespace.hpp

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

#ifndef GUINAMESPACE_HPP
#define GUINAMESPACE_HPP

#include <pointer/SharedPointer.hpp>

#include "gui/Config.hpp"
#include "gui/String.hpp"
#include "gui/Stream.hpp"


namespace gui
{
  /**
   * This class provides the interface to be implemented by all actual Namespace objects.
   */
  class LIBGUI_EXPORT Namespace
  {
  public:
    typedef ptr::SharedPointer<Stream> StreamPointer;

    /**
     * @param identifier
     * @return
     */
    virtual StreamPointer open(String const& identifier) const = 0;
  };
}


#endif
