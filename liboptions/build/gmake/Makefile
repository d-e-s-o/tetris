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

TARGETS_AR  = liboptions.a
TARGETS_BIN = liboptions_test


#/**
# * liboptions.a
# */
SRC_ROOT_liboptions.a = $(TARGET_DIR_liboptions_test)/../../src/options/
SRC_CXX_liboptions.a  = Scanner.cpp\
                        Parser.cpp\
                        Evaluate.cpp


CXXFLAGS_liboptions.a = -std=c++0x\
                        -I$(TARGET_DIR_liboptions_test)/../../../libtype/include/\
                        -I$(TARGET_DIR_liboptions_test)/../../../libcontainer/include/\
                        -I$(TARGET_DIR_liboptions_test)/../../../libtokenize/include/\
                        -I$(TARGET_DIR_liboptions_test)/../../../libutil/include/\
                        -I$(TARGET_DIR_liboptions_test)/../../src/\
                        -I$(TARGET_DIR_liboptions_test)/../../include/


#/**
# * liboptions_test
# */
DEPENDENCIES_liboptions_test = $(liboptions.a)

SRC_ROOT_liboptions_test = $(TARGET_DIR_liboptions_test)/../../src/test/
SRC_CXX_liboptions_test  = Test.cpp\
                           TestOptions.cpp

CXXFLAGS_liboptions_test = -I$(TARGET_DIR_liboptions_test)/../../../libtest/include/\
                           -I$(TARGET_DIR_liboptions_test)/../../../libtype/include/\
                           -I$(TARGET_DIR_liboptions_test)/../../../libcontainer/include/\
                           -I$(TARGET_DIR_liboptions_test)/../../../libutil/include/\
                           -I$(TARGET_DIR_liboptions_test)/../../include/
LDFLAGS_liboptions_test  = $(liboptions.a)


include $(MAKE_DIR)/make.mk
