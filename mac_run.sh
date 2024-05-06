#!/bin/bash

#clang -g main.c met.c timer.c /opt/homebrew/lib/libSDL2.dylib /opt/homebrew/lib/libSDL2_image.dylib /opt/homebrew/lib/libSDL2_ttf.dylib  -o app && ./app

clang main.c met.c timer.c widgets.c -lSDL2 -lSDL2_Image -lSDL2_ttf -lSDL2_mixer -o Cetronome && ./Cetronome
