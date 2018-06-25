#/***************************************************************************
# *   Copyright (C) 2009-2012 Daniel Mueller (deso@posteo.net)              *
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

SHELL ?= /bin/sh


AR       ?= ar
ARFLAGS  ?= -rs
CC       ?= gcc
CFLAGS   ?= -O0
CXX      ?= g++
CXXFLAGS ?= -O0
LD       ?= ld
LDFLAGS  ?=
TOUCH    ?= touch
RM       ?= rm
MKDIR    ?= mkdir
RMDIR    ?= rmdir
ECHO     ?= echo
SED      ?= sed

# QUIET supersedes VERBOSE
ifdef QUIET
  Q := 1
  V := @
endif

ifndef VERBOSE
  V := @
endif

ifdef SUPPRESS
  S := &> /dev/null
endif

ifdef DEBUG
  D := 1
endif


MSG_DEPEND   = $(if $(Q),,$(if $(V),@$(ECHO) "  DEPENDENCY "$@))
MSG_COMPILE  = $(if $(Q),,$(if $(V),@$(ECHO) "  COMPILE    "$@))
MSG_ARCHIVE  = $(if $(Q),,$(if $(V),@$(ECHO) "  ARCHIVE    "$@))
MSG_LINK     = $(if $(Q),,$(if $(V),@$(ECHO) "  LINK       "$@))
MSG_ABSTRACT = $(if $(Q),,$(if $(V),@$(ECHO) "  DOING      "$@))
MSG_CLEAN    = $(if $(Q),,$(if $(V),@$(ECHO) "  CLEAN      "))


#/**
# * The user should be able to define new types directly in the project Makefile. Thus we need the
# * operator '+='.
# */
TYPES_SRC += C CXX
TYPES_TRG += BIN AR ABS
TYPES_GEN += DEP OBJ


#/**
# * Those two variables define the extensions used for object and dependency files.
# */
EXT_OBJ ?= .o
EXT_DEP ?= .d


#/**
# * This is the name of the file that marks a directory as created.
# */
DIR_MARKER ?= .dir
