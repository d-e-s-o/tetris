// CodecBase.hpp

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

#ifndef IMGCODECBASE_HPP
#define IMGCODECBASE_HPP

#include "image/Config.hpp"
#include "image/String.hpp"


namespace img
{
  class ImageBase;
  class Stream;


  /**
   * This class defines the interface for all image data decoders. Basically it reads data from a
   * stream, converts it and writes it to the image.
   * @note all classes of this kind have to be copyable
   * @todo add template parameter for returning statically typed image (probably for new method
   *       decodeAs())
   * @todo remove dependencies to libbase stuff
   */
  class LIBIMAGE_EXPORT CodecBase
  {
  public:
    virtual ~CodecBase() = 0;

    /**
     * Method called for decoding an image. That includes reading data from stream, uncompressing
     * (if necessary) and writing it to buffer and its format into format.
     * This method is abstract. It has to be overwritten in subclasses.
     * @param[in] stream input stream to read data from
     * @return pointer to decoded image or 0 if an error occured
     */
    virtual ImageBase* decode(Stream& stream) const = 0;

    /**
     * This method checks the given filestream wether its data can be decoded with this codec.
     * @note this method will most likely read some data from the stream. This will be undone after
     *       reading, but to do that a seekable stream is required.
     * @param[in] stream seekable stream with image data
     * @return true if data can be decoded with this codec, false if not
     */
    virtual bool isForData(Stream& stream) const = 0;

    /**
     * This method is used to create a copy of the current image codec. The returned copy has to be
     * deleted.
     * @return copy of the current image codec object allocated with new
     */
    virtual CodecBase* duplicate() const = 0;

    /**
     * This method returns an unique string describing the codec.
     * @return unique string describing the codec
     */
    virtual String name() const = 0;
  };
}


#endif
