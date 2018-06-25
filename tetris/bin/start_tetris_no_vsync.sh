#!/bin/sh

TETRIS_DIR=$(dirname "$0")

vblank_mode=0 LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH $TETRIS_DIR/tetris --use-config=$TETRIS_DIR/tetris.cfg $*
