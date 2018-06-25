// Score.cpp

/***************************************************************************
 *   Copyright (C) 2013-2014 Daniel Mueller (deso@posteo.net)              *
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

#include "tetris/game/Score.hpp"


namespace ttrs
{
  /**
   * @param start_level
   * @param lines_for_level
   */
  Score::Score(int start_level, int lines_for_level)
    : level_(start_level),
      points_(0),
      lines_(0),
      lines_for_level_(lines_for_level),
      lines_since_up_(0)
  {
  }

  /**
   * @param lines
   */
  void Score::add(int lines)
  {
    // @todo strictly speaking the point calculation is wrong: if lines_for_level_ is a low value
    //       (e.g. 1) then the points will be calculated based only on the current level - though
    //       the level would increase after some lines are cleared (e.g. lines is 4 then the
    //       increase could be 4 levels) - however it should be quite impossible to change this
    //       because the points depend on the number of lines cleared and is not limited so we
    //       cannot split the calculation, increase the level and continue
    points_         += calculatePoints(lines);
    lines_          += lines;
    lines_since_up_ += lines;
    level_          += lines_since_up_ / lines_for_level_;
    lines_since_up_ %= lines_for_level_;
  }

  /**
   * This method is used to calculate the number of points for the given number of cleared
   * lines based on the current level.
   */
  int Score::calculatePoints(int lines) const
  {
    ASSERTOP(lines, gt, 0);
    return 5 * (lines * lines) * level_;
  }
}
