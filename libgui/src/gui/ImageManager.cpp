// ImageManager.cpp

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

#include <util/Assert.hpp>
#include <image/Stream.hpp>

#include "gui/NamespaceManager.hpp"
#include "gui/ImageManager.hpp"


namespace gui
{
  namespace
  {
    /**
     * This class implements the img::Stream interface for the supplied stream.
     */
    class ImageStream: public img::Stream
    {
    public:
      ImageStream(Namespace::StreamPointer stream)
        : stream_(stream)
      {
      }

      virtual size_t read(byte_t* buffer, size_t size)
      {
        return stream_->read(buffer, size);
      }

      virtual size_t position() const
      {
        return stream_->position();
      }

      virtual void reposition(size_t position)
      {
        stream_->reposition(position);
      }

      virtual size_t size() const
      {
        return stream_->size();
      }

    private:
      Namespace::StreamPointer stream_;
    };
  }


  /**
   * @param namespace_manager
   */
  ImageManager::ImageManager(NamespaceManager const& namespace_manager)
    : namespace_manager_(&namespace_manager)
  {
  }

  /**
   * This method registers a new image codec that can be used to load images.
   * @param[in] codec codec type to register
   * @return true if registering was successful, false if not
   */
  bool ImageManager::registerCodec(img::CodecBase const& codec)
  {
    String const& name = codec.name();

    if (codecs_.find(name) == codecs_.end())
    {
      codecs_.insert(Codecs::Entry(name, CodecPointer(codec.duplicate())));
      return true;
    }
    return false;
  }

  /**
   * This method removes a registered codec from the list of available ones.
   * @param[in] codec codec type to remove
   * @return true if codec could be removed, false if not
   */
  bool ImageManager::unregisterCodec(img::CodecBase const& codec)
  {
    Codecs::ConstIterator it = codecs_.find(codec.name());

    if (it != codecs_.end())
    {
      /**
       * @todo actually we need a version of remove() here that takes an iterator -- fix this!
       */
      codecs_.remove(it->first);
      return true;
    }
    return false;
  }

  /**
   * This method loads an image from a given ressource. It therefor checks
   * whether on of the registered codecs can be used to decode the image and
   * starts decoding.
   * @param[in] uri uri to load image from (relative or absolute)
   * @return pointer to created image or 0 on error
   */
  ImageManager::ImagePointer ImageManager::loadImage(String const& uri)
  {
    Images::ConstIterator const& it = images_.find(uri);

    if (it != images_.end())
    {
      ASSERTOP(it->second, ne, nullptr);
      return it->second;
    }
    else
    {
      Namespace::StreamPointer stream = namespace_manager_->open(uri);

      if (!stream)
        return ImagePointer(0);

      ImageStream image_stream = ImageStream(stream);

      for (Codecs::ConstIterator it = codecs_.begin(); it != codecs_.end(); ++it)
      {
        CodecPointer const& codec = it->second;
        ASSERTOP(codec, ne, nullptr);

        if (codec->isForData(image_stream))
        {
          ImagePointer image = ImagePointer(codec->decode(image_stream));

          if (image)
            images_.insert(Images::Entry(uri, image));

          return image;
        }
      }
    }
    return ImagePointer(0);
  }
}
