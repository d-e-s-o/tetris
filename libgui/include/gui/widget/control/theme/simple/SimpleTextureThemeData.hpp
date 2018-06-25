// SimpleTextureThemeData.hpp

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

#ifndef GUISIMPLETEXTURETHEMEDATA_HPP
#define GUISIMPLETEXTURETHEMEDATA_HPP

#include "gui/Config.hpp"
#include "gui/renderer/Rectangle.hpp"


namespace gui
{
  typedef Rectangle Pixels;


  /**
   *
   */
  class LIBGUI_EXPORT SimpleTextureThemeData
  {
  public:
    struct WidgetCoordinates
    {
      Pixels widget_;
    };

    struct ButtonCoordinates: public WidgetCoordinates
    {
      Pixels widget_pressed_;

      Pixels::Type left_margin_;
      Pixels::Type right_margin_;
    };

    struct CheckBoxCoordinates: public WidgetCoordinates
    {
      Pixels box_;
      Pixels box_checked_;
    };

    struct EditBoxCoordinates: public WidgetCoordinates
    {
      Pixels::Type left_margin_;
      Pixels::Type bottom_margin_;
      Pixels::Type right_margin_;
      Pixels::Type top_margin_;
    };

    struct SliderCoordinates: public WidgetCoordinates
    {
      Pixels line_;
      Pixels slider_;
    };

    struct ProgressBarCoordinates: public WidgetCoordinates
    {
      Pixels bar_;

      Pixels::Type left_margin_;
      Pixels::Type right_margin_;
    };

    struct PictureCoordinates: public WidgetCoordinates
    {
      Pixels picture_empty_;
    };

    struct CaptionBarCoordinates: public WidgetCoordinates
    {
      Pixels::Type left_margin_;
      Pixels::Type right_margin_;
    };

    struct CaptionBarButtonCoordinates: public WidgetCoordinates
    {
      Pixels widget_pressed_;
    };

    struct BorderCoordinates
    {
      Pixels bottom_;
      Pixels right_;
      Pixels top_;
      Pixels left_;

      Pixels::Type margin_left_right_;
    };


    WidgetCoordinates           static_text_;
    ButtonCoordinates           button_;
    CheckBoxCoordinates         check_box_;
    EditBoxCoordinates          edit_box_;
    SliderCoordinates           slider_;
    ProgressBarCoordinates      progress_bar_;
    PictureCoordinates          picture_;
    WidgetCoordinates           group_box_;
    WidgetCoordinates           dialog_;
    CaptionBarCoordinates       caption_bar_;
    CaptionBarButtonCoordinates caption_bar_button_;
    BorderCoordinates           border_;
  };
}


#endif
