// Direct3DWindow.hpp

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

#ifndef WNDDIRECT3DWINDOW_HPP
#define WNDDIRECT3DWINDOW_HPP

#include "window/Bounds.hpp"
#include "window/String.hpp"
#include "window/GraphicWindow.hpp"


namespace wnd
{
  /**
   * @todo is this class even used somewhere?
   */
  template<typename ImplT>
  class Direct3DWindow: public GraphicWindow<ImplT>
  {
  public:
    typedef typename Impl::Direct3D       Direct3D;
    typedef typename Impl::Direct3DDevice Direct3DDevice;

    direct3DWindow(Bounds const& bounds, String const& title = TEXT(""));

    virtual void initialize();

  protected:
    virtual void initializeView() const;

    Direct3D&       getD3D() const;
    Direct3DDevice& getD3DDevice() const;
  };
}


namespace wnd
{
  /**
   *
   */
  template<typename ImplT>
  inline Direct3DWindow<ImplT>::direct3DWindow(Bounds const& bounds, String const& title)
    : graphicWindow(bounds, title)
  {
  }

  /**
   * @copydoc GraphicWindow::initialize
   */
  template<typename ImplT>
  void Direct3DWindow<ImplT>::initialize()
  {
    initializeView();
    // @todo implement me!
  }

  /**
   * @copydoc GraphicWindow::initializeView
   */
  template<typename ImplT>
  void Direct3DWindow<ImplT>::initializeView() const
  {
    // @todo implement me!
  }

  /**
   *
   */
  template<typename ImplT>
  inline typename Direct3DWindow<ImplT>::Direct3D& Direct3DWindow<ImplT>::getD3D() const
  {
    return impl().getD3D();
  }

  /**
   *
   */
  template<typename ImplT>
  inline typename Direct3DWindow<ImplT>::Direct3DDevice& Direct3DWindow<ImplT>::getD3DDevice() const
  {
    return impl().getD3DDevice();
  }
}


#endif
