#!/bin/bash

set -e

g++ -o game.o src/main_game.cpp -I include -L liblinux -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

echo "BUILD OK"