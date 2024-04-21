#ifndef MET_H
#define MET_H

#include <SDL2/SDL.h>
#include <stdbool.h>

struct Met_t{
    SDL_Window* window;
    SDL_Surface* screenSurface;
    SDL_Event* e;
};

typedef struct Met_t Met;

//Met init();
int  setup(Met* met);
int  draw(Met* met);
bool eventHandle(Met* met);
int leave(Met* met);

#endif