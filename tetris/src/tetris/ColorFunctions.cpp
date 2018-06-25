// ColorFunctions.cpp

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

#include <util/ColorFunctions.hpp>

#include "tetris/ColorFunctions.hpp"


namespace ttrs
{
  Color red()
  {
    return utl::red<Color::ChannelType>();
  }

  Color green()
  {
    return utl::green<Color::ChannelType>();
  }

  Color blue()
  {
    return utl::blue<Color::ChannelType>();
  }

  Color white()
  {
    return utl::white<Color::ChannelType>();
  }

  Color black()
  {
    return utl::black<Color::ChannelType>();
  }

  Color yellow()
  {
    return utl::yellow<Color::ChannelType>();
  }

  Color violet()
  {
    return utl::violet<Color::ChannelType>();
  }

  Color cyan()
  {
    return utl::cyan<Color::ChannelType>();
  }

  /**
   * @return orange color
   */
  Color orange()
  {
    return Color(Color::max(), Color::max() / 2, Color::min());
  }

  /**
   * @return gray color
   */
  Color gray()
  {
    return Color(Color::max() / 2, Color::max() / 2, Color::max() / 2);
  }
}
