// GdiFont.hpp

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

#ifndef GUIGDIFONT_HPP
#define GUIGDIFONT_HPP

#include "gui/String.hpp"
#include "gui/font/Font.hpp"


namespace gui
{
  class GdiFont: public Font
  {
  public:
    GdiFont(String const& filename, SizeT size, Color const& color);

    virtual void renderText(String const& string, Coordinate x, Coordinate y) const;
    virtual void calculateTextSize(String const& string, Coordinate& width, Coordinate& height) const;

    virtual SizeT size() const;
    virtual Color const& getColor() const;

  private:
    Color color_;
    SizeT size_;
  };
}


#endif
