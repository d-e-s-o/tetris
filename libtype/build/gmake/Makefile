# Makefile

#/***************************************************************************
# *   Copyright (C) 2012-2014 Daniel Mueller                                *
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

TARGETS_BIN = libtype_test


#/**
# * libtype_test
# */
SRC_ROOT_libtype_test = $(TARGET_DIR_libtype_test)/../../src/test/
SRC_CXX_libtype_test  = Test.cpp\
                        TestTypes.cpp\
                        TestTraits.cpp\
                        TestMove.cpp\
                        TestTuple.cpp\
                        TestDecltype.cpp\
                        TestFunction.cpp\
                        TestDefer.cpp\
                        TestUtil.cpp

CXXFLAGS_libtype_test = -I$(TARGET_DIR_libtype_test)/../../../libtest/include/\
                        -I$(TARGET_DIR_libtype_test)/../../../libutil/include/\
                        -I$(TARGET_DIR_libtype_test)/../../include/


include $(MAKE_DIR)/make.mk
