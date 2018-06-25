// Win32D3D9WindowImpl.cpp

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

#include <d3d9.h>
#include <util/Assert.hpp>

#include "window/Error.hpp"
#include "window/GraphicWindowBase.hpp"
#include "window/win32/Win32D3D9WindowImpl.hpp"


namespace wnd
{
  /**
   * @copydoc Win32WindowImpl::Win32WindowImpl
   */
  Win32D3D9WindowImpl::Win32D3D9WindowImpl(GraphicWindowBase& window, Bounds const& bounds, String const& title)
    : Win32GraphicWindowImpl(window, bounds, title),
      d3d9_(nullptr),
      device_(nullptr)
  {
    d3d9_ = Direct3DCreate9(D3D_SDK_VERSION);

    if (d3d9_ == nullptr)
      throw Error(TEXT("Error initializing Direct3D"), TEXT("Direct3DCreate9 returned 0"));

    D3DPRESENT_PARAMETERS parameters = {};
    parameters.Windowed             = TRUE;
    parameters.SwapEffect           = D3DSWAPEFFECT_DISCARD;
    parameters.hDeviceWindow        = windowHandle();
    parameters.BackBufferFormat     = D3DFMT_UNKNOWN;
    parameters.BackBufferCount      = 1;
    parameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    if (FAILED(d3d9_->CreateDevice(D3DADAPTER_DEFAULT,
                                   D3DDEVTYPE_HAL,
                                   windowHandle(),
                                   D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                   //D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                   &parameters,
                                   &device_)))
    {
      throw Error(TEXT("Error creating Direct3D device"), TEXT("IDirect3D9::CreateDevice failed"));
    }

    ASSERTOP(d3d9_,   ne, nullptr);
    ASSERTOP(device_, ne, nullptr);
  }

  /**
   * The destructor destroys the OpenGl window and release the OpenGl context.
   */
  Win32D3D9WindowImpl::~Win32D3D9WindowImpl()
  {
    ASSERTOP(d3d9_,   ne, nullptr);
    ASSERTOP(device_, ne, nullptr);

    device_->Release();
    d3d9_->Release();
  }

  /**
   * @copydoc OpenGlWindow::render
   */
  void Win32D3D9WindowImpl::render() const
  {
    // @todo react on device lost
    /*if (*/device_->Present(0, 0, 0, 0); /*== D3DERR_DEVICELOST)*/
      //MessageBox(0, TEXT(""), TEXT(""), MB_OK);
  }
}
