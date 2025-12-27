#!/bin/bash

set -e

g++ -fPIC -o main src/main.cpp -I include -L liblinux -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 `pkg-config --cflags --libs Qt5Widgets`

echo "BUILD OK"