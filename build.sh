#!/bin/sh

set -xe

clang -O3 -Wall -Wextra -o smoothlife smoothlife.c -lm
