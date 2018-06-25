// ScreenImpl.hpp

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

#ifndef WNDSCREENIMPL_HPP
#define WNDSCREENIMPL_HPP

#include "window/ScreenInterface.hpp"


namespace wnd
{
  /**
   *
   */
  class LIBWINDOW_EXPORT ScreenImpl
  {
  public:
    ScreenImpl(ScreenInterface& screen);

    ScreenInterface::Iterator beginResolution() const;
    ScreenInterface::Iterator endResolution() const;

  protected:
    void addResolution(Resolution const& resolution);
    void removeAllResolutions();

    Resolution createResolution(dimension_t width, dimension_t height,
                                int color_depth, int refresh_rate) const;
    Resolution createDummyResolution() const;

    ScreenInterface&       owner();
    ScreenInterface const& owner() const;

  private:
    ScreenInterface*             screen_;
    ScreenInterface::Resolutions resolutions_;
  };
}


namespace wnd
{
  /**
   *
   */
  inline ScreenImpl::ScreenImpl(ScreenInterface& screen)
    : screen_(&screen)
  {
  }

  /**
   * @copydoc ScreenInterface::beginResolution
   */
  inline ScreenInterface::Iterator ScreenImpl::beginResolution() const
  {
    return resolutions_.begin();
  }

  /**
   * @copydoc ScreenInterface::endResolution
   */
  inline ScreenInterface::Iterator ScreenImpl::endResolution() const
  {
    return resolutions_.end();
  }

  /**
   * @param width horizontal resolution
   * @param height vertical resolution
   * @param color_depth color depth in bits
   * @param refresh_rate refresh rate in hertz
   * @return new resolution created from the given values
   */
  inline Resolution ScreenImpl::createResolution(dimension_t width, dimension_t height,
                                                 int color_depth, int refresh_rate) const
  {
    return Resolution(width, height, color_depth, refresh_rate);
  }

  /**
   * @return
   */
  inline Resolution ScreenImpl::createDummyResolution() const
  {
    return Resolution(0, 0, 0, 0);
  }

  /**
   * @return
   */
  inline ScreenInterface& ScreenImpl::owner()
  {
    return *screen_;
  }

  /**
   * @return
   */
  inline ScreenInterface const& ScreenImpl::owner() const
  {
    return *screen_;
  }
}


#endif
