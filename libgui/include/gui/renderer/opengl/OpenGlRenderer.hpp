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

#ifndef GUIOPENGLRENDERER_HPP
#define GUIOPENGLRENDERER_HPP

//#define USE_OPENGL_RASTER_FONT

#ifdef USE_OPENGL_RASTER_FONT
#  include "gui/renderer/opengl/OpenGlFont.hpp"
typedef gui::OpenGlFont UsedFont;
#else
#  include "gui/renderer/opengl/OpenGlTextureFont.hpp"
typedef gui::OpenGlTextureFont UsedFont;
#endif

#include "gui/renderer/opengl/OpenGlTexture.hpp"
#include "gui/renderer/opengl/OpenGlPrimitiveRenderer.hpp"
#include "gui/renderer/SpecificRenderer.hpp"


namespace gui
{
  /**
   * This class is the renderer for all OpenGL drawing operations. It implements the interface
   * provided by Renderer with OpenGL specific actions.
   * @todo with scissor test disabled dialogs move (in invalid regions) very strange - fix it
   */
  class LIBGUI_EXPORT OpenGlRenderer: public SpecificRenderer<OpenGlRenderer, OpenGlTexture, UsedFont>
  {
  public:
    OpenGlRenderer(Viewport const& viewport, ResourceManager const& resource_manager);

    virtual void onPreRender();
    virtual void onPostRender();

    //virtual void renderPoint(Point const& point) const;
    //virtual void renderLine(Point const& p1, Point const& p2) const;

    virtual void renderRectangle(Rectangle const& rect) const;
    virtual void renderRectangle(Rectangle const& rect, TextureRectangle const& tex_coords) const;

    virtual void renderString(String const& string, Point const& position) const;

    virtual void pushClippingRectangle(Rectangle const& rect);
    virtual void popClippingRectangle();

    virtual void pushTexture(Texture const* texture);
    virtual void popTexture();

    virtual void pushColor(Color const& color);
    virtual void popColor();

    bool isCaching() const;
    void setCaching(bool caching);

  protected:
    OpenGlPrimitiveRenderer&       getPrimitiveRenderer();
    OpenGlPrimitiveRenderer const& getPrimitiveRenderer() const;

  private:
    OpenGlPrimitiveRenderer renderer_;

    void setStates() const;
    void getStates() const;

    void setMatrizes() const;
    void getMatrizes() const;

    void setClippingRectangle() const;
  };
}


namespace gui
{
  /**
   * @copydoc OpenGlPrimitiveRenderer::isCaching
   */
  inline bool OpenGlRenderer::isCaching() const
  {
    return renderer_.isCaching();
  }

  /**
   * @copydoc OpenGlPrimitiveRenderer::setCaching
   * @todo we should not allow switching this between frames, because we had to set color again
   *       and enable or disable scissor test
   */
  inline void OpenGlRenderer::setCaching(bool caching)
  {
    renderer_.setCaching(caching);

    // if we switch to mode with caching we need to update the color, which would generally be
    // done in PushColor
    //if (renderer_.isCaching() && !isColorStackEmpty())
    //  renderer_.setColor(getColor());
  }

  /**
   * This method gives access to the primitive renderer used by this class. It is meant only for
   * implementation purposes and may be used in derived classes.
   */
  inline OpenGlPrimitiveRenderer& OpenGlRenderer::getPrimitiveRenderer()
  {
    return renderer_;
  }

  /**
   * @copydoc OpenGlRenderer::getPrimitiveRenderer
   */
  inline OpenGlPrimitiveRenderer const& OpenGlRenderer::getPrimitiveRenderer() const
  {
    return renderer_;
  }
}


#endif
