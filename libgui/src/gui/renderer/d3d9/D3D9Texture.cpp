// D3D9Texture.cpp

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

#include <algorithm>

#include <util/Assert.hpp>
#include <container/Algorithm.hpp>
//#include <pointer/Iterator.hpp>
#include <pointer/ResourceGuard.hpp>

#include <image/Pixel.hpp>
#include <image/Image.hpp>
#include <image/ImageFunctions.hpp>

#include "gui/include/D3D9.hpp"
#include "gui/Error.hpp"
#include "gui/renderer/d3d9/D3D9Functions.hpp"
#include "gui/renderer/d3d9/D3D9Renderer.hpp"
#include "gui/renderer/d3d9/D3D9Texture.hpp"


namespace img
{
#ifdef _MSC_VER
#  pragma pack(push)
#  pragma pack(1)
#endif

  /**
   * A new pixel representing the byte order Direct3D uses for RGBA format.
   */
  struct PixelUByteBGRA
  {
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t a;
  };

#ifdef _MSC_VER
#  pragma pack(pop)
#endif


  /**
   * This is the specialization of the convert function for conversion of RGBA to BGRA.
   */
  template<>
  inline void convert(PixelUByteRGBA const& src, PixelUByteBGRA& dst)
  {
    // this may look stupid, but the byte order differs
    dst.r = src.r;
    dst.g = src.g;
    dst.b = src.b;
    dst.a = src.a;
  }

  template<typename Pixel1>
  struct Converter
  {
    template<typename Pixel2>
    Pixel1 operator()(Pixel2 const& src)
    {
      Pixel1 dst;
      convert(src, dst);
      return dst;
    }
  };
}

namespace gui
{
  namespace
  {
    class TextureCreator
    {
    public:
      TextureCreator(IDirect3DTexture9& texture, bool flip)
        : texture_(&texture),
          flip_(flip)
      {
        if (FAILED(texture_->LockRect(0, &rect_, 0, D3DLOCK_DISCARD)))
          throw Error(TEXT("Error creating texture"), TEXT("IDirect3DTexture9::LockRect failed"));
      }

      ~TextureCreator()
      {
        texture_->UnlockRect(0);
      }

      /**
       * @todo implement routines for other formats as well
       */
      template<typename Pixel>
      void operator()(img::Image<Pixel> const& image) const
      {
        ASSERT(false);
      }

      template<>
      void operator()(img::Image<img::PixelUByteA> const& image) const
      {
        img::PixelUByteA* dst = static_cast<img::PixelUByteA*>(rect_.pBits);

        // depending on the value of flip we iterate in reverse order or not
        for (IteratorT it(0, image.height(), flip_); it(); ++it)
        {
          img::PixelUByteA const* src = image.scanline(it.getValue());

          ctr::copy(src, src + image.width(), dst);
          dst += rect_.Pitch;
        }
      }

      template<>
      void operator()(img::Image<img::PixelUByteRGBA> const& image) const
      {
        BYTE* line = static_cast<BYTE*>(rect_.pBits);

        // depending on the value of flip we iterate in reverse order or not
        for (IteratorT it(0, image.height(), flip_); it(); ++it)
        {
          img::PixelUByteRGBA const* src = image.scanline(it.getValue());
          img::PixelUByteBGRA* dst       = reinterpret_cast<img::PixelUByteBGRA*>(line);

          std::transform(src, src + image.width(), dst, Converter<img::PixelUByteBGRA>());
          line += rect_.Pitch;
        }
      }

    private:
      typedef Iterator<img::Size, true, false> IteratorT;

      IDirect3DTexture9* texture_;
      D3DLOCKED_RECT     rect_;
      bool               flip_;
    };

    struct D3DFormatGetter
    {
      template<typename Pixel>
      D3DFORMAT operator()(Image<Pixel> const& image) const
      {
        return getPixelFormat(image);
      }
    };

    inline void setTexture(IDirect3DDevice9& device, IDirect3DTexture9* texture)
    {
      if (FAILED(device.SetTexture(0, texture)))
        throw Error(TEXT("Error binding D3D9Texture."), TEXT("SetTexture failed"));
    }

    inline void releaseTexture(IDirect3DTexture9* texture)
    {
      texture->Release();
    }
  }


  /**
   *
   */
  D3D9Texture::D3D9Texture(D3D9Renderer& renderer, ImageBase const& image, bool flip)
    : texture(Size(image.width(), image.height())),
      renderer_(&renderer),
      texture_(0)
  {
    IDirect3DDevice9& device = renderer_->getDevice();

    UINT w           = image.width();
    UINT h           = image.height();
    D3DFORMAT format = useImage<D3DFORMAT>(image, d3DFormatGetter());
    D3DPOOL pool     = D3DPOOL_MANAGED;

    if (FAILED(device.CreateTexture(w, h, 0, 0, format, pool, &texture_, 0)))
      throw Error(TEXT("Error creating texture"), TEXT("IDirect3DDevice9::CreateTexture failed"));

    typedef ResourceGuard<IDirect3DTexture9*, void (*)(IDirect3DTexture9*)> TextureGuard;
    TextureGuard guard(texture_, &releaseTexture);

    useImage<void>(image, TextureCreator(*texture_, flip));

    guard.release();
  }

  /**
   * The destructor frees the texture.
   */
  D3D9Texture::~D3D9Texture()
  {
    texture_->Release();
  }

  /**
   * @copydoc Texture::bind
   */
  void D3D9Texture::bind() const
  {
    setTexture(renderer_->getDevice(), texture_);
  }

  /**
   * @copydoc Texture::unbind
   */
  void D3D9Texture::unbind() const
  {
    setTexture(renderer_->getDevice(), 0);
  }
}
