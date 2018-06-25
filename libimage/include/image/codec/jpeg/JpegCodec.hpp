// JpegCodec.hpp

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

#ifndef IMGJPEGCODEC_HPP
#define IMGJPEGCODEC_HPP

#include "image/codec/CodecBase.hpp"


namespace img
{
  /**
   * This class represents the jpeg codec. It directly uses the functions
   * provided by libjpeg.
   */
  class LIBIMAGE_EXPORT JpegCodec: public CodecBase
  {
  public:
    virtual ImageBase* decode(Stream& stream) const;
    virtual bool isForData(Stream& stream) const override;

    virtual CodecBase* duplicate() const override;

    virtual String name() const override;
  };
}


#endif
