#!/bin/sh

TETRIS_DIR=$(dirname "$0")

ulimit -c unlimited
$TETRIS_DIR/tetris --use-config=$TETRIS_DIR/tetris.cfg $*
