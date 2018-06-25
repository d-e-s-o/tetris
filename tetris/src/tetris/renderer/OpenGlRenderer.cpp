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
#include <util/Rectangle2Functions.hpp>
#include <gui/renderer/opengl/OpenGlRenderer.hpp>

#include "tetris/renderer/OpenGlGuiRenderer.hpp"
#include "tetris/renderer/OpenGlRenderer.hpp"


namespace ttrs
{
  /**
   * The constructor creates a new OpenGlRenderer for the tetris game.
   * @param renderer renderer to use for creating textures and to use primitive renderer of
   */
  OpenGlRenderer::OpenGlRenderer(OpenGlGuiRenderer& renderer)
    : renderer_(&renderer),
      renderer_impl_(&renderer.getPrimitiveRenderer()),
      origin_(),
      texture_(0),
      color_()
  {
  }

  /**
   * @copydoc Renderer::onPreRender
   */
  void OpenGlRenderer::onPreRender() const
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  /**
   * @copydoc Renderer::onPostRender
   */
  void OpenGlRenderer::onPostRender() const
  {
    renderer_impl_->flush();
  }

  /**
   * @copydoc Renderer::setupStates
   */
  void OpenGlRenderer::setupStates() const
  {
    glShadeModel(GL_SMOOTH);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);
  }

  /**
   * @copydoc Renderer::setupView
   */
  void OpenGlRenderer::setupView(int window_w, int window_h, int game_w, int game_h) const
  {
    ASSERTOP(window_h, gt, 0);
    ASSERTOP(game_h,   gt, 0);

    glViewport(0, 0, window_w, window_h);

    double window_ratio = 1.0f * window_w / window_h;
    double game_ratio   = 1.0f * game_w   / game_h;

    double right = 1.0f * game_w;
    double top   = 1.0f * game_h;

    // our goal is to make the two ratios equal, that means:
    //
    // window_w   game_w + x
    // -------- = ----------
    // window_h   game_h + y
    //
    // where x is zero if game_ratio > window_ratio, otherwise y is zero
    // resolve it to x or y to get the equation from below
    if (game_ratio > window_ratio)
      top   += 1.0f * game_w * window_h / window_w - game_h;
    else
      right += 1.0f * game_h * window_w / window_h - game_w;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // our renderer will render everything with z-coordinate of 0.0f, this must lie inside the
    // range [zNear, zFar] (last two parameters)
    glOrtho(0.0f, right, 0.0f, top, -0.5f, 0.5f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    ASSERTOP(glGetError(), eq, GL_NO_ERROR);
  }

  /**
   * @copydoc Renderer::createTexture
   */
  Texture* OpenGlRenderer::createTexture(String const& uri)
  {
    return renderer_->createTexture(uri);
  }

  /**
   * @copydoc Renderer::renderLine
   */
  void OpenGlRenderer::renderLine(Point const& p1, Point const& p2) const
  {
    renderer_impl_->renderLine(p1 + origin_, p2 + origin_);
  }

  /**
   * @copydoc Renderer::renderRectangle
   */
  void OpenGlRenderer::renderRectangle(Rectangle const& rect, TextureRectangle const& coords) const
  {
    Rectangle r = rect;

    utl::move(r, origin_);

    renderer_impl_->renderRectangle(r, coords);
  }

  /**
   * @copydoc Renderer::setOrigin
   */
  Point OpenGlRenderer::setOrigin(Point const& origin)
  {
    Point last = origin_;
    origin_ = origin;
    return last;
  }

  /**
   * @copydoc Renderer::setTexture
   */
  Texture const* OpenGlRenderer::setTexture(Texture const* texture)
  {
    if (texture != texture_)
    {
      Texture const* last = texture_;

      renderer_impl_->flush();

      if (texture != 0)
        texture->bind();
      else
        glBindTexture(GL_TEXTURE_2D, 0);

      texture_ = texture;
      return last;
    }
    return texture_;
  }

  /**
   * @copydoc Renderer::setColor
   */
  Color OpenGlRenderer::setColor(Color const& color)
  {
    if (color != color_)
    {
      Color last = color_;

      if (renderer_impl_->isCaching())
        renderer_impl_->setColor(color);
      else
        glColor4ub(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());

      color_ = color;
      return last;
    }
    return color_;
  }
}
