// IniFile.cpp

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
#include <functional>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <util/Assert.hpp>

#include "base/IniFile.hpp"


namespace base
{
  namespace
  {
    /**
     * This class is a functor wrapper around std::isspace for use with algorithms.
     */
    struct IsSpace: std::unary_function<int, bool>
    {
      /**
       * @return true if the given char is a whitespace character, false if not
       */
      bool operator()(int c) const
      {
        return std::isspace(c) != 0;
      }
    };

    /**
     * @param string string to trim on the left
     * @return string with removed white spaces on the left
     */
    inline std::string trimLeft(std::string s)
    {
      s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(IsSpace())));
      return s;
    }

    /**
     * @param string string to trim on the right
     * @return string with removed white spaces on the right
     */
    inline std::string trimRight(std::string s)
    {
      s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(IsSpace())).base(), s.end());
      return s;
    }

    /**
     * @param string string to trim
     * @return string with removed white spaces on the left and the right
     */
    inline std::string trim(std::string const& s)
    {
      return trimLeft(trimRight(s));
    }

    /**
     * Functor for checking if a line contains a given section
     */
    struct IsEqualSection: std::binary_function<std::string, std::string, bool>
    {
      /**
       * @param line line to check for equality to section
       * @param section section to check for equality to line (trimmed)
       * @return true if the line contains the section
       */
      bool operator()(std::string line, std::string const& section) const
      {
        return trim(line) == section;
      }
    };
  }


  /**
   * The default constructor creates an empty IniFile object.
   */
  IniFile::IniFile()
    : lines_(0)
  {
  }

  /**
   * This method creates an IniFile object from the given file. It calls the loadFromFile() method
   * to load its content into the memory.
   * @param filename filename of file to create the ini from
   */
  IniFile::IniFile(std::string const& filename)
    : lines_(0)
  {
    // check if the file exists, if not we do not have to load anything but everything is fine
    {
      std::ifstream stream(filename.c_str());

      if (!stream.is_open())
        return;
    }

    if (!loadFromFile(filename))
      throw std::runtime_error("Error loading file");
  }

  /**
   * This method loads the ini from the given file.
   * @param filename filename to load the ini from
   * @return true on success, false otherwise
   * @note if this method fails (returns false) there wont be any data in memory, but the new
   *       filename will be set
   */
  bool IniFile::loadFromFile(std::string const& filename)
  {
    std::ifstream file(filename.c_str());
    std::string   line;

    lines_.clear();

    if (file.fail())
      return false;

    while (std::getline(file, line))
      lines_.push_back(line);

    // fail bit gets set pretty often; in case we stopped only due to EOF we assume everything is
    // good, otherwise something must have gone wrong
    if (!file.eof())
    {
      lines_.clear();
      return false;
    }
    return true;
  }

  /**
   * This method saves the ini to the given file.
   * @param filename filename to save the ini to
   * @return true on success, false otherwise
   */
  bool IniFile::saveToFile(std::string const& filename) const
  {
    std::ofstream file(filename.c_str(), std::ios::out | std::ios::trunc);

    if (!file.good())
      return false;

    std::copy(lines_.begin(), lines_.end(), std::ostream_iterator<std::string>(file, "\n"));

    return file.good();
  }

  /**
   * @param section section to search for
   * @param begin pointer to line to begin search at
   * @return pointer to line containing the given section
   */
  IniFile::LinePointer IniFile::findSection(std::string const& section, LinePointer begin) const
  {
    ASSERT(section == trim(section));
    ASSERT(isSectionString(section));

    return std::find_if(begin, lines_.end(), std::bind2nd(IsEqualSection(), section));
  }

  /**
   * This method searches for the last occurrence of a section.
   * @param section section string to search for
   * @return pointer to line containing the given section
   */
  IniFile::LinePointer IniFile::findLastSection(std::string const& section) const
  {
    ASSERT(section == trim(section));
    ASSERT(isSectionString(section));

    Lines::reverse_iterator it = std::find_if(lines_.rbegin(),
                                              lines_.rend(),
                                              std::bind2nd(IsEqualSection(), section));

    if (it != lines_.rend())
      return it.base();

    return lines_.end();
  }

  /**
   * @param section section to search for that should contain key
   * @param key key to search for within the given section
   * @return iterator to line containing the given key
   */
  IniFile::LinePointer IniFile::findKey(std::string const& section, std::string const& key) const
  {
    ASSERT(section == trim(section));
    ASSERT(isSectionString(section));

    LinePointer it = lines_.begin();

    while (it = findSection(section, it), it != lines_.end())
    {
      for (++it; it != lines_.end(); ++it)
      {
        // if we found another section continue searching the "right" one
        if (isSectionString(*it) && !IsEqualSection()(*it, section))
          break;

        if (isKeyLine(*it, key))
          return it;
      }
    }
    return lines_.end();
  }

  /**
   * This method searches for a key and if it could not find it it creates it.
   * @param section section the key belongs to (trimmed)
   * @param key key to search for
   * @return pointer to line containing the key
   */
  IniFile::LinePointer IniFile::findOrCreateKey(std::string const& section, std::string const& key) const
  {
    ASSERT(section == trim(section));
    ASSERT(isSectionString(section));

    LinePointer it = findKey(section, key);

    if (it == lines_.end())
    {
      // if we did not find the key, we search for the last key in the section to append the new
      // one
      it = findLastKey(section);

      if (it == lines_.end())
      {
        lines_.push_back(section);
        it = lines_.end();
      }
      else
        ++it;

      it = lines_.insert(it, key + " =");
    }
    return it;
  }

  /**
   * This method searches all keys in a section and returns an iterator to the last key. If a
   * section exist multiple times the last occurrence of it is used.
   * If a section is empty the index points to the section title.
   * @param section section to get last key of
   * @return iterator to the last key in the given section, or lines_.end() if the given section
   *         could not be found
   */
  IniFile::LinePointer IniFile::findLastKey(std::string const& section) const
  {
    ASSERT(section == trim(section));
    ASSERT(isSectionString(section));

    LinePointer it = findLastSection(section);

    if (it == lines_.end())
      return it;

    // within that section we search for the last key
    LinePointer last_it = it;

    for (++it; it != lines_.end(); ++it)
    {
      if (isSectionString(*it))
        return last_it;

      if (isKeyLine(*it))
        last_it = it;
    }
    return last_it;
  }

  /**
   * @param s string to check if it is a valid section string
   * @return true if the given value is a valid section string, false if not
   */
  bool IniFile::isSectionString(std::string s) const
  {
    s = trim(s);

    std::string::size_type l = s.length();

    return (l > 2) && (s[0] == '[') && (s[l - 1] == ']');
  };

  /**
   * @param s string to make a valid section string
   * @return section string created from given string
   */
  std::string IniFile::getSectionString(std::string const& s) const
  {
    if (isSectionString(s))
      return s;

    return '[' + s + ']';
  }

  /**
   * @param line line of the ini
   * @return true if the given line is a valid line with key, false if not
   */
  bool IniFile::isKeyLine(std::string const& line) const
  {
    std::string::size_type i = line.find('=');

    if (i != std::string::npos)
      return !trim(line.substr(0, i)).empty();

    return false;
  }

  /**
   * @param line line of the ini
   * @param key key to check if it is part of the line
   * @return true if the line contains key and forms a valid line with it
   */
  bool IniFile::isKeyLine(std::string const& line, std::string const& key) const
  {
    std::string::size_type i1 = line.find(key);
    std::string::size_type i2 = line.find('=');

    if (i1 != std::string::npos && i2 != std::string::npos)
    {
      if (trim(line.substr(0, i1)).empty())
      {
        i1 += key.length();
        return trim(line.substr(i1, i2 - i1)).empty();
      }
    }
    return false;
  }

  /**
   * @param line line with key
   * @return content belonging to key (trimmed)
   */
  std::string IniFile::getKeyContent(std::string const& line) const
  {
    ASSERTOP(line.find('='), ne, std::string::npos);

    return trim(line.substr(line.find('=') + 1));
  }
}
