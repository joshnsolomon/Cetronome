#!/bin/bash

gcc main.c met.c timer.c widgets.c `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o Cetronome  && ./Cetronome
