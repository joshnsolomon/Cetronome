#!/bin/bash

clang fontexample.c `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_ttf -o font  && ./font