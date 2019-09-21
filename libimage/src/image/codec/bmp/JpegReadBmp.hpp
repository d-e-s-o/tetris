// JpegReadBmp.hpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2019 Daniel Mueller (deso@posteo.net)         *
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

#include <cstdio>
#include <jpeglib.h>


namespace img
{
  class Stream;


  #define JMESSAGE(code,string)  string ,

  static char const* const bmp_error_table[] =
  {
    #include "BmpError.hpp"
    NULL
  };


  typedef struct cjpeg_source_struct* cjpeg_source_ptr;

  struct cjpeg_source_struct
  {
    JMETHOD(void, start_input, (j_compress_ptr cinfo, cjpeg_source_ptr sinfo));
    JMETHOD(JDIMENSION, get_pixel_rows, (j_compress_ptr cinfo, cjpeg_source_ptr sinfo));
    JMETHOD(void, finish_input, (j_compress_ptr cinfo, cjpeg_source_ptr sinfo));

    Stream* stream;

    JSAMPARRAY buffer;
    JDIMENSION buffer_height;
  };


  cjpeg_source_ptr jinit_read_bmp(j_compress_ptr cinfo);
}
