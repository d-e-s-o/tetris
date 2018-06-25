# Makefile
#
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

TARGETS_AR  = libwindow.a
TARGETS_BIN = libwindow.so libwindow_test


#/**
# * libwindow.a
# */
SRC_ROOT_libwindow.a = $(TARGET_DIR_libwindow.a)/../../src/window/
SRC_CXX_libwindow.a  = Error.cpp\
                       Resolution.cpp\
                       ScreenImpl.cpp\
                       ScreenInterface.cpp\
                       WindowInterface.cpp\
                       x11/KeyFunctions.cpp\
                       x11/X11OpenGlVisualCreator.cpp\
                       x11/X11OpenGlWindowImpl.cpp\
                       x11/X11ScreenImpl.cpp\
                       x11/X11VisualCreator.cpp\
                       x11/X11WindowImpl.cpp\
                       x11/X11WindowImplBase.cpp

CXXFLAGS_libwindow.a = -fPIC\
                       -I$(TARGET_DIR_libwindow.a)/../../../libtype/include/\
                       -I$(TARGET_DIR_libwindow.a)/../../../libcontainer/include/\
                       -I$(TARGET_DIR_libwindow.a)/../../../libgraphicsutil/include/\
                       -I$(TARGET_DIR_libwindow.a)/../../../libpointer/include/\
                       -I$(TARGET_DIR_libwindow.a)/../../../libutil/include/\
                       -I$(TARGET_DIR_libwindow.a)/../../include/\
                       -I$(TARGET_DIR_libwindow.a)/../../src/


#/**
# * libwindow.so
# */
DEPENDENCIES_libwindow.so = $(libwindow.a)

LDFLAGS_libwindow.so = -shared\
                       -Wl,--whole-archive,$(libwindow.a),--no-whole-archive


#/**
# * libwindow_test
# */
DEPENDENCIES_libwindow_test = $(libwindow.a)

SRC_ROOT_libwindow_test = $(TARGET_DIR_libwindow_test)/../../src/test/
SRC_CXX_libwindow_test  = Test.cpp\
                          TestX11.cpp\
                          X11Window.cpp

CXXFLAGS_libwindow_test = -I$(TARGET_DIR_libwindow_test)/../../../libtype/include/\
                          -I$(TARGET_DIR_libwindow_test)/../../../libcontainer/include/\
                          -I$(TARGET_DIR_libwindow_test)/../../../libgraphicsutil/include/\
                          -I$(TARGET_DIR_libwindow_test)/../../../libpointer/include/\
                          -I$(TARGET_DIR_libwindow_test)/../../../libutil/include/\
                          -I$(TARGET_DIR_libwindow_test)/../../../libtest/include/\
                          -I$(TARGET_DIR_libwindow_test)/../../include/
LDFLAGS_libwindow_test  = $(libwindow.a)\
                          -lX11 -lXrandr


include $(MAKE_DIR)/make.mk
