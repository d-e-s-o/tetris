// ResourceManager.cpp

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

#include "gui/ResourceManager.hpp"


namespace gui
{
  /**
   * @param namespace_manager
   */
  ResourceManager::ResourceManager(NamespaceManager const& namespace_manager)
    : namespace_manager_(&namespace_manager),
      image_manager_(namespace_manager)
  {
  }

  /**
   * @param uri
   */
  ResourceManager::StreamPointer ResourceManager::open(String const& uri) const
  {
    return namespace_manager_->open(uri);
  }

  /**
   * @copydoc ImageManager::registerCodec
   */
  bool ResourceManager::registerCodec(img::CodecBase const& codec)
  {
    return image_manager_.registerCodec(codec);
  }

  /**
   * @copydoc ImageManager::unregisterCodec
   */
  bool ResourceManager::unregisterCodec(img::CodecBase const& codec)
  {
    return image_manager_.unregisterCodec(codec);
  }

  /**
   * @copydoc ImageManager::loadImage
   */
  ImageManager::ImagePointer ResourceManager::loadImage(String const& uri) const
  {
    return image_manager_.loadImage(uri);
  }

  NamespaceManager const& ResourceManager::getNamespaceManager() const
  {
    return *namespace_manager_;
  }
}
