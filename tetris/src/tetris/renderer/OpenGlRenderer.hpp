// OpenGlRenderer.hpp

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

#ifndef TTRSOPENGLRENDERER_HPP
#define TTRSOPENGLRENDERER_HPP

#include "tetris/renderer/Renderer.hpp"


namespace gui
{
  class OpenGlRenderer;
  class OpenGlPrimitiveRenderer;
}

namespace ttrs
{
  class OpenGlGuiRenderer;


  /**
   * This class implements the Renderer interface for OpenGl.
   */
  class OpenGlRenderer: public Renderer
  {
  public:
    OpenGlRenderer(OpenGlGuiRenderer& renderer);

    virtual void onPreRender() const;
    virtual void onPostRender() const;

    virtual void setupStates() const;
    virtual void setupView(int window_w, int window_h, int game_w, int game_h) const;

    virtual Texture* createTexture(String const& uri);

    virtual void renderLine(Point const& p1, Point const& p2) const;
    virtual void renderRectangle(Rectangle const& rect, TextureRectangle const& coords) const;

    virtual Point          setOrigin(Point const& origin);
    virtual Texture const* setTexture(Texture const* texture);
    virtual Color          setColor(Color const& color);

  private:
    gui::OpenGlRenderer*          renderer_;
    gui::OpenGlPrimitiveRenderer* renderer_impl_;

    Point          origin_;
    Texture const* texture_;
    Color          color_;
  };
}


#endif
