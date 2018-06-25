# Makefile

#/***************************************************************************
# *   Copyright (C) 2012-2014 Daniel Mueller (deso@posteo.net)              *
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

TARGETS_AR  = libgame.a
TARGETS_BIN = tetris tetris_test


SUBTARGETS = ../../../libbase/build/gmake/Makefile\
             ../../../liboptions/build/gmake/Makefile\
             ../../../libprogram/build/gmake/Makefile\
             ../../../libimage/build/gmake/Makefile\
             ../../../libfont/build/gmake/Makefile\
             ../../../libwindow/build/gmake/Makefile\
             ../../../libgui/build/gmake/Makefile\
             Makefile_resource\
             Makefile_settings


#/**
# * libgame.a
# */
SRC_ROOT_libgame.a = $(TARGET_DIR_libgame.a)/../../src/tetris/game/
SRC_CXX_libgame.a  = AbstractStoneFactory.cpp\
                     AbstractStone.cpp\
                     StoneTypeManager.cpp\
                     ai/StoneDropper.cpp\
                     ai/ClosedStones.cpp\
                     ai/State.cpp
CXXFLAGS_libgame.a = -I$(TARGET_DIR_libgame.a)/../../../libtype/include/\
                     -I$(TARGET_DIR_libgame.a)/../../../libgraphicsutil/include/\
                     -I$(TARGET_DIR_libgame.a)/../../../libpointer/include/\
                     -I$(TARGET_DIR_libgame.a)/../../../libcontainer/include/\
                     -I$(TARGET_DIR_libgame.a)/../../../libutil/include/\
                     -I$(TARGET_DIR_libgame.a)/../../src/


#/**
# * tetris
# */
PRE_DEPENDENCIES_tetris = $(tetris_piece_32x32.png.hpp) $(tetris_field_256x512.png.hpp)\
                          $(tetris_ttf-bitstream-vera.ttf.hpp) $(tetris_win_xp_silver_theme.png.hpp)\
                          $(Settings.hpp)
DEPENDENCIES_tetris     = $(libgame.a) $(libbase.a) $(liboptions.a) $(libprogram.a) $(libimage.a)\
                          $(libimage_png.a) $(libfont.a) $(libwindow.a) $(libgui.a)

FIXED_DIR_tetris = $(TARGET_DIR_tetris)/../../bin/
SRC_ROOT_tetris  = $(TARGET_DIR_tetris)/../../src/tetris/
SRC_CXX_tetris   = Application.cpp\
                   ColorFunctions.cpp\
                   HelpText.cpp\
                   KeyboardCache.cpp\
                   Main.cpp\
                   Options.cpp\
                   Window.cpp\
                   game/GameField.cpp\
                   game/Game.cpp\
                   game/Piece.cpp\
                   game/Score.cpp\
                   game/Stone.cpp\
                   game/PieceField.cpp\
                   game/StoneFactory.cpp\
                   game/Stones.cpp\
                   gui/FpsCounter.cpp\
                   gui/Hud.cpp\
                   gui/SettingsDialog.cpp\
                   gui/StatusHud.cpp\
                   renderer/OpenGlRenderer.cpp\
                   renderer/Renderer.cpp

CXXFLAGS_tetris = -I$(TARGET_DIR_tetris)/../../../libtype/include/\
                  -I$(TARGET_DIR_tetris)/../../../libgraphicsutil/include/\
                  -I$(TARGET_DIR_tetris)/../../../libcontainer/include/\
                  -I$(TARGET_DIR_tetris)/../../../libpointer/include/\
                  -I$(TARGET_DIR_tetris)/../../../liboptions/include/\
                  -I$(TARGET_DIR_tetris)/../../../libprogram/include/\
                  -I$(TARGET_DIR_tetris)/../../../libbase/include/\
                  -I$(TARGET_DIR_tetris)/../../../libimage/include/\
                  -I$(TARGET_DIR_tetris)/../../../libfont/include/\
                  -I$(TARGET_DIR_tetris)/../../../libwindow/include/\
                  -I$(TARGET_DIR_tetris)/../../../libgui/include/\
                  -I$(TARGET_DIR_tetris)/../../../libtime/include/\
                  -I$(TARGET_DIR_tetris)/../../../libutil/include/\
                  -I$(TARGET_DIR_tetris)/../../src/\
                  -I$(TARGET_DIR_tetris)/../../
LDFLAGS_tetris  = $(libgame.a) $(libprogram.a) $(liboptions.a) $(libgui.a) $(libwindow.a)\
                  $(libfont.a) $(libimage_png.a) $(libimage.a) $(libbase.a)\
                  -lX11 -lXrandr -lGL -lGLU -lpng -lfreetype


#/**
# * tetris_test
# */
DEPENDENCIES_tetris_test = $(libgame.a)

SRC_ROOT_tetris_test  = $(TARGET_DIR_tetris_test)/../../src/test/
SRC_CXX_tetris_test   = Test.cpp\
                        TestAbstractField.cpp\
                        TestAbstractStone.cpp\
                        TestAbstractStoneFactory.cpp\
                        TestFieldFunctions.cpp\
                        TestOrientation.cpp\
                        TestState.cpp\
                        TestStoneDropper.cpp\
                        StoneFactory.cpp\
                        Field1.cpp
CXXFLAGS_tetris_test = -I$(TARGET_DIR_tetris_test)/../../../libtype/include/\
                       -I$(TARGET_DIR_tetris_test)/../../../libgraphicsutil/include/\
                       -I$(TARGET_DIR_tetris_test)/../../../libpointer/include/\
                       -I$(TARGET_DIR_tetris_test)/../../../libcontainer/include/\
                       -I$(TARGET_DIR_tetris_test)/../../../libtest/include/\
                       -I$(TARGET_DIR_tetris_test)/../../../libutil/include/\
                       -I$(TARGET_DIR_tetris_test)/../../src/
LDFLAGS_tetris_test  = $(libgame.a)


include $(MAKE_DIR)/make.mk
