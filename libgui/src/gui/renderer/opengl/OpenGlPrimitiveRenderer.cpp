// OpenGlPrimitiveRenderer.cpp

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

#include "gui/renderer/opengl/OpenGlPrimitiveRenderer.hpp"


namespace gui
{
  unsigned int const OpenGlPrimitiveRenderer::VERTEX_BUFFER_CAPACITY = 1024;
  unsigned int const OpenGlPrimitiveRenderer::VERTEX_COUNT_QUAD      = 4;
  unsigned int const OpenGlPrimitiveRenderer::VERTEX_COUNT_LINE      = 2;


  /**
   *
   */
  OpenGlPrimitiveRenderer::OpenGlPrimitiveRenderer()
    : cache_(VERTEX_BUFFER_CAPACITY),
      primitive_(GL_QUADS),
      color_()
  {
    cache_.setActive(true);
  }

  /**
   *
   */
  void OpenGlPrimitiveRenderer::renderLine(Point const& p1, Point const& p2) const
  {
    if (cache_.isActive())
      fillVertexBuffer(p1, p2);
    else
    {
      glBegin(GL_LINES);
        glVertex2i(p1.x, p1.y);
        glVertex2i(p2.x, p2.y);
      glEnd();
    }
  }

  /**
   *
   */
  void OpenGlPrimitiveRenderer::renderRectangle(Rectangle const& rect) const
  {
    ASSERTOP(rect.x1_, le, rect.x2_);
    ASSERTOP(rect.y1_, le, rect.y2_);

    if (cache_.isActive())
      renderRectangle(rect, TextureRectangle(0.0f, 0.0f, 1.0f, 1.0f));
    else
      glRecti(rect.x1_, rect.y1_, rect.x2_, rect.y2_);
  }

  /**
   *
   */
  void OpenGlPrimitiveRenderer::renderRectangle(Rectangle const& rectangle, TextureRectangle const& tex_coords) const
  {
    ASSERT(rectangle.x1_ <= rectangle.x2_);
    ASSERT(rectangle.y1_ <= rectangle.y2_);

    ASSERT(tex_coords.x1_ <= tex_coords.x2_);
    ASSERT(tex_coords.y1_ <= tex_coords.y2_);

    if (cache_.isActive())
      fillVertexBuffer(rectangle, tex_coords);
    else
    {
      glBegin(GL_QUADS);
        glTexCoord2f(tex_coords.x1_, tex_coords.y1_);
        glVertex2i(rectangle.x1_, rectangle.y1_);

        glTexCoord2f(tex_coords.x2_, tex_coords.y1_);
        glVertex2i(rectangle.x2_, rectangle.y1_);

        glTexCoord2f(tex_coords.x2_, tex_coords.y2_);
        glVertex2i(rectangle.x2_, rectangle.y2_);

        glTexCoord2f(tex_coords.x1_, tex_coords.y2_);
        glVertex2i(rectangle.x1_, rectangle.y2_);
      glEnd();
    }

    ASSERTOP(glGetError(), eq, GL_NO_ERROR);
  }

  /**
   * This method forces the renderer to render all cached data.
   */
  void OpenGlPrimitiveRenderer::flush() const
  {
    renderVertexBuffer();
  }

  /**
   * This method checks if the given primitive type is different from the currently set one, if so
   * it will render the cached data and set the new type, otherwise it will do nothing. This
   * method also prevents buffer overflows by checking that there is enough space for the number of
   * vertices the primitive needs.
   * @param primitive primitive type to set for rendering
   * @param vertices number of vertices the primitive needs for rendering
   */
  inline void OpenGlPrimitiveRenderer::setPrimitive(GLenum primitive, unsigned int vertices) const
  {
    ASSERT(primitive == GL_QUADS || primitive == GL_LINES);

    if (primitive != primitive_ || cache_.getRemainingCapacity() < vertices)
    {
      renderVertexBuffer();

      primitive_ = primitive;
    }
  }

  /**
   * Fill the vertex buffer with the data of a line.
   * @param p1 first point of the line
   * @param p2 second point of the line
   */
  void OpenGlPrimitiveRenderer::fillVertexBuffer(Point const& p1, Point const& p2) const
  {
    setPrimitive(GL_LINES, VERTEX_COUNT_LINE);

    Vertex* cache = cache_.getCurrent();

    // @note '*cache++ = vertex' is like dereference, assign and increase - in that order
    // first point
    Vertex vertex;
    vertex.u = 0.0f;
    vertex.v = 0.0f;
    vertex.r = color_.getRed();
    vertex.g = color_.getGreen();
    vertex.b = color_.getBlue();
    vertex.a = color_.getAlpha();
    vertex.x = 1.0f * p1.x;
    vertex.y = 1.0f * p1.y;
    vertex.z = 0.0f;
    *cache++ = vertex;

    // second point
    vertex.x = 1.0f * p2.x;
    vertex.y = 1.0f * p2.y;
    *cache++ = vertex;

    cache_.increaseSize(VERTEX_COUNT_LINE);
  }

  /**
   * Fill the vertex buffer with the data of a rectangle.
   * @param rect rectangle to render
   * @param coords texture coordinates belonging to the rectangle
   */
  void OpenGlPrimitiveRenderer::fillVertexBuffer(Rectangle const& rect, TextureRectangle const& coords) const
  {
    setPrimitive(GL_QUADS, VERTEX_COUNT_QUAD);

    Vertex* cache = cache_.getCurrent();

    // @note '*cache++ = vertex' is like dereference, assign and increase - in that order
    // lower left
    Vertex vertex;
    vertex.u = coords.x1_;
    vertex.v = coords.y1_;
    vertex.r = color_.getRed();
    vertex.g = color_.getGreen();
    vertex.b = color_.getBlue();
    vertex.a = color_.getAlpha();
    vertex.x = 1.0f * rect.x1_;
    vertex.y = 1.0f * rect.y1_;
    vertex.z = 0.0f;
    *cache++ = vertex;

    // lower right
    vertex.u = coords.x2_;
    vertex.x = 1.0f * rect.x2_;
    *cache++ = vertex;

    // upper right
    vertex.v = coords.y2_;
    vertex.y = 1.0f * rect.y2_;
    *cache++ = vertex;

    // upper left
    vertex.u = coords.x1_;
    vertex.x = 1.0f * rect.x1_;
    *cache++ = vertex;

    cache_.increaseSize(VERTEX_COUNT_QUAD);
  }

  /**
   * Send the cached data to the graphics device for rendering.
   */
  void OpenGlPrimitiveRenderer::renderVertexBuffer() const
  {
    ASSERT(primitive_ == GL_QUADS || primitive_ == GL_LINES);

    if (cache_.isActive() && cache_.getCurrentSize() > 0)
    {
      glInterleavedArrays(GL_T2F_C4UB_V3F, 0, cache_.getBegin());
      glDrawArrays(primitive_, 0, static_cast<GLsizei>(cache_.getCurrentSize()));

      cache_.clear();

      ASSERTOP(cache_.getCurrentSize(), eq, 0);
    }
  }
}
