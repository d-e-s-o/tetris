// Renderer.hpp

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

#ifndef TTRSRENDERER_HPP
#define TTRSRENDERER_HPP

#include "tetris/String.hpp"
#include "tetris/Color.hpp"
#include "tetris/Rectangle.hpp"
#include "tetris/renderer/Point.hpp"
#include "tetris/renderer/Texture.hpp"


namespace ttrs
{
  /**
   * This class defines the interface every renderer for the tetris game has to implement.
   * @note Renderer objects are not meant to be copied
   */
  class Renderer
  {
  public:
    Renderer();
    virtual ~Renderer();

    virtual void onPreRender() const = 0;
    virtual void onPostRender() const = 0;

    virtual void setupStates() const = 0;
    virtual void setupView(int window_w, int window_h, int game_w, int game_h) const = 0;

    virtual Texture* createTexture(String const& uri) = 0;

    virtual void renderLine(Point const& p1, Point const& p2) const = 0;
    virtual void renderRectangle(Rectangle const& rect, TextureRectangle const& coords) const = 0;

    virtual Point          setOrigin(Point const& origin) = 0;
    virtual Texture const* setTexture(Texture const* texture) = 0;
    virtual Color          setColor(Color const& color) = 0;

  private:
    Renderer(Renderer const& rhs);
    Renderer& operator =(Renderer const& rhs);
  };
}


#endif
