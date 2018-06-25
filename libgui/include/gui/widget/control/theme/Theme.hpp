// Theme.hpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#ifndef GUITHEME_HPP
#define GUITHEME_HPP

#include <util/Assert.hpp>
#include <window/Key.hpp>
#include <window/MouseButton.hpp>

#include "gui/Size.hpp"
#include "gui/String.hpp"
#include "gui/Color.hpp"
#include "gui/Allocator.hpp"


namespace gui
{
  class Renderer;
  class Font;

  class StaticText;
  class Button;
  class CheckBox;
  class EditBox;
  class Slider;
  class ProgressBar;
  class Picture;
  class GroupBox;
  class Dialog;
  class CaptionBar;
  class CaptionBarButton;
  class Border;


  /**
   * This class is the base class for themes to be used for rendering controls. In general controls
   * share the same theme, as it is registered at the RootWidget. A theme should provide the same
   * look and feel for all controls.
   * @note due to RenderWidget and RenderContent being template methods one can actually extend
   *       widgets (like ExtendedButton) INCLUDING their interface. E.g. if you want the user to be
   *       able to set the background color for each widget, you can provide a method like
   *       SetBackgroundColor in the different widgets and the (also extended) theme can use it.
   * @note a Theme is always bound to a Renderer - this may first seem strange, but:
   *       - a theme (object) belongs to exactly one RootWidget
   *       - a RootWidget has exactly one Renderer, which cannot be changed later on
   *       -> therefor it makes sense, so a theme can also store a font, and the Widget itself does
   *          not
   *       - a texture theme would be really strange to implement if a theme could be used by many
   *         Renderers
   * @todo all the data stuff (FontData and control themes) should use virtual methods
   *       instead of all those public members - that would make overriding easy (as easy as now
   *       but maybe a bit more noticeable) and more secure because abstract methods cause compile
   *       errors if not defined later)
   */
  class LIBGUI_EXPORT Theme
  {
  protected:
    /**
     * Forward declaration for the actual control theme class.
     */
    template<typename WidgetT>
    struct ControlTheme;

  public:
    /**
     * Structure used for grouping different font values, pretty often appearing within the
     * same context.
     */
    struct FontData
    {
      String font_name;
      Color  font_color;
      SizeT  font_size;
    };


    template<typename CreatorT>
    Theme(Renderer& renderer, CreatorT const& creator);

    virtual ~Theme() = 0;

    /**
     * This is the access function for the different control themes. It is a template so it can be
     * extended later.
     * @return theme for the given type of control
     */
    template<typename WidgetT>
    ControlTheme<WidgetT> const& getControlTheme() const;

    virtual wnd::MouseButton actionButton() const = 0;
    virtual wnd::MouseButton menuButton() const = 0;

    virtual wnd::Key actionKey() const = 0;
    virtual wnd::Key leftKey() const = 0;
    virtual wnd::Key rightKey() const = 0;

    Renderer& getRenderer();

  protected:
    /**
     * This is the base class for all control themes. It takes a theme during construction and
     * allows later access to it (thats important for the control themes to be able to access the
     * renderer).
     */
    struct ControlThemeBase
    {
      virtual ~ControlThemeBase() = 0;

    protected:
      virtual Theme& getTheme() const = 0;
    };

    /**
     *
     */
    template<typename BaseT, typename ThemeT>
    class IntermediateControlTheme: public BaseT
    {
    public:
      IntermediateControlTheme(ThemeT& theme);

    protected:
      virtual ThemeT& getTheme() const;

    private:
      ThemeT* theme_;
    };

    /**
     * This class can be used for creating control themes. Instances of this class can be passed
     * to the constructor of Theme.
     * @see Theme::Theme
     * @note ControlThemeT has to be first template parameter, otherwise SunStudio complains
     */
    template<template<class> class ControlThemeT, typename ThemeT>
    class ControlThemeCreator
    {
    public:
      ControlThemeCreator(ThemeT& theme);

      template<typename WidgetT, template<class> class AllocatorT>
      ControlThemeT<WidgetT>* create() const;

    private:
      ThemeT* theme_;
    };

    template<typename WidgetT>
    void destroyControlTheme(ControlTheme<WidgetT>* control_theme);

  private:
    Renderer* renderer_;

    /**
     * Following are the control theme variables. When constructing the theme the control theme
     * creator is used to assign objects to theme.
     * @todo this allocator stuff is really nasty, improve it or remove it entirely
     * @todo having raw pointers here is pretty unsafe, use ptr::UniquePointer here
     */
    ControlTheme<StaticText>*       static_text_theme_;
    ControlTheme<Button>*           button_theme_;
    ControlTheme<CheckBox>*         check_box_theme_;
    ControlTheme<EditBox>*          edit_box_theme_;
    ControlTheme<Slider>*           slider_theme_;
    ControlTheme<ProgressBar>*      progress_bar_theme_;
    ControlTheme<Picture>*          picture_theme_;
    ControlTheme<GroupBox>*         group_box_theme_;
    ControlTheme<Dialog>*           dialog_theme_;
    ControlTheme<CaptionBar>*       caption_bar_theme_;
    ControlTheme<CaptionBarButton>* caption_bar_button_theme_;
    ControlTheme<Border>*           border_theme_;

    void destroy();
  };
}


namespace gui
{
  /**
   * The constructor creates a new theme object. It uses the supplied creator object for creating
   * the control themes.
   * @param renderer renderer to be used by this theme
   * @param creator object for creating the control themes
   * @note the creator object CAN be an instance of ControlThemeCreator, it does not have to -
   *       however it has to have the same interface (create() method)
   * @see SimpleTheme::SimpleTheme
   */
  template<typename CreatorT>
  Theme::Theme(Renderer& renderer, CreatorT const& creator)
    : renderer_(&renderer),
      static_text_theme_(nullptr),
      button_theme_(nullptr),
      check_box_theme_(nullptr),
      edit_box_theme_(nullptr),
      slider_theme_(nullptr),
      progress_bar_theme_(nullptr),
      picture_theme_(nullptr),
      group_box_theme_(nullptr),
      dialog_theme_(nullptr),
      caption_bar_theme_(nullptr),
      caption_bar_button_theme_(nullptr),
      border_theme_(nullptr)
  {
    try
    {
      static_text_theme_        = creator.template create<StaticText, Allocator::rebind>();
      button_theme_             = creator.template create<Button, Allocator::rebind>();
      check_box_theme_          = creator.template create<CheckBox, Allocator::rebind>();
      edit_box_theme_           = creator.template create<EditBox, Allocator::rebind>();
      slider_theme_             = creator.template create<Slider, Allocator::rebind>();
      progress_bar_theme_       = creator.template create<ProgressBar, Allocator::rebind>();
      picture_theme_            = creator.template create<Picture, Allocator::rebind>();
      group_box_theme_          = creator.template create<GroupBox, Allocator::rebind>();
      dialog_theme_             = creator.template create<Dialog, Allocator::rebind>();
      caption_bar_theme_        = creator.template create<CaptionBar, Allocator::rebind>();
      caption_bar_button_theme_ = creator.template create<CaptionBarButton, Allocator::rebind>();
      border_theme_             = creator.template create<Border, Allocator::rebind>();
    }
    catch(...)
    {
      destroy();
      throw;
    }
  }

  /**
   * @return renderer used by this theme
   */
  inline Renderer& Theme::getRenderer()
  {
    return *renderer_;
  }

  /**
   * @param theme theme the control theme belongs to
   */
  template<template<class> class ControlThemeT, typename ThemeT>
  Theme::ControlThemeCreator<ControlThemeT, ThemeT>::ControlThemeCreator(ThemeT& theme)
    : theme_(&theme)
  {
  }

  /**
   * @return created control theme
   */
  template<template<class> class ControlThemeT, typename ThemeT>
  template<typename WidgetT, template<class> class AllocatorT>
  ControlThemeT<WidgetT>* Theme::ControlThemeCreator<ControlThemeT, ThemeT>::create() const
  {
    typedef ControlThemeT<WidgetT> T;

    typename AllocatorT<T>::other allocator;

    T* result = allocator.allocate(1);
    ASSERTOP(result, ne, nullptr);
    allocator.construct(result, T(*theme_));

    return result;
  }

  /**
   * This method destroys the given control theme.
   */
  template<typename WidgetT>
  void Theme::destroyControlTheme(ControlTheme<WidgetT>* control_theme)
  {
    if (control_theme != nullptr)
    {
      typedef typename Allocator::rebind<ControlTheme<WidgetT> >::other Allocator;

      Allocator allocator;

      allocator.destroy(control_theme);
      allocator.deallocate(control_theme, 1);
    }
  }

  /**
   * @param theme theme the control theme belongs to
   */
  template<typename BaseT, typename ThemeT>
  inline Theme::IntermediateControlTheme<BaseT, ThemeT>::IntermediateControlTheme(ThemeT& theme)
    : BaseT(theme),
      theme_(&theme)
  {
  }

  /**
   * @return theme the control theme belongs to
   */
  template<typename BaseT, typename ThemeT>
  inline ThemeT& Theme::IntermediateControlTheme<BaseT, ThemeT>::getTheme() const
  {
    return *theme_;
  }

  /**
   *
   */
  template<>
  struct Theme::ControlTheme<StaticText>: public ControlThemeBase
  {
    Color bkgd_color;

    FontData font_data;
    Font*    font;

    SizeT text_space;

    ControlTheme(Theme& theme);

    virtual void renderWidget(StaticText const& widget, Size const& size) const = 0;
    virtual void renderContent(StaticText const& widget, Size const& size) const = 0;
  };

  template<>
  struct Theme::ControlTheme<Button>: public ControlThemeBase
  {
    Color press_color;
    Color bkgd_color;

    SizeT text_space;

    FontData font_data;
    Font*    font;

    ControlTheme(Theme& theme);

    virtual void renderWidget(Button const& widget, Size const& size) const = 0;
    virtual void renderContent(Button const& widget, Size const& size) const = 0;
  };

  template<>
  struct Theme::ControlTheme<CheckBox>: public ControlThemeBase
  {
    Color no_check_color;
    Color check_color;
    Color bkgd_color;

    FontData font_data;
    Font*    font;

    SizeT rectangle_space;
    SizeT text_space;

    ControlTheme(Theme& theme);

    virtual void renderWidget(CheckBox const& widget, Size const& size) const = 0;
    virtual void renderContent(CheckBox const& widget, Size const& size) const = 0;
  };

  template<>
  struct Theme::ControlTheme<EditBox>: public ControlThemeBase
  {
    Color select_color;
    Color bkgd_color;

    FontData font_data;
    Font*    font;

    SizeT text_space;

    ControlTheme(Theme& theme);

    virtual void renderWidget(EditBox const& widget, Size const& size) const = 0;
    virtual void renderContent(EditBox const& widget, Size const& size) const = 0;
  };

  template<>
  struct Theme::ControlTheme<Slider>: public ControlThemeBase
  {
    Color line_color;
    Color slider_color;
    Color bkgd_color;

    SizeT line_space;
    SizeT line_height;
    SizeT slider_space;
    SizeT slider_width;

    ControlTheme(Theme& theme);

    virtual void renderWidget(Slider const& widget, Size const& size) const = 0;
    virtual void renderContent(Slider const& widget, Size const& size) const = 0;
  };

  template<>
  struct Theme::ControlTheme<ProgressBar>: public ControlThemeBase
  {
    Color line_color;
    Color bar_color;
    Color bkgd_color;

    FontData font_data;
    Font*    font;

    SizeT bar_space;

    ControlTheme(Theme& theme);

    virtual void renderWidget(ProgressBar const& widget, Size const& size) const = 0;
    virtual void renderContent(ProgressBar const& widget, Size const& size) const = 0;
  };

  template<>
  struct Theme::ControlTheme<Picture>: public ControlThemeBase
  {
    Color blend_color;
    Color bkgd_color;

    SizeT picture_space;

    ControlTheme(Theme& theme);

    virtual void renderWidget(Picture const& widget, Size const& size) const = 0;
    virtual void renderContent(Picture const& widget, Size const& size) const = 0;
  };

  template<>
  struct Theme::ControlTheme<GroupBox>: public ControlThemeBase
  {
    Color bkgd_color;

    FontData font_data;
    Font*    font;

    ControlTheme(Theme& theme);

    virtual void renderWidget(GroupBox const& widget, Size const& size) const = 0;
    virtual void renderContent(GroupBox const& widget, Size const& size) const = 0;
  };

  template<>
  struct Theme::ControlTheme<Dialog>: public ControlThemeBase
  {
    Color bkgd_color;

    ControlTheme(Theme& theme);

    virtual void renderWidget(Dialog const& widget, Size const& size) const = 0;
    virtual void renderContent(Dialog const& widget, Size const& size) const = 0;
  };

  template<>
  struct Theme::ControlTheme<CaptionBar>: public ControlThemeBase
  {
    Color bkgd_color;

    FontData font_data;
    Font*    font;

    SizeT height;
    SizeT text_space;
    SizeT button_space;

    ControlTheme(Theme& theme);

    virtual void renderWidget(CaptionBar const& widget, Size const& size) const = 0;
  };

  template<>
  struct Theme::ControlTheme<CaptionBarButton>: public ControlThemeBase
  {
    Color press_color;
    Color bkgd_color;

    ControlTheme(Theme& theme);

    virtual void renderWidget(CaptionBarButton const& widget, Size const& size) const = 0;
  };

  template<>
  struct Theme::ControlTheme<Border>: public ControlThemeBase
  {
    Color bkgd_color;

    SizeT width;
    SizeT inner_space;
    SizeT outer_space;

    ControlTheme(Theme& theme);

    virtual void renderWidget(Border const& widget, Size const& size) const = 0;
  };
}


#endif
