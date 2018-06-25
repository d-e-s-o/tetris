# Makefile

#/***************************************************************************
# *   Copyright (C) 2012,2014 Daniel Mueller (deso@posteo.net)              *
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

TARGETS_AR  = libprogram.a
TARGETS_BIN = libprogram.so libprogram_test


#/**
# * libprogram.a
# */
SRC_ROOT_libprogram.a = $(TARGET_DIR_libprogram.a)/../../src/program/
SRC_CXX_libprogram.a  = HelpText.cpp\
                        ProgramOptions.cpp\
                        StringFunctions.cpp

SRC_C_libprogram.a    = extern/getopt.c\
                        extern/getopt1.c

CXXFLAGS_libprogram.a = -fPIC\
                        -I$(TARGET_DIR_libprogram.a)/../../../libbase/include/\
                        -I$(TARGET_DIR_libprogram.a)/../../../libcontainer/include/\
                        -I$(TARGET_DIR_libprogram.a)/../../../libtype/include/\
                        -I$(TARGET_DIR_libprogram.a)/../../../libutil/include/\
                        -I$(TARGET_DIR_libprogram.a)/../../include/\
                        -I$(TARGET_DIR_libprogram.a)/../../src/\


#/**
# * libprogram.so
# */
DEPENDENCIES_libprogram.so = $(libprogram.a)

LDFLAGS_libprogram.so = -shared\
                        -Wl,--whole-archive,$(libprogram.a),--no-whole-archive


#/**
# * libprogram_test
# */
DEPENDENCIES_libprogram_test = $(libprogram.a)

SRC_ROOT_libprogram_test = $(TARGET_DIR_libprogram_test)/../../src/test/
SRC_CXX_libprogram_test  = Test.cpp\
                           TestProgramOptions.cpp

CXXFLAGS_libprogram_test = -I$(TARGET_DIR_libprogram_test)/../../../libtype/include/\
                           -I$(TARGET_DIR_libprogram_test)/../../../libcontainer/include/\
                           -I$(TARGET_DIR_libprogram_test)/../../../libutil/include/\
                           -I$(TARGET_DIR_libprogram_test)/../../../libtest/include/\
                           -I$(TARGET_DIR_libprogram_test)/../../include/
LDFLAGS_libprogram_test  = $(libprogram.a)


include $(MAKE_DIR)/make.mk
