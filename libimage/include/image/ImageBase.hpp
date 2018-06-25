// ImageBase.hpp

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

#ifndef IMGIMAGEBASE_HPP
#define IMGIMAGEBASE_HPP

#include "image/Config.hpp"


namespace img
{
  class ImageAction;
  class ConstImageAction;


  /**
   *
   */
  class LIBIMAGE_EXPORT ImageBase
  {
  public:
    ImageBase() = default;
    ImageBase(ImageBase&& other) = default;
    ImageBase(ImageBase const& other) = default;

    virtual ~ImageBase() = 0;

    ImageBase& operator =(ImageBase&&) = default;
    ImageBase& operator =(ImageBase const&) = default;

    virtual void use(ImageAction& action) = 0;
    virtual void use(ConstImageAction& action) const = 0;

    virtual size_t width() const = 0;
    virtual size_t height() const = 0;
    virtual size_t alignment() const = 0;
  };
}


namespace img
{
  inline ImageBase::~ImageBase()
  {
  }
}


#endif
