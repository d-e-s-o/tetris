// StatusText.cpp

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
#include <gui/renderer/Font.hpp>
#include <gui/renderer/Renderer.hpp>
#include <gui/widget/RootWidget.hpp>
#include "StatusText.hpp"

namespace sample
{
  StatusText::StatusText(gui::Bounds const& bounds)
    : StaticText(bounds),
      fps_()
  {
    //setBackgroundColor(gui::Color(0xFF, 0xFF, 0xFF, 0xFF));
  }

  void StatusText::setFps(int fps)
  {
    fps_ = gui::lexicalCast<int, gui::String>(fps);
  }

  void StatusText::renderContent(gui::Size const& size) const
  {
    gui::Renderer&   renderer  = rootWidget()->getRenderer();
    gui::Font const& font      = getFont();
    gui::SizeT       font_size = font.size();

    renderer.pushFont(font);
    renderer.pushColor(gui::Color());

    int y = size.y - font_size;
    renderer.renderString(gui::String(TEXT("FPS: ")) + fps_, gui::Point(5, y));

    y -= 2 * font_size;

    gui::String w_str = gui::lexicalCast<int, gui::String>(rootWidget()->size().x);
    gui::String h_str = gui::lexicalCast<int, gui::String>(rootWidget()->size().y);

    renderer.renderString(gui::String(TEXT("RootWidget:")), gui::Point(5, y));
    y -= font_size;
    renderer.renderString(gui::String(TEXT("w: ")) + w_str, gui::Point(10, y));
    y -= font_size;
    renderer.renderString(gui::String(TEXT("h: ")) + h_str, gui::Point(10, y));
    y -= font_size;

    Widget* focused = focusedWidget();

    if (focused != 0)
    {
      gui::String x_str = gui::lexicalCast<int, gui::String>(focused->position().x);
      gui::String y_str = gui::lexicalCast<int, gui::String>(focused->position().y);
      gui::String w_str = gui::lexicalCast<int, gui::String>(focused->size().x);
      gui::String h_str = gui::lexicalCast<int, gui::String>(focused->size().y);

      renderer.renderString(gui::String(TEXT("Fokusiert:")), gui::Point(5, y));
      y -= font_size;
      renderer.renderString(gui::String(TEXT("x: ")) + x_str, gui::Point(10, y));
      y -= font_size;
      renderer.renderString(gui::String(TEXT("y: ")) + y_str, gui::Point(10, y));
      y -= font_size;
      renderer.renderString(gui::String(TEXT("w: ")) + w_str, gui::Point(10, y));
      y -= font_size;
      renderer.renderString(gui::String(TEXT("h: ")) + h_str, gui::Point(10, y));
      y -= font_size;
    }

    renderer.popColor();
    renderer.popFont();
  }
}
