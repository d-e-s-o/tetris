// IniFile.hpp

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

#ifndef BASEINIFILE_HPP
#define BASEINIFILE_HPP

#include <sstream>
#include <string>
#include <vector>
#include <util/Assert.hpp>

#include "base/Config.hpp"


namespace base
{
  /**
   * This class represents a ini file with sections and keys.
   */
  class LIBBASE_EXPORT IniFile
  {
  public:
    IniFile();
    IniFile(std::string const& filename);

    bool loadFromFile(std::string const& filename);
    bool saveToFile(std::string const& filename) const;

    template<typename T>
    bool readValue(std::string const& section, std::string const& key, T& value) const;

    template<typename T>
    bool writeValue(std::string const& section, std::string const& key, T const& value);

  private:
    typedef std::vector<std::string> Lines;
    typedef Lines::iterator LinePointer;

    mutable Lines lines_;

    IniFile(IniFile const&);
    IniFile& operator =(IniFile const&);

    LinePointer findSection(std::string const& section, LinePointer begin) const;
    LinePointer findLastSection(std::string const& section) const;
    LinePointer findKey(std::string const& section, std::string const& key) const;
    LinePointer findOrCreateKey(std::string const& section, std::string const& key) const;
    LinePointer findLastKey(std::string const& section) const;

    bool isSectionString(std::string s) const;
    std::string getSectionString(std::string const& s) const;

    bool isKeyLine(std::string const& line) const;
    bool isKeyLine(std::string const& line, std::string const& key) const;

    std::string getKeyContent(std::string const& line) const;
  };
}


namespace base
{
  /**
  * This method reads the value for the given key in the given section.
  * @param[in] section the section the key is in
  * @param[in] key the key the value belongs to
  * @param[out] value the value read on succes, on failure this value is not touched
  * @result true if reading was successful (value contains data read), false otherwise (value is
  *         not changed)
  */
  template<typename T>
  bool IniFile::readValue(std::string const& section, std::string const& key, T& value) const
  {
    LinePointer it = findKey(getSectionString(section), key);

    if (it != lines_.end())
    {
      std::istringstream stream(getKeyContent(*it));
      ASSERT(stream.good());

      stream >> value;
      return !stream.bad() && !stream.fail();
    }
    return false;
  }

  /**
   * This method writes a value into for the given key in the given section.
   * @param section the section the key is in
   * @param key the key the value belongs to
   * @param value the value that will be written to key
   * @result true if writing was successfull, false otherwise
   * @note if the given section and/or key does not exist it/they will be created
   */
  template<typename T>
  bool IniFile::writeValue(std::string const& section, std::string const& key, T const& value)
  {
    LinePointer it = findOrCreateKey(getSectionString(section), key);
    ASSERT(it != lines_.end());

    std::ostringstream stream;
    ASSERT(stream.good());

    stream << value;

    if (!stream.good())
      return false;

    ASSERTOP(it->find('='), ne, std::string::npos);
    ASSERT(isKeyLine(*it));

    it->replace(it->find('=') + 1, std::string::npos, ' ' + stream.str());
    return true;
  }
}


#endif
