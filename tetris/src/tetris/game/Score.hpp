// Score.hpp

/***************************************************************************
 *   Copyright (C) 2013 Daniel Mueller (deso@posteo.net)                   *
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

#ifndef TTRSSCORE_HPP
#define TTRSSCORE_HPP


namespace ttrs
{
  class Score
  {
  public:
    Score(int start_level, int lines_for_level);

    void add(int lines);

    int level() const;
    int points() const;
    int lines() const;

  private:
    int level_;
    int points_;
    int lines_;
    int lines_for_level_;
    int lines_since_up_;

    int calculatePoints(int lines) const;
  };
}


namespace ttrs
{
  /**
   * @return
   */
  inline int Score::level() const
  {
    return level_;
  }

  /**
   * @return
   */
  inline int Score::points() const
  {
    return points_;
  }

  /**
   * @return
   */
  inline int Score::lines() const
  {
    return lines_;
  }
}


#endif
