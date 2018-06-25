// Screen.hpp

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

#ifndef WNDSCREEN_HPP
#define WNDSCREEN_HPP

#include "window/ScreenInterface.hpp"


namespace wnd
{
  /**
   *
   */
  template<typename ImplT>
  class Screen: public ScreenInterface
  {
  public:
    Screen();

    virtual Resolution queryCurrentResolution() const;
    virtual void queryAvailableResolutions();

    virtual void changeResolution(Resolution const& resolution);

    virtual Iterator beginResolution() const;
    virtual Iterator endResolution() const;

  private:
    ImplT impl_;
  };
}


namespace wnd
{
  /**
   * @copydoc ScreenInterface::ScreenInterface
   */
  template<typename ImplT>
  inline Screen<ImplT>::Screen()
    : ScreenInterface(),
      impl_(*this)
  {
  }

  /**
   * @copydoc ScreenInterface::queryCurrentResolution
   */
  template<typename ImplT>
  Resolution Screen<ImplT>::queryCurrentResolution() const
  {
    return impl_.queryCurrentResolution();
  }

  /**
   * @copydoc ScreenInterface::queryAvailableResolutions
   */
  template<typename ImplT>
  void Screen<ImplT>::queryAvailableResolutions()
  {
    impl_.queryAvailableResolutions();
  }

  /**
   * @copydoc ScreenInterface::changeResolution
   */
  template<typename ImplT>
  void Screen<ImplT>::changeResolution(Resolution const& resolution)
  {
    impl_.changeResolution(resolution);
  }

  /**
   * @copydoc ScreenInterface::beginResolution
   */
  template<typename ImplT>
  ScreenInterface::Iterator Screen<ImplT>::beginResolution() const
  {
    return impl_.beginResolution();
  }

  /**
   * @copydoc ScreenInterface::endResolution
   */
  template<typename ImplT>
  ScreenInterface::Iterator Screen<ImplT>::endResolution() const
  {
    return impl_.endResolution();
  }
}


#endif
