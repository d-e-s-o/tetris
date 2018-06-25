// JpegReadBmp.cpp

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

#include <stdio.h>
#include <jpeglib.h>
#include <jerror.h>

#include "image/Stream.hpp"
#include "image/codec/bmp/BmpError.hpp"
#include "image/codec/bmp/JpegReadBmp.hpp"


namespace img
{
  /* Macros to deal with unsigned chars as efficiently as compiler allows */
  typedef unsigned char U_CHAR;
  #define UCH(x)  ((int) (x))


  /* Private version of data source object */
  typedef struct bmp_source_struct* bmp_source_ptr;

  struct bmp_source_struct
  {
    struct cjpeg_source_struct pub; /* public fields */

    j_compress_ptr cinfo;    /* back link saves passing separate parm */
    JSAMPARRAY colormap;    /* BMP colormap (converted to my format) */

    jvirt_sarray_ptr whole_image;  /* Needed to reverse row order */
    JDIMENSION source_row;  /* Current source row number */
    JDIMENSION row_width;    /* Physical width of scanlines in file */

    int bits_per_pixel;    /* remembers 8- or 24-bit format */
  };


  inline bool readOK(Stream& stream, byte_t* data, size_t size)
  {
    return stream.read(data, size) == size;
  }


  inline int read_byte(bmp_source_ptr sinfo)
    /* Read next byte from BMP file */
  {
    Stream* stream = sinfo->pub.stream;
    byte_t byte = 0;

    if ( stream->read(&byte, 1) != 1 )
      ERREXIT(sinfo->cinfo, JERR_INPUT_EOF);

    return byte;
  }


  void read_colormap(bmp_source_ptr sinfo, int cmaplen, int mapentrysize)
    /* Read the colormap from a BMP file */
  {
    switch (mapentrysize)
    {
    case 3:
      /* BGR format (occurs in OS/2 files) */
      for (int i = 0; i < cmaplen; i++)
      {
        sinfo->colormap[2][i] = static_cast<JSAMPLE>( read_byte(sinfo) );
        sinfo->colormap[1][i] = static_cast<JSAMPLE>( read_byte(sinfo) );
        sinfo->colormap[0][i] = static_cast<JSAMPLE>( read_byte(sinfo) );
      }
      break;

    case 4:
      /* BGR0 format (occurs in MS Windows files) */
      for (int i = 0; i < cmaplen; i++)
      {
        sinfo->colormap[2][i] = static_cast<JSAMPLE>( read_byte(sinfo) );
        sinfo->colormap[1][i] = static_cast<JSAMPLE>( read_byte(sinfo) );
        sinfo->colormap[0][i] = static_cast<JSAMPLE>( read_byte(sinfo) );
        read_byte(sinfo);
      }
      break;

    default:
      ERREXIT(sinfo->cinfo, JERR_BMP_BADCMAP);
      break;
    }
  }


  /*
   * Read one row of pixels.
   * The image has been read into the whole_image array, but is otherwise
   * unprocessed.  We must read it out in top-to-bottom row order, and if
   * it is an 8-bit image, we must expand colormapped pixels to 24bit format.
   */
  JDIMENSION get_8bit_row(j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
    /* This version is for reading 8-bit colormap indexes */
  {
    bmp_source_ptr source = (bmp_source_ptr) sinfo;
    register JSAMPARRAY colormap = source->colormap;
    JSAMPARRAY image_ptr;
    register int t;
    register JSAMPROW inptr, outptr;
    register JDIMENSION col;

    /* Fetch next row from virtual array */
    source->source_row--;
    image_ptr = (*cinfo->mem->access_virt_sarray)((j_common_ptr) cinfo, source->whole_image, source->source_row, 1, FALSE);

    /* Expand the colormap indexes to real data */
    inptr = image_ptr[0];
    outptr = source->pub.buffer[0];

    for (col = cinfo->image_width; col > 0; col--)
    {
      t = GETJSAMPLE(*inptr++);
      *outptr++ = colormap[0][t];  /* can omit GETJSAMPLE() safely */
      *outptr++ = colormap[1][t];
      *outptr++ = colormap[2][t];
    }
    return 1;
  }


  JDIMENSION get_24bit_row(j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
    /* This version is for reading 24-bit pixels */
  {
    bmp_source_ptr source = (bmp_source_ptr) sinfo;
    JSAMPARRAY image_ptr;
    register JSAMPROW inptr, outptr;
    register JDIMENSION col;

    /* Fetch next row from virtual array */
    source->source_row--;
    image_ptr = (*cinfo->mem->access_virt_sarray)((j_common_ptr) cinfo, source->whole_image, source->source_row, 1, FALSE);

    /* Transfer data.  Note source values are in BGR order
    * (even though Microsoft's own documents say the opposite).
    */
    inptr = image_ptr[0];
    outptr = source->pub.buffer[0];

    for (col = cinfo->image_width; col > 0; col--)
    {
      outptr[2] = *inptr++;  /* can omit GETJSAMPLE() safely */
      outptr[1] = *inptr++;
      outptr[0] = *inptr++;
      outptr += 3;
    }
    return 1;
  }


  /*
   * This method loads the image into whole_image during the first call on
   * get_pixel_rows.  The get_pixel_rows pointer is then adjusted to call
   * get_8bit_row or get_24bit_row on subsequent calls.
   */
  JDIMENSION preload_image(j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
  {
    bmp_source_ptr source = (bmp_source_ptr) sinfo;
    register JSAMPROW out_ptr;
    JSAMPARRAY image_ptr;
    JDIMENSION row, col;

    /* Read the data into a virtual array in input-file row order. */
    for (row = 0; row < cinfo->image_height; row++)
    {
      image_ptr = (*cinfo->mem->access_virt_sarray)((j_common_ptr) cinfo, source->whole_image, row, 1, TRUE);
      out_ptr = image_ptr[0];

      for (col = source->row_width; col > 0; col--)
        *out_ptr++ = static_cast<JSAMPLE>( read_byte(source) );
    }

    /* Set up to read from the virtual array in top-to-bottom order */
    switch (source->bits_per_pixel)
    {
    case 8:
      source->pub.get_pixel_rows = get_8bit_row;
      break;

    case 24:
      source->pub.get_pixel_rows = get_24bit_row;
      break;

    default:
      ERREXIT(cinfo, JERR_BMP_BADDEPTH);
      break;
    }

    source->source_row = cinfo->image_height;

    /* And read the first row */
    return (*source->pub.get_pixel_rows)(cinfo, sinfo);
  }


#define GET_2B(array,offset)  ((unsigned int) UCH(array[offset]) + \
  (((unsigned int) UCH(array[offset+1])) << 8))
#define GET_4B(array,offset)  ((INT32) UCH(array[offset]) + \
  (((INT32) UCH(array[offset+1])) << 8) + \
  (((INT32) UCH(array[offset+2])) << 16) + \
  (((INT32) UCH(array[offset+3])) << 24))


  /*
   * Read the file header; return image size and component count.
   */
  void start_input_bmp(j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
  {
    bmp_source_ptr source = (bmp_source_ptr) sinfo;
    U_CHAR bmpfileheader[14];
    U_CHAR bmpinfoheader[64];

    INT32 biWidth = 0;    /* initialize to avoid compiler warning */
    INT32 biHeight = 0;
    INT32 biClrUsed = 0;
    int mapentrysize = 0;    /* 0 indicates no colormap */

    /* Read and verify the bitmap file header */
    if ( !readOK(*source->pub.stream, bmpfileheader, 14) )
      ERREXIT(cinfo, JERR_INPUT_EOF);

    if ( GET_2B(bmpfileheader,0) != 0x4D42 ) /* 'BM' */
      ERREXIT(cinfo, JERR_BMP_NOT);

    INT32 bfOffBits = GET_4B(bmpfileheader, 10);
    /* We ignore the remaining fileheader fields */

    /* The infoheader might be 12 bytes (OS/2 1.x), 40 bytes (Windows),
    * or 64 bytes (OS/2 2.x).  Check the first 4 bytes to find out which.
    */
    if (! readOK(*source->pub.stream, bmpinfoheader, 4))
      ERREXIT(cinfo, JERR_INPUT_EOF);

    INT32 headerSize = (INT32) GET_4B(bmpinfoheader, 0);

    if (headerSize < 12 || headerSize > 64)
      ERREXIT(cinfo, JERR_BMP_BADHEADER);

    if ( !readOK(*source->pub.stream, bmpinfoheader + 4, headerSize - 4) )
      ERREXIT(cinfo, JERR_INPUT_EOF);

    switch(headerSize)
    {
    case 12:
      {
        /* Decode OS/2 1.x header (Microsoft calls this a BITMAPCOREHEADER) */
        biWidth = (INT32) GET_2B(bmpinfoheader, 4);
        biHeight = (INT32) GET_2B(bmpinfoheader, 6);

        unsigned int biPlanes = GET_2B(bmpinfoheader, 8);
        source->bits_per_pixel = GET_2B(bmpinfoheader, 10);

        switch (source->bits_per_pixel)
        {
        case 8:      /* colormapped image */
          mapentrysize = 3;    /* OS/2 uses RGBTRIPLE colormap */
          TRACEMS2(cinfo, 1, JTRC_BMP_OS2_MAPPED, biWidth, biHeight);
          break;

        case 24:      /* RGB image */
          TRACEMS2(cinfo, 1, JTRC_BMP_OS2, biWidth, biHeight);
          break;

        default:
          ERREXIT(cinfo, JERR_BMP_BADDEPTH);
          break;
        }

        if (biPlanes != 1)
          ERREXIT(cinfo, JERR_BMP_BADPLANES);
      }
      break;

    case 40:
    case 64:
      {
        /* Decode Windows 3.x header (Microsoft calls this a BITMAPINFOHEADER) */
        /* or OS/2 2.x header, which has additional fields that we ignore */
        biWidth = GET_4B(bmpinfoheader, 4);
        biHeight = GET_4B(bmpinfoheader, 8);

        unsigned int biPlanes = GET_2B(bmpinfoheader, 12);
        source->bits_per_pixel = GET_2B(bmpinfoheader, 14);

        INT32 biCompression = GET_4B(bmpinfoheader, 16);
        INT32 biXPelsPerMeter = GET_4B(bmpinfoheader, 24);
        INT32 biYPelsPerMeter = GET_4B(bmpinfoheader, 28);
        biClrUsed = GET_4B(bmpinfoheader, 32);
        /* biSizeImage, biClrImportant fields are ignored */

        switch (source->bits_per_pixel)
        {
        case 8:      /* colormapped image */
          mapentrysize = 4;    /* Windows uses RGBQUAD colormap */
          TRACEMS2(cinfo, 1, JTRC_BMP_MAPPED, biWidth, biHeight);
          break;

        case 24:      /* RGB image */
          TRACEMS2(cinfo, 1, JTRC_BMP, biWidth, biHeight);
          break;

        default:
          ERREXIT(cinfo, JERR_BMP_BADDEPTH);
          break;
        }

        if (biPlanes != 1)
          ERREXIT(cinfo, JERR_BMP_BADPLANES);

        if (biCompression != 0)
          ERREXIT(cinfo, JERR_BMP_COMPRESSED);

        if (biXPelsPerMeter > 0 && biYPelsPerMeter > 0)
        {
          /* Set JFIF density parameters from the BMP data */
          cinfo->X_density = (UINT16) (biXPelsPerMeter/100); /* 100 cm per meter */
          cinfo->Y_density = (UINT16) (biYPelsPerMeter/100);
          cinfo->density_unit = 2;  /* dots/cm */
        }
      }
      break;

    default:
      ERREXIT(cinfo, JERR_BMP_BADHEADER);
      break;
    }

    /* Compute distance to bitmap data --- will adjust for colormap below */
    INT32 bPad = bfOffBits - (headerSize + 14);

    /* Read the colormap, if any */
    if (mapentrysize > 0)
    {
      if (biClrUsed <= 0)
        biClrUsed = 256;    /* assume it's 256 */
      else if (biClrUsed > 256)
        ERREXIT(cinfo, JERR_BMP_BADCMAP);

      /* Allocate space to store the colormap */
      source->colormap = (*cinfo->mem->alloc_sarray)((j_common_ptr) cinfo, JPOOL_IMAGE, biClrUsed, 3);

      /* and read it from the file */
      read_colormap(source, biClrUsed, mapentrysize);

      /* account for size of colormap */
      bPad -= biClrUsed * mapentrysize;
    }

    /* Skip any remaining pad bytes */
    if (bPad < 0)      /* incorrect bfOffBits value? */
      ERREXIT(cinfo, JERR_BMP_BADHEADER);

    while (--bPad >= 0)
      read_byte(source);

    JDIMENSION row_width = 0;

    /* Compute row width in file, including padding to 4-byte boundary */
    if (source->bits_per_pixel == 24)
      row_width = (JDIMENSION) (biWidth * 3);
    else
      row_width = (JDIMENSION) biWidth;

    while ((row_width & 3) != 0)
      row_width++;

    source->row_width = row_width;

    /* Allocate space for inversion array, prepare for preload pass */
    source->whole_image = (*cinfo->mem->request_virt_sarray)((j_common_ptr) cinfo, JPOOL_IMAGE, FALSE, row_width, biHeight, 1);
    source->pub.get_pixel_rows = preload_image;

    /* Allocate one-row buffer for returned data */
    source->pub.buffer = (*cinfo->mem->alloc_sarray)((j_common_ptr) cinfo, JPOOL_IMAGE, biWidth * 3, 1);
    source->pub.buffer_height = 1;

    cinfo->in_color_space = JCS_RGB;
    cinfo->input_components = 3;
    cinfo->data_precision = 8;
    cinfo->image_width = biWidth;
    cinfo->image_height = biHeight;
  }


  /*
   * Finish up at the end of the file.
   */
  void finish_input_bmp(j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
  {
    /* no work */
  }


  /*
   * The module selection routine for BMP format input.
   */
  cjpeg_source_ptr jinit_read_bmp(j_compress_ptr cinfo)
  {
    bmp_source_ptr source;

    /* Create module interface object */
    source = (bmp_source_ptr) (*cinfo->mem->alloc_small)((j_common_ptr) cinfo, JPOOL_IMAGE, sizeof(bmp_source_struct));
    source->cinfo = cinfo;  /* make back link for subroutines */
    /* Fill in method ptrs, except get_pixel_rows which start_input sets */
    source->pub.start_input = start_input_bmp;
    source->pub.finish_input = finish_input_bmp;

    return reinterpret_cast<cjpeg_source_ptr>(source);
  }
}
