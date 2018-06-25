// BmpCodec.cpp

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

#include "image/Stream.hpp"
#include "image/codec/bmp/JpegReadBmp.hpp"
#include "image/codec/bmp/BmpError.hpp"
#include "image/codec/bmp/BmpCodec.hpp"


namespace img
{
  /**
   *
   */
  ImageBase* BmpCodec::decode(Stream& stream) const
  {
    //jpeg_compress_struct compress;
    //jpeg_error_mgr error;

    //compress.err = jpeg_std_error(&error);
    //jpeg_create_compress(&compress);

    //error.addon_message_table = bmp_error_table;
    //error.first_addon_message = JMSG_FIRSTADDONCODE;
    //error.last_addon_message = JMSG_LASTADDONCODE;

    //compress.in_color_space = JCS_RGB;
    //jpeg_set_defaults(&compress);

    //cjpeg_source_ptr src_mgr;
    //src_mgr = jinit_read_bmp(&compress);
    //src_mgr->stream = &stream;

    //(*src_mgr->start_input)(&compress, src_mgr);
    //jpeg_default_colorspace(&compress);

    //while (compress.next_scanline < compress.image_height)
    //  (*src_mgr->get_pixel_rows)(&compress, src_mgr);

    //jpeg_destroy_compress(&compress);
    return 0;
  }

  /**
   * @copydoc CodecBase::IsForData
   */
  bool BmpCodec::isForData(Stream& stream) const
  {
    size_t const BYTES_TO_CHECK = 2;

    byte_t buffer[BYTES_TO_CHECK] = {};
    size_t position = stream.position();

    stream.read(buffer, BYTES_TO_CHECK);
    stream.reposition(position);

    return buffer[0] == 'B' && buffer[1] == 'M';
  }

  /**
   * @copydoc CodecBase::Duplicate
   */
  CodecBase* BmpCodec::duplicate() const
  {
    return new BmpCodec();
  }

  /**
   * @copydoc CodecBase::Name
   */
  String BmpCodec::name() const
  {
    return String(TEXT("bmp"));
  }
}
