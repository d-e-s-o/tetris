CXXFLAGS=-O2 -std=c++0x
LD=g++

RES2H_DIR=$(MAKE_DIR)/../resource2header
PYTHON=python
RES2HPP=$(PYTHON) $(RES2H_DIR)/bin/resource2header.py

include $(RES2H_DIR)/build/gmake/rules.mk
