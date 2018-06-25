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

TARGETS_BIN = libcontainer_test


#/**
# * libcontainer_test
# */
SRC_ROOT_libcontainer_test = $(TARGET_DIR_libcontainer_test)/../../src/test/
SRC_CXX_libcontainer_test  = Moveable.cpp\
                             Test.cpp\
                             TestArray.cpp\
                             TestString.cpp\
                             TestBinaryHeap.cpp\
                             TestBinaryTree.cpp\
                             TestSplayTree.cpp\
                             TestSet.cpp\
                             TestMap.cpp\
                             TestStack.cpp\
                             TestQueue.cpp\
                             TestMoveIterator.cpp

CXXFLAGS_libcontainer_test = -I$(TARGET_DIR_libcontainer_test)/../../../libtest/include/\
                             -I$(TARGET_DIR_libcontainer_test)/../../../libtype/include/\
                             -I$(TARGET_DIR_libcontainer_test)/../../../libutil/include/\
                             -I$(TARGET_DIR_libcontainer_test)/../../include/


include $(MAKE_DIR)/make.mk
