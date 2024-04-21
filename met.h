#ifndef MET_H
#define MET_H

#include <SDL2/SDL.h>
#include <stdbool.h>

int  setup(SDL_Window** window, SDL_Surface** screenSurface);
int  draw(SDL_Window** window, SDL_Surface** screenSurface);
bool eventHandle(SDL_Event* e);
int leave(SDL_Window* window);

#endif