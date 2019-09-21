// JpegCodec.cpp

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

#include <climits>

#include <stdio.h>
#include <jpeglib.h>

#include <util/Assert.hpp>
#include <pointer/ResourceGuard.hpp>

#include "image/Pixel.hpp"
#include "image/Image.hpp"
#include "image/Error.hpp"
#include "image/Stream.hpp"
#include "image/codec/jpeg/JpegStreamSource.hpp"
#include "image/codec/jpeg/JpegCodec.hpp"


namespace img
{
  namespace
  {
    /**
     * This function is used as callback by libjpeg. It is called in
     * case of an critical error, which leads to abort decompression. It
     * throws an error exception with the given error message.
     * @param[in] cinfo jpeg structure for storing different information
     */
    void errorExit(j_common_ptr cinfo)
    {
      jpeg_error_mgr* error = static_cast<jpeg_error_mgr*>(cinfo->err);

      char message[JMSG_LENGTH_MAX];
      (*error->format_message)(cinfo, message);

      ASSERTOP(JMSG_LENGTH_MAX, gt, 0);
      ASSERTOP(message[0], ne, '\0');
      throw Error("Error loading image with jpeg codec", message);
    }

    /**
     * @param[in] decompress jpeg decompress structure ready to start
     *            reading data
     * @param[out] data pixel data that will be created and stored in
     *             there
     * @return true on success, false otherwise
     */
    template<typename PixelT>
    ImageBase* readScanlines(jpeg_decompress_struct& decompress, JDIMENSION w, JDIMENSION h)
    {
      Image<PixelT>* image = new Image<PixelT>(w, h);

      JDIMENSION const& line = decompress.output_scanline;
      JDIMENSION const& height = decompress.output_height;
      ASSERTOP(line, eq, 0);

      // now start reading the scanlines
      // if speed is an issue it would be possible to create 2D vector
      // and read multiple scanlines at once (not sure if its actually
      // faster) but in my tests only one scanline (maybe two) were read
      // at one, no matter what jpeg_read_scanlines's last parameter was
      while (line < height)
      {
        JSAMPROW scanline = reinterpret_cast<JSAMPROW>(image->scanline(line));
        ASSERTOP(scanline, ne, nullptr);

        jpeg_read_scanlines(&decompress, &scanline, 1);
      }
      ASSERTOP(line, eq, height);
      return image;
    }

    ImageBase* createImage(jpeg_decompress_struct& decompress)
    {
      JDIMENSION width = decompress.output_width;
      JDIMENSION height = decompress.output_height;

      switch(decompress.output_components)
      {
      case 3:
        switch(decompress.data_precision)
        {
        case 8:
          return readScanlines<PixelUByteRGB>(decompress, width, height);

        case 16:
          return readScanlines<PixelUWordRGB>(decompress, width, height);
        }

      case 4:
        switch(decompress.data_precision)
        {
        case 8:
          return readScanlines<PixelUByteRGBA>(decompress, width, height);

        case 16:
          return readScanlines<PixelUWordRGBA>(decompress, width, height);
        }
      }
      ASSERT(false);
      return 0;
    }

    /**
     * This function destroys the decompress structure.
     */
    void destroyDecompress(jpeg_decompress_struct& decompress)
    {
      jpeg_destroy_decompress(&decompress);
    }
  }

  /**
   * @copydoc CodecBase::Decode
   */
  ImageBase* JpegCodec::decode(Stream& stream) const
  {
    jpeg_decompress_struct decompress = {};
    jpeg_create_decompress(&decompress);

    typedef void (*DestroyFn)(jpeg_decompress_struct&);
    ptr::ResourceGuard<jpeg_decompress_struct&, DestroyFn> guard(decompress, &destroyDecompress);

    jpeg_stream_src(&decompress, stream);

    // create struct for storing error information and set it to default
    // behavior but overwrite the default callback for critical errors
    jpeg_error_mgr error = {};
    decompress.err = jpeg_std_error(&error);
    error.error_exit = &errorExit;

    jpeg_read_header(&decompress, TRUE);
    jpeg_start_decompress(&decompress);

    ImageBase* image = createImage(decompress);

    jpeg_finish_decompress(&decompress);
    jpeg_destroy_decompress(&decompress);

    return image;
  }

  /**
   * @copydoc CodecBase::IsForData
   */
  bool JpegCodec::isForData(Stream& stream) const
  {
    size_t const BYTES_TO_CHECK = 2;

    byte_t buffer[BYTES_TO_CHECK] = {};
    size_t position = stream.position();

    stream.read(buffer, BYTES_TO_CHECK);
    stream.reposition(position);

    return buffer[0] == 0xFF && buffer[1] == 0xD8;
  }

  /**
   * @copydoc CodecBase::Duplicate
   */
  CodecBase* JpegCodec::duplicate() const
  {
    return new JpegCodec();
  }

  /**
   * @copydoc CodecBase::Name
   */
  String JpegCodec::name() const
  {
    return String(TEXT("jpeg"));
  }
}
