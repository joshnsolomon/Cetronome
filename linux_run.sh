#!/bin/bash

clang -g main.c met.c timer.c `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL_mixer -o linapp &&./linapp
