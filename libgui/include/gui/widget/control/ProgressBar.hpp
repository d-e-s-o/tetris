// ProgressBar.hpp

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

#ifndef GUIPROGRESSBAR_HPP
#define GUIPROGRESSBAR_HPP

#include "gui/widget/Widget.hpp"


namespace gui
{
  class Font;


  /**
   * This class represents controls that symbol a progress of an action. It has a variable range
   * the progress can be set within, howevery only current percentual value will be displayed
   * (0% - 100%).
   */
  class LIBGUI_EXPORT ProgressBar: public Widget
  {
  public:
    ProgressBar(Bounds const& bounds);

    int getProgress() const;
    void setProgress(int progress);

    int getMinValue() const;
    int getMaxValue() const;

    Font const& getFont() const;

    SizeT getBarSpace() const;

  protected:
    virtual void renderWidget(Size const& size) const;
    virtual void renderContent(Size const& size) const;

  private:
    int progress_;
  };
}


namespace gui
{
  /**
   * @return current progress value
   */
  inline int ProgressBar::getProgress() const
  {
    return progress_;
  }

  /**
   * @param progress new progress value to set
   */
  inline void ProgressBar::setProgress(int progress)
  {
    int min = getMinValue();
    int max = getMaxValue();

    if (progress <= min)
      progress_ = min;
    else if (progress >= max)
      progress_ = max;
    else
      progress_ = progress;
  }

  /**
   * @return minimal value the ProgressBar represents when "empty"
   */
  inline int ProgressBar::getMinValue() const
  {
    return 0;
  }

  /**
   * @return maximal value the ProgressBar represents when "full"
   */
  inline int ProgressBar::getMaxValue() const
  {
    return 100;
  }
}


#endif
