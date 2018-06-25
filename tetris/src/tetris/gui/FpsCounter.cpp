// FpsCounter.cpp

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

#include <gui/util/LexicalCast.hpp>

#include "tetris/gui/FpsCounter.hpp"


namespace ttrs
{
  /**
   * @copydoc StaticText::StaticText
   */
  FpsCounter::FpsCounter(gui::Bounds const& bounds)
    : StaticText(bounds),
      fps_(0),
      time_(0.0f)
  {
  }

  /**
   * @param time time elapsed since last rendering
   */
  void FpsCounter::update(float time)
  {
    if (shown())
    {
      time_ += time;

      if (time_ >= 1.0f)
      {
        setText(gui::lexicalCast<int, gui::String>(fps_));

        fps_  = 0;
        time_ = 0.0f;
      }
    }
  }

  /**
   * @copydoc StaticText::renderWidget
   */
  void FpsCounter::renderWidget(gui::Size const& size) const
  {
    ++fps_;
    StaticText::renderWidget(size);
  }
}
