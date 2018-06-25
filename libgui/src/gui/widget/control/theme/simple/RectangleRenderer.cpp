// RectangleRenderer.cpp

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

#include "gui/Margin.hpp"
#include "gui/renderer/Texture.hpp"
#include "gui/renderer/Renderer.hpp"
#include "gui/widget/control/theme/simple/SimpleTextureTheme.hpp"
#include "gui/widget/control/theme/simple/RectangleRenderer.hpp"


namespace gui
{
  namespace
  {
    /**
     *
     */
    inline TextureRectangle convertPixels(Pixels const& pixels, Texture const& texture)
    {
      float w = 1.0f * texture.size().x;
      float h = 1.0f * texture.size().y;

      TextureRectangle coordinates;
      coordinates.x1_ = pixels.x1_ / w;
      coordinates.y1_ = pixels.y1_ / h;
      coordinates.x2_ = pixels.x2_ / w;
      coordinates.y2_ = pixels.y2_ / h;

      return coordinates;
    }

    /**
     * Rectangle Shrinker is the base class for the four side shrinkers (left, right, bottom, top).
     */
    class RectangleShrinker
    {
    public:
      RectangleShrinker(Rectangle& rectangle, Pixels& pixels, Margin const& margin)
        : rectangle_(&rectangle),
          pixels_(&pixels),
          margin_(&margin),
          new_rectangle_(rectangle),
          new_pixels_(pixels)
      {
      }

      template<typename Shrinker>
      RectangleShrinker(Shrinker const& shrinker)
        : rectangle_(&shrinker.new_rectangle_),
          pixels_(&shrinker.new_pixels_),
          margin_(shrinker.margin_),
          new_rectangle_(shrinker.new_rectangle_),
          new_pixels_(shrinker.new_pixels_)
      {
      }

      Rectangle const& getRectangle() const
      {
        return new_rectangle_;
      }

      Pixels const& getPixels() const
      {
        return new_pixels_;
      }

    protected:
      /**
       * We need to store the "parent" rectangle and pixels and modify it later. Margin is not
       * modified however.
       */
      Rectangle*    rectangle_;
      Pixels*       pixels_;
      Margin const* margin_;

      /**
       * Storage for the coordinate and pixel rectangle that is modified
       * @note this is mutable so we can make the copy constructor accept a const referenz which is
       *       necessary for creating temporary objects
       */
      mutable Rectangle new_rectangle_;
      mutable Pixels    new_pixels_;
    };

    /**
     *
     */
    struct LeftShrinker: public RectangleShrinker
    {
      LeftShrinker(Rectangle& rectangle, Pixels& pixels, Margin const& margin)
        : RectangleShrinker(rectangle, pixels, margin)
      {
      }

      template<typename Shrinker>
      LeftShrinker(Shrinker const& shrinker)
        : RectangleShrinker(shrinker)
      {
      }

      void shrink() const
      {
        new_rectangle_.x2_ = new_rectangle_.x1_ + margin_->left;
        new_pixels_.x2_    = new_pixels_.x1_    + margin_->left;
      }

      void shrinkParent() const
      {
        rectangle_->x1_ += margin_->left;
        pixels_->x1_    += margin_->left;
      }
    };

    struct BottomShrinker: public RectangleShrinker
    {
      BottomShrinker(Rectangle& rectangle, Pixels& pixels, Margin const& margin)
        : RectangleShrinker(rectangle, pixels, margin)
      {
      }

      template<typename Shrinker>
      BottomShrinker(Shrinker const& shrinker)
        : RectangleShrinker(shrinker)
      {
      }

      void shrink() const
      {
        new_rectangle_.y2_ = new_rectangle_.y1_ + margin_->bottom;
        new_pixels_.y2_    = new_pixels_.y1_    + margin_->bottom;
      }

      void shrinkParent() const
      {
        rectangle_->y1_ += margin_->bottom;
        pixels_->y1_    += margin_->bottom;
      }
    };

    struct RightShrinker: public RectangleShrinker
    {
      RightShrinker(Rectangle& rectangle, Pixels& pixels, Margin const& margin)
        : RectangleShrinker(rectangle, pixels, margin)
      {
      }

      template<typename Shrinker>
      RightShrinker(Shrinker const& shrinker)
        : RectangleShrinker(shrinker)
      {
      }

      void shrink() const
      {
        new_rectangle_.x1_ = new_rectangle_.x2_ - margin_->right;
        new_pixels_.x1_    = new_pixels_.x2_    - margin_->right;
      }

      void shrinkParent() const
      {
        rectangle_->x2_ -= margin_->right;
        pixels_->x2_    -= margin_->right;
      }
    };

    struct TopShrinker: public RectangleShrinker
    {
      TopShrinker(Rectangle& rectangle, Pixels& pixels, Margin const& margin)
        : RectangleShrinker(rectangle, pixels, margin)
      {
      }

      template<typename Shrinker>
      TopShrinker(Shrinker const& shrinker)
        : RectangleShrinker(shrinker)
      {
      }

      void shrink() const
      {
        new_rectangle_.y1_ = new_rectangle_.y2_ - margin_->top;
        new_pixels_.y1_    = new_pixels_.y2_    - margin_->top;
      }

      void shrinkParent() const
      {
        rectangle_->y2_ -= margin_->top;
        pixels_->y2_    -= margin_->top;
      }
    };
  }


  /**
   *
   */
  void RectangleRenderer::render(Rectangle const& rectangle, Pixels const& pixels, Color const& color, Margin const& margin) const
  {
    Renderer& renderer = theme_->getRenderer();

    renderer.pushTexture(&theme_->getTexture());
    renderer.pushColor(color);

    renderWithMargin(rectangle, pixels, margin);

    renderer.popColor();
    renderer.popTexture();
  }

  /**
   *
   */
  void RectangleRenderer::renderWithMargin(Rectangle rectangle, Pixels pixels, Margin const& margin) const
  {
    if (margin.left > 0)
    {
      LeftShrinker left(rectangle, pixels, margin);
      left.shrink();

      if (margin.bottom > 0)
        renderShrinker(BottomShrinker(left));

      if (margin.top > 0)
        renderShrinker(TopShrinker(left));

      renderRectangle(left.getRectangle(), left.getPixels());
      left.shrinkParent();
    }

    if (margin.right > 0)
    {
      RightShrinker right(rectangle, pixels, margin);
      right.shrink();

      if (margin.bottom > 0)
        renderShrinker(BottomShrinker(right));

      if (margin.top > 0)
        renderShrinker(TopShrinker(right));

      renderRectangle(right.getRectangle(), right.getPixels());
      right.shrinkParent();
    }

    if (margin.bottom > 0)
      renderShrinker(BottomShrinker(rectangle, pixels, margin));

    if (margin.top > 0)
      renderShrinker(TopShrinker(rectangle, pixels, margin));

    renderRectangle(rectangle, pixels);
  }

  /**
   *
   */
  inline void RectangleRenderer::renderRectangle(Rectangle const& rectangle, Pixels const& pixels) const
  {
    TextureRectangle coords = convertPixels(pixels, theme_->getTexture());

    Renderer& renderer = theme_->getRenderer();
    renderer.renderRectangle(rectangle, coords);
  }

  /**
   *
   */
  template<typename Shrinker>
  inline void RectangleRenderer::renderShrinker(Shrinker const& shrinker) const
  {
    shrinker.shrink();
    renderRectangle(shrinker.getRectangle(), shrinker.getPixels());
    shrinker.shrinkParent();
  }
}
