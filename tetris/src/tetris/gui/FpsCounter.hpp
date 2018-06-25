// FpsCounter.hpp

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

#ifndef TTRSFPSCOUNTER_HPP
#define TTRSFPSCOUNTER_HPP

#include <gui/widget/control/StaticText.hpp>


namespace ttrs
{
  /**
   * This class represents a small text capable of counting and displaying the frames per second.
   */
  class FpsCounter: public gui::StaticText
  {
  public:
    FpsCounter(gui::Bounds const& bounds);

    void update(float time);

  protected:
    virtual void renderWidget(gui::Size const& size) const;

  private:
    mutable int fps_;

    float time_;
  };
}


#endif
