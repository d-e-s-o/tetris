// HelpText.cpp

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

#include <cctype>
#include <string>
#include <iomanip>
#include <iostream>
#include <util/Assert.hpp>

#include "program/StringFunctions.hpp"
#include "program/HelpText.hpp"


namespace pgm
{
  /**
   *
   */
  HelpText::HelpText(ProgramOptions::Options const& options, int line_width, int indent_width)
    : line_width_(line_width),
      indent_width_(indent_width),
      indent_count_(0),
      options_(options)
  {
  }

  /**
   *
   */
  HelpText::~HelpText()
  {
  }

  void HelpText::BeginSection(ctr::String const& section)
  {
    DisplayLine(section + ctr::String(":"));
    IncIndentation();
  }

  void HelpText::EndSection()
  {
    DecIndentation();
  }

  void HelpText::BeginOption(int index)
  {
    ASSERTOP(index, ge, 0);
    ASSERTOP(index, lt, static_cast<int>(options_.size()));

    ProgramOptions::Option const& opt = options_[index];

    ctr::String line;

    if (opt.long_opt.size() > 0)
      line += ctr::String("--") + opt.long_opt;
    else
      line += ctr::String("-") + ctr::String(opt.short_opt);

    if (opt.argument_type == ProgramOptions::ARGUMENT_TYPE_OPTIONAL ||
        opt.argument_type == ProgramOptions::ARGUMENT_TYPE_REQUIRED)
    {
      line += ctr::String(" [param]");
    }

    if (opt.long_opt.size() > 0 && std::isalpha(opt.short_opt))
      line += ctr::String(" (-") + ctr::String(opt.short_opt) + ctr::String(" short option)");

    line += ctr::String(":");
    DisplayLine(line);
    IncIndentation();
  }

  void HelpText::EndOption()
  {
    DecIndentation();
  }

  void HelpText::IncIndentation()
  {
    ++indent_count_;
  }

  void HelpText::DecIndentation()
  {
    if (indent_count_ > 0)
      --indent_count_;
  }

  void HelpText::DisplayIndentation() const
  {
    for (int i = 0; i < indent_count_; ++i)
      std::cout << std::setw(indent_width_) << std::setfill(' ') << ' ';
  }

  void HelpText::DisplayLine(ctr::String const& text) const
  {
    DisplayText(text + ctr::String('\n'));
  }

  /**
   * @todo: recognize tabs in text, recognize spaces in front, ...
   */
  void HelpText::DisplayText(ctr::String const& text) const
  {
    int char_count = indent_count_ * indent_width_;
    Strings list(Text2Strings(text, ' '));
    ctr::String line;

    for (Strings::ConstIterator i = list.begin(); i != list.end(); ++i)
    {
      if (char_count + static_cast<int>(line.size() + i->size()) >= line_width_)
      {
        DisplayIndentation();
        std::cout << TrimRight(TrimLeft(line)).toString() << '\n';
        line = ctr::String();
      }

      line += *i + ctr::String(' ');
    }
    DisplayIndentation();
    std::cout << TrimRight(TrimLeft(line)).toString();
  }
}
