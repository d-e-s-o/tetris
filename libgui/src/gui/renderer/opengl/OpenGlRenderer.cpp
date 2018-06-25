// OpenGlRenderer.cpp

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

#include "gui/Error.hpp"
#include "gui/renderer/Viewport.hpp"
#include "gui/renderer/RendererFunctions.hpp"
#include "gui/renderer/opengl/OpenGlRenderer.hpp"


namespace gui
{
  namespace
  {
    /**
     * @param color Color to set for use in OpenGl
     */
    inline void glColor(Color const& color)
    {
      glColor4ub(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());

      ASSERTOP(glGetError(), eq, GL_NO_ERROR);
    }

    /**
     * @param texture texture to bind in OpenGl or 0 for none
     */
    inline void glBindTexture(Texture const* texture)
    {
      if (texture != 0)
        texture->bind();
      else
        ::glBindTexture(GL_TEXTURE_2D, 0);

      ASSERTOP(glGetError(), eq, GL_NO_ERROR);
    }

    /**
     * @param rectangle rectangle to set as scissor box
     */
    inline void glScissor(Rectangle const& rectangle)
    {
      ASSERTOP(rectangle.x1_, le, rectangle.x2_);
      ASSERTOP(rectangle.y1_, le, rectangle.y2_);

      Rectangle::Type w = rectangle.x2_ - rectangle.x1_;
      Rectangle::Type h = rectangle.y2_ - rectangle.y1_;

      ::glScissor(rectangle.x1_, rectangle.y1_, w, h);

      ASSERTOP(glGetError(), eq, GL_NO_ERROR);
    }
  }


  /**
   * @copydoc Renderer::Renderer
   */
  OpenGlRenderer::OpenGlRenderer(Viewport const& viewport, ResourceManager const& ressource_manager)
    : SpecificRenderer<OpenGlRenderer, OpenGlTexture, UsedFont>(*this, viewport, ressource_manager),
      renderer_()
  {
    renderer_.setCaching(true);
  }

  /**
   * This method initializes an orthogonal view for OpenGL and resets the
   * modelview, texture and projection matrix after pushing them on the stack.
   */
  void OpenGlRenderer::onPreRender()
  {
    setStates();
    setMatrizes();

    ASSERTOP(glGetError(), eq, GL_NO_ERROR);
  }

  /**
   * This method pops the matrizes and attributes pushed in onPreRender() from the stack.
   */
  void OpenGlRenderer::onPostRender()
  {
    renderer_.flush();

    getMatrizes();
    getStates();

    ASSERTOP(glGetError(), eq, GL_NO_ERROR);
  }

  /**
   * @copydoc Renderer::renderRectangle
   */
  void OpenGlRenderer::renderRectangle(Rectangle const& rect) const
  {
    ASSERTOP(rect.x1_, le, rect.x2_);
    ASSERTOP(rect.y1_, le, rect.y2_);

    renderRectangle(rect, TextureRectangle(0.0f, 0.0f, 1.0f, 1.0f));
  }

  /**
   * @copydoc Renderer::renderRectangle
   */
  void OpenGlRenderer::renderRectangle(Rectangle const& rectangle, TextureRectangle const& tex_coords) const
  {
    ASSERT(rectangle.x1_ <= rectangle.x2_);
    ASSERT(rectangle.y1_ <= rectangle.y2_);

    ASSERT(tex_coords.x1_ <= tex_coords.x2_);
    ASSERT(tex_coords.y1_ <= tex_coords.y2_);

    if (renderer_.isCaching() && !isClippingStackEmpty())
    {
      Rectangle        rect   = constructRectangle(rectangle);
      TextureRectangle coords = tex_coords;

      if (clipRectangle(getClippingRectangle(), rect, coords))
        renderer_.renderRectangle(rect, coords);
    }
    else
      renderer_.renderRectangle(rectangle, tex_coords);

    ASSERTOP(glGetError(), eq, GL_NO_ERROR);
  }

  /**
   * @copydoc Renderer::renderString
   * @throw Error if no font was found for rendering
   * @see Renderer::pushFont
   */
  void OpenGlRenderer::renderString(String const& string, Point const& point) const
  {
    Font const* font = getFont();

    if (font == 0)
      throw Error(TEXT("Error rendering text"), TEXT("No valid font set"));

    font->render(string, point);

    ASSERTOP(glGetError(), eq, GL_NO_ERROR);
  }

  /**
   * @copydoc Renderer::pushClippingRectangle
   */
  void OpenGlRenderer::pushClippingRectangle(Rectangle const& rect)
  {
    Renderer::pushClippingRectangle(rect);

    if (!renderer_.isCaching())
      setClippingRectangle();
  }

  /**
   * @copydoc Renderer::popClippingRectangle
   */
  void OpenGlRenderer::popClippingRectangle()
  {
    Renderer::popClippingRectangle();

    if (!renderer_.isCaching() && !isClippingStackEmpty())
      setClippingRectangle();
  }

  /**
   * @copydoc Renderer::pushTexture
   */
  void OpenGlRenderer::pushTexture(Texture const* texture)
  {
    Texture const* previous = isTextureStackEmpty() ? 0 : getTexture();

    if (previous != texture)
      renderer_.flush();

    Renderer::pushTexture(texture);

    if (previous != texture)
      glBindTexture(texture);
  }

  /**
   * @copydoc Renderer::popTexture
   */
  void OpenGlRenderer::popTexture()
  {
    Texture const* previous = getTexture();

    Renderer::popTexture();

    Texture const* texture = isTextureStackEmpty() ? 0 : getTexture();

    if (texture != previous)
    {
      renderer_.flush();
      glBindTexture(texture);
    }
  }

  /**
   * @copydoc Renderer::pushColor
   */
  void OpenGlRenderer::pushColor(Color const& color)
  {
    Renderer::pushColor(color);

    if (renderer_.isCaching())
      renderer_.setColor(color);
    else
      glColor(color);
  }

  /**
   * @copydoc Renderer::popColor
   */
  void OpenGlRenderer::popColor()
  {
    Renderer::popColor();

    if (!isColorStackEmpty())
    {
      if (renderer_.isCaching())
        renderer_.setColor(getColor());
      else
        glColor(getColor());
    }
  }

  /**
   *
   */
  void OpenGlRenderer::setStates() const
  {
    glPushAttrib(GL_CURRENT_BIT |
                 GL_COLOR_BUFFER_BIT |
                 GL_DEPTH_BUFFER_BIT |
                 GL_ENABLE_BIT |
                 GL_FOG_BIT |
                 GL_LIGHTING_BIT |
                 GL_LINE_BIT |
                 GL_POINT_BIT |
                 GL_SCISSOR_BIT |
                 GL_STENCIL_BUFFER_BIT |
                 GL_TEXTURE_BIT |
                 GL_TRANSFORM_BIT |
                 GL_VIEWPORT_BIT);

    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);

    if (renderer_.isCaching())
      glDisable(GL_SCISSOR_TEST);
    else
      glEnable(GL_SCISSOR_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glPointSize(1.0f);
    glLineWidth(1.0f);

    Position const& position = getViewport().offset();
    Size     const& size     = getViewport().size();

    glViewport(position.x, position.y, size.x, size.y);

    ASSERTOP(glGetError(), eq, GL_NO_ERROR);
  }

  /**
   *
   */
  void OpenGlRenderer::getStates() const
  {
    glPopAttrib();

    ASSERTOP(glGetError(), eq, GL_NO_ERROR);
  }

  /**
   *
   */
  void OpenGlRenderer::setMatrizes() const
  {
    Position const& position = getViewport().offset();
    Size     const& size     = getViewport().size();

    GLdouble left   = 1.0 * position.x;
    GLdouble right  = 1.0 * position.x + size.x;
    GLdouble bottom = 1.0 * position.y;
    GLdouble top    = 1.0 * position.y + size.y;

    // we create an orthogonal projection matrix with the same size as the virtual root widget
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(left, right, bottom, top, 0.0, 1.0);

    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    ASSERTOP(glGetError(), eq, GL_NO_ERROR);
  }

  /**
   *
   */
  void OpenGlRenderer::getMatrizes() const
  {
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_TEXTURE);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    ASSERTOP(glGetError(), eq, GL_NO_ERROR);
  }

  /**
   * This method sets up the OpenGl view for the new clipping rectangle by setting the scissor box
   * and translating to the appropriate position so that the lower left corner of the rectangle is
   * the origin.
   */
  void OpenGlRenderer::setClippingRectangle() const
  {
    Rectangle const& r = getClippingRectangle();
    Point     const& o = getClippingOrigin();

    ASSERTOP(r.x1_, le, r.x2_);
    ASSERTOP(r.y1_, le, r.y2_);

    glScissor(r);

    // i have read that moving by 0.375 on x and y axis increases chance for exact pixel matches,
    // however that makes texture mapped text look very fuzzy so we do not use it anymore
    glLoadIdentity();
    glTranslatef(1.0f * o.x + r.x1_ /*+ 0.375f*/, 1.0f * o.y + r.y1_ /*+ 0.375f*/, -0.5f);

    ASSERTOP(glGetError(), eq, GL_NO_ERROR);
  }
}
