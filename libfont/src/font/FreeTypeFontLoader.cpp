// FreeTypeFontLoader.cpp

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

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <util/Assert.hpp>
#include <util/Algorithm.hpp>

#include <image/Pixel.hpp>
#include <image/Image.hpp>

#include "font/Error.hpp"
#include "font/FreeTypeFontLoader.hpp"


namespace fnt
{
  namespace
  {
    int const FT_PIXEL_DIVISOR = 64;


    /**
     * @param value font value in 26.6 fractional pixel format
     * @return pixel value calculated from given value
     */
    inline int pixelValue(int value)
    {
      return value / FT_PIXEL_DIVISOR;
    }

    /**
     * This function is used as callback from FreeType to read data from a random access stream
     * object.
     * @param[in] stream FT_Stream object supplied to FT_Open_Face in FT_Open_Args parameter
     * @param[in] offset offset in stream from where to read
     * @param[out] buffer memory buffer to store data read in
     * @param[in] count number to read frm stream
     * @return number of bytes read
     */
    unsigned long read(FT_Stream stream, unsigned long offset, unsigned char* buffer, unsigned long count)
    {
      if (buffer != 0 && count > 0)
      {
        auto data_stream = static_cast<Stream*>(stream->descriptor.pointer);
        ASSERTOP(data_stream, ne, nullptr);

        return data_stream->read(offset, buffer, count);
      }
      return 0;
    }

    /**
     * @param[in] stream stream FT_Stream object supplied to FT_Open_Face in FT_Open_Args parameter
     */
    void close(FT_Stream stream)
    {
      // nothing to do
    }

    /**
     * This function creates an image object from a rendered glyph (FT_Bitmap).
     * @param[in] bitmap bitmap containing rendered glyph data
     * @param[in] width width of the image to create
     * @param[in] height height of the image to create
     * @return
     * @todo this function will most likely not work with bitmaps, fix this!
     */
    template<typename Pixel>
    img::ImageBase* renderBitmap(FT_Bitmap const& bitmap, size_t width, size_t height)
    {
      auto image = new img::Image<Pixel>(width, height);
      auto src = bitmap.buffer;

      // if there was something rendered (which is not always the case, for
      // example a space is not rendered
      if (src != 0)
      {
        ASSERTOP(bitmap.rows, eq, static_cast<int>(image->height()));

        // begin with last scanline in image, because otherwise the image is
        // the wrong way around and we had to flip it
        for (int i = image->height() - 1; i >= 0; --i)
        {
          auto dst = reinterpret_cast<unsigned char*>(image->scanline(i));
          ASSERTOP(dst, ne, nullptr);

          utl::copy(src, src + bitmap.width, dst);
          src += bitmap.pitch;
        }
      }
      return image;
    }

    /**
     * @param stream
     * @note the reason we have this function in the first place (and do not simply use
     *       ptr::Deleter, which would achieve the same) is that ptr::Deleter is included in the
     *       header, where the FT_Stream, i.e., FT_StreamRec_, is not fully defined and thus it
     *       cannot work reliably unless we include the whole freeype header there (which we clearly
     *       do not want)
     */
    void Done_Stream(FT_Stream stream)
    {
      delete stream;
    }
  }


  /**
   * The constructor loads the font and initializes everything for rendering.
   * @param[in] stream stream to load font from
   * @param[in] size font size in pixels
   */
  FreeTypeFontLoader::FreeTypeFontLoader(Stream& stream, size_t size)
    : input_(&stream),
      library_(initializeLibrary()),
      library_guard_(library_, &FT_Done_FreeType),
      stream_(initializeStream()),
      stream_guard_(stream_, &Done_Stream),
      face_(initializeFace()),
      face_guard_(face_, &FT_Done_Face),
      size_(0)
  {
    if (face_->charmap == 0)
      throw Error(TEXT("Error loading FreeType face"), TEXT("No default charmap found"));

    resize(size);
  }

  /**
   * This helper method initializes the FT_Library structure.
   * @return initialized FT_Library member variable
   */
  FT_Library FreeTypeFontLoader::initializeLibrary()
  {
    FT_Library library = 0;

    if (FT_Init_FreeType(&library) != 0)
      throw Error(TEXT("Error initializing FreeType library"), TEXT("FT_Init_FreeType returned error code"));

    return library;
  }

  /**
   * This helper method sets up the FT_Stream.
   * @return initialized FT_Stream member variable
   */
  FT_Stream FreeTypeFontLoader::initializeStream()
  {
    FT_Stream stream = new FT_StreamRec_;

    stream->read               = &read;
    stream->close              = &close;
    stream->size               = input_->size();
    stream->descriptor.pointer = input_;

    return stream;
  }

  /**
   * This helper method sets up the FT_Face structure.
   * @return initialized FT_Face member variable
   */
  FT_Face FreeTypeFontLoader::initializeFace()
  {
    FT_Open_Args args = {};
    args.flags  = FT_OPEN_STREAM;
    args.stream = stream_;

    FT_Face face = 0;

    if (FT_Open_Face(library_, &args, 0, &face) != 0)
      throw Error(TEXT("Error loading FreeType face"), TEXT("FT_Open_Face returned error code"));

    return face;
  }

  /**
   * @copydoc FontLoader::Render
   */
  img::ImageBase* FreeTypeFontLoader::render(char_t character, GlyphMetrics& metrics) const
  {
    if (loadGlyph(character) && renderGlyph())
    {
      FT_GlyphSlot slot = face_->glyph;

      // for illustration what each metrics value represents in freetype see:
      // http://freetype.sourceforge.net/freetype2/docs/tutorial/step2.html
      metrics.pen_x   = pixelValue(slot->metrics.horiBearingX);
      metrics.pen_y   = pixelValue(slot->metrics.horiBearingY - slot->metrics.height);
      metrics.width   = pixelValue(slot->metrics.width);
      metrics.height  = pixelValue(slot->metrics.height);
      metrics.advance = pixelValue(slot->metrics.horiAdvance);

      return copyGlyph();
    }
    return 0;
  }

  /**
   * @copydoc FontLoader::Size
   */
  size_t FreeTypeFontLoader::size() const
  {
    return size_;
  }

  /**
   * @param size
   */
  void FreeTypeFontLoader::resize(size_t size)
  {
    if (FT_Set_Pixel_Sizes(face_, 0, size) != 0)
      throw Error(TEXT("Error setting new FreeType font size"), TEXT("FT_Set_Pixel_Sizes returned error code"));

    size_ = size;
  }

  /**
   * This helper method loads a glyph from a given character code. The result can be found in
   * face_->glyph.
   * @param[in] character character to load
   * @return true on success, false otherwise
   */
  bool FreeTypeFontLoader::loadGlyph(char_t character) const
  {
    //FT_UInt glyph_index = FT_Get_Char_Index(face_, character);
    //FT_Error error = FT_Load_Glyph(face_, glyph_index, FT_LOAD_DEFAULT);

    FT_Error error = FT_Load_Char(face_, character, FT_LOAD_DEFAULT);

    ASSERT(error == 0 && face_->glyph != 0 || error != 0);
    return error == 0;
  }

  /**
   * This method makes the library render the currently selected glyph (or do nothing is glyph is
   * already rendered).
   * @return true on success, false otherwise
   */
  bool FreeTypeFontLoader::renderGlyph() const
  {
    FT_GlyphSlot slot = face_->glyph;

    if (slot->format != FT_GLYPH_FORMAT_BITMAP)
      return FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL) == 0;

    ASSERTOP(slot->format, eq, FT_GLYPH_FORMAT_BITMAP);
    return false;
  }

  /**
   * This method takes a glyph slot (that was rendered with FT_Render_Glyph) and copies its
   * contents to an image.
   * @return image with glyph copied from given bitmap
   */
  img::ImageBase* FreeTypeFontLoader::copyGlyph() const
  {
    FT_Bitmap const& bitmap = face_->glyph->bitmap;

    size_t width  = bitmap.width;
    size_t height = bitmap.rows;

    switch(bitmap.pixel_mode)
    {
    case FT_PIXEL_MODE_MONO:
      return renderBitmap<img::PixelBitmap>(bitmap, width, height);

    case FT_PIXEL_MODE_GRAY:
      return renderBitmap<img::PixelUByteA>(bitmap, width, height);

    case FT_PIXEL_MODE_LCD:
    case FT_PIXEL_MODE_LCD_V:
      return renderBitmap<img::PixelUByteRGB>(bitmap, width, height);
    }
    ASSERT(false);
    return 0;
  }

  ///**
  // * This method searches the error map for the corresponding error string and returns it.
  // * @param[in] FreeType error code
  // * @return corresponding string to given error code
  // */
  //String FreeTypeFontLoader::getErrorMessage(FT_Error error)
  //{
  //  errors.insert(FT_EOk,"no error");
  //  errors.insert(FT_Err_Cannot_Open_Resource, "cannot open resource");
  //  errors.insert(FT_Err_Unknown_File_Format, "unknown file format");
  //  errors.insert(FT_Err_Invalid_File_Format, "broken file");
  //  errors.insert(FT_Err_Invalid_Version, "invalid FreeType version");
  //  errors.insert(FT_Err_Lower_Module_Version, "module version is too low")
  //  errors.insert(FT_Err_Invalid_Argument, "invalid argument");
  //  errors.insert(FT_Err_Unimplemented_Feature, "unimplemented feature");
  //  errors.insert(FT_Err_Invalid_Table, "broken table");
  //  errors.insert(FT_Err_Invalid_Offset, "broken offset within table");
  //  errors.insert(FT_Err_Array_Too_Large, "array allocation size too large");

  //  errors.insert(FT_Err_Invalid_Glyph_Index, "invalid glyph index");
  //  errors.insert(FT_Err_Invalid_Character_Code, "invalid character code");
  //  errors.insert(FT_Err_Invalid_Glyph_Format, "unsupported glyph image format");
  //  errors.insert(FT_Err_Cannot_Render_Glyph, "cannot render this glyph format");
  //  errors.insert(FT_Err_Invalid_Outline, "invalid outline");
  //  errors.insert(FT_Err_Invalid_Composite, "invalid composite glyph");
  //  errors.insert(FT_Err_Too_Many_Hints, "too many hints");
  //  errors.insert(FT_Err_Invalid_Pixel_Size, "invalid pixel size");

  //  errors.insert(FT_Err_Invalid_Handle, "invalid object handle");
  //  errors.insert(FT_Err_Invalid_Library_Handle, "invalid library handle");
  //  errors.insert(FT_Err_Invalid_Driver_Handle, "invalid module handle");
  //  errors.insert(FT_Err_Invalid_Face_Handle, "invalid face_ handle");
  //  errors.insert(FT_Err_Invalid_Size_Handle, "invalid size handle");
  //  errors.insert(FT_Err_Invalid_Slot_Handle, "invalid glyph slot handle");
  //  errors.insert(FT_Err_Invalid_CharMap_Handle, "invalid charmap handle");
  //  errors.insert(FT_Err_Invalid_Cache_Handle, "invalid cache manager handle");
  //  errors.insert(FT_Err_Invalid_Stream_Handle, "invalid stream handle");

  //  errors.insert(FT_Err_Too_Many_Drivers, "too many modules");
  //  errors.insert(FT_Err_Too_Many_Extensions, "too many extensions");

  //  errors.insert(FT_Err_Out_Of_Memory, "out of memory");
  //  errors.insert(FT_Err_Unlisted_Object, "unlisted object");

  //  errors.insert(FT_Err_Cannot_Open_Stream, "cannot open stream");
  //  errors.insert(FT_Err_Invalid_Stream_Seek, "invalid stream seek");
  //  errors.insert(FT_Err_Invalid_Stream_Skip, "invalid stream skip");
  //  errors.insert(FT_Err_Invalid_Stream_Read, "invalid stream read");
  //  errors.insert(FT_Err_Invalid_Stream_Operation, "invalid stream operation");
  //  errors.insert(FT_Err_Invalid_Frame_Operation, "invalid frame operation");
  //  errors.insert(FT_Err_Nested_Frame_Access, "nested frame access");
  //  errors.insert(FT_Err_Invalid_Frame_Read, "invalid frame read");

  //  errors.insert(FT_Err_Raster_Uninitialized, "raster uninitialized");
  //  errors.insert(FT_Err_Raster_Corrupted, "raster corrupted");
  //  errors.insert(FT_Err_Raster_Overflow, "raster overflow");
  //  errors.insert(FT_Err_Raster_Negative_Height, "negative height while rastering");

  //  errors.insert(FT_Err_Too_Many_Caches, "too many registered caches");

  //  errors.insert(FT_Err_Invalid_Opcode, "invalid opcode");
  //  errors.insert(FT_Err_Too_Few_Arguments, "too few arguments");
  //  errors.insert(FT_Err_Stack_Overflow, "stack overflow");
  //  errors.insert(FT_Err_Code_Overflow, "code overflow");
  //  errors.insert(FT_Err_Bad_Argument, "bad argument");
  //  errors.insert(FT_Err_Divide_By_Zero, "division by zero");
  //  errors.insert(FT_Err_Invalid_Reference, "invalid reference");
  //  errors.insert(FT_Err_Debug_OpCode, "found debug opcode");
  //  errors.insert(FT_Err_ENDF_In_Exec_Stream, "found ENDF opcode in execution stream");
  //  errors.insert(FT_Err_Nested_DEFS, "nested DEFS");
  //  errors.insert(FT_Err_Invalid_CodeRange, "invalid code range");
  //  errors.insert(FT_Err_Execution_Too_Long, "execution context too long");
  //  errors.insert(FT_Err_Too_Many_Function_Defs, "too many function definitions");
  //  errors.insert(FT_Err_Too_Many_Instruction_Defs, "too many instruction definitions");
  //  errors.insert(FT_Err_Table_Missing, "SFNT font table missing");
  //  errors.insert(FT_Err_Horiz_Header_Missing, "horizontal header (hhea) table missing");
  //  errors.insert(FT_Err_Locations_Missing, "locations (loca) table missing");
  //  errors.insert(FT_Err_Name_Table_Missing, "name table missing");
  //  errors.insert(FT_Err_CMap_Table_Missing, "character map (cmap) table missing");
  //  errors.insert(FT_Err_Hmtx_Table_Missing, "horizontal metrics (hmtx) table missing");
  //  errors.insert(FT_Err_Post_Table_Missing, "PostScript (post) table missing");
  //  errors.insert(FT_Err_Invalid_Horiz_Metrics, "invalid horizontal metrics");
  //  errors.insert(FT_Err_Invalid_CharMap_Format, "invalid character map (cmap) format");
  //  errors.insert(FT_Err_Invalid_PPem, "invalid ppem value");
  //  errors.insert(FT_Err_Invalid_Vert_Metrics, "invalid vertical metrics");
  //  errors.insert(FT_Err_Could_Not_Find_Context, "could not find context");
  //  errors.insert(FT_Err_Invalid_Post_Table_Format, "invalid PostScript (post) table format");
  //  errors.insert(FT_Err_Invalid_Post_Table, "invalid PostScript (post) table");

  //  errors.insert(FT_Err_Syntax_Error, "opcode syntax error");
  //  errors.insert(FT_Err_Stack_Underflow, "argument stack underflow");
  //  errors.insert(FT_Err_Ignore, "ignore");

  //  errors.insert(FT_Err_Missing_Startfont_Field, "`STARTFONT' field missing");
  //  errors.insert(FT_Err_Missing_Font_Field, "`FONT' field missing");
  //  errors.insert(FT_Err_Missing_Size_Field, "`SIZE' field missing");
  //  errors.insert(FT_Err_Missing_Chars_Field, "`CHARS' field missing");
  //  errors.insert(FT_Err_Missing_Startchar_Field, "`STARTCHAR' field missing");
  //  errors.insert(FT_Err_Missing_Encoding_Field, "`ENCODING' field missing");
  //  errors.insert(FT_Err_Missing_Bbx_Field, "`BBX' field missing");
  //  errors.insert(FT_Err_Bbx_Too_Big, "`BBX' too big");
  //  errors.insert(FT_Err_Corrupted_Font_Header, "Font header corrupted or missing fields");
  //  errors.insert(FT_Err_Corrupted_Font_Glyphs, "Font glyphs corrupted or missing fields");

  //  FreeTypeErrors::const_iterator it = errors.find(error);

  //  if (it != errors.end())
  //    return it->second;

  //  return String("No error message found to error code");
  //}
}
