// Renderer.hpp

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

#ifndef GUIRENDERER_HPP
#define GUIRENDERER_HPP

#include <util/Assert.hpp>
#include <container/Pair.hpp>
#include <container/Stack.hpp>

#include "gui/Config.hpp"
#include "gui/Allocator.hpp"
#include "gui/String.hpp"
#include "gui/Color.hpp"
#include "gui/Alignment.hpp"
#include "gui/Size.hpp"
#include "gui/renderer/Point.hpp"
#include "gui/renderer/Rectangle.hpp"


namespace gui
{
  class Texture;
  class Font;
  class Viewport;


  /**
   * This class is the base class for every renderer. Renderers could be specialized (subclassed)
   * for different APIs (for example OpenGL, DirectX or Window GDI). They are used to render
   * primitives, such as (colored) lines, points or rectangular areas. They also provide a method
   * for creating fonts and textures (because every renderer uses another texture format).
   * @note there is no need to copy a renderer object, so the copy ctor and assignment operator are
   *       private and not implemented
   * @todo createTexture() and createFont() and should return a tr1::shared_ptr (and also store one
   *       internally) or get some different reference counting
   * @todo decide what should happen if the Viewport's bounds exceed the ones of the real window
   *       and implement that behavior (currently opengl just renderes, but d3d9 does nothing!)
   */
  class LIBGUI_EXPORT Renderer
  {
  public:
    Renderer(Viewport const& viewport);
    virtual ~Renderer() = 0;

    virtual Texture* createTexture(String const& file) = 0;
    virtual Font*    createFont(String const& name, SizeT size) = 0;

    virtual void onPreRender();
    virtual void onPostRender();

    //virtual void renderPoint(Point const& point) const = 0;
    //virtual void renderLine(Point const& p1, Point const& p2) const = 0;

    virtual void renderRectangle(Rectangle const& rect) const = 0;
    virtual void renderRectangle(Rectangle const& rect, TextureRectangle const& tex_coords) const = 0;

    virtual void renderString(String const& string, Point const& position) const = 0;

    virtual void pushClippingRectangle(Rectangle const& rect);
    virtual void popClippingRectangle();

    virtual void pushTexture(Texture const* texture);
    virtual void popTexture();

    virtual void pushFont(Font const& font);
    virtual void popFont();

    virtual void pushColor(Color const& color);
    virtual void popColor();

    Viewport const& getViewport() const;

  protected:
    Rectangle const& getClippingRectangle() const;
    Point const&     getClippingOrigin() const;
    Texture const*   getTexture() const;
    Font const*      getFont() const;
    Color const&     getColor() const;

    Rectangle constructRectangle(Rectangle rectangle) const;

    bool isClippingStackEmpty() const;
    bool isTextureStackEmpty() const;
    bool isFontStackEmpty() const;
    bool isColorStackEmpty() const;

  private:
    typedef ctr::Pair<Point, Rectangle> ClippingArea;

    //typedef Allocator::rebind<ClippingArea>::other Allocator1;
    //typedef Allocator::rebind<Texture const*>::other Allocator2;
    //typedef Allocator::rebind<Font const*>::other Allocator3;
    //typedef Allocator::rebind<Color>::other Allocator4;

    //typedef std::stack<ClippingArea,   std::deque<ClippingArea, Allocator1> >   Rectangles;
    //typedef std::stack<Texture const*, std::deque<Texture const*, Allocator2> > Textures;
    //typedef std::stack<Font const*,    std::deque<Font const*, Allocator3> >    Fonts;
    //typedef std::stack<Color,          std::deque<Color, Allocator4> >          Colors;

    /**
     * @todo use gui::Allocator here
     */
    typedef ctr::Stack<ClippingArea>   Rectangles;
    typedef ctr::Stack<Texture const*> Textures;
    typedef ctr::Stack<Font const*>    Fonts;
    typedef ctr::Stack<Color>          Colors;

    Rectangles rectangles_;
    Textures   textures_;
    Fonts      fonts_;
    Colors     colors_;

    Viewport const* viewport_;

    Renderer(Renderer const&);
    Renderer& operator =(Renderer const&);
  };
}


namespace gui
{
  /**
   * @return the renderer's Viewport
   */
  inline Viewport const& Renderer::getViewport() const
  {
    ASSERTOP(viewport_, ne, nullptr);
    return *viewport_;
  }


  /**
   * @return true if clipping stack is empty, false if not
   */
  inline bool Renderer::isClippingStackEmpty() const
  {
    return rectangles_.size() == 0;
  }

  /**
   * @return true if texture stack is empty, false if not
   */
  inline bool Renderer::isTextureStackEmpty() const
  {
    return textures_.size() == 0;
  }

  /**
   * @return true if font stack is empty, false if not
   */
  inline bool Renderer::isFontStackEmpty() const
  {
    return fonts_.size() == 0;
  }

  /**
   * @return true if color stack is empty, false if not
   */
  inline bool Renderer::isColorStackEmpty() const
  {
    return colors_.size() == 0;
  }
}


#endif
