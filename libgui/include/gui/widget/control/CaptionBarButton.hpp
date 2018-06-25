// CaptionBarButton.hpp

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

#ifndef GUICAPTIONBARBUTTON_HPP
#define GUICAPTIONBARBUTTON_HPP

#include "gui/widget/Decorator.hpp"
#include "gui/widget/control/ButtonLogic.hpp"


namespace gui
{
  class CaptionBar;


  /**
   * This class represents a button within a caption bar.
   */
  class LIBGUI_EXPORT CaptionBarButton: public Decorator
  {
  public:
    CaptionBarButton(CaptionBar& caption_bar, Widget& widget);

    virtual void onMouseDown(Position const& position, MouseButton button);
    virtual void onMouseUp(Position const& position, MouseButton button);

    virtual void onClick();

    virtual Position position() const;
    virtual Size     size() const;

    bool isPressed() const;

  protected:
    virtual void renderWidget(Size const& size) const;

    virtual void handlePositionEvent(PositionEvent const& event);

  private:
    ButtonLogic<CaptionBarButton> logic_;

    CaptionBar* caption_bar_;

    bool isPositionInButton(Position const& position) const;
  };
}


namespace gui
{
  /**
   * @return true if button is pressed, false if not
   */
  inline bool CaptionBarButton::isPressed() const
  {
    return logic_.isPressed();
  }
}


#endif
