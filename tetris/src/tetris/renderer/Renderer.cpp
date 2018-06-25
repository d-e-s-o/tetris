// Renderer.cpp

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

#include "tetris/renderer/Renderer.hpp"


namespace ttrs
{
  /**
   * The constructor creates a new Renderer object for the tetris game.
   */
  Renderer::Renderer()
  {
  }

  /**
   * The destructor is virtual to allow inheritance.
   */
  Renderer::~Renderer()
  {
  }

  /**
   * This method should be called before rendering the game (and with it all tetris related stuff).
   * Everything that has to be done every frame can be put in here (e.g. clearing the screen).
   */
  void Renderer::onPreRender() const
  {
  }

  /**
   * This method should be called right after rendering the game. You can undo everything from
   * OnPreRender here or do other things (like rendering the stuff from a vertex buffer).
   */
  void Renderer::onPostRender() const
  {
  }

  /**
   * This method should be called when initializing the window. In here should be put
   * initializations that have to be done once.
   */
  void Renderer::setupStates() const
  {
  }

  /**
   * This method should be called everytime the window size changes or the window should provide
   * space for more pieces. It will setup the view to allow the given number of pieces to be
   * displayed while keeping the correct aspect ratio.
   * @param window_w window width in pixels
   * @param window_h window height in pixels
   * @param game_w game width in pieces
   * @param game_h game height in pieces
   */
  void Renderer::setupView(int window_w, int window_h, int game_w, int game_h) const
  {
  }

  /**
   * This method creates a new texture from the given uri.
   * @param uri uri to load texture from
   * @return created texture or null if creation failed
   */
  Texture* Renderer::createTexture(String const& uri)
  {
    return 0;
  }

  /**
   * This method can be used for rendering a line, represented by two points.
   * @param p1 first point of the line
   * @param p2 second point of the line
   */
  void Renderer::renderLine(Point const& p1, Point const& p2) const
  {
  }

  /**
   * This method can be used for rendering a rectangle.
   * @param rect rectangle to be rendered (the coordinates are in pieces)
   * @param coords coordinates of the texture to be mapped onto the rendered rectangle
   */
  void Renderer::renderRectangle(Rectangle const& rect, TextureRectangle const& coords) const
  {
  }

  /**
   * This method can be used to set a new rendering origin, that is a point to which all new
   * rendered objects will be positioned relative to.
   * @param origin new origin to set
   * @return previously set origin
   */
  Point Renderer::setOrigin(Point const& origin)
  {
    return Point();
  }

  /**
   * With this method you can set a texture to be used when rendering primitives.
   * @param texture texture to be used next
   * @return previously used texture
   */
  Texture const* Renderer::setTexture(Texture const* texture)
  {
    return 0;
  }

  /**
   * This method can be used for setting a new color for rendering primitives.
   * @param color new color to set
   * @return previously set color
   */
  Color Renderer::setColor(Color const& color)
  {
    return Color();
  }
}
