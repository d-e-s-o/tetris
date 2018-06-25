// OpenGlDisplayLists.hpp

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

#ifndef OPENGLDISPLAYLISTS_HPP
#define OPENGLDISPLAYLISTS_HPP

#include "gui/Error.hpp"
#include "gui/include/OpenGl.hpp"


namespace gui
{
  /**
   * This class represents OpenGL Display Lists. It only manages the creation and destruction of the
   * ID's. You have to call glNewList for every id (which ranges from getBase() to getBase() +
   * getCount()).
   */
  class LIBGUI_EXPORT OpenGlDisplayLists
  {
  public:
    OpenGlDisplayLists(GLsizei count);
    ~OpenGlDisplayLists();

    GLuint getBase() const;
    GLsizei getCount() const;

  private:
    GLuint base_;
    GLsizei count_;

    OpenGlDisplayLists(OpenGlDisplayLists const&);
    OpenGlDisplayLists& operator =(OpenGlDisplayLists const&);
  };
}


namespace gui
{
  /**
   * @param[in] count number of display lists to allocate
   * @throw Error if the numer of display lists to create is invalid (e.g. 0) or if OpenGl fails to
   *        create the lists
   * @todo move this into a cpp file
   */
  inline OpenGlDisplayLists::OpenGlDisplayLists(GLsizei count)
    : base_(0),
      count_(count)
  {
    if (count_ > 0)
    {
      base_ = glGenLists(count);

      if (base_ <= 0)
        throw Error(TEXT("Error creating OpenGL display lists"), TEXT("glGenLists returned error code"));
    }
    else
      throw Error(TEXT("Error creating OpenGL display lists"), TEXT("Unable to create zero lists"));
  }

  /**
   * The destructor free's the allocated list ID's
   */
  inline OpenGlDisplayLists::~OpenGlDisplayLists()
  {
    glDeleteLists(base_, count_);
  }

  /**
   * @return base list id
   */
  inline GLuint OpenGlDisplayLists::getBase() const
  {
    return base_;
  }

  /**
   * @return number of lists allocated
   */
  inline GLsizei OpenGlDisplayLists::getCount() const
  {
    return count_;
  }
}


#endif
