# Makefile

#/***************************************************************************
# *   Copyright (C) 2012 Daniel Mueller (deso@posteo.net)                   *
# *                                                                         *
# *   This program is free software: you can redistribute it and/or modify  *
# *   it under the terms of the GNU General Public License as published by  *
# *   the Free Software Foundation, either version 3 of the License, or     *
# *   (at your option) any later version.                                   *
# *                                                                         *
# *   This program is distributed in the hope that it will be useful,       *
# *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
# *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
# *   GNU General Public License for more details.                          *
# *                                                                         *
# *   You should have received a copy of the GNU General Public License     *
# *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
# ***************************************************************************/

MAKE_DIR ?= ../../../make
CONF_DIR ?= .

TARGETS_AR  = libgui.a
TARGETS_BIN = libgui.so libgui_test libgui_sample


SUBTARGETS = ../../../libbase/build/gmake/Makefile\
             ../../../libimage/build/gmake/Makefile\
             ../../../libfont/build/gmake/Makefile\
             ../../../libwindow/build/gmake/Makefile\
             Makefile_resource


#/**
# * libgui.a
# */
SRC_ROOT_libgui.a = $(TARGET_DIR_libgui.a)/../../src/gui/
SRC_CXX_libgui.a  = Color.cpp\
                    Error.cpp\
                    MemoryStream.cpp\
                    MemoryNamespace.cpp\
                    NamespaceManager.cpp\
                    ResourceManager.cpp\
                    ImageManager.cpp\
                    event/BroadcastEvent.cpp\
                    event/CharacterEvent.cpp\
                    event/EventBase.cpp\
                    event/FocusEvent.cpp\
                    event/KeyDownEvent.cpp\
                    event/KeyUpEvent.cpp\
                    event/MouseDownEvent.cpp\
                    event/MouseMoveEvent.cpp\
                    event/MouseUpEvent.cpp\
                    event/MouseWheelDownEvent.cpp\
                    event/MouseWheelUpEvent.cpp\
                    event/PositionEvent.cpp\
                    event/ResizeEvent.cpp\
                    event/RootWidgetEvent.cpp\
                    event/WidgetEvent.cpp\
                    renderer/Font.cpp\
                    renderer/FontFunctions.cpp\
                    renderer/Renderer.cpp\
                    renderer/Texture.cpp\
                    renderer/TextureFont.cpp\
                    renderer/TextureFontCreator.cpp\
                    renderer/RootWidgetViewport.cpp\
                    renderer/null/NullFont.cpp\
                    renderer/null/NullRenderer.cpp\
                    renderer/null/NullTexture.cpp\
                    renderer/null/NullViewport.cpp\
                    renderer/opengl/OpenGlConstants.cpp\
                    renderer/opengl/OpenGlFont.cpp\
                    renderer/opengl/OpenGlFunctions.cpp\
                    renderer/opengl/OpenGlPrimitiveRenderer.cpp\
                    renderer/opengl/OpenGlRenderer.cpp\
                    renderer/opengl/OpenGlTexture.cpp\
                    renderer/opengl/OpenGlTextureFont.cpp\
                    widget/Container.cpp\
                    widget/Decorator.cpp\
                    widget/DummyWidget.cpp\
                    widget/RootWidget.cpp\
                    widget/Widget.cpp\
                    widget/WidgetBase.cpp\
                    widget/control/Border.cpp\
                    widget/control/Button.cpp\
                    widget/control/CaptionBar.cpp\
                    widget/control/CaptionBarButton.cpp\
                    widget/control/CheckBox.cpp\
                    widget/control/Dialog.cpp\
                    widget/control/EditBox.cpp\
                    widget/control/EditableText.cpp\
                    widget/control/GroupBox.cpp\
                    widget/control/Picture.cpp\
                    widget/control/ProgressBar.cpp\
                    widget/control/Slider.cpp\
                    widget/control/StaticText.cpp\
                    widget/control/theme/Theme.cpp\
                    widget/control/theme/ThemeFactory.cpp\
                    widget/control/theme/simple/RectangleRenderer.cpp\
                    widget/control/theme/simple/SimpleBorder.cpp\
                    widget/control/theme/simple/SimpleButton.cpp\
                    widget/control/theme/simple/SimpleCaptionBar.cpp\
                    widget/control/theme/simple/SimpleCaptionBarButton.cpp\
                    widget/control/theme/simple/SimpleCheckBox.cpp\
                    widget/control/theme/simple/SimpleDialog.cpp\
                    widget/control/theme/simple/SimpleEditBox.cpp\
                    widget/control/theme/simple/SimpleGroupBox.cpp\
                    widget/control/theme/simple/SimplePicture.cpp\
                    widget/control/theme/simple/SimpleProgressBar.cpp\
                    widget/control/theme/simple/SimpleSlider.cpp\
                    widget/control/theme/simple/SimpleStaticText.cpp\
                    widget/control/theme/simple/SimpleTextureTheme.cpp\
                    widget/control/theme/simple/SimpleTextureThemeFactory.cpp\
                    widget/control/theme/simple/SimpleTheme.cpp\
                    widget/control/theme/simple/SimpleThemeBase.cpp\
                    widget/control/theme/simple/SimpleThemeFactory.cpp

CXXFLAGS_libgui.a = -fPIC\
                    -I$(TARGET_DIR_libgui.a)/../../../libtype/include/\
                    -I$(TARGET_DIR_libgui.a)/../../../libutil/include/\
                    -I$(TARGET_DIR_libgui.a)/../../../libcontainer/include/\
                    -I$(TARGET_DIR_libgui.a)/../../../libpointer/include/\
                    -I$(TARGET_DIR_libgui.a)/../../../libwindow/include/\
                    -I$(TARGET_DIR_libgui.a)/../../../libfont/include/\
                    -I$(TARGET_DIR_libgui.a)/../../../libimage/include/\
                    -I$(TARGET_DIR_libgui.a)/../../../libbase/include/\
                    -I$(TARGET_DIR_libgui.a)/../../../libgraphicsutil/include/\
                    -I$(TARGET_DIR_libgui.a)/../../include/\
                    -I$(TARGET_DIR_libgui.a)/../../src/


#/**
# * libgui.so
# */
DEPENDENCIES_libgui.so = $(libgui.a) $(libimage.so) $(libimage_png.so) $(libfont.so)

LDFLAGS_libgui.so = -shared\
                    -Wl,-z,defs,--whole-archive,$(libgui.a),--no-whole-archive\
                    $(libimage_png.so) $(libimage.so) $(libfont.so)\
                    -lGL -lGLU


#/**
# * libgui_test
# */
DEPENDENCIES_libgui_test = $(libgui.a)

SRC_ROOT_libgui_test = $(TARGET_DIR_libgui_test)/../../src/test/
SRC_CXX_libgui_test  = Button1.cpp\
                       CheckBox1.cpp\
                       Decorator1.cpp\
                       Decorator2.cpp\
                       Renderer1.cpp\
                       RootWidget1.cpp\
                       Test.cpp\
                       TestMemoryStream.cpp\
                       TestMemoryNamespace.cpp\
                       TestNamespaceManager.cpp\
                       TestAnchors.cpp\
                       TestButton.cpp\
                       TestCheckBox.cpp\
                       TestDecorator.cpp\
                       TestEditableText.cpp\
                       TestFocusIndex.cpp\
                       TestFocusNext.cpp\
                       TestRenderer.cpp\
                       TestShow.cpp\
                       TestWidget.cpp

CXXFLAGS_libgui_test = -I$(TARGET_DIR_libgui_test)/../../../libtype/include/\
                       -I$(TARGET_DIR_libgui_test)/../../../libutil/include/\
                       -I$(TARGET_DIR_libgui_test)/../../../libcontainer/include/\
                       -I$(TARGET_DIR_libgui_test)/../../../libpointer/include/\
                       -I$(TARGET_DIR_libgui_test)/../../../libwindow/include/\
                       -I$(TARGET_DIR_libgui_test)/../../../libfont/include/\
                       -I$(TARGET_DIR_libgui_test)/../../../libgraphicsutil/include/\
                       -I$(TARGET_DIR_libgui_test)/../../../libimage/include/\
                       -I$(TARGET_DIR_libgui_test)/../../../libbase/include/\
                       -I$(TARGET_DIR_libgui_test)/../../../libtest/include/\
                       -I$(TARGET_DIR_libgui_test)/../../include/
LDFLAGS_libgui_test  = $(libgui.a)


#/**
# * libgui_sample
# */
PRE_DEPENDENCIES_libgui_sample = $(ttf-bitstream-vera.ttf.hpp) $(win_xp_silver_theme.png.hpp)
DEPENDENCIES_libgui_sample     = $(libbase.a) $(libimage.a) $(libimage_png.a)\
                                 $(libfont.a) $(libwindow.a) $(libgui.a)

SRC_ROOT_libgui_sample = $(TARGET_DIR_libgui_sample)/../../src/sample/
SRC_CXX_libgui_sample  = Gui.cpp\
                         SampleGui.cpp\
                         StatusText.cpp

CXXFLAGS_libgui_sample = -I$(TARGET_DIR_libgui_sample)/../../../libtype/include/\
                         -I$(TARGET_DIR_libgui_sample)/../../../libutil/include/\
                         -I$(TARGET_DIR_libgui_sample)/../../../libcontainer/include/\
                         -I$(TARGET_DIR_libgui_sample)/../../../libgraphicsutil/include/\
                         -I$(TARGET_DIR_libgui_sample)/../../../libpointer/include/\
                         -I$(TARGET_DIR_libgui_sample)/../../../libwindow/include/\
                         -I$(TARGET_DIR_libgui_sample)/../../../libfont/include/\
                         -I$(TARGET_DIR_libgui_sample)/../../../libimage/include/\
                         -I$(TARGET_DIR_libgui_sample)/../../../libbase/include/\
                         -I$(TARGET_DIR_libgui_sample)/../../../libtime/include/\
                         -I$(TARGET_DIR_libgui_sample)/../../../libtest/include/\
                         -I$(TARGET_DIR_libgui_sample)/../../include/\
                         -I$(TARGET_DIR_libgui_sample)/../../src/
LDFLAGS_libgui_sample  = $(libgui.a) $(libwindow.a) $(libfont.a) $(libimage_png.a) $(libimage.a) $(libbase.a)\
                         -lX11 -lXrandr -lGL -lGLU -lpng -lfreetype


include $(MAKE_DIR)/make.mk
