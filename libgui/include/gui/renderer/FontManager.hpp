// FontManager.hpp

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

#ifndef GUIFONTMANAGER_HPP
#define GUIFONTMANAGER_HPP

#include <util/Assert.hpp>
#include <container/Map.hpp>

//#include <font/RasterFontLoader.hpp>
#include <font/FreeTypeFontLoader.hpp>

#include "gui/Allocator.hpp"
//#include "gui/renderer/RasterFont.hpp"
#include "gui/renderer/FontKey.hpp"


namespace gui
{
  /**
   * @todo store and return ptr::SharedPointer objects here!
   */
  template<typename FontT>
  class FontManager
  {
  public:
    FontManager(NamespaceManager const& namespace_manager);
    ~FontManager();

    template<typename RendererT>
    FontT* createFont(RendererT& renderer, String const& name, SizeT size);

  private:
    typedef ctr::Map<FontKey, FontT*> Fonts;

    NamespaceManager const* namespace_manager_;

    Fonts fonts_;

    FontManager(FontManager const&);
    FontManager& operator =(FontManager const&);
  };
}


namespace gui
{
  /**
   * The default constructor creates a new FontManager object.
   */
  template<typename FontT>
  FontManager<FontT>::FontManager(NamespaceManager const& namespace_manager)
    : namespace_manager_(&namespace_manager)
  {
  }

  /**
   * The destructor destroys the font manager and free's all created fonts.
   */
  template<typename FontT>
  FontManager<FontT>::~FontManager()
  {
    for (typename Fonts::ConstIterator it = fonts_.begin(); it != fonts_.end(); ++it)
    {
      //Allocator::rebind<FontT>::other allocator;

      //allocator.destroy(it->second);
      //allocator.deallocate(it->second, 1);

      delete it->second;
    }
  }

  /**
   * @param[in] renderer renderer to create the font for
   * @param[in] name name of the font
   * @param[in] size size of the font
   * @return pointer to created font or null if creation failed
   */
  template<typename FontT>
  template<typename RendererT>
  FontT* FontManager<FontT>::createFont(RendererT& renderer, String const& name, SizeT size)
  {
    FontKey key(name, size);
    typename Fonts::ConstIterator const& it = fonts_.find(key);

    if (it != fonts_.end())
    {
      ASSERTOP(it->second, ne, nullptr);
      return it->second;
    }
    else
    {
      class FontStream: public fnt::Stream
      {
      public:
        FontStream(Namespace::StreamPointer stream)
          : stream_(stream)
        {
        }

        virtual size_t read(size_t position, byte_t* buffer, size_t size)
        {
          stream_->reposition(position);

          return stream_->read(buffer, size);
        }

        virtual size_t size() const
        {
          return stream_->size();
        }

      private:
        Namespace::StreamPointer stream_;
      };

      Namespace::StreamPointer stream = namespace_manager_->open(name);

      if (!stream)
        return nullptr;

      //Allocator::rebind<FontT>::other allocator;

      //FontT* font = allocator.allocate(1);
      //allocator.construct(font, FontT(renderer, fnt::FreeTypeFont(name, size)));

      // @todo check why RasterFont does not work (bitmap not supported as texture type?)
      //FontT* font = new FontT(renderer, fnt::RasterFont<32, 96, 8, 12, 2>(&glyphs, &spaces));

      FontStream font_stream = FontStream(stream);
      FontT*     font        = new FontT(renderer, fnt::FreeTypeFontLoader(font_stream, size));

      fonts_.insert(typename Fonts::Entry(key, font));

      return font;
    }
  }
}


#endif
