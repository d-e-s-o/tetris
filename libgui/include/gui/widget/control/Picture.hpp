// Picture.hpp

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

#ifndef GUIPICTURE_HPP
#define GUIPICTURE_HPP

#include "gui/widget/Widget.hpp"


namespace gui
{
  class Texture;


  /**
   *
   */
  class LIBGUI_EXPORT Picture: public Widget
  {
  public:
    Picture(Bounds const& bounds);

    Texture const* getPicture() const;
    void setPicture(Texture const* picture);

    SizeT getPictureSpace() const;

  protected:
    virtual void renderWidget(Size const& size) const;
    virtual void renderContent(Size const& size) const;

  private:
    Texture const* picture_;
  };
}


namespace gui
{
  /**
   *
   */
  inline Texture const* Picture::getPicture() const
  {
    return picture_;
  }

  /**
   *
   */
  inline void Picture::setPicture(Texture const* picture)
  {
    picture_ = picture;
  }
}


#endif
