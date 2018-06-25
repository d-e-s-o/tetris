# Makefile

#/***************************************************************************
# *   Copyright (C) 2014 Daniel Mueller (deso@posteo.net)                   *
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

TARGETS_BIN = libutil_test


#/**
# * libutil_test
# */
DEPENDENCIES_libutil_test =

SRC_ROOT_libutil_test = $(TARGET_DIR_libutil_test)/../../src/test/
SRC_CXX_libutil_test  = Test.cpp\
                        TestUtil.cpp\
                        TestBits.cpp\
                        TestString.cpp\
                        TestAlgorithm.cpp\
                        TestOutStream.cpp

CXXFLAGS_libutil_test = -I$(TARGET_DIR_libutil_test)/../../../libtype/include/\
                        -I$(TARGET_DIR_libutil_test)/../../../libtest/include/\
                        -I$(TARGET_DIR_libutil_test)/../../include/


include $(MAKE_DIR)/make.mk
