// TextureManager.hpp

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

#ifndef GUITEXTUREMANAGER_HPP
#define GUITEXTUREMANAGER_HPP

#include <util/Assert.hpp>
#include <container/Map.hpp>

#include "gui/Allocator.hpp"
#include "gui/ResourceManager.hpp"

#ifdef LoadImage
#undef LoadImage
#endif


namespace gui
{
  /**
   * This class template is used to manage textures. The template parameter
   * is the texture type that this manager uses.
   * Objects of this class can load textures and store them internally. They
   * are completely responsible for deleting them.
   * @todo use SharedPointer<TextureT> here
   */
  template<typename TextureT>
  class TextureManager
  {
  public:
    TextureManager(ResourceManager const& resource_manager);
    ~TextureManager();

    template<typename RendererT>
    TextureT* createTexture(RendererT& renderer, String const& uri);

  private:
    typedef ctr::Map<ImageManager::ImagePointer, TextureT*> Textures;

    ResourceManager const* resource_manager_;

    Textures textures_;

    TextureManager(TextureManager const&);
    TextureManager& operator =(TextureManager const&);

    ImageManager::ImagePointer loadImage(String const& uri) const;
  };
}


namespace gui
{
  /**
   * @param resource_manager
   */
  template<typename TextureT>
  TextureManager<TextureT>::TextureManager(ResourceManager const& resource_manager)
    : resource_manager_(&resource_manager)
  {
  }

  /**
   * The destructor free's all loaded textures.
   */
  template<typename TextureT>
  TextureManager<TextureT>::~TextureManager()
  {
    for (typename Textures::ConstIterator it = textures_.begin(); it != textures_.end(); ++it)
      delete it->second;
  }

  /**
   * This method can be used to create a texture from a given uri and stores
   * the pointer to it.
   * @param[in] uri image uri from which the texture should be created
   * @return pointer to loaded texture or null if the texture could not be loaded
   * @todo actually the TextureManager could also store <uri, texture> tuples in order to not have
   *       to query the image manager for every requested texture
   */
  template<typename TextureT>
  template<typename RendererT>
  TextureT* TextureManager<TextureT>::createTexture(RendererT& renderer, String const& uri)
  {
    ImageManager::ImagePointer const& image = loadImage(uri);

    if (image)
    {
      typename Textures::ConstIterator const& it = textures_.find(image);

      if (it != textures_.end())
      {
        ASSERTOP(it->second, ne, nullptr);
        return it->second;
      }
      else
      {
        TextureT* texture = new TextureT(renderer, *image, true);
        textures_.insert(typename Textures::Entry(image, texture));

        return texture;
      }
    }
    return nullptr;
  }

  /**
   * This method is used to load an image from a uri.
   * @param[in] uri image uri to load
   * @return pointer to loaded image or null if the image could not be loaded
   */
  template<typename TextureT>
  ImageManager::ImagePointer TextureManager<TextureT>::loadImage(String const& uri) const
  {
    return resource_manager_->loadImage(uri);
  }
}


#endif
