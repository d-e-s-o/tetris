// Orientation.hpp

/***************************************************************************
 *   Copyright (C) 2013-2014 Daniel Mueller (deso@posteo.net)              *
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

#ifndef TTRSAIORIENTATION_HPP
#define TTRSAIORIENTATION_HPP

#include <util/Bits.hpp>
#include <util/Assert.hpp>


namespace ttrs
{
  namespace ai
  {
    /**
     *
     */
    enum class Orientation : uint8_t
    {
      MIN         = 0,
      ROTATED_0   = 1 << 0,
      ROTATED_90  = 1 << 1,
      ROTATED_180 = 1 << 2,
      ROTATED_270 = 1 << 3,
      MAX         = 1 << 4
    };


    Orientation rotateLeft(Orientation orientation);
    Orientation rotateRight(Orientation orientation);

    Orientation combine(Orientation first, Orientation second);

    bool contains(Orientation orientation, Orientation value);
    bool full(Orientation orientation);
  }
}


namespace ttrs
{
  namespace ai
  {
    /**
     * @param orientation
     * @return
     */
    inline Orientation rotateLeft(Orientation orientation)
    {
      ASSERT(Orientation::MIN < orientation && orientation < Orientation::MAX);

      uint8_t value = static_cast<uint8_t>(orientation);
      return static_cast<Orientation>(utl::rotateRight<uint8_t, 4>(value, 1));
    }

    /**
     * @param orientation
     * @return
     */
    inline Orientation rotateRight(Orientation orientation)
    {
      ASSERT(Orientation::MIN < orientation && orientation < Orientation::MAX);

      uint8_t value = static_cast<uint8_t>(orientation);
      return static_cast<Orientation>(utl::rotateLeft<uint8_t, 4>(value, 1));
    }

    /**
     * @param first
     * @param second
     * @return
     */
    inline Orientation combine(Orientation first, Orientation second)
    {
      ASSERT(Orientation::MIN < first  && first  < Orientation::MAX);
      ASSERT(Orientation::MIN < second && second < Orientation::MAX);

      uint8_t value = static_cast<uint8_t>(first) | static_cast<uint8_t>(second);
      return static_cast<Orientation>(value);
    }

    /**
     * @param orientation
     * @param value
     * @return
     */
    inline bool contains(Orientation orientation, Orientation value)
    {
      ASSERT(Orientation::MIN < orientation && orientation < Orientation::MAX);
      ASSERT(Orientation::MIN < value       && value       < Orientation::MAX);

      return (static_cast<uint8_t>(orientation) & static_cast<uint8_t>(value)) != 0;
    }

    /**
     * @param orientation
     * @return
     */
    inline bool full(Orientation orientation)
    {
      Orientation all = Orientation::ROTATED_0;
      all = combine(all, Orientation::ROTATED_90);
      all = combine(all, Orientation::ROTATED_180);
      all = combine(all, Orientation::ROTATED_270);

      return orientation == all;
    }
  }
}

#endif
