#!/bin/bash

clang -g main.c met.c timer.c /opt/homebrew/lib/libSDL2.dylib /opt/homebrew/lib/libSDL2_image.dylib  -o app && ./app
