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

TARGETS_AR  = libimage.a  libimage_bmp.a  libimage_jpeg.a  libimage_png.a
TARGETS_BIN = libimage.so libimage_bmp.so libimage_jpeg.so libimage_png.so


#/**
# * libimage.a
# */
SRC_ROOT_libimage.a = $(TARGET_DIR_libimage.a)/../../src/image/
SRC_CXX_libimage.a  = Error.cpp\
                      codec/CodecBase.cpp

CXXFLAGS_libimage.a = -fPIC\
                      -I$(TARGET_DIR_libimage.a)/../../../libtype/include/\
                      -I$(TARGET_DIR_libimage.a)/../../../libcontainer/include/\
                      -I$(TARGET_DIR_libimage.a)/../../../libpointer/include/\
                      -I$(TARGET_DIR_libimage.a)/../../../libutil/include/\
                      -I$(TARGET_DIR_libimage.a)/../../include/\
                      -I$(TARGET_DIR_libimage.a)/../../src/


#/**
# * libimage.so
# */
DEPENDENCIES_libimage.so = $(libbase.so) $(libimage.a)
LDFLAGS_libimage.so      = -shared -Wl,-z,defs,--whole-archive,$(libimage.a),--no-whole-archive


#/**
# * libimage_bmp.a
# */
SRC_ROOT_libimage_bmp.a = $(TARGET_DIR_libimage_bmp.a)/../../src/image/codec/bmp/
SRC_CXX_libimage_bmp.a  = BmpCodec.cpp\
                          JpegReadBmp.cpp
CXXFLAGS_libimage_bmp.a = $(CXXFLAGS_libimage.a)


#/**
# * libimage_bmp.so
# */
DEPENDENCIES_libimage_bmp.so = $(libimage.so) $(libimage_bmp.a)
LDFLAGS_libimage_bmp.so      = -shared\
                               -Wl,-z,defs,--whole-archive,$(libimage_bmp.a),--no-whole-archive\
                               $(libimage.so) -ljpeg


#/**
# * libimage_jpeg.a
# */
SRC_ROOT_libimage_jpeg.a = $(TARGET_DIR_libimage_jpeg.a)/../../src/image/codec/jpeg/
SRC_CXX_libimage_jpeg.a  = JpegCodec.cpp\
                           JpegStreamSource.cpp
CXXFLAGS_libimage_jpeg.a = $(CXXFLAGS_libimage.a)


#/**
# * libimage_jpeg.so
# */
DEPENDENCIES_libimage_jpeg.so = $(libimage.so) $(libimage_jpeg.a)
LDFLAGS_libimage_jpeg.so      = -shared\
                                -Wl,-z,defs,--whole-archive,$(libimage_jpeg.a),--no-whole-archive\
                                $(libimage.so) -ljpeg


#/**
# * libimage_png.a
# */
SRC_ROOT_libimage_png.a = $(TARGET_DIR_libimage_png.a)/../../src/image/codec/png/
SRC_CXX_libimage_png.a  = PngCodec.cpp
CXXFLAGS_libimage_png.a = $(CXXFLAGS_libimage.a)


#/**
# * libimage_png.so
# */
DEPENDENCIES_libimage_png.so = $(libimage.so) $(libimage_png.a)
LDFLAGS_libimage_png.so      = -shared\
                               -Wl,-z,defs,--whole-archive,$(libimage_png.a),--no-whole-archive\
                               $(libimage.so) -lpng


include $(MAKE_DIR)/make.mk
