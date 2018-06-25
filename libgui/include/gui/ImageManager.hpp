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

#ifndef GUIIMAGEMANAGER_HPP
#define GUIIMAGEMANAGER_HPP

#include <pointer/SharedPointer.hpp>
#include <container/Map.hpp>

#include <image/ImageBase.hpp>
#include <image/codec/CodecBase.hpp>

#include "gui/Config.hpp"


#ifdef LoadImage
#undef LoadImage
#endif


namespace gui
{
  class NamespaceManager;


  /**
   *
   */
  class LIBGUI_EXPORT ImageManager
  {
  public:
    typedef ptr::SharedPointer<img::CodecBase> CodecPointer;
    typedef ptr::SharedPointer<img::ImageBase> ImagePointer;

    ImageManager(NamespaceManager const& namespace_manager);

    bool registerCodec(img::CodecBase const& codec);
    bool unregisterCodec(img::CodecBase const& codec);

    ImagePointer loadImage(String const& uri);

  private:
    typedef ctr::Map<String, CodecPointer> Codecs;
    typedef ctr::Map<String, ImagePointer> Images;

    NamespaceManager const* namespace_manager_;

    Codecs codecs_;
    Images images_;

    ImageManager(ImageManager const&);
    ImageManager& operator =(ImageManager const&);
  };
}


#endif
