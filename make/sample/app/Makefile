MAKE_DIR ?= ../..
CONF_DIR ?= .

TARGETS_BIN = app

SUBTARGETS = ../lib/Makefile

#/**
# * app
# */
DEPENDENCIES_app = $(lib.a)

SRC_ROOT_app = $(TARGET_DIR_app)/
SRC_C_app    = app.c

CFLAGS_app  = -I$(TARGET_DIR_app)/../lib/
LDFLAGS_app = $(lib.a)


include $(MAKE_DIR)/make.mk
