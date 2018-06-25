// ProgramOptions.hpp

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

#ifndef PGMPROGRAMOPTIONS_HPP
#define PGMPROGRAMOPTIONS_HPP

#include <vector>
#include <container/String.hpp>

#include "program/Config.hpp"


namespace pgm
{
  /**
   * This class can be used for handling command line options.
   * You will have to define ms_opts for your options and then
   * instantiate an object with argc and argv from main.
   * Then you can access all your defined options via GetOpt(..)
   * with the appropriate index.
   * Here is an example definition of ms_opts:
   *
   * template<int OptCount>
   * typename deso::ProgramOptions<OptCount>::Option deso::ProgramOptions<OptCount>::ms_opts[OptCount] =
   * {
   *   {'h',  "help", NO_ARGUMENT},
   *   {'\0', "no-sound", NO_ARGUMENT},
   *   {'l', "start-level", REQUIRED_ARGUMENT},
   *   {'i', 0, NO_ARGUMENT},
   *   {'p', 0, OPTIONAL_ARGUMENT}
   * };
   *
   * ProgramOptions<5> opts(argc, argv);
   * if (opts.GetOpt(0).avail)
   * // the option --help or -h was given as argument
   *
   * All parsing in this class is done via getopt_long.
   *
   * Note that in the example above the values for avail and arg of
   * each struct are set to 0, which is correct. If you explicitly set
   * them to other values they will not be changed if the option does
   * not exist in argv.
   */
  class LIBPROGRAM_EXPORT ProgramOptions
  {
  public:
    enum ArgumentType
    {
      ARGUMENT_TYPE_MIN,
      ARGUMENT_TYPE_NONE,
      ARGUMENT_TYPE_REQUIRED,
      ARGUMENT_TYPE_OPTIONAL,
      ARGUMENT_TYPE_MAX
    };

    struct LIBPROGRAM_EXPORT Option
    {
      achar_t      short_opt;
      ctr::StringA long_opt;

      ArgumentType argument_type;

      Option(achar_t short_opt, ctr::StringA long_opt, ArgumentType argument);
    };

    typedef std::vector<Option> Options;

    struct LIBPROGRAM_EXPORT ParsedOption
    {
      Option option;
      bool   available;

      ctr::StringA argument;

      ParsedOption(Option const& option);
    };


    ProgramOptions(int argc, char* argv[], Options const& options);

    ParsedOption const& GetOption(int index) const;

    //int GetAvailableNonOptCount() const;
    //char const* GetNonOpt(int index) const;

    //bool HasNoOptsGiven() const;

  private:
    typedef std::vector<ParsedOption>  ParsedOptions;
    typedef std::vector<struct option> GetoptOptions;

    int    argc_;
    char** argv_;

    ParsedOptions options_;

    int first_non_option_;

    void ParseOptions();

    ctr::String   GetOptionString() const;
    GetoptOptions GetOptions(int* flag) const;
    struct option GetOption(Option const& option, int index, int* flag) const;

    int FindShortOption(char short_opt) const;

    ProgramOptions(ProgramOptions const&);
    ProgramOptions& operator=(ProgramOptions const&);
  };
}


#endif
