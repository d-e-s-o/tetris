// LexicalCast.hpp

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

#ifndef GUILEXICALCAST_HPP
#define GUILEXICALCAST_HPP

#include <sstream>
#include "gui/Error.hpp"
#include "gui/String.hpp"


namespace gui
{
  /**
   * @todo this implementation really isn't nice -- we need a native Stream thingy for ctr::String
   *       -- fix this!
   */
  template<typename SourceT, typename TargetT>
  struct LexicalCaster
  {
    TargetT operator ()(SourceT const& source)
    {
#if defined(UNICODE) || defined(_UNICODE)
      typedef std::wstringstream Interpreter;
#else
      typedef std::stringstream Interpreter;
#endif

      Interpreter interpreter;
      TargetT     target;

      if(!(interpreter << source && interpreter >> target))
        throw Error(TEXT("Error during type conversion"), TEXT("Error in LexicalCast"));

      return target;
    }
  };

  template<typename SourceT>
  struct LexicalCaster<SourceT, String>
  {
    String operator ()(SourceT const& source)
    {
      LexicalCaster<SourceT, std::basic_string<char_t> > caster;
      return String(caster(source).c_str());
    }
  };

  template<typename TargetT>
  struct LexicalCaster<String, TargetT>
  {
    TargetT operator ()(String const& source)
    {
      LexicalCaster<std::basic_string<char_t>, TargetT> caster;
      return caster(source.toString());
    }
  };


  /**
   * This function converts a given variable to another one. This can work only
   * if operator << and operator >> is overloaded for std::stringstream.
   */
  template<typename SourceT, typename TargetT>
  TargetT lexicalCast(SourceT const& source)
  {
    LexicalCaster<SourceT, TargetT> caster;
    return caster(source);
  }
}


#endif
