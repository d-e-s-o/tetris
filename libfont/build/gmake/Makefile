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

TARGETS_AR  = libfont.a
TARGETS_BIN = libfont.so


#/**
# * libfont.a
# */
SRC_ROOT_libfont.a = $(TARGET_DIR_libfont.a)/../../src/font/
SRC_CXX_libfont.a  = FreeTypeFontLoader.cpp\
                     FontLoader.cpp\
                     GlyphMetrics.cpp\
                     Error.cpp

CXXFLAGS_libfont.a = -fPIC\
                     -I/usr/include/freetype2/\
                     -I$(TARGET_DIR_libfont.a)/../../../libtype/include/\
                     -I$(TARGET_DIR_libfont.a)/../../../libcontainer/include/\
                     -I$(TARGET_DIR_libfont.a)/../../../libpointer/include/\
                     -I$(TARGET_DIR_libfont.a)/../../../libimage/include/\
                     -I$(TARGET_DIR_libfont.a)/../../../libutil/include/\
                     -I$(TARGET_DIR_libfont.a)/../../include/


#/**
# * libfont.so
# */
DEPENDENCIES_libfont.so = $(libfont.a)

LDFLAGS_libfont.so = -shared\
                     -Wl,-z,defs,--whole-archive,$(libfont.a),--no-whole-archive\
                     -lfreetype


include $(MAKE_DIR)/make.mk
