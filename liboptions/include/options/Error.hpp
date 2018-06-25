// Error.hpp

/***************************************************************************
 *   Copyright (C) 2012 Daniel Mueller (deso@posteo.net)                   *
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

#ifndef OPTERROR_HPP
#define OPTERROR_HPP

#include "options/Config.hpp"


namespace opt
{
  enum ErrorType
  {
    /**
     * Everything went fine.
     * @param option_index undefined
     * @param string_index undefined
     */
    ERROR_NONE,

    /**
     * Input coult not be scanned correctly, i.e., it contained symbols that could not be consumed
     * by any rule.
     * @param option_index undefined
     * @param string_index points to symbols that could not be consumed
     */
    ERROR_SYMBOL,

    /**
     * Input could not be parsed correctly. Although it consists of valid tokens no rule matched all
     * the tokens.
     * @param option_index undefined
     * @param string_index points to tokens that could not be consumed
     */
    ERROR_TOKEN,

    /**
     * Option found multiple times but option type was not OPTION_TYPE_ALLOW_MULTIPLE.
     * @param option_index points to option that appeared multiple times
     * @param string_index undefined
     */
    ERROR_TOO_MANY,

    /**
     * Found an unknown option.
     * @param option_index undefined
     * @param string_index points to the unknown option
     */
    ERROR_UNKNOWN,

    /**
     * An argument was required but none found.
     * @param option_index points to option that was missing an argument
     * @param string_index undefined
     */
    ERROR_NO_ARGUMENT,

    /**
     * An argument was found but no argument expected/accepted.
     * @param option_index points to option that does not accept an argument but had one given
     * @param string_index points to argument that was found
     */
    ERROR_ARGUMENT,
  };


  /**
   *
   */
  struct Error
  {
    ErrorType type;

    size_t option_index;
    size_t string_index;
    size_t string_length;
  };
}


#endif
