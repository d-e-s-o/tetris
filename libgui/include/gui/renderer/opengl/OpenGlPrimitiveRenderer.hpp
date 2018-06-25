// OpenGlPrimitiveRenderer.hpp

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

#ifndef GUIOPENGLPRIMITIVERENDERER_HPP
#define GUIOPENGLPRIMITIVERENDERER_HPP

#include "gui/include/OpenGl.hpp"
#include "gui/Color.hpp"
#include "gui/renderer/Point.hpp"
#include "gui/renderer/Rectangle.hpp"
#include "gui/renderer/VertexBuffer.hpp"


namespace gui
{
  /**
   *
   */
  class LIBGUI_EXPORT OpenGlPrimitiveRenderer
  {
  public:
    OpenGlPrimitiveRenderer();

    void renderLine(Point const& p1, Point const& p2) const;

    void renderRectangle(Rectangle const& rect) const;
    void renderRectangle(Rectangle const& rect, TextureRectangle const& tex_coords) const;

    void flush() const;

    Color const& getColor() const;
    void setColor(Color const& color);

    bool isCaching() const;
    void setCaching(bool caching);

  private:
    struct Vertex
    {
      // texture coordinates
      GLfloat u;
      GLfloat v;

      // color
      GLubyte r;
      GLubyte g;
      GLubyte b;
      GLubyte a;

      // position
      GLfloat x;
      GLfloat y;
      GLfloat z;
    };

    typedef VertexBuffer<Vertex> VertexCache;

    static unsigned int const VERTEX_BUFFER_CAPACITY;
    static unsigned int const VERTEX_COUNT_QUAD;
    static unsigned int const VERTEX_COUNT_LINE;

    mutable VertexCache cache_;
    mutable GLenum primitive_;

    Color color_;

    OpenGlPrimitiveRenderer(OpenGlPrimitiveRenderer const&);
    OpenGlPrimitiveRenderer& operator =(OpenGlPrimitiveRenderer const&);

    void setPrimitive(GLenum primitive, unsigned int vertices) const;

    void fillVertexBuffer(Point const& p1, Point const& p2) const;
    void fillVertexBuffer(Rectangle const& rect, TextureRectangle const& coords) const;
    void renderVertexBuffer() const;
  };
}


namespace gui
{
  /**
   * @return color currently used to render primitives
   */
  inline Color const& OpenGlPrimitiveRenderer::getColor() const
  {
    return color_;
  }

  /**
   * @param color color to set for rendering primitives
   */
  inline void OpenGlPrimitiveRenderer::setColor(Color const& color)
  {
    color_ = color;
  }

  /**
   * @return true if the renderer caches all rendering commands and sends them to the graphics
   *         device later but on one piece, false if it renders them directly
   */
  inline bool OpenGlPrimitiveRenderer::isCaching() const
  {
    return cache_.isActive();
  }

  /**
   * @param caching true for enabling caching of the render commands, false to disable it
   */
  inline void OpenGlPrimitiveRenderer::setCaching(bool caching)
  {
    renderVertexBuffer();

    cache_.setActive(caching);
  }
}


#endif
