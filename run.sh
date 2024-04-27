#!/bin/bash

#clang -g main.c met.c timer.c /opt/homebrew/lib/libSDL2.dylib /opt/homebrew/lib/libSDL2_image.dylib /opt/homebrew/lib/libSDL2_ttf.dylib  -o app && ./app

clang -g main.c met.c timer.c -lSDL2 -lSDL2_Image -lSDL2_ttf -o app && ./app
