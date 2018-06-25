// Resolution.hpp

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

#ifndef WNDRESOLUTION_HPP
#define WNDRESOLUTION_HPP

#include <iosfwd>

#include "window/Config.hpp"
#include "window/Dimensions.hpp"


namespace wnd
{
  class ScreenInterface;


  /**
   * This class represents a resolution a screen can have.
   */
  class LIBWINDOW_EXPORT Resolution
  {
  public:
    dimension_t width() const;
    dimension_t height() const;

    int colorDepth() const;
    int refreshRate() const;

  private:
    friend class ScreenImpl;

    Resolution(dimension_t width, dimension_t height, int color_depth, int refresh_rate);

    dimension_t width_;
    dimension_t height_;

    int color_depth_;
    int refresh_rate_;
  };


  LIBWINDOW_EXPORT bool operator ==(Resolution const& lhs, Resolution const& rhs);
  LIBWINDOW_EXPORT bool operator !=(Resolution const& lhs, Resolution const& rhs);
  LIBWINDOW_EXPORT bool operator < (Resolution const& lhs, Resolution const& rhs);

  LIBWINDOW_EXPORT std::ostream& operator <<(std::ostream& lhs, Resolution const& rhs);
}


namespace wnd
{
  /**
   * @return horizontal resolution
   */
  inline dimension_t Resolution::width() const
  {
    return width_;
  }

  /**
   * @return vertical resolution
   */
  inline dimension_t Resolution::height() const
  {
    return height_;
  }

  /**
   * @return color depth in bits
   */
  inline int Resolution::colorDepth() const
  {
    return color_depth_;
  }

  /**
   * @return vertical refresh rate in hertz
   */
  inline int Resolution::refreshRate() const
  {
    return refresh_rate_;
  }
}


#endif
