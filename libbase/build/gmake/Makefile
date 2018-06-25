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

TARGETS_AR  = libbase.a
TARGETS_BIN = libbase.so libbase_test


#/**
# * libbase.a
# */
SRC_ROOT_libbase.a = $(TARGET_DIR_libbase.a)/../../src/base/
SRC_CXX_libbase.a  = IniFile.cpp\
                     stream/FileStream.cpp\
                     stream/MemoryStream.cpp

CXXFLAGS_libbase.a = -fPIC\
                     -I$(TARGET_DIR_libbase.a)/../../../libtype/include/\
                     -I$(TARGET_DIR_libbase.a)/../../../libutil/include/\
                     -I$(TARGET_DIR_libbase.a)/../../include/


#/**
# * libbase.so
# */
DEPENDENCIES_libbase.so = $(libbase.a)

LDFLAGS_libbase.so = -shared\
                     -Wl,--whole-archive,$(libbase.a),--no-whole-archive


#/**
# * libbase_test
# */
DEPENDENCIES_libbase_test = $(libbase.a)

SRC_ROOT_libbase_test = $(TARGET_DIR_libbase_test)/../../src/test/
SRC_CXX_libbase_test  = Test.cpp\
                        TestIniFile.cpp\
                        TestMemoryStream.cpp

CXXFLAGS_libbase_test = -I$(TARGET_DIR_libbase_test)/../../../libtest/include/\
                        -I$(TARGET_DIR_libbase_test)/../../../libtype/include/\
                        -I$(TARGET_DIR_libbase_test)/../../../libutil/include/\
                        -I$(TARGET_DIR_libbase_test)/../../include/
LDFLAGS_libbase_test  = $(libbase.a)


include $(MAKE_DIR)/make.mk
