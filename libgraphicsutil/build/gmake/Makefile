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

TARGETS_BIN = libgraphicsutil_test


#/**
# * libgraphicsutil_test
# */
SRC_ROOT_libgraphicsutil_test = $(TARGET_DIR_libgraphicsutil_test)/../../src/test/
SRC_CXX_libgraphicsutil_test  = Test.cpp\
                        TestColor.cpp\
                        TestPoint.cpp\
                        TestRectangle1.cpp\
                        TestRectangle1Functions.cpp\
                        TestRectangle2.cpp\
                        TestRectangle2Functions.cpp\
                        TestVector2D.cpp\
                        TestVector3D.cpp

CXXFLAGS_libgraphicsutil_test = -I$(TARGET_DIR_libgraphicsutil_test)/../../../libtest/include/\
                                -I$(TARGET_DIR_libgraphicsutil_test)/../../../libtype/include/\
                                -I$(TARGET_DIR_libgraphicsutil_test)/../../../libutil/include/\
                                -I$(TARGET_DIR_libgraphicsutil_test)/../../include/


include $(MAKE_DIR)/make.mk
