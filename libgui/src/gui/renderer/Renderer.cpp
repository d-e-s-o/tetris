// Renderer.cpp

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
#include <util/Rectangle2Functions.hpp>

#include "gui/Error.hpp"
#include "gui/renderer/RendererFunctions.hpp"
#include "gui/renderer/Renderer.hpp"


namespace gui
{
  /**
   * The constructor creates a new renderer object. The given viewport defines the area in which to
   * render.
   * @param viewport Viewport defining the area to render to
   * @note the given Viewport has to live at least as long as the renderer does
   */
  Renderer::Renderer(Viewport const& viewport)
    : viewport_(&viewport)
  {
  }

  /**
   * The destructor destroys the renderer object and free's all loaded textures and fonts.
   */
  Renderer::~Renderer()
  {
  }

  /**
   * This method creates a texture object that can be used with the actual
   * renderer.
   * @param[in] file filename to load the texture from
   * @return pointer to created texture or 0 if texture could not be loaded
   * @note The renderer is responsible for freeing the loaded textures, the user must NOT delete it.
   */
  Texture* Renderer::createTexture(String const& file)
  {
    return 0;
  }

  /**
   * This method creates a font object that can be used to display text in combination with the
   * renderer.
   * @param name name of the font to load
   * @param size size of the font to load
   * @return pointer to created font or 0 if font could not be loaded or was not found
   * @note The renderer is responsible for freeing the loaded fonts, the user must NOT delete it.
   */
  Font* Renderer::createFont(String const& name, SizeT size)
  {
    return 0;
  }

  /**
   * This method is called once every frame before the actual rendering is done.
   * By default it does nothing. It does not necessary have to be overwritten.
   */
  void Renderer::onPreRender()
  {
  }

  /**
   * This method is called once every frame after the actual rendering is done.
   * It should undo the probably made changes of onPreRender().
   */
  void Renderer::onPostRender()
  {
  }

  /**
   * @param point point to render
   * @note the color used is the one on top of the color stack
   * @note as in every render function the coordinates of the rectangle are in pixel relative to
   *       the last pushed clipping rectangle
   * @see Renderer::pushClippingRectangle
   */
  //void Renderer::renderPoint(Point const& point) const
  //{
  //}

  /**
   * @param p1 first point of the line to render
   * @param p2 second point of the line to render
   * @note the color used is the one on top of the color stack
   * @note as in every render function the coordinates of the rectangle are in pixel relative to
   *       the last pushed clipping rectangle
   * @see Renderer::pushClippingRectangle
   */
  //void Renderer::renderLine(Point const& p1, Point const& p2) const
  //{
  //}

  /**
   * @param rect rectangle to render (in pixels)
   * @note for optimization purpose it is not defined whether a texture is mapped onto the rectangle
   *       or not - therefor you should always call pushTexture(0) before usage of this function
   * @note the color used is the one on top of the color stack
   * @note as in every render function the coordinates of the rectangle are in pixel relative to
   *       the last pushed clipping rectangle
   * @see Renderer::pushClippingRectangle
   */
  void Renderer::renderRectangle(Rectangle const& rect) const
  {
  }

  /**
   * @param rect rectangle to render (in pixels)
   * @param tex_coords texture coordinates of the texture to map into the rectangle
   * @note the texture used is the one on top of the texture stack
   */
  void Renderer::renderRectangle(Rectangle const& rect, TextureRectangle const& tex_coords) const
  {
  }

  /**
   * @param string string to render to screen
   * @param position position of the text
   * @note as in every render function the coordinates of the rectangle are in pixel relative to
   *       the last pushed clipping rectangle
   * @see Renderer::pushClippingRectangle
   */
  void Renderer::renderString(String const& string, Point const& position) const
  {
  }

  /**
   * This method pushes a new clipping rectangle onto the clipping stack.
   * @param rect new clipping rectangle to push onto the clipping stack
   * @note the rectangle's coordinates are treatet to be relative to the clipping rectangle pushed
   *       before, that means that the position is relative to the position of the last rectangle
   *       and the size is cut if it exceeds the one of the last
   * @note pushing a new clipping rectangle also means that the drawing origin is set, that means
   *       after pushing e.g. Rectangle(1000, 2000, 5000, 6000) and drawing a Point(0, 0) it will
   *       appear actually at Point(1000, 2000) because thats the origin (at least if no clipping
   *       rect was pushed before)
   * @note to get the actual clipping rectangle that was pushed call getClippingRectangle and to
   *       get the calculated origin call getClippingOrigin after pushing the rectangle
   * @see Renderer::getClippingRectangle
   * @see Renderer::getClippingOrigin
   */
  void Renderer::pushClippingRectangle(Rectangle const& rect)
  {
    if (!isClippingStackEmpty())
    {
      Point const& origin = getClippingOrigin();
      Point new_origin    = origin;

      new_origin.x += rect.x1_;
      new_origin.y += rect.y1_;

      if (new_origin.x > 0)
        new_origin.x = 0;

      if (new_origin.y > 0)
        new_origin.y = 0;

      Rectangle const& clipper = getClippingRectangle();

      Rectangle new_rect = rect;
      new_rect.x1_ += clipper.x1_ + origin.x;
      new_rect.y1_ += clipper.y1_ + origin.y;
      new_rect.x2_ += clipper.x1_ + origin.x;
      new_rect.y2_ += clipper.y1_ + origin.y;

      clipRectangle(clipper, new_rect);

      rectangles_.push(ClippingArea(new_origin, new_rect));
    }
    else
      rectangles_.push(ClippingArea(Point(), rect));
  }

  /**
   * This method pops the last rectangle from the clipping stack
   * @throw Error if the stack is empty
   */
  void Renderer::popClippingRectangle()
  {
    if (isClippingStackEmpty())
      throw Error(TEXT("Error popping clipping rectangle"), TEXT("Stack is empty"));

    rectangles_.pop();
  }

  /**
   * @param texture new texture to push onto the texture stack (it needs to be created by this
   *        renderer and needs to be valid until it is popped)
   * @note if you do not want your rectangles to use a texture you should call this method with 0
   */
  void Renderer::pushTexture(Texture const* texture)
  {
    textures_.push(texture);
  }

  /**
   * This method pops the last texture from the texture stack
   * @throw Error if the stack is empty
   */
  void Renderer::popTexture()
  {
    if (isTextureStackEmpty())
      throw Error(TEXT("Error popping texture"), TEXT("Stack is empty"));

    textures_.pop();
  }

  /**
   * @param font new font to push onto font stack (it has to be created by this renderer and needs
   *        to be valid until it is popped)
   * @note before renderering text via RenderString you MUST push a font onto the font stack that
   *       can be used
   */
  void Renderer::pushFont(Font const& font)
  {
    fonts_.push(&font);
  }

  /**
   * This method pops the last font from the font stack
   * @throw Error if the stack is empty
   */
  void Renderer::popFont()
  {
    if (isFontStackEmpty())
      throw Error(TEXT("Error popping font"), TEXT("Stack is empty"));

    fonts_.pop();
  }

  /**
   * @param color new color to push onto the color stack
   */
  void Renderer::pushColor(Color const& color)
  {
    colors_.push(color);
  }

  /**
   * This method pops the last color from the color stack
   * @throw Error if the stack is empty
   */
  void Renderer::popColor()
  {
    if (isColorStackEmpty())
      throw Error(TEXT("Error popping color"), TEXT("Stack is empty"));

    colors_.pop();
  }

  /**
   * @return top clipping rectangle
   * @throw Error if the clipping stack is empty
   */
  Rectangle const& Renderer::getClippingRectangle() const
  {
    if (isClippingStackEmpty())
      throw Error(TEXT("Error returning clipping rectangle"), TEXT("Stack is empty"));

    return rectangles_.top().second;
  }

  /**
   * @return
   * @throw Error if the clipping stack is empty
   */
  Point const& Renderer::getClippingOrigin() const
  {
    if (isClippingStackEmpty())
      throw Error(TEXT("Error returning clipping rectangle"), TEXT("Stack is empty"));

    return rectangles_.top().first;
  }

  /**
   * @return pointer to top texture
   * @throw Error if the texture stack is empty
   */
  Texture const* Renderer::getTexture() const
  {
    if (isTextureStackEmpty())
      throw Error(TEXT("Error returning texture"), TEXT("Stack is empty"));

    return textures_.top();
  }

  /**
   * @return pointer to top font
   * @throw Error if the font stack is empty
   */
  Font const* Renderer::getFont() const
  {
    if (isFontStackEmpty())
      throw Error(TEXT("Error returning font"), TEXT("Stack is empty"));

    return fonts_.top();
  }

  /**
   * @return top color of stack
   * @throw Error if the color stack is empty
   */
  Color const& Renderer::getColor() const
  {
    if (isColorStackEmpty())
      throw Error(TEXT("Error returning color"), TEXT("Stack is empty"));

    return colors_.top();
  }

  /**
   * This method modifies the given rectangle by adding the clipping origin and current clipping
   * rectangle.
   * It is for internal use only.
   * @param rectangle rectangle to modify
   * @return rectangle with applied clipping stuff
   * @see OpenGlRenderer::pushClippingRectangle
   * @see D3D9Renderer::pushClippingRectangle
   */
  Rectangle Renderer::constructRectangle(Rectangle rectangle) const
  {
    Rectangle const& clip_r = getClippingRectangle();
    Point     const& clip_o = getClippingOrigin();

    ASSERTOP(clip_r.x1_, le, clip_r.x2_);
    ASSERTOP(clip_r.y1_, le, clip_r.y2_);

    rectangle.x1_ += clip_o.x + clip_r.x1_;
    rectangle.y1_ += clip_o.y + clip_r.y1_;
    rectangle.x2_ += clip_o.x + clip_r.x1_;
    rectangle.y2_ += clip_o.y + clip_r.y1_;

    return rectangle;
  }
}
