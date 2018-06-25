// tiostream.hpp

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

#ifndef STDTIOSTREAM_HPP
#define STDTIOSTREAM_HPP

#include <iosfwd>


namespace std
{
#if defined UNICODE || defined _UNICODE
  typedef wstringbuf     tstringbuf;
  typedef wstringstream  tstringstream;
  typedef wostringstream tostringstream;
  typedef wistringstream tistringstream;
  typedef wstreambuf     tstreambuf;
  typedef wistream       tistream;
  typedef wiostream      tiostream;
  typedef wostream       tostream;
  typedef wfilebuf       tfilebuf;
  typedef wfstream       tfstream;
  typedef wifstream      tifstream;
  typedef wofstream      tofstream;
  typedef wios           tios;

  #define tcerr          wcerr
  #define tcin           wcin
  #define tclog          wclog
  #define tcout          wcout
#else
  typedef stringbuf      tstringbuf;
  typedef stringstream   tstringstream;
  typedef ostringstream  tostringstream;
  typedef istringstream  tistringstream;
  typedef streambuf      tstreambuf;
  typedef istream        tistream;
  typedef iostream       tiostream;
  typedef ostream        tostream;
  typedef filebuf        tfilebuf;
  typedef fstream        tfstream;
  typedef ifstream       tifstream;
  typedef ofstream       tofstream;
  typedef ios            tios;

  #define tcerr          cerr
  #define tcin           cin
  #define tclog          clog
  #define tcout          cout
#endif
}


#endif
