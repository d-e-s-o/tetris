// OpenGlGuiRenderer.hpp

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

#ifndef TTRSOPENGLGUIRENDERER_HPP
#define TTRSOPENGLGUIRENDERER_HPP

#include <gui/renderer/opengl/OpenGlRenderer.hpp>


namespace ttrs
{
  /**
   * This class gives us access to the OpenGlPrimitiveRenderer, so we do not need our own (that is
   * important because the used vertex buffer can be pretty big).
   */
  class OpenGlGuiRenderer: public gui::OpenGlRenderer
  {
  public:
    OpenGlGuiRenderer(gui::Viewport const& viewport, gui::ResourceManager const& resource_manager);

    using OpenGlRenderer::getPrimitiveRenderer;
  };
}


namespace ttrs
{
  /**
   * @copydoc OpenGlRenderer::OpenGlRenderer
   */
  inline OpenGlGuiRenderer::OpenGlGuiRenderer(gui::Viewport        const& viewport,
                                              gui::ResourceManager const& resource_manager)
    : OpenGlRenderer(viewport, resource_manager)
  {
    //setCaching(false);
  }
}


#endif
