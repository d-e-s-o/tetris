// HelpText.cpp

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

#include "tetris/HelpText.hpp"


namespace ttrs
{
  /**
   * Create the help text object with the Options.
   * @param opts Options used in the tetris game
   */
  HelpText::HelpText(pgm::ProgramOptions::Options const& options)
    : pgm::HelpText(options)
  {
  }

  /**
   * Write the help text to standard out.
   */
  void HelpText::displayHelpText()
  {
    DisplayLine(ctr::String("Clone of the famous tetris for GameBoy (tm).\n"));
    DisplayLine(ctr::String("The game is written in C++ by DeSoVoDaMu. It is licensed under the GPL General Public License.\n"));
    //DisplayLine("The source code and binaries for Windows and Linux are available at http://www.DeSoVoDaMu.de.\n\n");

    BeginSection(ctr::String("Options"));
      //BeginOption(1);
      //  DisplayLine("Start the game without sound. The sounds will not be loaded, you do not have to carry them around if you start with this option. Also the vorbisfile.dll, vorbis.dll and ogg.dll on Windows machines are not needed.\n");
      //EndOption();
      //BeginOption(2);
      //  DisplayLine("Start the game without textures. The textures will not be loaded, you do not have to carry them around if you start with this option.\n");
      //EndOption();
      BeginOption(4);
        DisplayLine(ctr::String("Start game with configuration file. If a file is given it will be used, otherwise 'tetris.cfg' will be used.\n"));
      EndOption();
      BeginOption(3);
        DisplayLine(ctr::String("Display the version of this tetris.\n"));
      EndSection();
      BeginOption(0);
        DisplayLine(ctr::String("Display this help text.\n"));
      EndOption();
    EndSection();

    // @todo we need support for automatic "tab-amount" detection (to correctly align the text) -
    //       here we needed to add some double tabs
    BeginSection(ctr::String("Controls"));
      DisplayLine(ctr::String("Left:\t\tmove the stone one unit left"));
      DisplayLine(ctr::String("Right:\tmove the stone one unit right"));
      DisplayLine(ctr::String("Down:\t\tmove the stone one unit down"));
      DisplayLine(ctr::String("Up:\t\tmove the stone down until it collides\n"));

      DisplayLine(ctr::String("1:\t\tturn the stone left"));
      DisplayLine(ctr::String("2:\t\tturn the stone right\n"));

      DisplayLine(ctr::String("F:\t\tenable/disable frames"));
      DisplayLine(ctr::String("S:\t\tshow settings dialog"));
      DisplayLine(ctr::String("Space:\tpause/unpause the game"));
      DisplayLine(ctr::String("Return:\tstart new game"));
    EndSection();
  }
}
