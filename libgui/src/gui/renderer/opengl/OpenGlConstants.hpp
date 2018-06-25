// OpenGlFunctions.hpp

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

#ifndef GUIOPENGLCONSTANTS_HPP
#define GUIOPENGLCONSTANTS_HPP

#include "gui/include/OpenGl.hpp"


namespace gui
{
  /**
   * This template function returns the OpenGL constant representing a type.
   * P.ex. int -> GL_INT, float -> GL_FLOAT
   * @param type variable of type T to which the OpenGL constant is of interest
   * @return symbolic constant representing the type
   * @todo check if the OpenGL constants represent the size of a type
   *       (int == 4, short == 2) or a type (int could be 4 or 8 or ...)
   */
  template<typename T>
  GLenum getOpenGlConstant(T type);
}


#endif
