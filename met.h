#ifndef MET_H
#define MET_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define INIT_DEFAULT_MET_VARS\
    SDL_Window* window;\
    SDL_Event e;\
    SDL_Renderer* renderer;\
    SDL_Texture* dog;

#define DEFAULY_MET\
    {.window = window,\
    .e = e,\
    .renderer = renderer,\
    .dog = dog\
    }


struct Met_t{
    SDL_Window* window;
    SDL_Event e;
    SDL_Renderer* renderer;
    SDL_Texture* dog;
};

typedef struct Met_t Met;

//Met init();
int  setup(Met* met);
int  draw(Met* met);
bool eventHandle(Met* met);
int leave(Met* met);

int drawDog(Met* met);

#endif