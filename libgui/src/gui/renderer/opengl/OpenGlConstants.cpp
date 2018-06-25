// OpenGlConstants.cpp

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

#include <util/Assert.hpp>

#include "OpenGlConstants.hpp"


namespace gui
{
  // the MS compiler complains about double specialization
#ifndef _MS_VER
  /**
   * @todo find a way to find out whether char is signed or not
   */
  template<>
  GLenum getOpenGlConstant(char type)
  {
    return GL_BYTE;
  }
#endif

  template<>
  GLenum getOpenGlConstant(signed char type)
  {
    return GL_BYTE;
  }

  template<>
  GLenum getOpenGlConstant(unsigned char type)
  {
    return GL_UNSIGNED_BYTE;
  }

  template<>
  GLenum getOpenGlConstant(short type)
  {
    return GL_SHORT;
  }

  template<>
  GLenum getOpenGlConstant(unsigned short type)
  {
    return GL_UNSIGNED_SHORT;
  }

  template<>
  GLenum getOpenGlConstant(int type)
  {
    return GL_INT;
  }

  template<>
  GLenum getOpenGlConstant(unsigned int type)
  {
    return GL_UNSIGNED_INT;
  }

  template<>
  GLenum getOpenGlConstant(float type)
  {
    return GL_FLOAT;
  }

  template<>
  GLenum getOpenGlConstant(double type)
  {
    return GL_DOUBLE;
  }

  template<>
  GLenum getOpenGlConstant(long type)
  {
    if (sizeof(long) == sizeof(int))
      return getOpenGlConstant<int>(0);

    ASSERT(false);
  }

  /**
   * @todo this runtime stuff is really bad - find a better way
   *       -> we need another template thing here to match wchar_t to either
   *       int or short or whatever size it matches
   * @todo wchar_t can be signed or unsigned, find a way to differ between that
   */
  template<>
  GLenum getOpenGlConstant(wchar_t type)
  {
    if (sizeof(wchar_t) == sizeof(long))
      return getOpenGlConstant<long>(0);
    if (sizeof(wchar_t) == sizeof(int))
      return getOpenGlConstant<int>(0);
    if (sizeof(wchar_t) == sizeof(short))
      return getOpenGlConstant<short>(0);

    ASSERT(false);
  }
}
