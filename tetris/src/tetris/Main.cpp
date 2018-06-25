// Main.cpp

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

#include <iostream>
#include <base/Error.hpp>

#include "tetris/Options.hpp"
#include "tetris/HelpText.hpp"
#include "tetris/Application.hpp"

#ifdef GetMessage
#  undef GetMessage
#endif


namespace
{
  uint32_t const VERSION = 0x02010000;
}


/**
 * The main function creates an Application object and runs it.
 */
int main(int argc, char* argv[])
{
  try
  {
    ttrs::Options options(argc, argv);

    if (options.help().available)
    {
      //ttrs::HelpText help_text(options.getOptions());
      //help_text.displayHelpText();
    }
    else if (options.version().available)
    {
      std::cout << "tetris "
                << (VERSION >> 24)        << '.'
                << (VERSION >> 16 & 0xFF) << '.'
                << (VERSION >> 8  & 0xFF);

      if ((VERSION & 0xFF) > 0)
        std::cout << "-r" << (VERSION & 0xFF);

      std::cout << std::endl;
    }
    else
    {
      ttrs::Application app(options);
      return app.run();
    }
    return 0;
  }
  catch(base::Error const& error)
  {
    std::cerr << "Error: " << error.getMessage() << '\n'
              << "Cause: " << error.getCause()   << std::endl;
  }
  catch(...)
  {
    std::cerr << "An unexpected error occured" << std::endl;
  }
  return -1;
}
