#!/bin/sh

set -xe

export PKG_CONFIG_PATH=$HOME/.local/src/raylib/build/raylib/

#clang -O3 -Wall -Wextra -o smoothlife_term smoothlife_term.c -lm
clang -O3 -Wall -Wextra `pkg-config --cflags raylib` -o smoothlife_gpu smoothlife_gpu.c -lm `pkg-config --libs raylib`
