// HelpText.hpp

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

#ifndef PGMHELPTEXT_HPP
#define PGMHELPTEXT_HPP

#include "program/Config.hpp"
#include "program/ProgramOptions.hpp"


namespace pgm
{
  class LIBPROGRAM_EXPORT HelpText
  {
  public:
    HelpText(ProgramOptions::Options const& options, int line_width = 80, int indent_width = 2);
    virtual ~HelpText();

    virtual void displayHelpText() = 0;

  protected:
    void BeginSection(ctr::String const& section);
    void EndSection();

    void BeginOption(int index);
    void EndOption();

    void IncIndentation();
    void DecIndentation();

    void DisplayIndentation() const;
    void DisplayLine(ctr::String const& line) const;
    void DisplayText(ctr::String const& text) const;

  private:
    int line_width_;
    int indent_width_;
    int indent_count_;

    ProgramOptions::Options options_;

    HelpText(HelpText const&);
    HelpText& operator =(HelpText const&);
  };
}


#endif
