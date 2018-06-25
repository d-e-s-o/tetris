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

#ifndef GUISPECIFICRENDERER_HPP
#define GUISPECIFICRENDERER_HPP

#include "gui/renderer/TextureManager.hpp"
#include "gui/renderer/FontManager.hpp"
#include "gui/renderer/Renderer.hpp"


namespace gui
{
  /**
   * This class template implements the texture and font handling actions all derived renderers
   * would have to care about (but actually do not because this class does).
   * It uses a texture manager and font manager for the specified texture/font type to manage all
   * created textures/fonts.
   * Basically every renderer should derive from this class, unless it wants
   * to implement texture and font handling itself.
   * @see TextureManager
   * @see FontManager
   */
  template<typename RendererT, typename TextureT, typename FontT>
  class SpecificRenderer: public Renderer
  {
  public:
    SpecificRenderer(RendererT& renderer, Viewport const& viewport, ResourceManager const& resource_manager);
    virtual ~SpecificRenderer() = 0;

    virtual TextureT* createTexture(String const& file);
    virtual FontT*    createFont(String const& name, SizeT size);

  private:
    RendererT* renderer_;

    TextureManager<TextureT> texture_manager_;
    FontManager<FontT>       font_manager_;
  };
}


namespace gui
{
  /**
   * @copydoc Renderer::renderer
   */
  template<typename RendererT, typename TextureT, typename FontT>
  SpecificRenderer<RendererT, TextureT, FontT>::SpecificRenderer(RendererT& renderer, Viewport const& viewport, ResourceManager const& resource_manager)
    : Renderer(viewport),
      renderer_(&renderer),
      texture_manager_(resource_manager),
      font_manager_(resource_manager.getNamespaceManager())
  {
  }

  /**
   * The destructor is abstract - no objects of this class can be created.
   */
  template<typename RendererT, typename TextureT, typename FontT>
  SpecificRenderer<RendererT, TextureT, FontT>::~SpecificRenderer()
  {
  }

  /**
   * @copydoc Renderer::createTexture
   */
  template<typename RendererT, typename TextureT, typename FontT>
  TextureT* SpecificRenderer<RendererT, TextureT, FontT>::createTexture(String const& uri)
  {
    return texture_manager_.createTexture(*renderer_, uri);
  }

  /**
   * @copydoc Renderer::createFont
   */
  template<typename RendererT, typename TextureT, typename FontT>
  FontT* SpecificRenderer<RendererT, TextureT, FontT>::createFont(String const& uri, SizeT size)
  {
    return font_manager_.createFont(*renderer_, uri, size);
  }
}


#endif
