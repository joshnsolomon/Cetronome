#!/bin/bash

gcc main.c met.c /opt/homebrew/lib/libSDL2.dylib /opt/homebrew/lib/libSDL2_image.dylib  -o app && ./app