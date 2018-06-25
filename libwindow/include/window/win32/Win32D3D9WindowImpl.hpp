// Win32D3D9WindowImpl.hpp

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

#ifndef WNDWIN32D3D9WINDOWIMPL_HPP
#define WNDWIN32D3D9WINDOWIMPL_HPP

#include "window/win32/Win32GraphicWindowImpl.hpp"


struct IDirect3D9;
struct IDirect3DDevice9;

namespace wnd
{
  /**
   *
   */
  class LIBWINDOW_EXPORT Win32D3D9WindowImpl: public Win32GraphicWindowImpl
  {
  public:
    typedef IDirect3D9       Direct3D;
    typedef IDirect3DDevice9 Direct3DDevice;

    Win32D3D9WindowImpl(GraphicWindowBase& window, Bounds const& bounds, String const& title);
    virtual ~Win32D3D9WindowImpl();

    void render() const;

    Direct3D&       getD3D() const;
    Direct3DDevice& getD3DDevice() const;

  private:
    IDirect3D9*       d3d9_;
    IDirect3DDevice9* device_;
  };
}


namespace wnd
{
  /**
   *
   */
  inline Win32D3D9WindowImpl::Direct3D& Win32D3D9WindowImpl::getD3D() const
  {
    return *d3d9_;
  }

  /**
   *
   */
  inline Win32D3D9WindowImpl::Direct3DDevice& Win32D3D9WindowImpl::getD3DDevice() const
  {
    return *device_;
  }
}


#endif
