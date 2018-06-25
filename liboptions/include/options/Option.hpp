// Option.hpp

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

#ifndef OPTOPTION_HPP
#define OPTOPTION_HPP

#include "options/Config.hpp"


namespace opt
{
  /**
   *
   */
  enum OptionType
  {
    OPTION_TYPE_MIN,
    OPTION_TYPE_NORMAL,
    OPTION_TYPE_ALLOW_MULTIPLE,
    OPTION_TYPE_OPTIONAL_ARGUMENT,
    OPTION_TYPE_REQUIRED_ARGUMENT,
    OPTION_TYPE_MAX
  };


  /**
   * @note although one can specify any character for the long and short options, only letters and
   *       digits are allowed (and in case of long options also a dash as long as it is not at the
   *       beginning or the end of the option name; options using other characters will never be
   *       found
   * @todo think about adding support for querying the position of an option; this way one could
   *       make one overwrite the other if it appears later
   */
  struct Option
  {
    /**
     * Input fields
     */

    /**
     * Type of the given option
     */
    OptionType type;

    /**
     * String specifying the long option (without any leading dashes). Set to null if no long option
     * is desired.
     */
    char_t const* long_option;

    /**
     * Character specifying the short option. Set to null if no short option is desired.
     */
    char_t short_option;


    /**
     * Output fields
     */

    /**
     * The number of times the option was found. Can only be zero or one in case of a normal option.
     * Only options of type OPTION_TYPE_ALLOW_MULTIPLE can have a count greater one.
     */
    size_t count;

    /**
     * Set to the argument that was found. Note that options of type OPTION_TYPE_ALLOW_MULTIPLE will
     * always have this field set to null as they cannot contain any arguments.
     */
    size_t argument_index;
    size_t argument_length;
  };
}


#endif
