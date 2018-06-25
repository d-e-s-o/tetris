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

TARGETS_BIN = libpointer_test


#/**
# * libpointer_test
# */
SRC_ROOT_libpointer_test = $(TARGET_DIR_libpointer_test)/../../src/test/
SRC_CXX_libpointer_test  = Test.cpp\
                           InstanceCounter.cpp\
                           TestResourceGuard.cpp\
                           TestUniquePointer.cpp\
                           TestSharedPointer.cpp

CXXFLAGS_libpointer_test = -I$(TARGET_DIR_libpointer_test)/../../../libtype/include/\
                           -I$(TARGET_DIR_libpointer_test)/../../../libutil/include/\
                           -I$(TARGET_DIR_libpointer_test)/../../../libtest/include/\
                           -I$(TARGET_DIR_libpointer_test)/../../include/


include $(MAKE_DIR)/make.mk
