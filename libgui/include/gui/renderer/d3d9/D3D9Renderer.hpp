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

#ifndef GUID3D9RENDERER_HPP
#define GUID3D9RENDERER_HPP

#include "gui/renderer/d3d9/D3D9Texture.hpp"
#include "gui/renderer/d3d9/D3D9Font.hpp"
#include "gui/renderer/VertexBuffer.hpp"
#include "gui/renderer/SpecificRenderer.hpp"


struct IDirect3DDevice9;
struct IDirect3DVertexBuffer9;
struct IDirect3DStateBlock9;

typedef float         FLOAT;
typedef unsigned long DWORD;
typedef DWORD         D3DCOLOR;


namespace gui
{
  /**
   * @todo try if we could speed things up using another (pre-transformed vertex format):
   *       D3DFVF_XYZRHW
   * @todo make the renderer support device losses (by recreating all the textures and buffers)
   */
  class LIBGUI_EXPORT D3D9Renderer: public SpecificRenderer<D3D9Renderer, D3D9Texture, D3D9Font>
  {
  public:
    D3D9Renderer(Viewport const& viewport, IDirect3DDevice9& device);
    virtual ~D3D9Renderer();

    virtual void onPreRender();
    virtual void onPostRender();

    //virtual void renderPoint(Point const& point) const;
    //virtual void renderLine(Point const& p1, Point const& p2) const;

    virtual void renderRectangle(Rectangle const& rect) const;
    virtual void renderRectangle(Rectangle const& rect, TextureRectangle const& tex_coords) const;

    virtual void renderString(String const& string, Point const& position) const;

    virtual void pushClippingRectangle(Rectangle const& rect);
    virtual void popClippingRectangle();

    virtual void pushTexture(Texture const* texture);
    virtual void popTexture();

    bool isDirectRendering() const;
    void setDirectRendering(bool direct_rendering);

  protected:
    IDirect3DDevice9&       getDevice();
    IDirect3DDevice9 const& getDevice() const;

  private:
    friend class D3D9Texture;
    friend class D3D9Font;

    /**
     * @note it is pretty important to have the color within the vertex, because with ambient light
     *       (which can be used for coloring as well), we cannot set alpha values and thus no
     *       blending is possible.
     */
    struct Vertex
    {
      FLOAT x;
      FLOAT y;
      FLOAT z;

      D3DCOLOR c;

      FLOAT u;
      FLOAT v;
    };

    /**
     * This class automates the locking and unlocking of the vertex buffer.
     */
    class VertexBufferLocker
    {
    public:
      VertexBufferLocker(IDirect3DVertexBuffer9& buffer, Vertex*& vertices, unsigned int count);
      ~VertexBufferLocker();

    private:
      IDirect3DVertexBuffer9* buffer_;
    };

    typedef VertexBuffer<Vertex> VertexCache;

    static unsigned int const VERTEX_FORMAT;
    static unsigned int const VERTEX_BUFFER_CAPACITY;
    static unsigned int const VERTEX_COUNT_QUAD;

    IDirect3DDevice9*       device_;
    IDirect3DVertexBuffer9* vertex_buffer_;
    IDirect3DStateBlock9*   states_;

    mutable VertexCache cache_;

    SizeT height_;

    void setStates() const;
    void getStates() const;

    //void setMaterial() const;
    void setViewport() const;

    void setClippingRectangle() const;
    void setScissorRectangle(Rectangle const& rectangle) const;

    void fillVertexBuffer(Rectangle const& rect, TextureRectangle const& coords) const;
    void renderVertexBuffer() const;
  };
}


namespace gui
{
  /**
   * @return true if the renderer sends all rendering commands directly to the graphics device,
   *         false if it caches them and sends them later in one piece
   */
  inline bool D3D9Renderer::isDirectRendering() const
  {
    return !cache_.isActive();
  }

  /**
   * @param direct_rendering true for enabling direct rendering, false to disable it
   * @see OpenGlRenderer::isDirectRendering
   */
  inline void D3D9Renderer::setDirectRendering(bool direct_rendering)
  {
    renderVertexBuffer();

    cache_.setActive(!direct_rendering);
  }

  /**
   * @return direct3d device used by this renderer
   */
  inline IDirect3DDevice9& D3D9Renderer::getDevice()
  {
    return *device_;
  }

  /**
   * @return direct3d device used by this renderer
   */
  inline IDirect3DDevice9 const& D3D9Renderer::getDevice() const
  {
    return *device_;
  }
}


#endif
