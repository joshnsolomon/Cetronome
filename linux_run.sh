#!/bin/bash

clang -g main.c met.c `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -o linapp &&./linapp