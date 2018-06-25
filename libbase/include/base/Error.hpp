// Error.hpp

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

#ifndef BASEERROR_HPP
#define BASEERROR_HPP

#include "base/Config.hpp"

/**
 * @todo remove typedef
 */
typedef char Char;


namespace base
{
  /**
   * Generally exception class for use in this library. It should also be used
   * as baseclass for user defined errors.
   * This class is exception safe and copyable. It does however not own the
   * message strings nor copy them.
   * Depending on the Char typedef (which depends on tchar.h typedefs) this
   * class can be used with unicode strings or normal strings.
   */
  class LIBBASE_EXPORT Error
  {
  public:
    Error(Char const* message, Char const* cause);
    virtual ~Error();

    Char const* getMessage() const;
    Char const* getCause() const;

  private:
    Char const* message_;
    Char const* cause_;
  };
}


namespace base
{
  /**
   * The constructor creates an error object from a general message and a reason
   * for the error. Note that both messages are simple char arrays, since
   * std::string may throw an exception on construction.
   * @param[in] message general error message
   * @param[in] cause message describing the problem that caused the error
   */
  inline Error::Error(Char const* message, Char const* cause)
    : message_(message),
      cause_(cause)
  {
  }

  /**
   * The destructor is virtual so that derived classes can be created.
   */
  inline Error::~Error()
  {
  }

  /**
   * @return general message given in constructor
   */
  inline Char const* Error::getMessage() const
  {
    return message_;
  }

  /**
   * @return cause message given in constructor
   */
  inline Char const* Error::getCause() const
  {
    return cause_;
  }
}


#endif
