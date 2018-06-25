// OpenGlTexture.cpp

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

#include <util/Assert.hpp>
#include <pointer/ResourceGuard.hpp>

#include <image/Pixel.hpp>
#include <image/Image.hpp>
#include <image/ImageFunctions.hpp>

#include "gui/Error.hpp"
#include "gui/renderer/opengl/ImageFunctions.hpp"
#include "gui/renderer/opengl/OpenGlFunctions.hpp"
#include "gui/renderer/opengl/OpenGlTexture.hpp"


namespace gui
{
  namespace
  {
    /**
     * @todo this class should first try to create a texture with the exact width and height of the
     *       picture but if that is not supported then try to create it with sizes power of two
     */
    class TextureCreator
    {
    public:
      TextureCreator(bool flip, bool mip_maps);

      template<typename Pixel>
      void operator()(img::Image<Pixel> const& image) const;

    private:
      bool flip_;
      bool mip_maps_;

      template<typename Pixel>
      void prepareTexture(img::Image<Pixel> const& image) const;

      template<typename Pixel>
      bool checkTexture(img::Image<Pixel> const& image) const;

      template<typename Pixel>
      void createTexture(img::Image<Pixel> const& image) const;
    };

    /**
     * @param[in] mip_maps true if mip maps should be created for the texture,
     *            false if not
     */
    TextureCreator::TextureCreator(bool flip, bool mip_maps)
      : flip_(flip),
        mip_maps_(mip_maps)
    {
    }

    /**
     * This method creates an OpenGlTexture from a given image.
     * @param image image to create texture from
     */
    template<typename Pixel>
    void TextureCreator::operator()(img::Image<Pixel> const& image) const
    {
      if (!checkTexture(image))
        throw Error(TEXT("Error creating OpenGL texture"), TEXT("Texture size not supported"));

      if (flip_)
      {
        img::Image<Pixel> new_image(image);
        img::flipHorizontal(new_image);

        createTexture(new_image);
      }
      else
        createTexture(image);
    }

    /**
     * This method creates a dummy texture to see whether a real texture with this
     * width and height can be created successfully.
     * @return true if dummy created successful, false if not
     */
    template<typename Pixel>
    bool TextureCreator::checkTexture(img::Image<Pixel> const& image) const
    {
      GLsizei width        = static_cast<GLsizei>(image.width());
      GLsizei height       = static_cast<GLsizei>(image.height());
      GLint   colors       = getColors(image);
      GLenum  pixel_format = getPixelFormat(image);
      GLenum  color_format = getColorFormat(image);

      return isTextureSizeSupported(width, height, colors, pixel_format, color_format);
    }

    /**
     * This method actually creates the texture from the image.
     * @param image image to create the texture from
     * @todo check whether we need to push and pop the GL_TEXTURE_XXX_FILTER stuff (it is probably
     *       only for the texture, not sure though)
     */
    template<typename Pixel>
    void TextureCreator::createTexture(img::Image<Pixel> const& image) const
    {
      GLsizei width        = image.width();
      GLsizei height       = image.height();
      GLenum  pixel_format = getPixelFormat(image);
      GLenum  color_format = getColorFormat(image);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

      GLvoid const* pixels = image.scanline(0);

      glPushAttrib(GL_PIXEL_MODE_BIT);
      glPixelStorei(GL_UNPACK_ALIGNMENT, image.alignment());

      if (mip_maps_)
        gluBuild2DMipmaps(GL_TEXTURE_2D, getColors(image), width, height, pixel_format, color_format, pixels);
      else
        glTexImage2D(GL_TEXTURE_2D, 0, getFormat(image), width, height, 0, pixel_format, color_format, pixels);

      glPopAttrib();
    }

    /**
     * @param texture texture to call unbind() on
     */
    void unbind(OpenGlTexture const& texture)
    {
      texture.unbind();
    }
  }


  /**
   * The constructor creates an OpenGL texture from a given image.
   * @param[in] renderer renderer the texture belongs to
   * @param[in] image image with pixel data to create the texture from
   * @param[in] flip flip the image first before creating the texture
   * @param[in] mip_maps true if you wish to generate mip maps, false if not
   * @throw Error if the texture size is not supported or OpenGl fails creating the texture id
   * @note since gui systems have their coordinate origin in the upper left edge, but OpenGl has
   *       it in the lower left edge (as most 3D graphics systems), the image may need to be flip
   *       before creating a texture from it - that is what the flip parameter is for
   */
  OpenGlTexture::OpenGlTexture(OpenGlRenderer& renderer, img::ImageBase const& image, bool flip, bool mip_maps)
    : Texture(Size(image.width(), image.height())),
      id_(0)
  {
    ASSERTOP(glGetError(), eq, GL_NO_ERROR);
    generateTextureId();

    try
    {
      bind();
      ptr::ResourceGuard<OpenGlTexture const&, void(*)(OpenGlTexture const&)> guard(*this, &gui::unbind);

      img::useImage<void>(image, TextureCreator(flip, mip_maps));
    }
    catch(...)
    {
      deleteTextureId();
      throw;
    }
    ASSERTOP(glGetError(), eq, GL_NO_ERROR);
  }

  /**
   * The destructor frees the texture.
   */
  OpenGlTexture::~OpenGlTexture()
  {
    deleteTextureId();
  }

  /**
   * @copydoc Texture::bind
   */
  void OpenGlTexture::bind() const
  {
    ASSERTOP(id_, ne, 0);
    glBindTexture(GL_TEXTURE_2D, id_);
  }

  /**
   * @copydoc Texture::unbind
   */
  void OpenGlTexture::unbind() const
  {
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  /**
   * This helper method generates an OpenGL texture id.
   * @throw Error if OpenGl failed creating the texture id
   */
  void OpenGlTexture::generateTextureId()
  {
    ASSERTOP(id_, eq, 0);
    glGenTextures(1, &id_);

    if (id_ == 0)
      throw Error(TEXT("Error generating new texture name"), TEXT("glGenTextures returned 0"));

    ASSERTOP(id_, ne, 0);
  }

  /**
   * This helper method deletes the previously generated texture id.
   */
  void OpenGlTexture::deleteTextureId()
  {
    ASSERTOP(id_, ne, 0);

    glDeleteTextures(1, &id_);
    id_ = 0;

    ASSERTOP(id_, eq, 0);
  }
}
