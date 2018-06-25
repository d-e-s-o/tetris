// FreeTypeFontLoader.hpp

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

#ifndef FNTFREETYPEFONT_HPP
#define FNTFREETYPEFONT_HPP

#include <pointer/ResourceGuard.hpp>

#include "font/Stream.hpp"
#include "font/FontLoader.hpp"


struct FT_LibraryRec_;
struct FT_FaceRec_;
struct FT_StreamRec_;

typedef FT_LibraryRec_* FT_Library;
typedef FT_FaceRec_* FT_Face;
typedef FT_StreamRec_* FT_Stream;

typedef int FT_Error;

typedef FT_Error (*Done_FreeType)(FT_Library);
typedef void     (*Done_Stream)(FT_Stream);
typedef FT_Error (*Done_Face)(FT_Face);


namespace fnt
{
  /**
   * This class represents the FreeType library.
   * @todo find a file that uses FT_PIXEL_MODE_MONO and test it
   */
  class LIBFONT_EXPORT FreeTypeFontLoader: public FontLoader
  {
  public:
    FreeTypeFontLoader(Stream& stream, size_t size);

    virtual img::ImageBase* render(char_t, GlyphMetrics& metrics) const override;

    virtual size_t size() const override;
    void resize(size_t size);

  private:
    //typedef std::map<FT_Error, String> FreeTypeErrors;

    //static FreeTypeErrors errors;
    //static String const& getErrorMessage(FT_Error error);

    typedef ptr::ResourceGuard<FT_Library, Done_FreeType> FTLibraryGuard;
    typedef ptr::ResourceGuard<FT_Stream,  Done_Stream>   FTStreamGuard;
    typedef ptr::ResourceGuard<FT_Face,    Done_Face>     FTFaceGuard;

    Stream* input_;

    FT_Library     library_;
    FTLibraryGuard library_guard_;

    FT_Stream     stream_;
    FTStreamGuard stream_guard_;

    FT_Face     face_;
    FTFaceGuard face_guard_;

    size_t size_;

    FT_Library initializeLibrary();
    FT_Stream  initializeStream();
    FT_Face    initializeFace();

    bool loadGlyph(char_t character) const;
    bool renderGlyph() const;

    img::ImageBase* copyGlyph() const;
  };
}


#endif
