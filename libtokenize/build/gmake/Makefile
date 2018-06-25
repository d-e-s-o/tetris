MAKE_DIR ?= ../../../make
CONF_DIR ?= .

TARGETS_BIN = libtokenize_test libtokenize_example


#/**
# * libtokenize_test
# */
SRC_ROOT_libtokenize_test = $(TARGET_DIR_libtokenize_test)/../../src/test/
SRC_CXX_libtokenize_test  = Test.cpp\
                            TestTerminal.cpp\
                            TestTerminalRange.cpp\
                            TestTerminalCustom.cpp\
                            TestAlternative.cpp\
                            TestSequence.cpp\
                            TestRepetition.cpp\
                            TestToken.cpp\
                            TestTokenize.cpp

CXXFLAGS_libtokenize_test = -std=c++0x\
                            -I$(TARGET_DIR_libtokenize_test)/../../../libtest/include/\
                            -I$(TARGET_DIR_libtokenize_test)/../../../libtype/include/\
                            -I$(TARGET_DIR_libtokenize_test)/../../../libcontainer/include/\
                            -I$(TARGET_DIR_libtokenize_test)/../../../libutil/include/\
                            -I$(TARGET_DIR_libtokenize_test)/../../include/

#/**
# * libtokenize_example
# */
SRC_ROOT_libtokenize_example = $(TARGET_DIR_libtokenize_example)/../../src/example
SRC_CXX_libtokenize_example  = Tokenizer.cpp

CXXFLAGS_libtokenize_example = -std=c++0x\
                               -I$(TARGET_DIR_libtokenize_example)/../../../libtype/include/\
                               -I$(TARGET_DIR_libtokenize_example)/../../../libcontainer/include/\
                               -I$(TARGET_DIR_libtokenize_example)/../../../libutil/include/\
                               -I$(TARGET_DIR_libtokenize_example)/../../include/


include $(MAKE_DIR)/make.mk
