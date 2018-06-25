// Options.cpp

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

#include <container/ArrayFunctions.hpp>

#include <options/Error.hpp>
#include <options/Option.hpp>
#include <options/Evaluate.hpp>

#include "resource/Settings.hpp"
#include "tetris/Options.hpp"


namespace ttrs
{
  namespace
  {
    String makeArguments(int argc, char const* const argv[])
    {
      String arguments("");

      // start at index one, zero contains the path of the program which is no actual option
      for (int i = 1; i < argc; i++)
        arguments += String(argv[i]) + String(" ");

      return arguments;
    }

  }


  /**
   * @param available
   * @param argument
   */
  Option::Option(bool available, String const& argument)
    : available(available),
      argument(argument)
  {
  }

  /**
   * @param argc argc from main
   * @param argv argv from main
   */
  Options::Options(int argc, char const* const argv[])
    : arguments_(makeArguments(argc, argv)),
      options_()
  {
    /**
     * @todo we could probably use an description attached to the option, for the help text and
     *       other stuff
     * @todo this code looks horrible and meant to be refactored and stuff -- do this!
     */

    opt::Option options[attribute_count + 4] =
    {
      {opt::OPTION_TYPE_NORMAL,            "help",        'h'},
      {opt::OPTION_TYPE_NORMAL,            "no-textures",  0 },
      {opt::OPTION_TYPE_NORMAL,            "version",     'v'},
      {opt::OPTION_TYPE_OPTIONAL_ARGUMENT, "use-config",  'c'}
    };

    for (size_t i = 0; i < attribute_count; i++)
    {
      options[4 + i].type         = opt::OPTION_TYPE_NORMAL;
      options[4 + i].long_option  = attributes[i].name_;
      options[4 + i].short_option = 0;
    }

    int const options_size = sizeof(options) / sizeof(options[0]);

    opt::Error e = opt::evaluate(arguments_.begin(), arguments_.end(),
                                 options, options_size);

    if (e.type != opt::ERROR_NONE)
      throw 1;

    for (int i = 0; i < options_size; i++)
    {
      char const* begin = 0;
      char const* end   = 0;

      if (options[i].argument_index >= 0 && options[i].argument_length >= 0)
      {
        begin = arguments_.begin() + options[i].argument_index;
        end   = begin + options[i].argument_length;
      }

      ctr::append(options_, Option(options[i].count > 0, String(begin, end)));
    }
  }

  /**
   * @return option structure to the help option
   */
  Option const& Options::help() const
  {
    return options_[0];
  }

  /**
   * @return option structure to the no texture option
   */
  Option const& Options::noTextures() const
  {
    return options_[1];
  }

  /**
   * @return option structure to the version option
   */
  Option const& Options::version() const
  {
    return options_[2];
  }

  /**
   * @return option structure to no config option
   */
  Option const& Options::config() const
  {
    return options_[3];
  }
}
