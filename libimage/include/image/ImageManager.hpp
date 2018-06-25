// ImageManager.hpp

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

#ifndef IMGIMAGEMANAGER_HPP
#define IMGIMAGEMANAGER_HPP

#include <container/Map.hpp>

#include "image/Config.hpp"
#include "image/String.hpp"


#ifdef LoadImage
#undef LoadImage
#endif


namespace img
{
  class CodecBase;
  class ImageBase;


  /**
   *
   */
  class LIBIMAGE_EXPORT ImageManager
  {
  public:
    ImageManager();
    ImageManager(ImageManager&& other) = delete;
    ImageManager(ImageManager const& other) = delete;

    ~ImageManager();

    ImageManager& operator =(ImageManager&& other);
    ImageManager& operator =(ImageManager const& other);

    bool registerCodec(CodecBase const& codec);
    bool unregisterCodec(CodecBase const& codec);

    ImageBase* loadImage(String const& filename);

  private:
    typedef ctr::Map<String, CodecBase*> Codecs;
    typedef ctr::Map<String, ImageBase*> Images;

    Codecs codecs_;
    Images images_;
  };
}


#endif
