// ProgramOptions.cpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#include <getopt.h>

/**
 * @todo remove dependency to libbase
 */
#include <base/Error.hpp>
#include <util/Assert.hpp>

#include "program/ProgramOptions.hpp"


namespace pgm
{
  namespace
  {
    /**
     *
     */
    int ConvertArgumentType(ProgramOptions::ArgumentType argument_type)
    {
      switch(argument_type)
      {
      case ProgramOptions::ARGUMENT_TYPE_NONE:
        return no_argument;

      case ProgramOptions::ARGUMENT_TYPE_REQUIRED:
        return required_argument;

      case ProgramOptions::ARGUMENT_TYPE_OPTIONAL:
        return optional_argument;

      default:
        ASSERT(false);
      }
      return -1;
    }
  }


  /**
   *
   */
  ProgramOptions::Option::Option(achar_t short_opt, ctr::StringA long_opt, ArgumentType argument)
    : short_opt(short_opt),
      long_opt(long_opt),
      argument_type(argument)
  {
    if (short_opt == '\0' && long_opt.size() == 0)
    {
      throw base::Error("Error creating program option",
                        "Both options (short and long) must not be empty");
    }
  }

  /**
   *
   */
  ProgramOptions::ParsedOption::ParsedOption(Option const& option)
    : option(option),
      available(false),
      argument()
  {
  }

  /**
   * The constructor parses all command line options and sets the avail value of each option to
   * true of it was found in argv. If an argument was given arg points to it.
   * @param argc argc value from int main(int argc...)
   * @param argv argv value from int main(..., char* argv[])
   */
  ProgramOptions::ProgramOptions(int argc, char* argv[], Options const& options)
    : argc_(argc),
      argv_(argv),
      options_(),
      first_non_option_(-1)
  {
    if (argc <= 0 || argv == 0 || options.empty())
    {
      throw base::Error("Error creating ProgramOptions object",
                        "Invalid argument given");
    }

    // copy the given options into the other array by creating new objects from them
    std::copy(options.begin(), options.end(), std::back_inserter(options_));
    ASSERTOP(options.size(), eq, options_.size());

    ParseOptions();
  }

  /**
   * This method returns the Option at index index.
   * @param index index of the option in the range 0 to GetAvailableOptCount - 1
   * @return Option at index
   */
  ProgramOptions::ParsedOption const& ProgramOptions::GetOption(int index) const
  {
    ASSERTOP(index, ge, 0);
    ASSERTOP(index, lt, static_cast<int>(options_.size()));
    return options_[index];
  }

  /**
   * Get the number of arguments that are no options (and no arguments of options)
   */
  //int ProgramOptions::GetAvailableNonOptCount() const
  //{
  //  ASSERTOP(argc_, ge, first_non_option_);
  //  return argc_ - first_non_option_;
  //}

  /**
   * Get the non-opt argument at given index
   * This method returns the argument string at the index index.
   * @param index index of the argument in the range 0 to GetAvailableNonOptCount - 1
   * @return argument string at index index
   */
  //char const* ProgramOptions::GetNonOpt(int index) const
  //{
  //  ASSERTOP(first_non_option_, ge, 0);

  //  index += first_non_option_;

  //  ASSERTOP(index, ge, 0);
  //  ASSERTOP(index, lt, argc_);
  //  return argv_[index];
  //}

  /**
   * Check whether one or more of the options were set
   * @return true if no of the options in options_ were found in argv false otherwise
   */
  //bool ProgramOptions::HasNoOptsGiven() const
  //{
  //  bool no_opts = true;

  //  for (int i = 0; no_opts && i < GetAvailableOptCount(); ++i)
  //    no_opts = no_opts && !options_[i].available;

  //  return no_opts;
  //}

  /**
   *
   */
  void ProgramOptions::ParseOptions()
  {
    // it is important to reset optind, especially if parsing multiple command lines
    optind = 0;

    int index  = -1;
    int result = -1;
    int flag;

    ctr::String option_string = GetOptionString();
    GetoptOptions options     = GetOptions(&flag);

    // get all arguments in argv
    // all non option arguments (p.ex. filenames) are moved to the end of argv
    // if a short option is found, getopt_long returns the ascii code of the short option
    // if a long option was found, zero is returned (because we set flag to zero)
    // and index contains the index of the long option in options from GetOpts()
    while (result = getopt_long(argc_, argv_, option_string.toString(), &options[0], &index), result != -1)
    {
      if (result != '?')
      {
        ASSERTOP(result, ne, ':');

        // if a short option was found we need to find the appropriate index
        // otherwise (long option) getopt_long did that for us
        if (result > 0)
          index = FindShortOption(static_cast<char>(result));

        ASSERTOP(index, ge, 0);
        ASSERTOP(index, lt, static_cast<int>(options_.size()));

        if (index >= 0 && index < static_cast<int>(options_.size()))
        {
          ParsedOption& opt = options_[index];

          opt.available = true;

          if (opt.option.argument_type == ARGUMENT_TYPE_REQUIRED ||
              opt.option.argument_type == ARGUMENT_TYPE_OPTIONAL)
          {
            opt.argument = (optarg == 0) ? ctr::String() : ctr::String(optarg);
          }
        }
      }
      index = -1;
    }
    // the non option arguments are at the end, optind is the index of the first
    first_non_option_ = optind;
  }

  /**
   * This method creates the option string needed by getopt_long, filled with the information from
   * the options_ array.
   */
  ctr::String ProgramOptions::GetOptionString() const
  {
    ctr::String s;

    for (ParsedOptions::const_iterator it = options_.begin(); it != options_.end(); ++it)
    {
      Option const& option = it->option;

      // accept every char but no zero byte
      if (option.short_opt != '\0')
      {
        s += ctr::String(option.short_opt);

        if (option.argument_type == ARGUMENT_TYPE_REQUIRED)
          s += ctr::String(":");
        else if (option.argument_type == ARGUMENT_TYPE_OPTIONAL)
          s += ctr::String("::");
      }
    }
    return s;
  }

  /**
   * This method creates an array of the option structure, representing the given Options in
   * options_. It is used for getopt_long.
   * @return array of option objects filled with data of options_
   */
  ProgramOptions::GetoptOptions ProgramOptions::GetOptions(int* flag) const
  {
    GetoptOptions options;

    for (int i = 0; i < static_cast<int>(options_.size()); ++i)
      options.push_back(GetOption(options_[i].option, i, flag));

    return options;
  }

  /**
   * This method creates a option needed by getopt_long.
   */
  option ProgramOptions::GetOption(ProgramOptions::Option const& option, int index, int* flag) const
  {
    ASSERT(!(option.long_opt.size() == 0 && option.short_opt == '\0'));

    ::option opt = {};

    opt.has_arg = ConvertArgumentType(option.argument_type);
    opt.name    = option.long_opt.toString();

    // If flag is 0 getopt will return the value of val.
    // If it is not 0 then it has to be the address of an
    // integer to store the value of val in, in that case
    // getopt_long will return 0 (thats what we need).
    // Tmp has to be unique to distinguish between the options.
    opt.flag = flag;

    // 256 is definitely no valid ascii value for a short option
    opt.val = 256 + index;

    return opt;
  }

  /**
   * This function takes the ascii value of a short option and tries to find it in the options_
   * array.
   * @param short_opt ascii code of the short option to find
   * @return if the option was found the index of it in options_
   * -1 if the option was not found
   */
  int ProgramOptions::FindShortOption(char short_opt) const
  {
    for (int i = 0; i < static_cast<int>(options_.size()); ++i)
    {
      if (options_[i].option.short_opt == short_opt)
        return i;
    }
    return -1;
  }
}
