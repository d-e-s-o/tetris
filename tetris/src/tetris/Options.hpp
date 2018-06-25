// Options.hpp

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

#ifndef TTRSOPTIONS_HPP
#define TTRSOPTIONS_HPP

#include <container/Array.hpp>

#include "tetris/String.hpp"


namespace ttrs
{
  /**
   *
   */
  struct Option
  {
    bool   available;
    String argument;

    Option(bool available, String const& argument);
  };


  /**
   * This class handles the command line options for the game.
   */
  class Options
  {
  public:
    Options(int argc, char const* const argv[]);

    Option const& help() const;
    Option const& noTextures() const;
    Option const& version() const;
    Option const& config() const;

  private:
    typedef ctr::Array<Option> OptionsArray;

    String       arguments_;
    OptionsArray options_;
  };
}


#endif
