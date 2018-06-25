// ResourceManager.hpp

/***************************************************************************
 *   Copyright (C) 2006-2012 Daniel Mueller (deso@posteo.net)              *
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

#ifndef GUIRESOURCEMANAGER_HPP
#define GUIRESOURCEMANAGER_HPP

#include "gui/Config.hpp"
#include "gui/NamespaceManager.hpp"
#include "gui/ImageManager.hpp"



namespace gui
{
  /**
   * This class manages all external resources needed during runtime. At the
   * moment it takes care for loading images and storing them. Users do not
   * have to care about the resource management, they just have to use the
   * resources.
   */
  class LIBGUI_EXPORT ResourceManager
  {
  public:
    typedef Namespace::StreamPointer StreamPointer;

    ResourceManager(NamespaceManager const& namespace_manager);

    StreamPointer open(String const& uri) const;

    bool registerCodec(img::CodecBase const& codec);
    bool unregisterCodec(img::CodecBase const& codec);

    ImageManager::ImagePointer loadImage(String const& uri) const;

    NamespaceManager const& getNamespaceManager() const;

  private:
    NamespaceManager const* namespace_manager_;

    /**
     * @todo remove mutability?
     */
    mutable ImageManager image_manager_;

    ResourceManager();
    ResourceManager(ResourceManager const&);
    ResourceManager& operator =(ResourceManager const&);
  };
}


#endif
