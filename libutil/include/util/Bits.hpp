// Bits.hpp

/***************************************************************************
 *   Copyright (C) 2014 Daniel Mueller (deso@posteo.net)                   *
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

#ifndef UTLBITS_HPP
#define UTLBITS_HPP

#include "util/Config.hpp"


namespace utl
{
  template<typename T, size_t Bits>
  constexpr T rotateLeft(T value, size_t shift);

  template<typename T, size_t Bits>
  constexpr T rotateRight(T value, size_t shift);
}


namespace utl
{
  template<typename T, size_t Bits>
  struct Mask
  {
    /**
     * Calculation of the mask for the given number of bits by example
     * Bits = 5 => goal is mask 011111b
     * - Bits - 1 => 4
     * - 1 << 4   => 16 = 010000b
     * - 16 - 1   => 15 = 001111b
     * - 15 << 1  => 30 = 011110b
     * - 30 | 1   => 31 = 011111b
     * @note 'Bits' might equal the number of bits of the given data type; this means we cannot
     *       safely assume that we can always perform 'Bit' shifts, so the algorithm is slightly
     *       more complicated and we only shift by 'Bit'-1 initially
     */
    static T const value = (((static_cast<T>(1 << (Bits - 1)) - 1) << 1) | 1);
  };


  /**
   * @param value some integral value
   * @param shift amount of bit rotations to apply
   */
  template<typename T, size_t Bits>
  constexpr T rotateLeft(T value, size_t shift)
  {
    // the following checks can no longer be used for a constexpr function; the invariants have to
    // be enforced by the caller
    //assert(Bits  <= typ::typeBits(value));
    //assert(shift <= typ::typeBits(value));
    //assert((value & Mask<T, Bits>::value) == value);
    return ((value << shift) | (value >> (Bits - shift))) & Mask<T, Bits>::value;
  }

  /**
   * @param value some integral value
   * @param shift amount of bit rotations to apply
   */
  template<typename T, size_t Bits>
  constexpr T rotateRight(T value, size_t shift)
  {
    // the following checks can no longer be used for a constexpr function; the invariants have to
    // be enforced by the caller
    //assert(Bits  <= typ::typeBits(value));
    //assert(shift <= typ::typeBits(value));
    //assert((value & Mask<T, Bits>::value) == value);
    return ((value >> shift) | (value << (Bits - shift))) & Mask<T, Bits>::value;
  }
}


#endif
