// CaptionBar.hpp

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

#ifndef GUICAPTIONBAR_HPP
#define GUICAPTIONBAR_HPP

#include "gui/String.hpp"
#include "gui/widget/Decorator.hpp"
#include "gui/widget/control/CaptionBarButton.hpp"
#include "gui/widget/control/CaptionBarLogic.hpp"


namespace gui
{
  class Font;


  /**
   * This class is used to implement the CaptionBar. It shrinks the client area the caption bar is
   * in. This is necessary because the CaptionBar itself cannot shrink it because then it could not
   * have a button on it. That is, however, by design.
   */
  class LIBGUI_EXPORT CaptionBarArea: public Decorator
  {
  public:
    CaptionBarArea(CaptionBar const& caption_bar, Widget& widget);

  protected:
    virtual void shrinkClientArea(Bounds& bounds) const;

  private:
    friend class CaptionBar;

    CaptionBar const* caption_bar_;
  };


  /**
   * The caption bar decorates a Dialog so that it can be moved with the mouse and also be closed.
   * It therefor consists of two other decorators: a button and another that is only used for
   * shrinking the client area.
   */
  class LIBGUI_EXPORT CaptionBar: public Decorator
  {
  public:
    CaptionBar(Widget& widget);

    virtual void onMouseDown(Position const& position, MouseButton button);
    virtual void onMouseUp(Position const& position, MouseButton button);
    virtual void onMouseMove(Position const& position);

    virtual void onClose();

    virtual Position position() const;
    virtual Size     size() const;

    String const& getCaption() const;
    void setCaption(String const& caption);

    Font const& getFont() const;

    SizeT height() const;
    SizeT textSpace() const;
    SizeT buttonSpace() const;

  protected:
    virtual void renderWidget(Size const& size) const;

    virtual void handlePositionEvent(PositionEvent const& event);

    virtual Decorator& getFirst();
    virtual Decorator& getLast();

    virtual bool isChild(Decorator const& decorator) const;

  private:
    CaptionBarButton button_;
    CaptionBarArea   area_;

    CaptionBarLogic<CaptionBar> logic_;

    String caption_;

    bool isPositionInCaptionBar(Position const& position) const;
  };
}


namespace gui
{
  /**
   * @return caption to be displayed in the bar
   */
  inline String const& CaptionBar::getCaption() const
  {
    return caption_;
  }

  /**
   * @param caption new caption to be displayed
   */
  inline void CaptionBar::setCaption(String const& caption)
  {
    caption_ = caption;
  }
}


#endif
