// PngCodec.cpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014,2019 Daniel Mueller (deso@posteo.net)    *
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

#include <png.h>

#include <util/Assert.hpp>
#include <pointer/ResourceGuard.hpp>

#include "image/Pixel.hpp"
#include "image/Image.hpp"
#include "image/Error.hpp"
#include "image/Stream.hpp"
#include "image/codec/png/PngCodec.hpp"


namespace img
{
  namespace
  {
    /**
     * This function is used as callback function for reading data from a
     * stream into the supplied buffer.
     * @param[in] png_ptr pointer to png structure with stream data
     * @param[out] buffer buffer to fill with data
     * @param[in] size size of buffer
     */
    void readStreamSource(png_structp png_ptr, png_bytep buffer, png_size_t size)
    {
      ASSERTOP(png_get_io_ptr(png_ptr), ne, nullptr);

      Stream* stream = static_cast<Stream*>(png_get_io_ptr(png_ptr));
      stream->read(buffer, static_cast<size_t>(size));
    }

    /**
    * This is a callback function for libpng. It is called whenever an
    * error occurred. In that case an exception is thrown.
    * @param[in] png_ptr pointer to png structure (ignored, but needed in
    *            interface)
    * @param[in] message error message string
    */
    void errorExit(png_structp png_ptr, png_const_charp message)
    {
      ASSERTOP(message, ne, nullptr);
      ASSERTOP(message[0], ne, '\0');
      throw Error("Error loading image with png codec", message);
    }

    /**
     *
     */
    template<typename PixelT>
    ImageBase* readImage(png_struct& png, png_uint_32 w, png_uint_32 h)
    {
      Image<PixelT>* image = new Image<PixelT>(w, h);

      ctr::Array<PixelT*> pixel = get2DData(*image);
      ASSERTOP(pixel.size(), gt, 0);

      png_bytepp ptr = reinterpret_cast<png_bytepp>(&pixel[0]);

      // we could also read every single scanline, but thats more complicated and probably slower
      png_read_image(&png, ptr);

      return image;
    }

    /**
     * This function fills the image format struct with data from given png structures.
     * @param[in] png png structure
     * @param[in] info png info structure
     * @return pointer to created image (has to be free'd with delete) or 0 if
     *         an error occurred
     */
    ImageBase* createImage(png_struct& png, png_info& info)
    {
      png_uint_32 width  = 0;
      png_uint_32 height = 0;

      int color_type = 0;
      int bit_depth  = 0;

      png_get_IHDR(&png, &info, &width, &height, &bit_depth, &color_type, 0, 0, 0);

      switch (color_type)
      {
      case PNG_COLOR_TYPE_RGB:
        switch(bit_depth)
        {
        case 8:
          return readImage<PixelUByteRGB>(png, width, height);

        case 16:
          return readImage<PixelUWordRGB>(png, width, height);
        }
        break;

      case PNG_COLOR_TYPE_RGB_ALPHA:
        switch (bit_depth)
        {
        case 8:
          return readImage<PixelUByteRGBA>(png, width, height);

        case 16:
          return readImage<PixelUWordRGBA>(png, width, height);
        }
        break;
      }
      ASSERT(false);
      return 0;
    }

    /**
     * @param[in] png png structure
     * @param{in] info png info structure
     * @return pointer to created image (has to be free'd with delete) or 0 if an error occurred
     */
    ImageBase* readData(png_struct& png, png_info& info)
    {
      png_read_info(&png, &info);
      png_read_update_info(&png, &info);

      ImageBase* image = createImage(png, info);

      png_read_end(&png, &info);
      return image;
    }

    struct PngData
    {
      png_structp png_ptr;
      png_infop info_ptr;
    };

    /**
     * @param png_data
     */
    void destroyReadStruct(PngData png_data)
    {
      png_destroy_read_struct(&png_data.png_ptr, &png_data.info_ptr, 0);
    }
  }

  /**
   * @copydoc CodecBase::Decode
   */
  ImageBase* PngCodec::decode(Stream& stream) const
  {
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, &errorExit, 0);

    if (png_ptr != 0)
    {
      png_infop info_ptr = 0;
      info_ptr = png_create_info_struct(png_ptr);

      if (info_ptr != 0)
      {
        PngData data;
        data.png_ptr = png_ptr;
        data.info_ptr = info_ptr;

        ptr::ResourceGuard<PngData const&, void (*)(PngData)> guard(data, &destroyReadStruct);

        png_set_read_fn(png_ptr, &stream, &readStreamSource);
        return readData(*png_ptr, *info_ptr);
      }
      png_destroy_read_struct(&png_ptr, 0, 0);
    }
    return 0;
  }

  /**
   * @copydoc CodecBase::IsForData
   */
  bool PngCodec::isForData(Stream& stream) const
  {
    png_size_t const PNG_BYTES_TO_CHECK = 4;

    png_byte buffer[PNG_BYTES_TO_CHECK] = {};
    size_t position = stream.position();

    stream.read(buffer, PNG_BYTES_TO_CHECK);
    stream.reposition(position);

    return png_sig_cmp(buffer, 0, PNG_BYTES_TO_CHECK) == 0;
  }

  /**
   * @copydoc CodecBase::Duplicate
   */
  CodecBase* PngCodec::duplicate() const
  {
    return new PngCodec();
  }

  /**
   * @copydoc CodecBase::Name
   */
  String PngCodec::name() const
  {
    return String(TEXT("png"));
  }
}
