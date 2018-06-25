// D3D9Renderer.cpp

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

#include "gui/include/D3D9.hpp"
#include <d3dx9math.h>

#include <util/Assert.hpp>
#include <util/Rectangle1Functions.hpp>
#include <container/Algorithm.hpp>
#include <pointer/ResourceGuard.hpp>

#include "gui/Error.hpp"
#include "gui/renderer/Viewport.hpp"
#include "gui/renderer/RendererFunctions.hpp"
#include "gui/renderer/d3d9/D3D9Renderer.hpp"


namespace gui
{
  namespace
  {
    /**
     * Value to add when translating the world matrix to get exact pixel matches.
     */
    FLOAT const TRANSLATION_CORRECTION = 0.5f;


    /**
     * @param color color value to convert to Direct3D color format
     */
    inline D3DCOLOR getD3DColor(Color const& color)
    {
      Color::Type r = color.getRed();
      Color::Type g = color.getGreen();
      Color::Type b = color.getBlue();
      Color::Type a = color.getAlpha();

      return D3DCOLOR_RGBA(r, g, b, a);
    }

    /**
     * @param texture texture to bind, or 0 if none should be bound
     * @param device direct3d device to bind texture to
     */
    void setTexture(Texture const* texture, IDirect3DDevice9& device)
    {
      if (texture != 0)
        texture->bind();
      else
        device.SetTexture(0, 0);
    }

    /**
     * @param device direct3d device bound to window to query client height from
     * @return client height of the window bound to the given direct3d device
     */
    SizeT getWindowClientHeight(IDirect3DDevice9& device)
    {
      D3DDEVICE_CREATION_PARAMETERS p = {};
      RECT                          r = {};

      if (FAILED(device.GetCreationParameters(&p)))
        throw Error(TEXT("Error retrieving creation parameters"), TEXT("GetCreationParameters failed"));

      if (GetClientRect(p.hFocusWindow, &r) != TRUE)
        throw Error(TEXT("Error retrieving window height"), TEXT("GetClientRect failed"));

      ASSERTOP(r.top, eq, 0);

      return r.bottom;
    }

    inline void release(IDirect3DVertexBuffer9* vertex_buffer)
    {
      ASSERTOP(vertex_buffer, ne, 0);
      vertex_buffer->Release();
    }
  }


  unsigned int const D3D9Renderer::VERTEX_FORMAT          = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;
  unsigned int const D3D9Renderer::VERTEX_BUFFER_CAPACITY = 1024;
  unsigned int const D3D9Renderer::VERTEX_COUNT_QUAD      = 6;


  D3D9Renderer::VertexBufferLocker::VertexBufferLocker(IDirect3DVertexBuffer9& buffer, Vertex*& vertices, unsigned int count)
    : buffer_(&buffer)
  {
    if (FAILED(buffer_->Lock(0, count * sizeof(Vertex), reinterpret_cast<void**>(&vertices), 0)))
      throw Error(TEXT("Error rendering primitive"), TEXT("Locking vertex buffer failed"));
  }

  D3D9Renderer::VertexBufferLocker::~VertexBufferLocker()
  {
    if (FAILED(buffer_->Unlock()))
      throw Error(TEXT("Error rendering primitve"), TEXT("Unlocking vertex buffer failed"));
  }

  /**
   * @param root_widget root widget the renderer belongs to
   * @param device direct 3d device to be used for rendering
   */
  D3D9Renderer::D3D9Renderer(Viewport const& viewport, IDirect3DDevice9& device)
    : SpecificRenderer(*this, viewport),
      device_(&device),
      vertex_buffer_(0),
      states_(0),
      cache_(VERTEX_BUFFER_CAPACITY),
      height_(0)
  {
    UINT    size = VERTEX_BUFFER_CAPACITY * sizeof(Vertex);
    D3DPOOL pool = D3DPOOL_DEFAULT;

    if (FAILED(device_->CreateVertexBuffer(size, 0, VERTEX_FORMAT, pool, &vertex_buffer_, 0)))
      throw Error(TEXT("Error creating D3D9Renderer"), TEXT("Creating vertex buffer failed"));

    typedef ptr::ResourceGuard<IDirect3DVertexBuffer9*, void(*)(IDirect3DVertexBuffer9*)> Guard;
    Guard guard(vertex_buffer_, &release);

    if (FAILED(device_->CreateStateBlock(D3DSBT_ALL, &states_)))
      throw Error(TEXT("Error creating D3D9Renderer"), TEXT("Creating state block failed"));

#ifndef NDEBUG
    D3DCAPS9 caps = {};
    device_->GetDeviceCaps(&caps);
    ASSERTOP((caps.RasterCaps & D3DPRASTERCAPS_SCISSORTEST),   eq, D3DPRASTERCAPS_SCISSORTEST);
    ASSERTOP((caps.SrcBlendCaps & D3DPBLENDCAPS_SRCALPHA),     eq, D3DPBLENDCAPS_SRCALPHA);
    ASSERTOP((caps.DestBlendCaps & D3DPBLENDCAPS_INVSRCALPHA), eq, D3DPBLENDCAPS_INVSRCALPHA);
#endif

    cache_.setActive(true);

    device_->AddRef();

    guard.release();
  }

  /**
   * The destructor free's the allocated vertex buffer and destroys the renderer.
   */
  D3D9Renderer::~D3D9Renderer()
  {
    device_->Release();
    states_->Release();
    vertex_buffer_->Release();
  }

  /**
   * @copydoc Renderer::onPreRender
   */
  void D3D9Renderer::onPreRender()
  {
    height_ = getWindowClientHeight(*device_);

    setStates();
    //setMaterial();
    setViewport();

    D3DXMATRIX matrix;
    D3DXMatrixIdentity(&matrix);
    device_->SetTransform(D3DTS_VIEW, &matrix);

    D3DXMatrixTranslation(&matrix, TRANSLATION_CORRECTION, TRANSLATION_CORRECTION, 0.0f);
    device_->SetTransform(D3DTS_WORLD, &matrix);

    Position const& position = getViewport().offset();
    Size     const& size     = getViewport().size();

    FLOAT left   = 1.0f * position.x;
    FLOAT right  = 1.0f * position.x + size.x;
    FLOAT bottom = 1.0f * position.y;
    FLOAT top    = 1.0f * position.y + size.y;

    D3DXMatrixOrthoOffCenterRH(&matrix, left, right, bottom, top, 0.0f, 1.0f);
    device_->SetTransform(D3DTS_PROJECTION, &matrix);
  }

  /**
   * @copydoc Renderer::onPostRender
   */
  void D3D9Renderer::onPostRender()
  {
    renderVertexBuffer();

    // restore saved states
    getStates();
  }

  /**
   * @copydoc Renderer::renderRectangle
   */
  void D3D9Renderer::renderRectangle(Rectangle const& rect) const
  {
    renderRectangle(rect, TextureRectangle(0.0f, 0.0f, 1.0f, 1.0f));
  }

  /**
   * @copydoc Renderer::renderRectangle
   */
  void D3D9Renderer::renderRectangle(Rectangle const& rectangle, TextureRectangle const& tex_coords) const
  {
    ASSERTOP(rectangle.x1_, le, rectangle.x2_);
    ASSERTOP(rectangle.y1_, le, rectangle.y2_);

    ASSERTOP(tex_coords.x1_, le, tex_coords.x2_);
    ASSERTOP(tex_coords.y1_, le, tex_coords.y2_);

    if (cache_.isActive())
    {
      if (!isClippingStackEmpty())
      {
        Rectangle        rect   = constructRectangle(rectangle);
        TextureRectangle coords = tex_coords;

        if (clipRectangle(getClippingRectangle(), rect, coords))
          fillVertexBuffer(rect, coords);
      }
      else
        fillVertexBuffer(rectangle, tex_coords);
    }
    else
    {
      {
        Vertex* vertices = 0;
        VertexBufferLocker locker(*vertex_buffer_, vertices, 4);

        D3DCOLOR color = getD3DColor(getColor());

        // lower left
        Vertex vertex;
        vertex.x = 1.0f * rectangle.x1_;
        vertex.y = 1.0f * rectangle.y1_;
        vertex.z = 0.0f;
        vertex.c = color;
        vertex.u = tex_coords.x1_;
        vertex.v = tex_coords.y1_;
        *vertices++ = vertex;

        // lower right
        vertex.x = 1.0f * rectangle.x2_;
        vertex.u = tex_coords.x2_;
        *vertices++ = vertex;

        // upper left
        vertex.x = 1.0f * rectangle.x1_;
        vertex.y = 1.0f * rectangle.y2_;
        vertex.u = tex_coords.x1_;
        vertex.v = tex_coords.y2_;
        *vertices++ = vertex;

        // upper right
        vertex.x = 1.0f * rectangle.x2_;
        vertex.u = tex_coords.x2_;
        *vertices++ = vertex;
      }
      device_->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    }
  }

  /**
   * @copydoc Renderer::renderString
   */
  void D3D9Renderer::renderString(String const& string, Point const& point) const
  {
    Font const* font = getFont();

    if (font == 0)
      throw Error(TEXT("Error rendering text"), TEXT("No valid font set"));

    font->render(string, point);
  }

  /**
   * @copydoc Renderer::pushClippingRectangle
   */
  void D3D9Renderer::pushClippingRectangle(Rectangle const& rect)
  {
    Renderer::pushClippingRectangle(rect);

    if (!cache_.isActive())
      setClippingRectangle();
  }

  /**
   * @copydoc Renderer::popClippingRectangle
   */
  void D3D9Renderer::popClippingRectangle()
  {
    Renderer::popClippingRectangle();

    if (!cache_.isActive() && !isClippingStackEmpty())
      setClippingRectangle();
  }

  /**
   * @copydoc Renderer::pushTexture
   */
  void D3D9Renderer::pushTexture(Texture const* texture)
  {
    Texture const* previous = isTextureStackEmpty() ? 0 : getTexture();

    if (previous != texture)
      renderVertexBuffer();

    Renderer::pushTexture(texture);

    if (previous != texture)
      setTexture(texture, *device_);
  }

  /**
   * @copydoc Renderer::popTexture
   */
  void D3D9Renderer::popTexture()
  {
    Texture const* previous = getTexture();

    Renderer::popTexture();

    Texture const* texture = isTextureStackEmpty() ? 0 : getTexture();

    if (texture != previous)
    {
      renderVertexBuffer();
      setTexture(texture, *device_);
    }
  }

  /**
   * This method sets a new material. This is nesecarry for working with lightning.
   */
  //void D3D9Renderer::setMaterial() const
  //{
  //  D3DMATERIAL9 material = {};
  //  material.Ambient.r = 1.0f;
  //  material.Ambient.g = 1.0f;
  //  material.Ambient.b = 1.0f;
  //  material.Ambient.a = 1.0f;

  //  device_->setMaterial(&material);
  //}

  /**
   *
   */
  void D3D9Renderer::setStates() const
  {
    // save all states and set new ones for gui rendering
    states_->Capture();

    device_->SetStreamSource(0, vertex_buffer_, 0, sizeof(Vertex));
    device_->SetFVF(VERTEX_FORMAT);
    device_->SetVertexShader(0);
    device_->SetPixelShader(0);

    device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

    device_->SetRenderState(D3DRS_SCISSORTESTENABLE, cache_.isActive() ? FALSE : TRUE);
    device_->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    device_->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
    device_->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
    device_->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
    device_->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
    device_->SetRenderState(D3DRS_FOGENABLE, FALSE);
    device_->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    device_->SetRenderState(D3DRS_LIGHTING, FALSE);
    device_->SetRenderState(D3DRS_STENCILENABLE, FALSE);
    device_->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    device_->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD);
    device_->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_LESSEQUAL);
    device_->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, FALSE);
    device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
  }

  /**
   *
   */
  void D3D9Renderer::getStates() const
  {
    states_->Apply();
  }

  /**
   * @todo check that viewport does not exceed the actual window size, otherwise nothing will be
   *       drawn
   */
  void D3D9Renderer::setViewport() const
  {
    Position const& position = getViewport().offset();
    Size     const& size     = getViewport().size();

    D3DVIEWPORT9 viewport = {};
    viewport.X      = position.x;
    viewport.Y      = height_ - position.y - size.y;
    viewport.Width  = size.x;
    viewport.Height = size.y;
    viewport.MinZ   = 0.0f;
    viewport.MaxZ   = 1.0f;

    if (FAILED(device_->SetViewport(&viewport)))
      throw Error(TEXT("Error setting viewport"), TEXT("SetViewport failed"));
  }

  /**
   *
   */
  void D3D9Renderer::setClippingRectangle() const
  {
    Rectangle const& r = getClippingRectangle();
    Point     const& o = getClippingOrigin();

    ASSERTOP(r.x1_, le, r.x2_);
    ASSERTOP(r.y1_, le, r.y2_);

    setScissorRectangle(r);

    FLOAT x = o.x + r.x1_ + TRANSLATION_CORRECTION;
    FLOAT y = o.y + r.y1_ + TRANSLATION_CORRECTION;

    D3DXMATRIX matrix;
    D3DXMatrixIdentity(&matrix);
    D3DXMatrixTranslation(&matrix, x, y, 0.0f);
    device_->SetTransform(D3DTS_WORLD, &matrix);
  }

  /**
   * @param rectangle clipping rectangle in pixel coordinates to be set
   */
  void D3D9Renderer::setScissorRectangle(Rectangle const& rectangle) const
  {
    ASSERTOP(rectangle.x1_, le, rectangle.x2_);
    ASSERTOP(rectangle.y1_, le, rectangle.y2_);

    // the gui coordinates have their origin in the lower left corner, Windows however treats
    // all coordinates relative to the upper left corner, so we need to convert them using height_
    RECT rect = {};
    rect.left   = rectangle.x1_;
    rect.top    = height_ - rectangle.y2_;
    rect.right  = rectangle.x2_;
    rect.bottom = height_ - rectangle.y1_;

    // @note I am not exactly sure why, but we need this adjustements to make the result look
    //       exactly like that of the OpenGlRenderer - otherwise the Rectangles seem to be too
    //       small
    // @todo find out why exactly thats the case and if not maybe it is the OpenGlRenderer's fault
    --rect.top;
    ++rect.right;

    ASSERTOP(rect.left, le, rect.right);
    ASSERTOP(rect.top,  le, rect.bottom);

    if (FAILED(device_->SetScissorRect(&rect)))
      throw Error(TEXT("Error setting clipping rectangle"), TEXT("SetScissorRect failed"));
  }

  /**
   * @note Direct3D expects a quad to be splittet into two triangles
   */
  void D3D9Renderer::fillVertexBuffer(Rectangle const& rect, TextureRectangle const& coords) const
  {
    if (cache_.getRemainingCapacity() < VERTEX_COUNT_QUAD)
      renderVertexBuffer();

    D3DCOLOR color = getD3DColor(getColor());
    Vertex*  cache = cache_.getCurrent();

    // @note '*cache++ = vertex' is like dereference, assign and increase - in that order
    // lower left
    Vertex vertex;
    vertex.u = coords.x1_;
    vertex.v = coords.y1_;
    vertex.c = color;
    vertex.x = 1.0f * rect.x1_;
    vertex.y = 1.0f * rect.y1_;
    vertex.z = 0.0f;
    *cache++ = vertex;

    // lower right
    vertex.u = coords.x2_;
    vertex.x = 1.0f * rect.x2_;
    *cache++ = vertex;

    // upper right
    vertex.v = coords.y2_;
    vertex.y = 1.0f * rect.y2_;
    *cache++ = vertex;

    // lower left again
    *cache = *(cache - 3);
    ++cache;

    // upper right again
    *cache = *(cache - 2);
    ++cache;

    // upper left
    vertex.u = coords.x1_;
    vertex.x = 1.0f * rect.x1_;
    *cache++ = vertex;

    cache_.increaseSize(VERTEX_COUNT_QUAD);
  }

  /**
   *
   */
  void D3D9Renderer::renderVertexBuffer() const
  {
    if (cache_.isActive() && cache_.getCurrentSize() > 0)
    {
      // lock the buffer and copy the contents of the cache into it, then render the stuff
      {
        Vertex* vertices  = 0;
        unsigned int size = static_cast<unsigned int>(cache_.getCurrentSize());

        VertexBufferLocker locker(*vertex_buffer_, vertices, size);

        ctr::copy(cache_.getBegin(), cache_.getEnd(), vertices);
      }

      // divide by three because a triangle has 3 vertices
      UINT triangle_count = static_cast<UINT>(cache_.getCurrentSize() / 3);
      device_->DrawPrimitive(D3DPT_TRIANGLELIST, 0, triangle_count);

      cache_.clear();

      ASSERTOP(cache_.getCurrentSize(), eq, 0);
    }
  }
}
